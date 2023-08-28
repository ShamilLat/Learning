
// ЦИКЛЫ
// Обычный for
sum := 0
for i := 1; i < 5; i++ {
    sum += i
}
fmt.Println(sum) // 10 (1+2+3+4)

// Аналог while
n := 1
for n < 5 {
    n *= 2
}
fmt.Println(n) // 8 (1*2*2*2)

// Вечный цикл
sum := 0
for {
    sum++ // repeated forever
}
fmt.Println(sum) // never reached

// for each loop
strings := []string{"hello", "world"}
for i, s := range strings {
    fmt.Println(i, s)
}
/*
0 hello
1 world
*/

// Выход из цикла
sum := 0
for i := 1; i < 5; i++ {
    if i%2 != 0 { // skip odd numbers
        continue
    }
    sum += i
}
fmt.Println(sum) // 6 (2+4)
// continue и break работают также как в C++



// РАБОТА С ГОРУТИНАМИ
// Горутины позволяют сделать любую функцию асинхронной. 
// Другими словами, какую бы функцию ни написал разработчик,
// её можно запустить в фоновом режиме, и она будет работать

func main() {
    go sleepyGopher() // Начало горутины
    time.Sleep(4 * time.Second) // Ожидание
} // Здесь все горутины останавливаются

// Создание канала ждя передачи данных м\у горутинами

c := make(chan int)


// ОТСУТСТВУЕТ ТЕРНАРНЫЙ ОПЕРАТОР
var isAdmin bool
if user.Role == "admin" {
    isAdmin = true
}

// НАЧАЛО ПРОГРАММЫ
package main

import "fmt"

func main() {
    fmt.Println("Hello, Go")
}


// ООП

type Stringer interface {
    String() string
}

type myType int

// myType реализует интерфейс Stringer 
func (t myType) String() string {
    // представление типа myType в виде строки
}

// КОНСТРУКЦИИ try catch на Питоне

try:
    foo()
except IndexError:
    # обработка исключений, связанных с выходом за пределы массива
except:
    # обработка всех остальных исключений


// КОНСТРУКЦИИ try catch на GO

func foo() (int, error) { 
    // в теле функции может быть ошибка
}

result, err = foo()
if err != nil {
    // handle error
}


// Паника
// Завершает программу "аварийно" в случае тяжелой ошибки (завершение main из-за выхода за память например)

func foo() {
    // паникуем
    panic("unexpected!")
}
//...
    // defer позволяет отложено выполнят отдельные блоки кода
    // выполняется после срабатывания паники
    defer func() {
        if r := recover(); r != nil {
            // обработка паники, в переменной r будет лежать строка "unexpected!"
        }
    }()
    // внутри foo срабатывает паника
    foo()


// Тестирование программ
// Библиотека testing
// Для теста нужно в той же папке создать _test файл. Например:
// foo.go ==> foo_test.go

// Содержимое foo.go
package foo

func Foo() string {
    return "bar"
}

// файл foo_test.go
package foo

import (
    "testing"
)

func TestFooFunc(t *testing.T) {
    expectedFooResult := "bar"
    if actualFooResult := Foo(); actualFooResult != expectedFooResult {
        t.Errorf("expected %s; got: %s", expectedFooResult, actualFooResult)
    }
}