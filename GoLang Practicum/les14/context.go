package main

import (
	"context"
	"fmt"
	"net/http"
	"time"
)

func main() {
	// Пустые контексты
	// ctx := context.Background()
	// context.TODO()

	// ctx, cancel := context.WithCancel(ctx)
	// cancel()

	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)
	// ctx, _ := context.WithCancel(ctx)

	defer cancel()

	go func() {
		err := cancelRequest(ctx)
		if err != nil {
			cancel()
		}
	}()

	doRequest(ctx, "https://ya.ru")
}

// Контекст это как каналы, но со своими приколами
// Конкретно тут мы обращаемся к яндексу через http, и cancelRequest даёт
// нам для этого 500 милисекунд
// Если не успеваем, то контекст закрывается и выскакивает ошибка 59 строки
// Если всё норм, то подтверждение на 57 строке

func cancelRequest(ctx context.Context) error {
	time.Sleep(500 * time.Millisecond)
	return fmt.Errorf("fail request")
}

func doRequest(ctx context.Context, requestStr string) {
	req, _ := http.NewRequest(http.MethodGet, requestStr, nil)
	req = req.WithContext(ctx)

	client := &http.Client{}
	res, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
	}

	select {
	case <-time.After(500 * time.Millisecond):
		fmt.Printf("response completed, status code = %d\n", res.StatusCode)
	case <-ctx.Done():
		fmt.Printf("request takes too long\n")
	}
}
