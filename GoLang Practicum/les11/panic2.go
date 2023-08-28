package main

import "fmt"

type name struct {
	A, B int
}

func (n *name) method() {
	fmt.Println("ok")

	// panic, т.к. мы в указатель n вписани nil.
	// Таким образом, методы работают, если не обращаться к полям структуры
	fmt.Println(n.A)
}

func main() {
	// n := &name{1, 2}
	// n = nil
	// n.method()

	// defer отработает раньше panic
	defer func() {
		fmt.Println("OK")
	}()

	// Искусственно вызвать панику
	panic("Something goes wrong")

}
