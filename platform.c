#include "platform.h"

#include <pspgu.h>
#include <pspkernel.h>
#include <math.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspgum.h>
#include <psputils.h>
#include <time.h>

// display list buffer
static unsigned int __attribute__( ( aligned( 16 ) ) ) displayList[ 262144 ];
// beginning of free vram
static unsigned int platform_staticOffset = 0;
// used to relinquish control to the kernel
static int platform_IsRunning = 1;

int platform_isGameRunning() {
	return platform_IsRunning;
}

int exitCallback( int arg1, int arg2, void *common ) {
	platform_IsRunning = 0;
	return 0;
}

int callbackThread( SceSize args, void *argp ) {
	int callbackId;

	callbackId = sceKernelCreateCallback( "Exit Callback", exitCallback, NULL );
	sceKernelRegisterExitCallback( callbackId );

	sceKernelSleepThreadCB();

	return 0;
}

int platform_installCallbacks( void ) {
	int threadId = 0;

	threadId = sceKernelCreateThread( "update_thread", callbackThread, 0x11, 0xFA0, 0, 0 );
	if( threadId >= 0 ) {
		sceKernelStartThread( threadId, 0, 0 );
	}

	return threadId;
}

float platform_safeAtan2( float x, float y ) {
	if( x == 0.0000000f && y == 0.0000000f ) {
		return 0.0f;
	}

	return atan2( x, y );
}

// return memory size needed to allocate a bitmap, given its dimensions and colour format
static unsigned int getMemorySize( unsigned int width, unsigned int height, unsigned int psm ) {
	switch ( psm ) {
		case GU_PSM_T4:
			return ( width * height ) >> 1;

		case GU_PSM_T8:
			return width * height;

		case GU_PSM_5650:
		case GU_PSM_5551:
		case GU_PSM_4444:
		case GU_PSM_T16:
			return 2 * width * height;

		case GU_PSM_8888:
		case GU_PSM_T32:
			return 4 * width * height;

		default:
			return 0;
	}
}

void* allocateVideoRamBuffer( unsigned int width, unsigned int height, unsigned int psm ) {
	unsigned int memSize = getMemorySize( width,height,psm );
	void* result = (void*)platform_staticOffset;
	platform_staticOffset += memSize;

	return result;
}

void platform_initialize() {
	platform_installCallbacks();

	sceGuInit();

	void* fbp0 = allocateVideoRamBuffer( BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888 );
	void* fbp1 = allocateVideoRamBuffer( BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888 );
	void* zbp = allocateVideoRamBuffer( BUF_WIDTH, SCR_HEIGHT, GU_PSM_4444 );

	sceGuStart( GU_DIRECT, displayList );
	sceGuDrawBuffer( GU_PSM_8888, fbp0,BUF_WIDTH );
	sceGuDispBuffer( SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH );
	sceGuDepthBuffer( zbp, BUF_WIDTH );
	sceGuOffset( 2048 - ( SCR_WIDTH/2 ), 2048 - ( SCR_HEIGHT/2 ) );
	sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT );
	sceGuDepthRange( 0xc350, 0x2710 );
	sceGuScissor( 0, 0, SCR_WIDTH, SCR_HEIGHT );
	sceGuEnable( GU_SCISSOR_TEST );
	sceGuAlphaFunc( GU_GREATER, 0, 0xff );
	sceGuEnable( GU_ALPHA_TEST );
	sceGuDepthFunc( GU_GEQUAL );
	sceGuEnable( GU_DEPTH_TEST );
	sceGuFrontFace( GU_CW );
	sceGuShadeModel( GU_SMOOTH );
	sceGuEnable( GU_CULL_FACE );
	sceGuEnable( GU_TEXTURE_2D );
	sceGuFinish();
	sceGuSync( 0, 0 );

	sceDisplayWaitVblankStart();
	sceGuDisplay( GU_TRUE );
	
	sceCtrlSetSamplingCycle( 0 );
	sceCtrlSetSamplingMode( PSP_CTRL_MODE_ANALOG );
}

void platform_preFrame() {
	sceGuStart( GU_DIRECT, displayList );
	sceGuClearColor( 0xff330000 );
	sceGuClearDepth( 0 );
	sceGuClear( GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT );
	
	sceGuAmbientColor( 0xffffffff );

	sceGumMatrixMode( GU_PROJECTION );
	sceGumLoadIdentity();
	sceGumPerspective(
		75.0f,
		16.0f/9.0f,
		0.0f,
		100.0f
		);

	sceGumMatrixMode( GU_VIEW );
	ScePspFVector3 pos = { 0.0f, 0.0f, -0.1f };
	sceGumLoadIdentity();
	sceGumTranslate( &pos );
	
	sceGumMatrixMode( GU_MODEL );
	ScePspFVector3 rot = { 0.0f, 0.0f, 0.0f };
	sceGumRotateXYZ( &rot );
}

void platform_postFrame() {
	sceGuFinish();
	sceGuSync( 0, 0 );

	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}

void platform_shutdown() {
	sceGuTerm();
	sceKernelExitGame();
}
