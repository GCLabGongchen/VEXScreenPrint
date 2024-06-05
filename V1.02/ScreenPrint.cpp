/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.cpp                                             */
/*    Created:    12 July 2023                                                */
/*                         Github GCLab_GongChen                              */
/*    Revisions:  V1.02                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*————————————————————全局初始化————————————————————*/
//--引用函数库
#include "vex.h"
#include "Control.h"
#include "v5_api.h"
#include "string"
using namespace vex;

//--定义全局变量
int RowAngle = 20;
int RowLimit = 60;
int Page = 0;
int RowChange = 0;
//Row-显示在第几行
//Line-首字母在第几列
//Name-提示信息
//Value-提示信息对应值
//Mode-显示模式-默认为1
// -打印提示信息改为0
// -打印提示信息+值为1
// -打印提示信息+值+提示信息改为2
//
void LinePrint(int Row, int Line, int Mode = 1, char Name1[30] = "", float Value = 0, char Name2[30] = "")
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
int List(void)
{
  Brain.Screen.clearScreen();//清除之前的东西
  int LM1R = 2, LM2R = 3, LM3R = 0, RM1R = 7, RM2R = 8, RM3R = 0;//底盘电机端口号
  int Motor1R = 11, Motor2R = 20, Motor3R = 0, Motor4R = 0;//其他电机端口号,默认先填1和2
  int RowChange = 0, RowChangeLast = 0;
  float Last;
  //存储池
  int LM1, LM2, LM3, RM1, RM2, RM3;
  int Motor1 , Motor2 , Motor3, Motor4;
  //由于API是从0端口开始定义的，所以需要减一
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
    //电池百分比计算
    float BatteryPercentage, BatteryLeft;
    BatteryLeft = Brain.Battery.voltage() - 11.00;
    BatteryPercentage = (BatteryLeft / 2.2) * 100;
    /*——————————————算法开始——————————————*/
    float Control = Port21.position(degrees);//滚轮赋值
    RowChange = Control / RowAngle;//换行检测
    //上限检测
    if(RowChange > 0)
    {
      RowChange = 0;
      Port21.setPosition(0,degrees);
    }
    //下限检测
    if(RowChange + RowLimit == 12)
    {
      Last = Port21.position(degrees);
    }
    if(RowChange + RowLimit < 12)
    {
      RowChange = RowLimit - 12;
      Port21.setPosition(Last,degrees);
    }
    //显示开始
    LinePrint(1+RowChange,1,0,"System Information");
      LinePrint(2+RowChange,5,1,"Custom Package Version",Version);
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
    vexDisplayRectClear(300,0,450,300);
    if(RowChangeLast != RowChange)
    {
      Brain.Screen.clearScreen();
    }
    RowChangeLast = RowChange;
  }
  return 0;
}