/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.h                                               */
/*    Created:    26 July 2023                                                */
/*                         Github GCLab_GongChen                              */
/*    Revisions:  V1.06                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*————————————————————全局初始化————————————————————*/
#ifndef __SCREENPRINT_H__
#define __SCREENPRINT_H__
//--引用函数库
#include "vex.h"
/*————————————————————命令使用提示————————————————————*/
/*LinePrint(从上向下数第几行, 从左往右数第几列, 打印模式-见下方 默认为1, 提示信息1, 传入值, 提示信息2)    :行文字打印*/
/*RectDraw(起点X, 起点Y ，X方向长度, Y方向长度, 填充颜色HUE值)                                        :长方形绘制-绘制带填充的长方形*/
/*RectClear(起点X, 起点Y, 终点X, 终点Y)                                                             :局部刷新(长方形)-长方形清空*/
/*FunctionOutput(二次函数a, 二次函数b, 二次函数c, 二次函数自变量输入x)                                 ：二次函数运算-以二次函数的形式输出值*/
/*RectFunctionMove(起点X, 起点Y ，X方向长度, Y方向长度, 填充颜色HUE值, 二次函数a, 二次函数b, 二次函数c) ：以二次函数的变化情况使长方体移动*/
/*List()                                                                                           :作为线程使用, 车辆实时状态界面*/
/*Start()                                                                                          :作为线程使用, 开屏界面，结束后接实时状态界面*/


/*————————————————底层区————————————————*/
//行文字打印
void LinePrint(int Row, int Line, int Mode = 1, const char Name1[30] = "", float Value = 0, const char Name2[30] = "");
/*—————————————打印模式———————————————*/
// -打印提示信息改为0
// -打印提示信息+值为1
// -打印提示信息+值+提示信息改为2
/*———————————————————————————————————*/
//长方形绘制-绘制带填充的长方形
void RectDraw(int X1, int Y1, int XLong, int YLong, int Color);
//局部刷新(长方形)-长方形清空
void RectClear(int X1, int Y1, int X2, int Y2);
//二次函数运算-以二次函数的形式输出值
int FunctionOutput(float A, float B, float C, float Input);


/*————————————————功能区————————————————*/
int Video(void);
int Video2(void);
//长方形二次函数缓动移动(起点X， 起点Y, X长度， Y长度， HUE颜色, A ,B, C)
//示例-RectFunctionMove(20, 210, 20, 29, 125, -1, 2, 0);
void RectFunctionMove(int X1, int Y1, int XLong, int YLong, int ColorHue, float A, float B, float C);
//实时状态列表
int List(void);
//开屏界面
int Start(void);
#endif