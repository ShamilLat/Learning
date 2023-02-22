package les12

import (
	"fmt"
	"testing"
)

func TestExampleCleanup(t *testing.T) {
	fmt.Println("SETUP")

	t.Run("FIRST", func(t *testing.T) {
		fmt.Println("ok")
	})
	t.Run("SECOND", func(t *testing.T) {
		fmt.Println("ok")
	})
	t.Run("THIRD", func(t *testing.T) {
		t.Fatal("fatal test")
	})

	fmt.Println("TEARDOWN AT END")

	t.Cleanup(func() {
		fmt.Println("TEARDOWN ON CLEANUP")
	})
}
