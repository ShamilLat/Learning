package main

import "fmt"

// Передача функции в функцию
func doSomething(callback func(int, int) int, s string) int {
	result := callback(5, 1)
	fmt.Println(s)
	return result
}

func main() {
	sumCallback := func(n1, n2 int) int {
		return n1 + n2
	}
	result := (doSomething(sumCallback, "plus"))
	fmt.Println(result)

	fmt.Println(sumCallback(6, 7))

	multipleCallback := func(n1, n2 int) int {
		return n1 * n2
	}
	result2 := doSomething(multipleCallback, "multiple")
	fmt.Println(result2)

}
