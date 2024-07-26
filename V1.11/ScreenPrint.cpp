/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.cpp                                             */
/*    Author:     GongChen & ChenEnXiu                                        */
/*    Created:    26 July 2024                                                */
/*                                                                            */
/*    Revisions:  V1.11                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#define SPVersion 1.11
#define FrameWorkVersion 2.01
/*————————————————————全局初始化————————————————————*/
//--引用函数库
#include "vex.h"
#include "Control.h"
#include "v5_api.h"
#include "string"
using namespace vex;

//--定义全局变量
int RowLimit = 50;//行数限制
int RowAngle = 10;//滚轮转多少度换行
char FileName[5];
int Counter = 1;
//初始化
int RowChange = 0;

//Row-显示在第几行
//Line-首字母在第几列
//Name-提示信息
//Value-提示信息对应值
//Mode-显示模式-默认为1
// -打印提示信息改为0
// -打印提示信息+值为1
// -打印提示信息+值+提示信息改为2
void LinePrint(int Row, int Line, int Mode = 1, const char Name1[30] = "", float Value = 0, const char Name2[30] = "")
{
  if(Row+RowChange <= 12)
    {
      Brain.Screen.setCursor(Row+RowChange,Line);
      Brain.Screen.print(Name1);
      if(Mode == 1)
      {
        Brain.Screen.setCursor(Row+RowChange,Line+30);
        Brain.Screen.print(Value);
      }
      if(Mode == 2)
      {
        Brain.Screen.setCursor(Row+RowChange,Line+10);
        Brain.Screen.print(Value);
        Brain.Screen.setCursor(Row+RowChange,Line+18);
        Brain.Screen.print(Name2);
      }
    }
}

//绘制带填充的长方形（起点X， 起点Y, X长度， Y长度， HUE颜色）
void RectDraw(int X1, int Y1, int XLong, int YLong, int ColorHue)
{
  Brain.Screen.setFillColor(ColorHue);
  Brain.Screen.drawRectangle(X1,Y1,XLong,YLong);
}

//长方形清空（起点X， 起点Y, 终点X， 终点Y）
void RectClear(int X1, int Y1, int X2, int Y2)
{
  Brain.Screen.setFillColor(transparent);
  vexDisplayRectClear(X1,Y1,X2,Y2);
}

//以二次函数的形式输出值
float FunctionOutput(float A, float B, float C, float Input)
{
  float Output;
  Output = A * Input * Input +  B * Input + C;
  return Output;
}

