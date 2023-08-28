package main

import (
	"fmt"

	"github.com/tidwall/sjson"
)

func main() {

	//sjson библиотека нужна для изменения самого json
	json := `{
		"name": {"first": "Shamil", "last": "Latypov"},
		"age": 42,
		"is_blocked": true,
		"massive": ["A", "B", "C"]
		"books": [
			{
				"name": "BN",
				"year": 1990,
				"color": "blue"
			},
			{
				"name": "BN2",
				"year": 2090,
				"color": "green"
			},
			{
				"name": "BN3",
				"year": 1500,
				"color": "red"
			},
			{
				"name": "NewBook",
				"year": 1990,
				"color": "red"
			}
		]
		}`

	// Поменять значение в json
	value, _ := sjson.Set(json, "name.first", "Shoma")
	// fmt.Println(value)

	value, _ = sjson.Set(json, "books.1.color", "white")
	// fmt.Println(value)

	// Добавить в массив по новому индексу
	value, _ = sjson.Set(json, "massive.5", "D") // На 4й позиции будет null
	// fmt.Println(value)

	value, _ = sjson.Set(json, "massive.-1", "D")
	// fmt.Println(value)

	value, _ = sjson.Set(json, "new_obj", map[string]interface{}{"hello": "world"})
	// fmt.Println(value)

	// Удаление
	value, _ = sjson.Delete(json, "new_obj")
	fmt.Println(value)
}
