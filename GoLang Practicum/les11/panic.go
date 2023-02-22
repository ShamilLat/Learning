package main

import (
	"fmt"
	"time"
)

func main() {
	a := []int{1, 2, 3}

	// panic
	c := a[3]
	fmt.Println(c)

	go test()
	time.Sleep(300 * time.Millisecond)

}

func test() int {
	a := []int{1, 2, 3}
	return a[3]
}
