package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var wq sync.WaitGroup

	// Счётчик для atomic
	var counter uint64
	var mu sync.Mutex

	for i := 0; i < 10; i++ {
		wq.Add(1)
		k := i
		go func() {
			defer wq.Done()

			for j := 0; j < 1000; j++ {
				mu.Lock()
				counter++
				mu.Unlock()
				// atomic.AddUint64(&counter, 1)
			}
			fmt.Printf("%d goroutine works\n", k)
			time.Sleep(300 * time.Millisecond)
		}()

	}

	wq.Wait()
	fmt.Printf("all done. counter = %d\n", counter)
}
