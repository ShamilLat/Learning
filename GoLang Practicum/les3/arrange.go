package main

import "fmt"

func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "world"
	fmt.Println(a)

	// Компилятор сам посчитает количество элементов
	numbers := [...]int{1, 2, 3}
	fmt.Println(numbers)

	numbers[2] = 4
	fmt.Println(numbers)

	// slices
	// Slice - массивы динамической длинны
	fmt.Println("\nSlices")
	letters := []string{"a", "b", "c"}
	fmt.Println(letters)

	letters[1] = "lol"
	fmt.Println(letters)

	letters = append(letters, "d")
	fmt.Println(letters)

	letters = append(letters, "d", "e", "f") // Вставка нескольких элементов
	fmt.Println(letters)

	fmt.Println("\nCreate Slices")

	createSlice := make([]string, 3)
	fmt.Println(len(createSlice))
	fmt.Println(cap(createSlice))

	createSlice[0] = "1"
	createSlice[1] = "2"
	createSlice[2] = "3"
	// createSlice[3] = "4" // panic

	createSlice = append(createSlice, "4")
	fmt.Println(createSlice)
	fmt.Println(len(createSlice))
	fmt.Println(cap(createSlice))
	// Длинна увеличилась на один, а вместимость в два раза

}
