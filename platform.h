#ifndef __PLATFORM___H__
#define __PLATFORM___H__

//
// Platform-level utilities
//

#ifdef __cplusplus
extern "C" {
#endif

#define BUF_WIDTH ( 512 )
#define SCR_WIDTH ( 480 )
#define SCR_HEIGHT ( 272 )

// threads and program exiting
int platform_isGameRunning( void );

// initialize graphics, controller polling, etc.
void platform_initialize( void );
// pre-frame initializations
void platform_preFrame( void );
// post-frame buffer swapping, vblank waiting, etc.
void platform_postFrame( void );

// math utilities
float platform_safeAtan2( float x, float y );

// finalize context before yielding control to the kernel
void platform_shutdown( void );

#ifdef __cplusplus
}
#endif



#endif