/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.h                                               */
/*    Created:    18 July 2023                                                */
/*                         Github GCLab_GongChen                              */
/*    Revisions:  V1.03                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*————————————————————全局初始化————————————————————*/
#ifndef __SCREENPRINT_H__
#define __SCREENPRINT_H__
//--引用函数库
#include "vex.h"
/*————————————————底层区————————————————*/
//行文字打印
void LinePrint(int Row, int Line, int Mode = 1, char Name1[30] = "", float Value = 0, char Name2[30] = "");
//长方形绘制
//绘制带填充的长方形（起点X， 起点Y, X长度， Y长度， HUE颜色）
void RectDraw(int X1, int Y1, int XLong, int YLong, int Color);
//局部刷新（长方形）
//长方形清空（起点X， 起点Y, 终点X， 终点Y）
void RectClear(int X1, int Y1, int X2, int Y2);
//二次函数运算
//以二次函数的形式输出值
int FunctionOutput(float A, float B, float C, float Input);
/*————————————————功能区————————————————*/
//长方形二次函数缓动移动（起点X， 起点Y, X长度， Y长度， HUE颜色, A ,B, C）
//RectFunctionMove(20, 210, 20, 29, 125, -1, 2, 0);
void RectFunctionMove(int X1, int Y1, int XLong, int YLong, int ColorHue, float A, float B, float C);
//实时状态列表
int List(void);
//开屏界面
int Start(void);
#endif