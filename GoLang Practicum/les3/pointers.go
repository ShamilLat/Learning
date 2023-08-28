package main

import "fmt"

func main() {
	fmt.Println("Hello")

	pointers()
}

func pointers() {
	a := "Hello world"
	b := 42

	fmt.Println(a)
	fmt.Println(b)

	p := &a
	g := &b
	fmt.Println(p)
	fmt.Println(*p)

	*g = *g / 2
	fmt.Println(b)
}
