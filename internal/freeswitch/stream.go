package freeswitch

import (
	// "solod.dev/so/c"
	// "solod.dev/so/fmt"
	// "solod.dev/so/strings"
)

//so:extern
type StreamWriteFunc func(st *Stream, fotrmat string, args ...any)

//so:extern
func switch_stream_write(stream *Stream, s string)
func (stream *Stream)Write(s string) {
	switch_stream_write(stream, s);
}
//so:extern
func (stream *Stream)Write2(format string, args ...any) {
	// stream.write_function(stream, format, args...)
}
