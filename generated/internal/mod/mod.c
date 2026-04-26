#include "mod.h"

// -- Forward declarations --
static void app(freeswitch_Session* session, cchar_t* data);
static switch_status_t api(cchar_t* cmd, freeswitch_Session* session, freeswitch_Stream* stream);
static void config(void);

// -- Implementation --

static void app(freeswitch_Session* session, cchar_t* data) {
    freeswitch_Infof("app\n");
    // session.Infof("in app\n")
    // session.Infof("%s", "in app\n")
    freeswitch_Frame* frame = NULL;
    freeswitch_Session_ReadFrame(session, &frame);
    freeswitch_Infof("read len=%d\n", freeswitch_Frame_DataLen(frame));
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

static void config(void) {
    freeswitch_XMLRoot xml = (freeswitch_XMLRoot){};
    freeswitch_XML* cfg = freeswitch_XMLRoot_OpenConfig(xml, so_str("sofia.conf"));
    if (cfg == NULL) {
        freeswitch_Warnf("Open sofia.conf err\n");
        freeswitch_XMLRoot_Free(xml);
        return;
    }
    freeswitch_XML* settings = freeswitch_XML_Child(cfg, so_str("global_settings"));
    if (settings != NULL) {
        freeswitch_XML* param = freeswitch_XML_Child(settings, so_str("param"));
        for (; param != NULL;) {
            so_String key = freeswitch_XML_Attr(param, so_str("name"));
            so_String val = freeswitch_XML_Attr(param, so_str("value"));
            freeswitch_Debugf("params %s=%s\n", so_cstr(key), so_cstr(val));
            param = freeswitch_XML_Next(param);
        }
    } else {
        freeswitch_Debugf("no settings\n");
    }
    freeswitch_XMLRoot_Free(xml);
}

void mod_OnLoad(freeswitch_ModuleInterface** module_interface) {
    freeswitch_APIInterface* apii = NULL;
    freeswitch_AppInterface* appi = NULL;
    freeswitch_Infof("Loading ...\n");
    config();
    SWITCH_ADD_API(apii, "solod", "solod", api, "solod");
    SWITCH_ADD_APP(appi, "solod", "solod", "solod", app, "solod", freeswitch_SAF_NONE);
}
