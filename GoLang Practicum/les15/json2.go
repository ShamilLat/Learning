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
	byt := []byte(`{"name":"Shamil","age":42,"is_blocked":true,"books":[{"name":"BN","year":1990},{"name":"BN2","year":2090}]}`)
	var dat User

	if err := json.Unmarshal(byt, &dat); err != nil {
		panic(err)
	}
	fmt.Println(dat.Books[1].Name)
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
