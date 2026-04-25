package freeswitch

import (
	// "solod.dev/so/c"
	// "solod.dev/so/fmt"
)

//so:extern
type switch_module_interface_name_t int
type SwitchModuleInterfaceName switch_module_interface_name_t
const (
	SWITCH_ENDPOINT_INTERFACE SwitchModuleInterfaceName = iota
	SWITCH_TIMER_INTERFACE
	SWITCH_DIALPLAN_INTERFACE
	SWITCH_CODEC_INTERFACE
	SWITCH_APPLICATION_INTERFACE
	SWITCH_API_INTERFACE
	SWITCH_FILE_INTERFACE
	SWITCH_SPEECH_INTERFACE
	SWITCH_DIRECTORY_INTERFACE
	SWITCH_CHAT_INTERFACE
	SWITCH_SAY_INTERFACE
	SWITCH_ASR_INTERFACE
	SWITCH_MANAGEMENT_INTERFACE
	SWITCH_LIMIT_INTERFACE
	SWITCH_CHAT_APPLICATION_INTERFACE
	SWITCH_JSON_API_INTERFACE
	SWITCH_DATABASE_INTERFACE
)

//so:extern
type switch_api_interface_t struct{}
type APIInterface switch_api_interface_t
//so:extern
type switch_application_interface_t struct{}
type AppInterface switch_application_interface_t

type ApplicationFlag uint32
const (
	SAF_NONE ApplicationFlag = 0
	SAF_SUPPORT_NOMEDIA = (1 << 0)
	SAF_ROUTING_EXEC = (1 << 1)
	SAF_MEDIA_TAP = (1 << 2)
	SAF_ZOMBIE_EXEC = (1 << 3)
	SAF_NO_LOOPBACK = (1 << 4)
	SAF_SUPPORT_TEXT_ONLY = (1 << 5)
)

//so:extern
type switch_io_flag_t uint32
type IOFlag switch_io_flag_t

const (
	SWITCH_IO_FLAG_NONE IOFlag = 0
	SWITCH_IO_FLAG_NOBLOCK = (1 << 0)
	SWITCH_IO_FLAG_SINGLE_READ = (1 << 1)
	SWITCH_IO_FLAG_FORCE = (1 << 2)
	SWITCH_IO_FLAG_QUEUED = (1 << 3)
)

//so:extern
func switch_core_set_globals()
//so:extern
func switch_core_init_and_modload(flags int, console int, err **char)
//so:extern
func switch_core_runtime_loop(int)

//so:extern
func switch_loadable_module_create_interface(mod *ModuleInterface, name SwitchModuleInterfaceName) any

//so:extern SWITCH_ADD_API
func SWITCH_ADD_API(apii *APIInterface, name string, desc string, funcptr APIFunc, syntax string)
//so:extern SWITCH_ADD_APP
func SWITCH_ADD_APP(appi *AppInterface, name string, desc string, long_desc string, funcptr AppFunc, syntax string, flag ApplicationFlag)
