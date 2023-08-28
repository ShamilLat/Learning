package main

import "testing"
import "fmt"
import "os"

func TestMain(m *testing.M) {
	fmt.Println("setup")
	res := m.Run()
	fmt.Println("tear-down")

	os.Exit(res)
}

func TestMultiple(t *testing.T) {
	t.Run("groupA", func(t *testing.T) {

		t.Run("simple", func(t *testing.T) {
			// Для параллельного запуска тестов
			t.Parallel()
			t.Log("simple")

			var x, y, result = 2, 2, 4

			realresult := Multiple(x, y)

			if realresult != result {
				t.Errorf("%d != %d", realresult, result)
			}
			t.Run("more_simple", func(t *testing.T) {
				r := Multiple(1, 1)
				if r != 1 {
					t.Errorf("failed")
				}
			})
		})

		t.Run("medium", func(t *testing.T) {
			t.Parallel()
			t.Log("midle")
			var x, y, result = 222, 222, 49284

			realresult := Multiple(x, y)

			if realresult != result {
				t.Errorf("%d != %d", realresult, result)
			}
		})

		t.Run("negative", func(t *testing.T) {
			t.Parallel()
			t.Log("negative")
			var x, y, result = -2, 4, -8

			realresult := Multiple(x, y)

			if realresult != result {
				t.Errorf("%d != %d", realresult, result)
			}
		})

	})
	// var x, y, result = 2, 2, 4

	// realresult := Multiple(x, y)

	// if realresult != result {
	// 	t.Errorf("%d != %d", realresult, result)
	// }
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

// go test -v -run TestMultiple/simple (Запуск конкретных тестов)
// go test -v -run /simple
