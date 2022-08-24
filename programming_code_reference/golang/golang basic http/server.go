package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
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
	fmt.Println("##################################################")
	fmt.Println("                 BASIC     SERVER                 ")
	fmt.Println("##################################################")

	fmt.Println("/echo")

	//http
	http.HandleFunc("/echo", Handle_echo)
	http.ListenAndServe(Config.IP, nil)
}

type json_POST_Echo_receive struct {
	Code int `json:"code"`
}
type json_Echo_respond struct {
	Message string `json:"message"`
}

func Handle_echo(w http.ResponseWriter, r *http.Request) {
	funcName := "[Handle_echo] -"
	fmt.Println(funcName, r.URL.Path, r.Method)

	switch r.Method {
	case "POST":
		// read respond
		var data_receive json_POST_Echo_receive              // a struct to receive data
		err := json.NewDecoder(r.Body).Decode(&data_receive) // decode data in json format
		if err != nil {                                      //check error
			fmt.Printf("[Handle_echo POST] - failed to decode json:%s\n", err)
			return
		}
		fmt.Printf("[Handle_echo POST] - Data:%+v\n", data_receive)

		// do things with the received data
		var message_respond json_Echo_respond // write json using struct sample
		switch data_receive.Code {
		case 0:
			message_respond.Message = "Receive 0"
			w.WriteHeader(http.StatusOK)
		case 1:
			message_respond.Message = "Receive 1"
			w.WriteHeader(http.StatusOK)
		default:
			message_respond.Message = "Echo!"
			w.WriteHeader(http.StatusNotFound)
		}

		jsonByte, _ := json.MarshalIndent(message_respond, "", "	")
		w.Header().Set("Content-Type", "application/json")                                                                                   // set header
		w.Header().Set("Access-Control-Allow-Origin", "*")                                                                                   // set header
		w.Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE")                                                    // set header
		w.Header().Set("Access-Control-Allow-Headers", "Accept, Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization") // set header
		// set error code
		w.Write(jsonByte)
		break
	case "GET":

		var message_byte = []byte(`{"message":"echo GET"}`)

		w.WriteHeader(http.StatusOK)
		w.Write(message_byte)
		break
	default:
		w.WriteHeader(404)
		break
	}
}
