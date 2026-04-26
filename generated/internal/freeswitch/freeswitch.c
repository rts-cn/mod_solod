#include "freeswitch.h"
#include <switch.h>

// -- Embeds --

//go:build ignore

void switch_stream_write(switch_stream_handle_t *stream, const char *s)
{
	stream->write_function(stream, s);
}

void freeswitch_Stream_Write2(switch_stream_handle_t *stream, const char *fmt, ...)
{
	va_list args;
    va_start(args, fmt);
    stream->write_function(stream, fmt, args);
    va_end(args);
}

// -- Variables and constants --
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ENDPOINT_INTERFACE = 0;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_TIMER_INTERFACE = 1;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIALPLAN_INTERFACE = 2;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CODEC_INTERFACE = 3;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_APPLICATION_INTERFACE = 4;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_API_INTERFACE = 5;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_FILE_INTERFACE = 6;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SPEECH_INTERFACE = 7;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DIRECTORY_INTERFACE = 8;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_INTERFACE = 9;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_SAY_INTERFACE = 10;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_ASR_INTERFACE = 11;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_MANAGEMENT_INTERFACE = 12;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_LIMIT_INTERFACE = 13;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_CHAT_APPLICATION_INTERFACE = 14;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_JSON_API_INTERFACE = 15;
const freeswitch_SwitchModuleInterfaceName freeswitch_SWITCH_DATABASE_INTERFACE = 16;
const freeswitch_ApplicationFlag freeswitch_SAF_NONE = 0;
const so_int freeswitch_SAF_SUPPORT_NOMEDIA = ((so_int)1 << 0);
const so_int freeswitch_SAF_ROUTING_EXEC = ((so_int)1 << 1);
const so_int freeswitch_SAF_MEDIA_TAP = ((so_int)1 << 2);
const so_int freeswitch_SAF_ZOMBIE_EXEC = ((so_int)1 << 3);
const so_int freeswitch_SAF_NO_LOOPBACK = ((so_int)1 << 4);
const so_int freeswitch_SAF_SUPPORT_TEXT_ONLY = ((so_int)1 << 5);
const freeswitch_IOFlag freeswitch_SWITCH_IO_FLAG_NONE = 0;
const so_int freeswitch_SWITCH_IO_FLAG_NOBLOCK = ((so_int)1 << 0);
const so_int freeswitch_SWITCH_IO_FLAG_SINGLE_READ = ((so_int)1 << 1);
const so_int freeswitch_SWITCH_IO_FLAG_FORCE = ((so_int)1 << 2);
const so_int freeswitch_SWITCH_IO_FLAG_QUEUED = ((so_int)1 << 3);
const freeswitch_LogLevel freeswitch_LOG_ERROR = 3;
const freeswitch_LogLevel freeswitch_LOG_INFO = 6;

// -- core.go --

// -- event.go --

// -- frame.go --

uint8_t* freeswitch_Frame_Data(void* self) {
    freeswitch_Frame* frame = self;
    return frame->data;
}

uint32_t freeswitch_Frame_DataLen(void* self) {
    freeswitch_Frame* frame = self;
    return frame->datalen;
}

// -- freeswitch.go --

void freeswitch_Init(void) {
    // todo, this function is incomplete
    so_int flags = 0;
    so_int console = 1;
    cchar_t* err = NULL;
    so_int loop = 0;
    so_println("%s", "Hello, MySWITCH is running ...\n");
    switch_core_set_globals();
    switch_core_init_and_modload(flags, console, &err);
    so_String errStr = c_String((so_byte*)(err));
    so_println("%s %.*s", "err:", errStr.len, errStr.ptr);
    freeswitch_Infof("%s", "blah\n");
    switch_core_runtime_loop(loop);
}

// -- log.go --

void freeswitch_Log(freeswitch_LogLevel level, so_String format, so_Slice args) {
    strings_Builder sb = {0};
    so_R_int_err _res1 = fmt_Fprintf((io_Writer){.self = &sb, .Write = strings_Builder_Write}, so_cstr(format), so_decay(args));
    so_Error err = _res1.err;
    // switch_log_printf(0, "", "", 0, nil, level, format, sb.String())
    // switch_log_printf(0, "", "", 0, nil, level, format, args...)
    if (err != NULL) {
        strings_Builder_Free(&sb);
        so_panic(err->msg);
    }
    strings_Builder_Free(&sb);
}

// -- session.go --

void freeswitch_Session_ReadFrame(void* self, freeswitch_Frame** frame) {
    freeswitch_Session* session = self;
    freeswitch_IOFlag flags = freeswitch_SWITCH_IO_FLAG_NONE;
    so_int stream_id = 0;
    switch_core_session_read_frame(session, frame, flags, stream_id);
}

void freeswitch_Session_WriteFrame(void* self, freeswitch_Frame* frame) {
    freeswitch_Session* session = self;
    freeswitch_IOFlag flags = freeswitch_SWITCH_IO_FLAG_NONE;
    so_int stream_id = 0;
    switch_core_session_write_frame(session, frame, flags, stream_id);
}

// -- stream.go --

void freeswitch_Stream_Write(void* self, so_String s) {
    freeswitch_Stream* stream = self;
    switch_stream_write(stream, so_cstr(s));
}

// -- xml.go --

so_R_ptr_ptr freeswitch_OpenXMLConfig(so_String file) {
    freeswitch_XML* cfg = NULL;
    freeswitch_XML* root = switch_xml_open_cfg(so_cstr(file), &cfg, NULL);
    return (so_R_ptr_ptr){.val = root, .val2 = cfg};
}

void freeswitch_XML_Free(void* self) {
    freeswitch_XML* xml = self;
    switch_xml_free(xml);
}

freeswitch_XML* freeswitch_XML_Next(void* self) {
    freeswitch_XML* xml = self;
    return switch_xml_next(xml);
}

freeswitch_XML* freeswitch_XML_Child(void* self, so_String name) {
    freeswitch_XML* xml = self;
    return switch_xml_child(xml, so_cstr(name));
}

so_String freeswitch_XML_Attr(void* self, so_String attr) {
    freeswitch_XML* xml = self;
    cchar_t* val = switch_xml_attr_soft(xml, so_cstr(attr));
    return c_String((so_byte*)(val));
}
