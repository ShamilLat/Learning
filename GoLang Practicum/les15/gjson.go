package main

import (
	"fmt"
	"strings"

	"github.com/tidwall/gjson"
)

func main() {
	// gjson
	json := `{"name": {"first": "shamil", "last": "latypov"}, "age": 21}`
	// Уровни вложенности через .
	value := gjson.Get(json, "name.first")
	fmt.Println(value.String())

	// Если у нас какие то массивы в json, то обращаться по индексу по .0 .1 .2 итд
	json2 := `{
		"name": {"first": "Shamil", "last": "Latypov"},
		"age": 42,
		"is_blocked": true,
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
	value = gjson.Get(json2, "books.1.year")
	fmt.Println(value.String()) // 2090

	// Регулярные выражения * ? работают
	value = gjson.Get(json2, "b*.1.year")
	fmt.Println(value.String()) // 2090

	// Первое вхождение по запросу
	value = gjson.Get(json2, "books.#(year==2090).name")
	fmt.Println(value.String()) // BN2

	// Все вхождения
	value = gjson.Get(json2, "books.#(year==1990)#.name")
	fmt.Println(value.String()) // ["BN", "NewBook"]

	// Модифайр
	gjson.AddModifier("case", func(json2, arg string) string {
		if arg == "upper" {
			return strings.ToUpper(json2)
		} else if arg == "lower" {
			return strings.ToLower(json2)
		}
		return json2
	})

	value = gjson.Get(json2, "books.#(year==1990)#.name|@case:upper")
	fmt.Println(value.String()) // ["BN", "NEWBOOK"]

	// Можно парсить
	fmt.Println(gjson.Parse(json2).Get("name"))

	// Проверка на валидность
	if !gjson.Valid(json2) {
		panic("JSON NOT VALID")
	}

	// Пробежаться по массиву из строки 70
	for _, name := range value.Array() {
		fmt.Println("name", name.String())
	}

	// Парсить json в мэп
	result, ok := gjson.Parse(json2).Value().(map[string]interface{})
	if !ok {
		panic("Not ok")
	}
	fmt.Println(result)

}
