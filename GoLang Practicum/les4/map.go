package main

import "fmt"

type Point struct {
	X, Y int
}

func (p Point) method() {
	fmt.Printf("Hello from Point! My x is %d\n", p.X)
}

func main() {
	//				  Ключ Значение
	pointsMap := map[string]Point{
		"c": Point{5, 6},
	}

	// Та же инициализация
	otherPointsMap := make(map[string]Point)
	// otherMap := map[string]Point{}

	pointsMap["a"] = Point{1, 2}
	fmt.Println(pointsMap)
	fmt.Println(pointsMap["a"])

	fmt.Println()
	otherPointsMap["b"] = Point{3, 4}
	fmt.Println(otherPointsMap)
	fmt.Println(otherPointsMap["b"])

	fmt.Println()
	// Объявили, но не проинициализировали
	var oneMorePointsMap map[string]Point
	if oneMorePointsMap == nil {
		fmt.Println("oneMorePointsMap is nil")
		oneMorePointsMap = map[string]Point{
			"d": Point{3, 6},
		}
	} else {
		oneMorePointsMap["a"] = Point{7, 8}
	}
	oneMorePointsMap["a"] = Point{7, 8}
	fmt.Println(oneMorePointsMap)
	oneMorePointsMap["a"].method()

	fmt.Println()
	// Проверка на наличие значения по ключу
	key := "a"
	value, ok := oneMorePointsMap[key]
	if ok {
		fmt.Printf("key=%s is exist\n", key)
		fmt.Println(value)
	} else {
		fmt.Printf("key=%s doesnt is exist\n", key)
	}

	fmt.Println()
	// key value
	for k, v := range pointsMap {
		fmt.Println(k)
		fmt.Println(v)
	}

}
