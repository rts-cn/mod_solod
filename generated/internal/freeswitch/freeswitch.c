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
    freeswitch_Bool flags = SWITCH_TRUE;
    uint32_t console = SCF_USE_SQL;
    const char* err = NULL;
    so_int loop = 0;
    so_println("%s", "Hello, MySWITCH is running ...\n");
    switch_core_set_globals();
    switch_core_init_and_modload(flags, console, &err);
    if ((err != NULL)) {
        freeswitch_Errorf("error: %s", err);
    }
    switch_core_runtime_loop(loop);
}

// -- log.go --

void freeswitch_Log(freeswitch_LogLevel level, so_String format, so_Slice args) {
    strings_Builder sb = {0};
    so_R_int_err _res1 = fmt_Fprintf((io_Writer){.self = &sb, .Write = strings_Builder_Write}, so_cstr(format), so_decay(args));
    so_Error err = _res1.err;
    if (err.self != NULL) {
        strings_Builder_Free(&sb);
        so_panic(so_error_cstr(err));
    }
    so_String s = strings_Builder_String(&sb);
    if (so_string_ne(s, so_str(""))) {
        // fix: declared and not used: s
        switch_log_printf(SWITCH_CHANNEL_LOG, level, so_cstr(format), s);
    }
    // spreading variadic arguments to an extern function is not supported
    // switch_log_printf(0, "", "", 0, nil, level, format, args...)
    switch_log_printf(0, so_cstr(so_str(__FILE__)), so_cstr(so_str(__func__)), __LINE__, NULL, level, so_cstr(format), so_cstr(strings_Builder_String(&sb)));
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
    const char* val = switch_xml_attr_soft(xml, so_cstr(attr));
    return c_String(const char, (val));
}
