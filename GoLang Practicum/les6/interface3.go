package main

import (
	"fmt"
)

func main() {
	var a interface{}
	a = "jelly"
	fmt.Println(a)
	fmt.Printf("(%v, %T)\n\n", a, a)

	a = 42
	fmt.Println(a)
	fmt.Printf("(%v, %T)\n\n", a, a)

	// Interface может быть любым типом данных

	// Если в питоне так могут любые переменные, то в Go для этого
	// существует Интерфейс

	var b interface{} = 3.14

	// Приведение типов через .(type)
	// s := b.(string)
	// fmt.Println(s)

	s, ok := b.(string)
	fmt.Println(s, ok)

	f, ok := b.(float32)
	fmt.Println(f, ok)

	// panic
	// g := b.(float64)
	// fmt.Println(g)

	switch b.(type) {
	case int:
		fmt.Println("b is int")
	case string:
		fmt.Println("b is string")
	case bool:
		fmt.Println("b is bool")
	default:
		fmt.Printf("unknown type. %T\n", b)

	}
}
