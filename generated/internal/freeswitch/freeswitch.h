#pragma once
#include "so/builtin/builtin.h"
#include "so/c/c.h"
#include "so/fmt/fmt.h"
#include "so/strings/strings.h"

// -- Embeds --

#include <switch.h>

#define freeswitch_Infof(...) switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, __VA_ARGS__)
#define freeswitch_Debugf(...) switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, __VA_ARGS__)
#define freeswitch_Errorf(...) switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, __VA_ARGS__)
#define freeswitch_Warnf(...) switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING, __VA_ARGS__)
#define freeswitch_Noticef(...) switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_NOTICE, __VA_ARGS__)

#define freeswitch_Session_Infof(s, ...) switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(s), SWITCH_LOG_INFO, __VA_ARGS__)
#define freeswitch_Session_Debugf(s, ...) switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(s), SWITCH_LOG_DEBUG, __VA_ARGS__)
#define freeswitch_Session_Errorf(s, ...) switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(s), SWITCH_LOG_ERROR, __VA_ARGS__)
#define freeswitch_Session_Warnf(s, ...) switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(s), SWITCH_LOG_WARNING, __VA_ARGS__)
#define freeswitch_Session_Noticef(s, ...) switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(s), SWITCH_LOG_NOTICE, __VA_ARGS__)

typedef const char cchar_t;   // some functions need a const char *
#define Writef write_function // stream->write_function

// -- Types --
typedef so_int freeswitch_SwitchModuleInterfaceName;
typedef switch_api_interface_t freeswitch_APIInterface;
typedef switch_application_interface_t freeswitch_AppInterface;
typedef uint32_t freeswitch_ApplicationFlag;
typedef uint32_t freeswitch_IOFlag;
typedef switch_frame_t freeswitch_Frame;
typedef switch_core_session_t freeswitch_Session;
typedef switch_loadable_module_interface_t freeswitch_ModuleInterface;
typedef switch_stream_handle_t freeswitch_Stream;

typedef switch_status_t (*freeswitch_APIFunc)(cchar_t*, freeswitch_Session*, freeswitch_Stream*);

typedef void (*freeswitch_AppFunc)(freeswitch_Session*, cchar_t*);
typedef so_int freeswitch_LogLevel;

// -- Variables and constants --
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ENDPOINT_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_TIMER_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIALPLAN_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CODEC_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_APPLICATION_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_API_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_FILE_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SPEECH_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIRECTORY_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SAY_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ASR_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_MANAGEMENT_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_LIMIT_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_APPLICATION_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_JSON_API_INTERFACE;
extern const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DATABASE_INTERFACE;
extern const freeswitch_ApplicationFlag freeswitch_SAF_NONE;
extern const so_int freeswitch_SAF_SUPPORT_NOMEDIA;
extern const so_int freeswitch_SAF_ROUTING_EXEC;
extern const so_int freeswitch_SAF_MEDIA_TAP;
extern const so_int freeswitch_SAF_ZOMBIE_EXEC;
extern const so_int freeswitch_SAF_NO_LOOPBACK;
extern const so_int freeswitch_SAF_SUPPORT_TEXT_ONLY;
extern const freeswitch_IOFlag freeswitch_SWITCH_IO_FLAG_NONE;
extern const so_int freeswitch_SWITCH_IO_FLAG_NOBLOCK;
extern const so_int freeswitch_SWITCH_IO_FLAG_SINGLE_READ;
extern const so_int freeswitch_SWITCH_IO_FLAG_FORCE;
extern const so_int freeswitch_SWITCH_IO_FLAG_QUEUED;
extern const freeswitch_LogLevel freeswitch_LOG_ERROR;
extern const freeswitch_LogLevel freeswitch_LOG_INFO;

// -- Functions and methods --
uint8_t* freeswitch_Frame_Data(void* self);
uint32_t freeswitch_Frame_DataLen(void* self);
void freeswitch_Init(void);
void freeswitch_Log(freeswitch_LogLevel level, so_String format, so_Slice args);
void freeswitch_Session_ReadFrame(void* self, freeswitch_Frame** frame);
void freeswitch_Session_WriteFrame(void* self, freeswitch_Frame* frame);
void freeswitch_Stream_Write(void* self, so_String s);
