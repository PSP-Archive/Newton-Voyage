#include "input.h"

static SceCtrlData pad;

void input_read( void ) {
	sceCtrlReadBufferPositive( &pad, 1 );
}

int input_isPressed( int which ) {
	return pad.Buttons & which;
}