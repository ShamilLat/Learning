package main

import "fmt"

const global string = "Global const string"

func main() {
	const a string = "name"

	fmt.Println(a)

	fmt.Println(test())
	fmt.Println(test2())

	// Option + Enter
	test()
	s, s2, s3 := test()
	fmt.Println("Im here!", s, s2, s3)

}

func test2() string {
	a := "Hello world"
	return a
}

func test() (string, string, string) {
	a := "Hello"
	b := "world"
	c := "!"
	return a, b, c
}

// Initialisation is complete if var in return () written
// a := 5 - init
// a = 5 - not init, just =

func test3() (a, b, c string) {
	a = "Hello"
	b = "world"
	c = "!"
	return a, b, c
	// return
	// This working too, but not recommended
}
