
#include "StdTypes.h"
#include "MATH_Functions.h"
#include "LCD_Interface.h"
s16 MATH_Functions_Interpolation (u16 num,s16 x1,s16 y1,s16 x2,s16 y2)
{
	s16 inter_result;
	s16 slope=(((s32)(y2-y1)*100)/(x2-x1));

	s16 y_intercept = y1-(slope*((s32)x1))/100;

	inter_result=((slope*((s32)num))/100)+y_intercept;
	
	return inter_result;
}