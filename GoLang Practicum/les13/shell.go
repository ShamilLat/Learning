package main

import (
	"os"
	"os/exec"
)

func main() {
	c := exec.Command("top")
	c.Stdin = os.Stdin
	c.Stdout = os.Stdout
	c.Stderr = os.Stderr
	c.Run()
}
