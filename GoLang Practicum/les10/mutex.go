package main

import (
	"fmt"
	"sync"
	"time"
)

type Counter struct {
	mu sync.Mutex
	c  map[string]int
}

func (c *Counter) Inc(key string) {
	c.mu.Lock()
	c.c[key]++
	c.mu.Unlock()
}

func (c *Counter) Value(key string) int {
	c.mu.Lock()

	defer c.mu.Unlock()
	return c.c[key]
}

func main() {
	key := "test"
	c := Counter{c: make(map[string]int)}

	for i := 0; i < 1000; i++ {
		go c.Inc(key)
	}

	time.Sleep(3 * time.Second)
	fmt.Println(c.Value(key))
}
