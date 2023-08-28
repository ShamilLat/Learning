package main

import "fmt"

func main() {
	var (
		name = "Egor"
		age  = 42
	)
	fmt.Println(name)
	fmt.Println(age)

	var name2, age2 = "Shamil", 43
	fmt.Println(name2)
	fmt.Println(age2)

	c := fmt.Sprintf("Name is: %s, and I'm %d", name2, age2)
	fmt.Println(c)

}
