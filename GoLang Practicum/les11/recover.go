package main

import (
	"errors"
	"fmt"
	"log"
)

func main() {
	divide(4, 0)
	fmt.Println("After Panic")
}

type AppError struct {
	Message string
	Err     error
}

func (ae *AppError) Error() string {
	return ae.Message
}

// Такая конструкция позволяет "восстанавливать" паникой
func divide(a, b int) {
	defer func() {
		var appErr *AppError
		if err := recover(); err != nil {
			switch err.(type) {
			case error:
				if errors.As(err.(error), &appErr) {
					fmt.Println("Panic!", err)
				} else {
					fmt.Println("custom panic!")
				}
			default:
				panic("some panic")
			}
			log.Println("Panic", err)
		}
	}()
	fmt.Println(div(a, b))

}

// Через panic возвращаем ошибку, далее обрабатываем ее в 29-31 строках
func div(a, b int) int {
	if b == 0 {
		panic(&AppError{
			Message: "this is divide by zero custom error",
			Err:     nil,
		})

		// Если вызвать другую ошибку, то попадём в условие 32
		panic(fmt.Errorf("second error-panic"))

	}
	return a / b
}
