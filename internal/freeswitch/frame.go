package freeswitch

//so:extern
type switch_frame_t struct{
	Data *uint8
	DataLen uint32
}
type Frame switch_frame_t
