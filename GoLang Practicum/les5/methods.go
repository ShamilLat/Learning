package main

import "fmt"

type Point struct {
	X, Y int
}

// Практически никогда нет смысла писать вот так
func movePoint(p Point, x, y int) Point {
	p.X += x
	p.Y += y
	return p
}

func movePointPtr(p *Point, x, y int) {
	p.X += x
	p.Y += y
}

// Объявляем функцию в структуре
// Практически никогда нет смысла писать вот так
func (p Point) movePoint2(x, y int) Point {
	p.X += x
	p.Y += y
	return p
}

func (p *Point) movePointPtr2(x, y int) {
	p.X += x
	p.Y += y
}

func main() {
	p := Point{1, 2}
	fmt.Println(p)                  // 1 2
	fmt.Println(movePoint(p, 1, 1)) // 2 3
	fmt.Println(p)                  // 1 2

	movePointPtr(&p, 1, 1)
	fmt.Println(p) // 2 3

	fmt.Println("\nNewline")

	fmt.Println(p)                  // 2 3
	fmt.Println(p.movePoint2(1, 1)) // 3 4
	fmt.Println(p)                  // 2 3

	p.movePointPtr2(1, 1)
	fmt.Println(p) // 3 4

	fmt.Println("\nNewline")
	v := &p
	fmt.Println(p)
	v.movePoint2(1, 1)
	fmt.Println(p)
	v.movePointPtr2(1, 1)
	fmt.Println(p)

}
