package main

import (
	"encoding/json"
	"fmt"
)

type User struct {
	//				  Тэги для json отображения
	Name      string `json:"name"`
	Age       int    `json:"age"`
	IsBlocked bool   `json:"is_blocked"`
	Books     []Book `json:"books"`
}

type Book struct {
	Name string `json:"name"`
	Year int    `json:"year"`
}

func main() {
	// Массив байт и ошибка
	// boolVar, err := json.Marshal(true)
	// boolVar, _ := json.Marshal(true)
	// json.Unmarshal()

	sv := map[string]interface{}{"field1": "A", "field2": 123, "field3": true, "field4": []int{1, 2, 3}}
	boolVar, _ := json.Marshal(sv)
	fmt.Println(string(boolVar))

	// serialize()

	byt := []byte(`{"name":"Shamil","age":42,"is_blocked":true,"books":[{"name":"BN","year":1990},{"name":"BN2","year":2090}]}`)
	var dat map[string]interface{}
	if err := json.Unmarshal(byt, &dat); err != nil {
		panic(err)
	}
	fmt.Println(dat["name"])
	fmt.Println(dat["books"].([]interface{})[1].(map[string]interface{})["year"])
}

func serialize() {
	var books []Book

	book := Book{
		Name: "BN",
		Year: 1990,
	}
	book2 := Book{
		Name: "BN2",
		Year: 2090,
	}

	books = append(books, book, book2)

	u := User{
		Name:      "Shamil",
		Age:       42,
		IsBlocked: true,
		Books:     books,
	}
	boolVar2, _ := json.Marshal(u)
	fmt.Println(string(boolVar2))
}
