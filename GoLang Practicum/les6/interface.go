package main

import "fmt"

type structHere struct {
	N1, N2 int
}

func (s *structHere) Sum() int {
	return s.N1 + s.N2
}

type InterfaceHere interface {
	// X, Y int - Не может быть
	// Только методы
	Sum() int
}

func main() {
	var a InterfaceHere
	sh := structHere{1, 2}
	os := otherStruct{2, 3}

	a = &sh
	fmt.Println(a.Sum())

	a = &os
	fmt.Println(a.Sum())

	var i InterfaceHere = otherStruct{3, 3}
	fmt.Println(i.Sum())

	fmt.Println()
	fmt.Printf("(%v, %T)\n", i, i)

	// Создание пустого интерфейса
	var s *structHere
	var j InterfaceHere
	j = s
	fmt.Println(j)
}

type otherStruct struct {
	A, B int
}

func (o otherStruct) Sum() int {
	return o.A + o.B
}
