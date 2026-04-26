package mod

import (
	"solod.dev/so/fmt"
	// "solod.dev/so/strings"
	"mod_solod/internal/freeswitch"
)

func app(session *freeswitch.Session, data *freeswitch.Char) {
	freeswitch.Infof("app\n")
	// session.Infof("in app\n")
	// session.Infof("%s", "in app\n")
	var frame *freeswitch.Frame
	session.ReadFrame(&frame)
	freeswitch.Infof("read len=%d\n", frame.DataLen())
	session.WriteFrame(frame)
}

func api(cmd *freeswitch.Char, session *freeswitch.Session, stream *freeswitch.Stream) freeswitch.Status {
	stream.Write("blah blah\n")
	buf := fmt.NewBuffer(64)
	s := fmt.Sprintf(buf, "%s\n", "blah")
	stream.Write(s)
	stream.Writef(stream, s)
	stream.Writef(stream, "%d %s", 7, "blah")
	// stream.Write2("%d %s", 7, "blah")
	return 0
}

func config() {
	root, cfg := freeswitch.OpenXMLConfig("sofia.conf")
	if root == nil || cfg == nil {
		freeswitch.Warnf("Open sofia.conf err\n")
		return
	}
	defer root.Free()
	settings := cfg.Child("global_settings")
	if settings != nil {
		param := settings.Child("param")
		for param != nil {
			key := param.Attr("name")
			val := param.Attr("value")
			freeswitch.Debugf("params %s=%s\n", key, val)
			param = param.Next()
		}
	} else {
		freeswitch.Debugf("no settings\n");
	}
}

func OnLoad(module_interface **freeswitch.ModuleInterface) {
	var apii *freeswitch.APIInterface
	var appi *freeswitch.AppInterface
	freeswitch.Infof("Loading ...\n")
	config()
	freeswitch.SWITCH_ADD_API(apii, "solod", "solod", api, "solod")
	freeswitch.SWITCH_ADD_APP(appi, "solod", "solod", "solod", app, "solod", freeswitch.SAF_NONE)
}
