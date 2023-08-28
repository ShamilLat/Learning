package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int)
	ch2 := make(chan string)

	fmt.Println("\nNewline")
	go say("Hello", ch, ch2)
	fmt.Println("1")
	fmt.Println("2")
	fmt.Println("3")
	fmt.Println("4")
	fmt.Println("5")

	// <-ch Вытащить из канала
	// ch<- записать в канал
	fmt.Println("\nNewline")
	data := <-ch
	fmt.Printf("channel value is %d\n", data)
	fmt.Println(<-ch2)

	fmt.Println("\nNewline")
	go sayHello(ch2)
	fmt.Println(<-ch2)

	fmt.Println("\nNewline")
	go sayHello2(ch)
	for i := 0; i < 5; i++ {
		fmt.Println(<-ch)
	}
}

func say(s string, ch chan int, ch2 chan string) {
	time.Sleep(1 * time.Second)
	fmt.Println(s)
	ch <- 1
	ch2 <- "word"
}

func say2(s string) {
	time.Sleep(1 * time.Second)
	fmt.Println(s)
}

func sayHello(exit chan string) {
	for i := 0; i < 5; i++ {
		time.Sleep(100 * time.Millisecond)
		say2("hello")
	}
	exit <- "s"
}

func sayHello2(exit chan int) {
	for i := 0; i < 5; i++ {
		time.Sleep(100 * time.Millisecond)
		say2("hello")
		exit <- i
	}
}
