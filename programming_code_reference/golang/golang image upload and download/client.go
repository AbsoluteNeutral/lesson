package main

import (
	"bytes"
	"fmt"
	"io"
	"log"
	"mime/multipart"
	"net/http"
	"os"
	"time"
)

func main() {
	call_POST_image_upload("http://localhost:9999/image/upload", "POST")
	//call_GET_image_upload("http://localhost:9999/image/upload", "GET")
	call_POST_image_download("http://localhost:9999/image/download", "POST")
}

// ======================================================================================================================================================
func call_POST_image_upload(urlPath, method string) error {

	body := &bytes.Buffer{}                                      // create buffer
	writer := multipart.NewWriter(body)                          // New multipart writer.
	fw, err := writer.CreateFormFile("photo", "uploadImage.png") // key, create empty file to be sent to server later
	if err != nil {                                              // check error
		return err
	}
	file, err := os.Open("a.png") // find the file path to send
	if err != nil {               // check error
		return err
	}
	_, err = io.Copy(fw, file) // copy file
	if err != nil {            // check error
		return err
	}
	writer.Close()

	req, err := http.NewRequest(method, urlPath, bytes.NewReader(body.Bytes())) // send to server in bytes, form format
	if err != nil {                                                             // check error
		return err
	}
	req.Header.Set("Content-Type", writer.FormDataContentType()) // set header
	client := &http.Client{}                                     // client struct
	respond, _ := client.Do(req)                                 // get respond status code
	if respond.StatusCode != http.StatusOK {
		log.Printf("Request failed with response code: %d", respond.StatusCode)
	}
	return nil
}

// ======================================================================================================================================================
func call_GET_image_upload(urlPath, method string) error {
	// New multipart writer.
	body := &bytes.Buffer{}

	req, err := http.NewRequest(method, urlPath, bytes.NewReader(body.Bytes()))
	if err != nil {
		return err
	}

	fileName := "c.png"
	client := &http.Client{
		Timeout: time.Second * 10,
	}
	rsp, _ := client.Do(req)
	file, err := os.Create("c.png")
	size, err := io.Copy(file, rsp.Body)
	fmt.Println("Just Downloaded a file %s with size %d", fileName, size)
	return nil
}

// ======================================================================================================================================================
func call_POST_image_download(urlPath, method string) error {

	var jsonStr = []byte(`{"image":"a.png"}`)                              // sending a json string
	req, err := http.NewRequest(method, urlPath, bytes.NewBuffer(jsonStr)) // send to server
	if err != nil {                                                        // check error
		return err
	}
	req.Header.Set("Content-Type", "application/json") // set header

	fileName := "dowloaded_image.png" // my file name to be received from server
	file, err := os.Create(fileName)  // create empty file

	client := &http.Client{}             // client struct
	rsp, _ := client.Do(req)             // get respond from server
	size, err := io.Copy(file, rsp.Body) // decode and save/copy image to emptyfile
	fmt.Println("Just Downloaded a file %s with size %d", fileName, size)
	return nil
}
