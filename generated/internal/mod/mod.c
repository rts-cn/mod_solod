#include "mod.h"

// -- Forward declarations --
static void app(freeswitch_Session* session, cchar_t* data);
static switch_status_t api(cchar_t* cmd, freeswitch_Session* session, freeswitch_Stream* stream);

// -- Implementation --

static void app(freeswitch_Session* session, cchar_t* data) {
    freeswitch_Infof("app\n");
    // session.Infof("in app\n")
    // session.Infof("%s", "in app\n")
    freeswitch_Frame* frame = NULL;
    freeswitch_Session_ReadFrame(session, &frame);
    freeswitch_Infof("read len=%d\n", frame->DataLen);
    freeswitch_Session_WriteFrame(session, frame);
}

static switch_status_t api(cchar_t* cmd, freeswitch_Session* session, freeswitch_Stream* stream) {
    freeswitch_Stream_Write(stream, so_str("blah blah\n"));
    fmt_Buffer buf = fmt_NewBuffer(64);
    so_String s = fmt_Sprintf(buf, "%s\n", "blah");
    freeswitch_Stream_Write(stream, s);
    stream->Writef(stream, so_cstr(s));
    stream->Writef(stream, "%d %s", 7, "blah");
    // stream.Write2("%d %s", 7, "blah")
    return 0;
}

void mod_OnLoad(freeswitch_ModuleInterface** module_interface) {
    freeswitch_APIInterface* apii = NULL;
    freeswitch_AppInterface* appi = NULL;
    freeswitch_Infof("Loading ...\n");
    SWITCH_ADD_API(apii, "solod", "solod", api, "solod");
    SWITCH_ADD_APP(appi, "solod", "solod", "solod", app, "solod", freeswitch_SAF_NONE);
}
