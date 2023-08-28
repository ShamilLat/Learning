package main

import (
	"errors"
	"fmt"
	"log"
)

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
	// fmt.Println(div(a, b))

}

type Dashboard struct {
	Name             string
	WindowSize       Size
	WindowCoordinate Coordinate
}

type Size struct {
	Width  int
	Height int
}

type Coordinate struct {
	CoordX int
	CoordY int
}

func (d *Dashboard) updateDashboard(new_d *Dashboard) error {
	if new_d.WindowCoordinate.CoordX < 0 || new_d.WindowCoordinate.CoordY < 0 {
		return fmt.Errorf("Error: incorrect coordinate")
	}

	if new_d.WindowSize.Width <= 0 || new_d.WindowSize.Height <= 0 {
		return fmt.Errorf("Error: incorrect size")
	}

	d.Name = new_d.Name
	d.WindowCoordinate = new_d.WindowCoordinate
	d.WindowSize = new_d.WindowSize

	return nil
}

func (d *Dashboard) deleteDashboard() error {
	if d.Name == "" {
		fmt.Errorf("Error: dashboard is already deleted")
	}

	d.Name = ""
	d.WindowCoordinate.CoordX = 0
	d.WindowCoordinate.CoordY = 0
	d.WindowSize.Width = 0
	d.WindowSize.Height = 0

	return nil
}
