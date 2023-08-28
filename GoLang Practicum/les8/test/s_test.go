package test_test

import (
	"fmt"
	"os"
	"testing"
)

func TestMain(m *testing.M) {
	fmt.Println("setup tt")
	res := m.Run()
	fmt.Println("tear-down tt")

	os.Exit(res)
}

func TestAdd(t *testing.T) {
	t.Run("simple", func(t *testing.T) {
		var x, y, result = 2, 2, 4

		realresult := Add(x, y)

		if realresult != result {
			t.Errorf("%d != %d", realresult, result)
		}
		t.Run("more_simple", func(t *testing.T) {
			r := Add(1, 1)
			if r != 2 {
				t.Errorf("failed")
			}
		})
	})
}
