package main

import (
	"fmt"
	"io"
	"strings"
)

type name struct {
	A int
	B string
}

func (n *name) String() string {
	return n.B
}

func main() {
	r := strings.NewReader("hello world")

	arr := make([]byte, 8)

	for {
		n, err := r.Read(arr)
		fmt.Printf("n = %d, err = %v, b = %v\n", n, err, arr)
		fmt.Printf("arr n bytes: %q\n", arr[:n])
		if err == io.EOF {
			break

		}
	}
}
