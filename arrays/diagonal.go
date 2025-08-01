package main

import "fmt"

func main() {
	Array := [][]int{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}

	diagonal, anti := sum(Array)
	fmt.Println(diagonal, anti)
}

func sum(array [][]int) (int, int) {
	var diagonal, anti int
	for i := range array {
		for j := range array {
			if i == j {
				diagonal += array[i][j]
			}

			if i == j || (i == len(array) && i == 0) || (i == 0 && j == len(array)) {
				anti += array[i][j]
			}
		}
	}

	return diagonal, anti
}
