package main

import "fmt"

func main() {
	fmt.Println("Hello")

	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)

	for sum < 1000 { // Analog while
		sum += 10
	}
	fmt.Println(sum)

	// for {
	// 	// Infinity cycle
	// }

}
