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