//长方形二次函数缓动移动（起点X， 起点Y, X长度， Y长度， HUE颜色, A ,B, C）
//RectFunctionMove(20, 210, 20, 29, 125, -1, 2, 0);
void RectFunctionMove(int X1, int Y1, int XLong, int YLong, int ColorHue, float A, float B, float C)
{
  float Time = 0;
  float RunnerYDelta;
  float RunnerYDeltaLast;
  RunnerYDelta = 0;
  RunnerYDeltaLast = 0;
  while(1)
  {
    Time = Brain.Timer.value();
    RunnerYDelta = 100 * FunctionOutput(A, B, C, Time);
    RectDraw(X1,Y1-RunnerYDelta,XLong,YLong,ColorHue);
    if (RunnerYDelta > RunnerYDeltaLast)
    {
      RectClear(X1,Y1+YLong-RunnerYDeltaLast,X1+XLong,Y1+YLong-RunnerYDelta);
    }
    if (RunnerYDelta < RunnerYDeltaLast)
    {
      RectClear(X1,Y1-RunnerYDeltaLast,X1+XLong,Y1-RunnerYDelta);
    }
    RunnerYDeltaLast = RunnerYDelta;
    if (Time >= 5)
    {
      break;
    }
  }
}
//SD卡视频播放--EXPERIMENTAL FEATURE
int Video(void)
{
  uint8_t (pBuffer)[5];
  while(1)
  {
    sprintf(FileName,"%04d.png",Counter);
    Brain.SDcard.loadfile(FileName, pBuffer, 16384);
    wait(33,msec);
    Brain.Screen.drawImageFromBuffer(pBuffer,20,20,16384);
    Counter += 1;
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(Counter);
    if(Counter >= 6500)
    {
      Counter = 0;
    }
  }
  return 0;
}
//———————————————————————————功能区———————————————————————————————
int MainPrint(void)
{
  Brain.Screen.clearScreen();//清除之前的东西
  int LM1R = 8, LM2R = 9, LM3R = 10, RM1R = 3, RM2R = 4, RM3R = 5;//底盘电机端口号
  int Motor1R = 6, Motor2R = 7, Motor3R = 0, Motor4R = 0;//其他电机端口号,默认先填1和2
  int RowChange = 0, RowChangeLast = 0, Page = 0;
  int PressLock = 0, LastPressPosition = 0, SlideTime = 0, PressTime = 0;
  float TouchControl = 0, Last = 0, Control = 0, PhyTime = 0;
  int FreshLock = 0;
  Last = - (RowLimit - 12) * RowAngle;
  //存储池
  int LM1, LM2, LM3, RM1, RM2, RM3;
  int Motor1 , Motor2 , Motor3, Motor4;
  //由于API是从0端口开始定义的，所以需要减一
  Brain.Screen.setFont(monoM);
  //设置字体
  LM1 = LM1R - 1;
  LM2 = LM2R - 1;
  LM3 = LM3R - 1;
  RM1 = RM1R - 1;
  RM2 = RM2R - 1;
  RM3 = RM3R - 1;
  Motor1 = Motor1R - 1;
  Motor2 = Motor2R - 1;
  Motor3 = Motor3R - 1;
  Motor4 = Motor4R - 1;
  while(1)
  {
    Brain.Screen.setFillColor(transparent);
    if(FreshLock == 0)
    {
      RectClear(0,0,480,240);
      FreshLock = 1;
    }
    if(Page == 0)
    {
      //电池百分比计算
      float BatteryPercentage, BatteryLeft;
      BatteryLeft = Brain.Battery.voltage() - 11.00;
      BatteryPercentage = (BatteryLeft / 2.2) * 100;
      /*——————————————算法开始——————————————*/
      if(Brain.Screen.pressing() == 1 && PressLock == 0)
      {
        LastPressPosition = Brain.Screen.yPosition();
        SlideTime = Brain.Timer.value();
        PressLock = 1;
      }
      if(PressLock == 1 && Brain.Timer.value() - SlideTime > 0.1)
      {
        TouchControl = Brain.Screen.yPosition() - LastPressPosition;
        LastPressPosition = Brain.Screen.yPosition();
      }
      if(Brain.Screen.pressing() == 0)
      {
        PressLock = 0;
        TouchControl = 0;
        Control = Port21.position(degrees);//滚轮赋值
        if (Control  != 0)
        {
          RowChange = Control / RowAngle;//换行检测
          PhyTime = Brain.Timer.value();
        }
      }
      RowChange += TouchControl / 10;
      //上限检测
      if(RowChange > 0)
      {
        RowChange = 0;
        Port21.setPosition(0,degrees);
      }
      //下限检测
      if(RowChange + RowLimit < 12 && (TouchControl < 0 || Port21.position(degrees) < Last))
      {
        RowChange = 12 - RowLimit;
        Port21.setPosition(Last,degrees);
      }
        LinePrint(1+RowChange,1,0,"System Information");
        LinePrint(2+RowChange,5,1,"Std Framework Version",FrameWorkVersion);
        LinePrint(3+RowChange,5,1,"System Version",vexSystemVersion());
        LinePrint(4+RowChange,5,1,"SDK Version",vexSdkVersion());
        LinePrint(5+RowChange,5,1,"Stdlib Version",vexStdlibVersion());
        LinePrint(6+RowChange,5,1,"System Time",Brain.Timer.value());
        LinePrint(7+RowChange,5,1,"USB Connection Status",vexSystemUsbStatus());
      LinePrint(8+RowChange,1,0,"Battery Status");
        LinePrint(9+RowChange,5,1,"Battery Voltage(V)",Brain.Battery.voltage());
        LinePrint(10+RowChange,5,1,"Battery Percentage",BatteryPercentage);
        LinePrint(11+RowChange,5,1,"Battery Current(A)",Brain.Battery.current());
        LinePrint(12+RowChange,5,1,"Battery Temperature(.C)",vexBatteryTemperatureGet());
      LinePrint(13+RowChange,1,0,"Competition Status");
        LinePrint(14+RowChange,5,1,"Competition Status",vexCompetitionStatus());
        LinePrint(15+RowChange,5,1,"Battery Percentage",BatteryPercentage);
        LinePrint(16+RowChange,5,1,"Battery Current(A)",Brain.Battery.current());
        LinePrint(17+RowChange,5,1,"Battery Temperature(.C)",vexBatteryTemperatureGet());
      LinePrint(18+RowChange,1,0,"Motor Status");
      if(LM3 !=-1 && RM3 != -1)
      {
        LinePrint(19+RowChange,5,2,"MotorPort",LM1R,"Status");
          LinePrint(20+RowChange,10,1,"Temperature",vexMotorTemperatureGet(LM1));
          LinePrint(21+RowChange,10,1,"Current",vexMotorCurrentGet(LM1));
          LinePrint(22+RowChange,10,1,"Voltage",vexMotorVoltageGet(LM1));
        LinePrint(23+RowChange,5,2,"MotorPort",LM2R,"Status");
          LinePrint(24+RowChange,10,1,"Temperature",vexMotorTemperatureGet(LM2));
          LinePrint(25+RowChange,10,1,"Current",vexMotorCurrentGet(LM2));
          LinePrint(26+RowChange,10,1,"Voltage",vexMotorVoltageGet(LM2));
        LinePrint(27+RowChange,5,2,"MotorPort",LM3R,"Status");
          LinePrint(28+RowChange,10,1,"Temperature",vexMotorTemperatureGet(LM3));
          LinePrint(29+RowChange,10,1,"Current",vexMotorCurrentGet(LM3));
          LinePrint(30+RowChange,10,1,"Voltage",vexMotorVoltageGet(LM3));
        LinePrint(31+RowChange,5,2,"MotorPort",RM1R,"Status");
          LinePrint(32+RowChange,10,1,"Temperature",vexMotorTemperatureGet(RM1));
          LinePrint(33+RowChange,10,1,"Current",vexMotorCurrentGet(RM1));
          LinePrint(34+RowChange,10,1,"Voltage",vexMotorVoltageGet(RM1));
        LinePrint(35+RowChange,5,2,"MotorPort",RM2R,"Status");
          LinePrint(36+RowChange,10,1,"Temperature",vexMotorTemperatureGet(RM2));
          LinePrint(37+RowChange,10,1,"Current",vexMotorCurrentGet(RM2));
          LinePrint(38+RowChange,10,1,"Voltage",vexMotorVoltageGet(RM2));
        LinePrint(39+RowChange,5,2,"MotorPort",RM3R,"Status");
          LinePrint(40+RowChange,10,1,"Temperature",vexMotorTemperatureGet(RM3));
          LinePrint(41+RowChange,10,1,"Current",vexMotorCurrentGet(RM3));
          LinePrint(42+RowChange,10,1,"Voltage",vexMotorVoltageGet(RM3));
        LinePrint(43+RowChange,5,2,"MotorPort",Motor1R,"Status");
          LinePrint(44+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor1));
          LinePrint(45+RowChange,10,1,"Current",vexMotorCurrentGet(Motor1));
          LinePrint(46+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor1));
        LinePrint(47+RowChange,5,2,"MotorPort",Motor2R,"Status");
          LinePrint(48+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor2));
          LinePrint(49+RowChange,10,1,"Current",vexMotorCurrentGet(Motor2));
          LinePrint(50+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor2));
      }
      else if(RM3 == -1 && LM3 == -1)
      {
        LinePrint(19+RowChange,5,2,"MotorPort",LM1R,"Status");
          LinePrint(20+RowChange,10,1,"Temperature",vexMotorTemperatureGet(LM1));
          LinePrint(21+RowChange,10,1,"Current",vexMotorCurrentGet(LM1));
          LinePrint(22+RowChange,10,1,"Voltage",vexMotorVoltageGet(LM1));
        LinePrint(23+RowChange,5,2,"MotorPort",LM2R,"Status");
          LinePrint(24+RowChange,10,1,"Temperature",vexMotorTemperatureGet(LM2));
          LinePrint(25+RowChange,10,1,"Current",vexMotorCurrentGet(LM2));
          LinePrint(26+RowChange,10,1,"Voltage",vexMotorVoltageGet(LM2));
        LinePrint(27+RowChange,5,2,"MotorPort",RM1R,"Status");
          LinePrint(28+RowChange,10,1,"Temperature",vexMotorTemperatureGet(RM1));
          LinePrint(29+RowChange,10,1,"Current",vexMotorCurrentGet(RM1));
          LinePrint(30+RowChange,10,1,"Voltage",vexMotorVoltageGet(RM1));
        LinePrint(31+RowChange,5,2,"MotorPort",RM2R,"Status");
          LinePrint(32+RowChange,10,1,"Temperature",vexMotorTemperatureGet(RM2));
          LinePrint(33+RowChange,10,1,"Current",vexMotorCurrentGet(RM2));
          LinePrint(34+RowChange,10,1,"Voltage",vexMotorVoltageGet(RM2));
        LinePrint(35+RowChange,5,2,"MotorPort",Motor1R,"Status");
          LinePrint(36+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor1));
          LinePrint(37+RowChange,10,1,"Current",vexMotorCurrentGet(Motor1));
          LinePrint(38+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor1));
        LinePrint(39+RowChange,5,2,"MotorPort",Motor2R,"Status");
          LinePrint(40+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor2));
          LinePrint(41+RowChange,10,1,"Current",vexMotorCurrentGet(Motor2));
          LinePrint(42+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor2));
        LinePrint(43+RowChange,5,2,"MotorPort",Motor3R,"Status");
          LinePrint(44+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor3));
          LinePrint(45+RowChange,10,1,"Current",vexMotorCurrentGet(Motor3));
          LinePrint(46+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor3));
        LinePrint(47+RowChange,5,2,"MotorPort",Motor4R,"Status");
          LinePrint(48+RowChange,10,1,"Temperature",vexMotorTemperatureGet(Motor4));
          LinePrint(49+RowChange,10,1,"Current",vexMotorCurrentGet(Motor4));
          LinePrint(50+RowChange,10,1,"Voltage",vexMotorVoltageGet(Motor4));
      }
      wait(50,msec);
      RectClear(300,0,480,300);
      if(RowChangeLast != RowChange)
      {
        RectClear(0,0,480,240);
      }
      if (Brain.Screen.pressing() == 1 && Brain.Screen.xPosition() > 440 && Brain.Timer.value() - PressTime > 1)
      {
        RectClear(0,0,480,240);
        PressTime = Brain.Timer.value();
        Page = 1;
      }
      RowChangeLast = RowChange;
    }
    else if(Page == 1)
    {
      LinePrint(1,1,0,"About");
      LinePrint(2,5,0,"Author : GongChen & ChenEnXiu");
      LinePrint(3,1,0,"Package Version");
      LinePrint(4,5,1,"Screen Print Package Version",SPVersion);
      LinePrint(5,5,1,"Control Package Version",CVersion);
      LinePrint(6,5,1,"Std Framework Version",FrameWorkVersion);
      if(Brain.Screen.pressing() == 1 && Brain.Screen.xPosition() > 440 && Brain.Timer.value() - PressTime > 1)
      {
        RectClear(0,0,480,240);
        PressTime = Brain.Timer.value();
        Page = 0;
      }
    }
  }
  return 0;
}
//开屏界面
int Start()
{
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(transparent);
  RectClear(0,0,480,240);
  float Time;
  float RunnerYDelta = 0, RunnerY1Delta = 0, RunnerY2Delta = 0, RunnerY3Delta = 0, RunnerY4Delta = 0, RunnerY5Delta = 0;
  float RunnerY6Delta = 0, RunnerY7Delta = 0, RunnerY8Delta = 0, RunnerY9Delta = 0, RunnerY10Delta = 0, RunnerY11Delta = 0;
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setCursor(1,36);
  Brain.Screen.setFont(propM);
  Brain.Screen.print("SI YUAN");
  Brain.Screen.setCursor(3,35);
  Brain.Screen.print("ZHI KONG");
  Brain.Screen.setCursor(5,37);
  Brain.Screen.print("J D F Z");
  Brain.Timer.reset();//清零计时器
  while(1)
  {
    //时间赋值
    Time = Brain.Timer.value();
    
    RunnerYDelta = 100 * FunctionOutput(-1, 2, 0, Time);
    RectDraw(0,210-RunnerYDelta,20,30,125);
    RunnerY1Delta = 100 * FunctionOutput(-2, 3, 0.2, Time);
    RectDraw(20,210-RunnerY1Delta,20,30,300);
    RunnerY2Delta = 100 * FunctionOutput(-1.5, 4, 0.6, Time);
    RectDraw(40,210-RunnerY2Delta,20,30,195);
    RunnerY3Delta = 100 * FunctionOutput(-3, 1.8, 0.13, Time);
    RectDraw(60,210-RunnerY3Delta,20,30,274);
    RunnerY4Delta = 100 * FunctionOutput(-2, 3, 0.4, Time);
    RectDraw(80,210-RunnerY4Delta,20,30,164);
    RunnerY5Delta = 100 * FunctionOutput(-5, 1.8, 0.2, Time);
    RectDraw(100,210-RunnerY5Delta,20,30,285);
    RunnerY6Delta = 100 * FunctionOutput(-1, 2, 0.6, Time);
    RectDraw(120,210-RunnerY6Delta,20,30,346);
    RunnerY7Delta = 100 * FunctionOutput(-2, 4, 0.19, Time);
    RectDraw(140,210-RunnerY7Delta,20,30,12);
    RunnerY8Delta = 100 * FunctionOutput(-2, 2.4, 0.3, Time);
    RectDraw(160,210-RunnerY8Delta,20,30,95);
    RunnerY9Delta = 100 * FunctionOutput(-2, 1.8, 0.255, Time);
    RectDraw(180,210-RunnerY9Delta,20,30,49);
    RunnerY10Delta = 100 * FunctionOutput(-2, 2.9, 0.114514, Time);
    RectDraw(200,210-RunnerY10Delta,20,30,276);
    RunnerY11Delta = 100 * FunctionOutput(-2, 1.7, 0.1919810, Time);
    RectDraw(220,210-RunnerY11Delta,20,30,325);

    wait(10,msec);

    RectClear(0,210-RunnerYDelta,20,240-RunnerYDelta);
    RectClear(20,210-RunnerY1Delta,40,240-RunnerY1Delta);
    RectClear(40,210-RunnerY2Delta,60,240-RunnerY2Delta);
    RectClear(60,210-RunnerY3Delta,80,240-RunnerY3Delta);
    RectClear(80,210-RunnerY4Delta,100,240-RunnerY4Delta);
    RectClear(100,210-RunnerY5Delta,120,240-RunnerY5Delta);
    RectClear(120,210-RunnerY6Delta,140,240-RunnerY6Delta);
    RectClear(140,210-RunnerY7Delta,160,240-RunnerY7Delta);
    RectClear(160,210-RunnerY8Delta,180,240-RunnerY8Delta);
    RectClear(180,210-RunnerY9Delta,200,240-RunnerY9Delta);
    RectClear(200,210-RunnerY10Delta,220,240-RunnerY10Delta);
    RectClear(220,210-RunnerY11Delta,240,240-RunnerY11Delta);
    
    if (Time > 3)
    {
      Brain.Screen.setFillColor(transparent);
      break;
    }
  }
  //调用状态界面
  MainPrint();
  return 0;
}
//写着玩的，请插入SD卡并将四张图片命名为7001,7002,7003,7004
int YuanShenStart()
{
   uint8_t (fBuffer)[3000];
  Brain.SDcard.loadfile("7001.png", fBuffer, 32768);
  Brain.Screen.drawImageFromBuffer(fBuffer,0,0,32768);
  wait(300,msec);
  Brain.SDcard.loadfile("7002.png", fBuffer, 32768);
  Brain.Screen.drawImageFromBuffer(fBuffer,0,0,32768);
  wait(300,msec);
  Brain.SDcard.loadfile("7003.png", fBuffer, 32768);
  Brain.Screen.drawImageFromBuffer(fBuffer,0,0,32768);
  wait(300,msec);
  Brain.SDcard.loadfile("7004.png", fBuffer, 32768);
  Brain.Screen.drawImageFromBuffer(fBuffer,0,0,32768);
  wait(300,msec);
  Brain.Screen.setFillColor(transparent);
  MainPrint();
  return 0;
}