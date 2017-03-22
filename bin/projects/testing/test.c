#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"

bool fpsbool = false;
int fpsgrab = 0;
int fps = 25;
int FrameCountPre;
int FrameCount;
 
void main(){
	
	char dest[16] = "";
	
	stradd(&dest, "hello", 16);
	
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	SETTIMERA(0);
	while(true){
		WAIT(0);
		if(TIMERA() <= 500 ){
			if(!fpsbool){
				fpsgrab = TIMERA();
				fpsbool = true;
				FrameCountPre = GET_FRAME_COUNT();
			}
		}
		if(TIMERA() >= 1000 + fpsgrab){
			if(fpsbool){
				fpsbool = false;
				FrameCount = GET_FRAME_COUNT();
				fps = FrameCount - FrameCountPre;
				SETTIMERA(0);
			}
		}
		DRAW_CURVED_WINDOW(0.034f, 0.032f, 0.054f, 0.057f, 200);
		SET_TEXT_SCALE(0.35, 0.35);
		SET_TEXT_COLOUR(240,160,0, 255);
		SET_TEXT_DROPSHADOW(0, 255, 255, 255, 255);
		DISPLAY_TEXT_WITH_NUMBER(0.05f, 0.05f, "NUMBER",fps);
	}
}
	
