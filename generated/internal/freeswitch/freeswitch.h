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

#define Writef write_function // stream->write_function
typedef struct switch_xml switch_xml_node_t;

typedef struct so_R_ptr_ptr {
    void *val;
    void *val2;
} so_R_ptr_ptr;

// -- Types --

typedef struct freeswitch_XMLRoot freeswitch_XMLRoot;
typedef so_int freeswitch_SwitchModuleInterfaceName;
typedef switch_api_interface_t freeswitch_APIInterface;
typedef switch_application_interface_t freeswitch_AppInterface;
typedef uint32_t freeswitch_ApplicationFlag;
typedef uint32_t freeswitch_IOFlag;
typedef uint32_t freeswitch_Bool;
typedef switch_event_t freeswitch_Event;
typedef switch_frame_t freeswitch_Frame;
typedef switch_core_session_t freeswitch_Session;
typedef switch_loadable_module_interface_t freeswitch_ModuleInterface;
typedef switch_stream_handle_t freeswitch_Stream;

typedef switch_status_t (*freeswitch_APIFunc)(const char*, freeswitch_Session*, freeswitch_Stream*);

typedef void (*freeswitch_AppFunc)(freeswitch_Session*, const char*);
typedef so_int freeswitch_LogLevel;

// *(switch_xml_t) xml element
typedef switch_xml_node_t freeswitch_XML;

typedef struct freeswitch_XMLRoot {
    freeswitch_XML* root;
} freeswitch_XMLRoot;

// -- Variables and constants --
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ENDPOINT_INTERFACE = 0;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_TIMER_INTERFACE = 1;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIALPLAN_INTERFACE = 2;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CODEC_INTERFACE = 3;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_APPLICATION_INTERFACE = 4;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_API_INTERFACE = 5;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_FILE_INTERFACE = 6;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SPEECH_INTERFACE = 7;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIRECTORY_INTERFACE = 8;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_INTERFACE = 9;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SAY_INTERFACE = 10;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ASR_INTERFACE = 11;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_MANAGEMENT_INTERFACE = 12;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_LIMIT_INTERFACE = 13;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_APPLICATION_INTERFACE = 14;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_JSON_API_INTERFACE = 15;
static const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DATABASE_INTERFACE = 16;
static const freeswitch_ApplicationFlag freeswitch_SAF_NONE = 0;
static const int64_t freeswitch_SAF_SUPPORT_NOMEDIA = ((int64_t)1 << 0);
static const int64_t freeswitch_SAF_ROUTING_EXEC = ((int64_t)1 << 1);
static const int64_t freeswitch_SAF_MEDIA_TAP = ((int64_t)1 << 2);
static const int64_t freeswitch_SAF_ZOMBIE_EXEC = ((int64_t)1 << 3);
static const int64_t freeswitch_SAF_NO_LOOPBACK = ((int64_t)1 << 4);
static const int64_t freeswitch_SAF_SUPPORT_TEXT_ONLY = ((int64_t)1 << 5);
static const freeswitch_IOFlag freeswitch_SWITCH_IO_FLAG_NONE = 0;
static const int64_t freeswitch_SWITCH_IO_FLAG_NOBLOCK = ((int64_t)1 << 0);
static const int64_t freeswitch_SWITCH_IO_FLAG_SINGLE_READ = ((int64_t)1 << 1);
static const int64_t freeswitch_SWITCH_IO_FLAG_FORCE = ((int64_t)1 << 2);
static const int64_t freeswitch_SWITCH_IO_FLAG_QUEUED = ((int64_t)1 << 3);
static const freeswitch_LogLevel freeswitch_LOG_ERROR = 3;
static const freeswitch_LogLevel freeswitch_LOG_INFO = 6;

// -- Functions and methods --
uint8_t* freeswitch_Frame_Data(void* self);
uint32_t freeswitch_Frame_DataLen(void* self);
void freeswitch_Init(void);
void freeswitch_Log(freeswitch_LogLevel level, so_String format, so_Slice args);
void freeswitch_Session_ReadFrame(void* self, freeswitch_Frame** frame);
void freeswitch_Session_WriteFrame(void* self, freeswitch_Frame* frame);
void freeswitch_Stream_Write(void* self, so_String s);
so_R_ptr_ptr freeswitch_OpenXMLConfig(so_String file);
void freeswitch_XML_Free(void* self);
freeswitch_XML* freeswitch_XML_Next(void* self);
freeswitch_XML* freeswitch_XML_Child(void* self, so_String name);
so_String freeswitch_XML_Attr(void* self, so_String attr);
