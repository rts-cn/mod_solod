package freeswitch

import (
	"solod.dev/so/c"
	// "solod.dev/so/fmt"
	// "solod.dev/so/strings"
	// "unsafe"
)

//so:include.c <switch.h>
//so:embed embed.h
var embed_h string
//so:embed embed.c
var embed_c string

//so:extern
type switch_status_t uint32
//so:extern switch_status_t
type Status switch_status_t

//so:extern
type switch_core_session_t struct {}
type Session switch_core_session_t
//so:extern
type switch_loadable_module_interface_t struct {}
type ModuleInterface switch_loadable_module_interface_t
//so:extern
type switch_stream_handle_t struct {
	Writef StreamWriteFunc
}
type Stream switch_stream_handle_t
type APIFunc func(cmd *Char, session *Session, stream *Stream) Status
type AppFunc func(session *Session, data *Char)

//so:extern cchar_t
type char byte
//so:extern cchar_t
type Char byte

func Init() { // todo, this function is incomplete
	flags := c.Val[Bool]("SWITCH_TRUE")
	console := c.Val[uint32]("SCF_USE_SQL")
	var err *c.ConstChar
	loop := 0

	println("Hello, MySWITCH is running ...\n")
	switch_core_set_globals()
	switch_core_init_and_modload(flags, console, &err)
	if (err != nil) {
		Errorf("error: %s", err)
	}
	switch_core_runtime_loop(loop)
}
