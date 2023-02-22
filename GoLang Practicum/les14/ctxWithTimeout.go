package main

import (
	"context"
	"fmt"
	"net/http"
	"time"
)

func main() {

	// Timeout, как Deadlock, закрывает канал сам, без вызова cancelRequest
	// Только ему нужно duration напрямую, а не time.time
	duration := 5000 * time.Millisecond
	ctx := context.Background()
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
	case <-ctx.Done():
		fmt.Printf("request takes too long\n")
	}
}
