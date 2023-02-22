package main

import (
	"context"
	"fmt"
	"net/http"
	"time"
)

func main() {

	duration := 5000 * time.Millisecond
	ctx := context.Background()
	// Можно хранить некоторые данные в контекте, но лучше делать это только
	// для данных запросов
	ctx = context.WithValue(ctx, "test", "hello")
	ctx, cancel := context.WithTimeout(ctx, duration)

	defer cancel()

	doRequest(ctx, "https://ya.ru")
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
		fmt.Println(ctx.Value("test"))
	case <-ctx.Done():
		fmt.Printf("request takes too long\n")
	}
}
