package main

import "fmt"

func main() {
	animals := [4]string{
		"dog",
		"cat",
		"cow",
		"frog",
	}
	fmt.Println(animals)

	animalSlice := []string{
		"dog",
		"cat",
		"cow",
		"frog",
	}
	fmt.Println(animalSlice)

	var a []string = animals[0:2]
	fmt.Println(a) // dog cat
	var b []string = animals[1:3]
	fmt.Println(b) // cat cow

	fmt.Println("\nNew element in Slice")
	b[0] = "123"
	fmt.Println(a)
	fmt.Println(b)
	fmt.Println(animals)
	// Т.е. слайсы работают как указатели на основной массив, и соответственно меняя
	// значение в слайсе, мы меняем сам массив и все привязанные к нему слайсы

	fmt.Println("\nNewline")
	s := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	t := s[5:6]
	fmt.Println(t)
	t = s[:5] // С начала
	fmt.Println(t)
	t = s[5:] // До конца
	fmt.Println(t)

	t = s[:]
	fmt.Println(t)

	fmt.Println("\nNewline")
	var snil []int
	fmt.Println(snil, len(snil), cap(snil))
	if snil == nil {
		fmt.Println("slice is nil!")
	}
}
