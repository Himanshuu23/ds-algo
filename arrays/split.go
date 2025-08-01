package main

import "fmt"

func main() {
	Array1 := []int{1, 2, 3, 4, 5}
	Array2 := []int{1, 2, 3, 4}
	
	split(Array1)
	split(Array2)
}

func split(array []int) {
	var array1, array2 []int
	mid := len(array) / 2

	if len(array) % 2 == 0 {
		array1 = append(array1, array[:mid]...)
		array2 = append(array2, array[mid:]...)
	} else {
		array1 = append(array1, array[:mid+1]...)
		array2 = append(array2, array[mid+1:]...)
	}

	fmt.Println(array1, array2)
}
