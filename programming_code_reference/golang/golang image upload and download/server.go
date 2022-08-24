package main

import (
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
)

type ConfigData struct {
	IP string `json:"ip"`
}

var (
	ConfigFile = "config.json"
	Config     ConfigData
)

func init() {
	file, err := ioutil.ReadFile(ConfigFile)
	if err != nil {
		fmt.Println("Error reading config file:", err)
		return
	}
	err = json.Unmarshal([]byte(file), &Config)
	if err != nil {
		fmt.Println("Error json config file:", err)
		return
	}

	fmt.Println("\nConfig:", Config)
}

func main() {
	fmt.Println("/image/upload")
	fmt.Println("/image/download")

	//http
	http.HandleFunc("/image/upload", Handle_Image_Upload)
	http.HandleFunc("/image/download", Handle_Image_Download)

	http.ListenAndServe(Config.IP, nil)
}

// ======================================================================================================================================================
func Handle_Image_Upload(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Handle_Image_Upload:", r.Method)

	//Upload photo from client to server
	switch r.Method {
	case "POST":
		err := r.ParseMultipartForm(32 << 20) // maxMemory 32MB
		if err != nil {                       // check error
			w.WriteHeader(http.StatusBadRequest)
			return
		}

		file, h, err := r.FormFile("photo") // Access the photo key - First Approach
		if err != nil {                     // check error
			w.WriteHeader(http.StatusBadRequest)
			return
		}
		tmpfile, err := os.Create("./" + h.Filename) // create the file where you want to save
		defer tmpfile.Close()                        // close the file when function exit
		if err != nil {                              //check error
			w.WriteHeader(http.StatusInternalServerError)
			return
		}
		_, err = io.Copy(tmpfile, file) // copy client's content to the newly created file
		if err != nil {                 // check error
			w.WriteHeader(http.StatusInternalServerError)
			return
		}
		w.WriteHeader(http.StatusOK)
	case "GET":
		/*
			- this upload "GET" is to simlulate an automatic file sending when GET is called
			- this should be a "download" from server
			- see /image/download
		*/
		img, err := os.Open("a.png") // New multipart writer.
		if err != nil {
			log.Fatal(err) // perhaps handle this nicer
		}
		defer img.Close()
		w.Header().Set("Content-Type", "image/png") // set the content-type header
		w.WriteHeader(http.StatusOK)                // status ok
		io.Copy(w, img)                             // send image to client
	default:
		w.WriteHeader(http.StatusNotFound)
	}
}

// ======================================================================================================================================================
type json_Handle_Image_Download struct {
	ImageName string `json:"image"`
}

func Handle_Image_Download(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Handle_Image_Download:", r.Method)

	switch r.Method {
	case "POST":
		var data json_Handle_Image_Download          // request POST message
		err := json.NewDecoder(r.Body).Decode(&data) // decode data json format
		if err != nil {                              // check error
			fmt.Printf("[Handle_Image_Download] - failed to decode json:%s\n", err)
			return
		}
		fmt.Printf("[Handle_Image_Download] - Data:%+v\n", data)

		// New multipart writer.
		img, err := os.Open(data.ImageName) // open the image file
		if err != nil {                     // check error
			log.Fatal(err)
		}
		defer img.Close()
		w.Header().Set("Content-Type", "image/png") // set the content-type header
		w.WriteHeader(http.StatusOK)                // status ok
		io.Copy(w, img)                             // send image to client
	case "GET":
		w.WriteHeader(http.StatusNotFound)
	default:
		w.WriteHeader(http.StatusNotFound)
	}
}
