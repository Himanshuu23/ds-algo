package main

import "fmt"

func main() {
	Map := make(map[string]int)
	Map["A"] = 100
	Map["B"] = 200
	Map["C"] = 300
	Map["D"] = 400

	var name string
	fmt.Println("Enter the name of the student whose marks you want to see: ")
	fmt.Scanln(&name)
	fmt.Println(name, "->", Map[name])
}
