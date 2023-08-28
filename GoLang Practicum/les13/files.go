package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	writeToFile()
	appendToFile()
}

func appendToFile() {
	f, err := os.OpenFile("test.txt", os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0600)
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()
	if _, err = f.WriteString(" Shamil"); err != nil {
		panic(err)
	}
}

func writeToFile() {
	data := []byte("My name is Shamil")
	err := ioutil.WriteFile("text.txt", data, 0600)
	if err != nil {
		fmt.Println(err)
	}
}

func readFile() {
	data, err := ioutil.ReadFile("test.txt")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(data))
}
