/**
  ******************************************************************************
  * @file    GUI_com.cpp
  * @author  cat_li
  * @brief   ���
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form
  * or means, without the prior written consent of shentq. This specification is
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gui_com.h"

void GUI_COM::show(){
  _state |= obj_State_Visible | obj_State_Update | obj_State_ReDraw;
}

void GUI_COM::hide(){
  _state &= ~obj_State_Visible;
  _state |= obj_State_Update;
}

void GUI_COM::setForeColor(E_COLOR c){ 
  _para.fc = c;
}
void GUI_COM::setBackColor(E_COLOR c){ 
  _para.bc = c;
}

void GUI_COM::_paraInit(uint16_t w,uint16_t h){
  _para.x = 0;
  _para.y = 0;
  _para.w = w;
  _para.h = h;
  _para.bc = C_WHITE;
  _para.fc = C_BLACK;
  _para.mode = DispMode_Normal;
}

void GUI_COM::getAvailiableArea(AREA_S *a){
	uint8_t d = ( _style & STYLE_3D ) ? 3 : 1;
	a->xs	= _para.x+d;
	a->ys = _para.y+d;
	a->xe = _para.w	+	a->xs	-	d;
	a->ye = _para.h	+	a->ys	-	d;
}

void TXT_COM::setTxt(char *s){
  _str = s;
  _state |= obj_State_Update;
}

void TXT_COM::setAlignMode(uint8_t align){
  _align = align;
  _state |= obj_State_Visible | obj_State_Update;
}

