package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("Hello world")
	go method("Hey")
	fmt.Println("1")
	fmt.Println("2")
	fmt.Println("3")
	fmt.Println("4")
	fmt.Println("5")

	time.Sleep(2 * time.Second)
}

func method(s string) {
	time.Sleep(1 * time.Second)
	fmt.Println(s)
}
