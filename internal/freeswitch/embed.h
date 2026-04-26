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
typedef struct switch_xml switch_xml_node_t;
