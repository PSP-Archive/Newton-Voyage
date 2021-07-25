#ifndef __INPUT___H__
#define __INPUT___H__

#include <pspctrl.h>
#include "types.h"

//
// Provides input functionality
//

#ifdef __cplusplus
extern "C" {
#endif

#define PAD_UP PSP_CTRL_UP
#define PAD_DOWN PSP_CTRL_DOWN
#define BUTTON_X PSP_CTRL_CROSS

void input_read( void );
int input_isPressed( int which );

#ifdef __cplusplus
}
#endif

#endif