package main

import (
	"mod_solod/internal/freeswitch"
	_ "mod_solod/internal/mod"
)

//so:embed mod_solod.c
var mod_c string

func main() {
	freeswitch.Init()
}
