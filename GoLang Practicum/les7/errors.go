package main

import "fmt"

type error interface {
	Error() string
}

type appError struct {
	Err    error
	Custom string
	Field  int
}

type AppError interface {
	Error() string
	Unwarp() error
}

func (e *appError) Error() string {
	err := fmt.Errorf("new error %s", e.Custom)
	fmt.Println(err.Error())
	// return err.Error()
	return e.Err.Error()
}

func (e *appError) Unwarp() error {
	return e.Err
}

func main() {
	err := m()
	if err != nil {
		fmt.Println(err.Error())
	}

	err2 := method1()
	if err2 != nil {
		fmt.Println(err2.Unwarp())
	}

}

func m() error {
	return &appError{
		Err:    fmt.Errorf("my error"),
		Custom: "value here",
		Field:  89,
	}
}

func method1() *appError {
	return method2()
}

func method2() *appError {
	return method3()
}

func method3() *appError {
	return &appError{
		Err:    fmt.Errorf("internal error"),
		Custom: "something goes wrong",
	}
}
