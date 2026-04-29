package freeswitch

import (
	"solod.dev/so/c"
	"solod.dev/so/fmt"
	"solod.dev/so/strings"
	// "unsafe"
)

type LogLevel int

const (
	LOG_ERROR LogLevel = 3
	LOG_INFO  LogLevel = 6
)

//so:extern
func switch_log_printf(t int, file string, fun string, line int, session any, level LogLevel, format string, args ...any);
//so:extern
func Infof(format string, args ...any);
//so:extern
func Debugf(format string, args ...any);
//so:extern
func Errorf(format string, args ...any);
//so:extern
func Warnf(format string, args ...any);

func Log(level LogLevel, format string, args ...any) {
	var sb strings.Builder
	defer sb.Free()
	_, err := fmt.Fprintf(&sb, format, args)
	if err != nil {
		panic(err)
	}
	s := sb.String()
	if s != "" { // fix: declared and not used: s
		c.Raw(`switch_log_printf(SWITCH_CHANNEL_LOG, level, so_cstr(format), s);`)
	}
	switch_log_printf(0, "", "", 0, nil, level, format, sb.String())
	// spreading variadic arguments to an extern function is not supported
	// switch_log_printf(0, "", "", 0, nil, level, format, args...)
}
