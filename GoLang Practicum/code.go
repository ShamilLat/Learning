package main

import "fmt"

func main() {
	// fmt.Println("Hello world")

	results := make(map[string]map[string]int)

	results["a"] = make(map[string]int)
	results["b"] = make(map[string]int)

	// Затестим с буквой которая уже есть
	if _, ok := results["a"]; !ok {
		fmt.Println("In if of letter 'a'")
		results["a"] = make(map[string]int)
	}

	results["a"]["letter"] = 5
	//

	// А тут буква которой еще нет
	if _, ok := results["c"]; !ok {
		fmt.Println("In if of letter 'c'")
		results["c"] = make(map[string]int)
	}

	results["c"]["new lettter"] = 1
	//

	fmt.Println(results)

}
