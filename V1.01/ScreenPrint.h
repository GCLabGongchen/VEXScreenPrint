/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.h                                               */
/*    Created:    12 July 2023                                                */
/*                         Github GCLab_GongChen                              */
/*    Revisions:  V1.01                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*————————————————————全局初始化————————————————————*/
#ifndef __SCREENPRINT_H__
#define __SCREENPRINT_H__
//--引用函数库
#include "vex.h"
//--Print
void LinePrint(int Row, int Line, int Mode = 1, char Name1[30] = "", float Value = 0, char Name2[30] = "");
int List(void);
//int Test(float StartX, float StartY, float DestX, float DestY, float XLong, float YLong);
#endif