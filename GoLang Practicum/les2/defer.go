package main

import "fmt"

func main() {
	// Отложенный запуск.
	// Функция после слова defer выполнится только при завершении main.
	// Удобно если надо чистить память
	defer fmt.Println("world")
	fmt.Println("Hello")

	// Some example code
	sum := 0
	for i := 0; i < 100; i++ {
		sum += i
	}

	sum2 := 0
	for sum > 0 {
		sum2 += sum
		sum -= 10
	}
	fmt.Println(sum2)

	// defer - stack, LIFO
	// Последний defer выполнится первым
	defer fmt.Println("1")
	defer fmt.Println("2")
	defer fmt.Println("3")
	// Output: 3 2 1
}
