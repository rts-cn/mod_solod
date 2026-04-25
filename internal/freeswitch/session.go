package freeswitch

//so:extern
func switch_core_session_read_frame(session *Session,  frame **Frame, flags IOFlag, stream_id int)
//so:extern
func switch_core_session_write_frame(session *Session,  frame *Frame, flags IOFlag, stream_id int)

//so:extern
func (session *Session) Infof(format string, args ...any)
func (session *Session) ReadFrame(frame **Frame) {
	flags := SWITCH_IO_FLAG_NONE
	stream_id := 0
	switch_core_session_read_frame(session, frame, flags, stream_id)
}
func (session *Session) WriteFrame(frame *Frame) {
	flags := SWITCH_IO_FLAG_NONE
	stream_id := 0
	switch_core_session_write_frame(session, frame, flags, stream_id)
}
