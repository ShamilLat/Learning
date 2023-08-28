package main

import "fmt"

// Большие первые буквы означают экспортируемые даннные
// Маленькие - не экспортируемые
// Name и name "по анаологии" public и private из-за первой буквы N n
type Point struct {
	X int
	Y int
	S string
}

func (p Point) method() {
	fmt.Println(p.X)
	fmt.Println(p.Y)
	fmt.Println(p.S)
}

func main() {
	fmt.Println("Hello")
	// structs()

	p1 := Point{
		X: 1,
		Y: 2,
		S: "P1 text",
	}

	p2 := &p1

	p1.method()
	p2.method()
}

func structs() {
	p1 := Point{
		X: 1,
		Y: 2,
		S: "12str",
	}
	fmt.Println(p1)
	fmt.Println(p1.X)

	p2 := Point{
		X: 123,
	}
	// p2 := Point{X: 123}

	fmt.Println(p2)

	fmt.Println("\nNewLine")
	g := &p1
	fmt.Println(g)
	fmt.Println(g.X)
	fmt.Println(*g)
	fmt.Println(&g)
}
