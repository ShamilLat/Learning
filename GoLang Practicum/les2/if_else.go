package main

import "fmt"

func main() {
	fmt.Println("Hello")

	a := 0
	for ; a < 20; a++ {
		fmt.Println("Hello")
		b := test(a)
		if b == 1 {
			fmt.Println("a is 2")
		} else if b == 2 {
			fmt.Println("a is 3")
		} else {
			fmt.Printf("unknown a, a is %d\n", a)
		}

		// Init var in if
		if i := test(a); i == 1 {
			fmt.Println("a is 2")
		} else if i == 2 {
			fmt.Println("a is 3")
		} else {
			fmt.Printf("unknown a, a is %d\n", a)
		}

		// switch case
		switch i := test(a); i {
		case 1:
			fmt.Println("a is 2")
		case 2:
			fmt.Println("a is 3")
		default:
			fmt.Printf("unknown a, a is %d\n", a)
		}

		// switch without var
		switch {
		case b == 1:
			fmt.Println("a is 2")
		case b == 2:
			fmt.Println("a is 3")
		default:
			fmt.Printf("unknown a, a is %d\n", a)

		}

		// if a == 10 {
		// 	fmt.Println("a is", a)
		// } else {
		// 	// fmt.Println("a is not 10")
		// 	fmt.Printf(fmt.Sprintf("a is not 10, a is %d\n", a))
		// }
	}

}

func test(a int) int {
	if a == 2 {
		return 1
	} else if a == 3 {
		return 2
	}
	return 3
}
