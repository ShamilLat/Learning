package main

import "sync"

type Counter struct {
	mu sync.RWMutex
	c  map[string]int
}

func (c *Counter) CountMe() map[string]int {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.c
}

func (c *Counter) CountMeAgain() map[string]int {
	c.mu.RLock()
	defer c.mu.RUnlock()
	return c.c
}

func main() {

}
