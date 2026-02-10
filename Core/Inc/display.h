/*
 * display.h
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "oled.h"

void display_init(void);
void display_welcom(void); //欢迎界面
void Face_Sleep(void);		//睡觉
void Face_Stare(void);		//瞪大眼
void Face_Happy(void);		//开心
void Face_Mania(void);  	//狂热
void Face_VeryHappy(void);  //非常开心
void Face_OpenEyes(void);   //睁眼
void Face_Xiaoxiao(void); //小小萌照

#endif /* INC_DISPLAY_H_ */
