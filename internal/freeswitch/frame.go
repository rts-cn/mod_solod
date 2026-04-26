package freeswitch

//so:extern
type switch_frame_t struct{
	data *uint8
	datalen uint32
}
type Frame switch_frame_t

func (frame *Frame) Data() *uint8{
	return frame.data
}

func (frame *Frame) DataLen() uint32 {
	return frame.datalen
}
