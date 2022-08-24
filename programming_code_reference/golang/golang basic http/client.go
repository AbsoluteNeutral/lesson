package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
	"time"
)

func main() {
	call_Echo_POST_1("http://127.0.0.1:9999/echo", "POST")
	call_Echo_POST_2("http://127.0.0.1:9999/echo", "POST")
	call_Echo_GET("http://127.0.0.1:9999/echo", "GET")
}

type json_POST_Echo_receive struct {
	Code int `json:"code"`
}

type json_POST_echo struct {
	Message string `json:"message"`
}

// ======================================================================================================================================================
func call_Echo_POST_1(urlPath, method string) error {
	funcName := "call_Echo_POST_1:"

	var json_byte = []byte(`{"code":0}`)                                     // sending json format in bytes
	req, err := http.NewRequest(method, urlPath, bytes.NewBuffer(json_byte)) // send url
	if err != nil {                                                          // check for error
		fmt.Println(funcName, urlPath, err)
		return err
	}
	req.Header.Set("Content-Type", "application/json") // set json header type

	client := &http.Client{ //client struct
		Timeout: time.Second * 10, //set timeout
	}
	getRespond, err := client.Do(req) // connect to client
	if err != nil {                   // check client connection
		fmt.Println(funcName, urlPath, err)
		return err
	}

	var receiveMsg json_POST_echo                              // sturct to decode
	err = json.NewDecoder(getRespond.Body).Decode(&receiveMsg) // decode json
	if err != nil {                                            // check json decode error
		fmt.Println(funcName, urlPath, err)
		return err
	}

	// close body when function exit
	defer getRespond.Body.Close()

	// received successfully, decode your message
	if getRespond.StatusCode == 200 {
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	} else {
		fmt.Printf("Status:%+v\n", http.StatusText(getRespond.StatusCode))
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	}
	return nil
}

// ======================================================================================================================================================
func call_Echo_POST_2(urlPath, method string) error {
	funcName := "call_Echo_POST_2:"

	// sending a json  using struct
	data_to_send := json_POST_Echo_receive{
		Code: 2,
	}
	json_byte, _ := json.MarshalIndent(data_to_send, "", "	")                // sending json format in bytes
	req, err := http.NewRequest(method, urlPath, bytes.NewBuffer(json_byte)) // send url
	if err != nil {                                                          // check for error
		fmt.Println(funcName, urlPath, err)
		return err
	}
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}          // default struct
	getRespond, err := client.Do(req) // connect to client
	if err != nil {                   // check client connection
		fmt.Println(funcName, urlPath, err)
		return err
	}

	// check json decode error
	var receiveMsg json_POST_echo                              // sturct to decode
	err = json.NewDecoder(getRespond.Body).Decode(&receiveMsg) // decode json
	if err != nil {                                            // check json decode error
		fmt.Println(funcName, urlPath, err)
		return err
	}

	// close body when function exit
	defer getRespond.Body.Close()

	// received successfully, decode your message
	if getRespond.StatusCode == 200 {
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	} else {
		fmt.Printf("Status:%+v\n", http.StatusText(getRespond.StatusCode))
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	}
	return nil
}

// ======================================================================================================================================================
func call_Echo_GET(urlPath, method string) error {
	funcName := "call_Echo_GET:"

	req, err := http.NewRequest(method, urlPath, nil) //send nothing
	if err != nil {                                   //check for error
		fmt.Println(funcName, urlPath, err) //print error
		return err
	}
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}          // default struct
	getRespond, err := client.Do(req) // connect to client
	if err != nil {                   // check client connection
		fmt.Println(funcName, urlPath, err)
		return err
	}

	// check json decode error
	var receiveMsg json_POST_echo                              // sturct to decode
	err = json.NewDecoder(getRespond.Body).Decode(&receiveMsg) // decode json
	if err != nil {                                            // check json decode error
		fmt.Println(funcName, urlPath, err)
		return err
	}

	// close body when function exit
	defer getRespond.Body.Close()

	// received successfully, decode your message
	if getRespond.StatusCode == 200 {
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	} else {
		fmt.Printf("Status:%+v\n", http.StatusText(getRespond.StatusCode))
		fmt.Printf("Message Received:%+v\n", receiveMsg)
	}
	return nil
}
