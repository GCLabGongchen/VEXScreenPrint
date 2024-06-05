/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     ScreenPrint.cpp                                             */
/*    Created:    15 June 2023                                                */
/*                         Github GCLab_GongChen                              */
/*    Revisions:  V0.01                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*_____________PrintScreen Package Version：0.01_______________*/
/*————————————————————全局初始化————————————————————*/
//--引用函数库
#include "vex.h"
using namespace vex;
//--定义全局变量
int Rowangle = 20;
int Rowlimit = 47;
int Print(void)
{

  int LM1 = 11, LM2 = 12, LM3 = 13, RM1 = 1, RM2 = 2, RM3 = 3;//底盘电机端口号
  int Motor1 = 4, Motor2 = 5, Motor3 = 6, Motor4 = 7;//其他电机端口号
  int Rowchange = 0, Lastrowchange = 0;
  float Last;
  while(1)
  {
    /*——————————————检测值定义区——————————————*/
    float Value2 = Brain.Battery.temperature(percent);
    float Value3 = Brain.Battery.voltage();
    float Value4 = Brain.Battery.current();
    float Value6 = Brain.Timer.value();
    float Value9 = vexMotorTemperatureGet(LM1);
    float Value10 = vexMotorCurrentGet(LM1);
    float Value11 = vexMotorVoltageGet(LM1);
    float Value13 = vexMotorTemperatureGet(LM2);
    float Value14 = vexMotorCurrentGet(LM2);
    float Value15 = vexMotorVoltageGet(LM2);
    float Value17 = vexMotorTemperatureGet(LM3);
    float Value18 = vexMotorCurrentGet(LM3);
    float Value19 = vexMotorVoltageGet(LM3);
    float Value21 = vexMotorTemperatureGet(RM1);
    float Value22 = vexMotorCurrentGet(RM1);
    float Value23 = vexMotorVoltageGet(RM1);
    float Value25 = vexMotorTemperatureGet(RM2);
    float Value26 = vexMotorCurrentGet(RM2);
    float Value27 = vexMotorVoltageGet(RM2);
    float Value29 = vexMotorTemperatureGet(RM3);
    float Value30 = vexMotorCurrentGet(RM3);
    float Value31 = vexMotorVoltageGet(RM3);
    float Value33 = vexMotorTemperatureGet(Motor1);
    float Value34 = vexMotorCurrentGet(Motor1);
    float Value35 = vexMotorVoltageGet(Motor1);
    float Value37 = vexMotorTemperatureGet(Motor2);
    float Value38 = vexMotorCurrentGet(Motor2);
    float Value39 = vexMotorVoltageGet(Motor2);
    float Value41 = vexMotorTemperatureGet(Motor3);
    float Value42 = vexMotorCurrentGet(Motor3);
    float Value43 = vexMotorVoltageGet(Motor3);
    float Value45 = vexMotorTemperatureGet(Motor4);
    float Value46 = vexMotorCurrentGet(Motor4);
    float Value47 = vexMotorVoltageGet(Motor4);
    /*——————————————算法开始——————————————*/
    float Control = port21.position(degrees);//滚轮赋值
    Rowchange = Control / Rowangle;//换行检测
    //上限检测
    if(Rowchange > 0)
    {
      Rowchange = 0;
      port21.setPosition(0,degrees);
    }
    //
    if(Rowchange + Rowlimit == 12)
    {
      Last = port21.position(degrees);
    }
    if(Rowchange + Rowlimit < 12)
    {
      Rowchange = Rowlimit - 12;
      port21.setPosition(Last,degrees);
    }
    //显示开始
    if(Rowchange != Lastrowchange)
    {
      Brain.Screen.clearScreen();
    }
    if(1+Rowchange <= 12)
    {
      Brain.Screen.setCursor(1+Rowchange,1);
      Brain.Screen.print("BATTERY STATUS");
    }
    if(2+Rowchange <= 12)
    {
      Brain.Screen.setCursor(2+Rowchange,5);
      Brain.Screen.print("Battery Temperature");
      Brain.Screen.setCursor(2+Rowchange,5+30);
      Brain.Screen.print(Value2);
    }
    if(3+Rowchange <= 12)
    {
      Brain.Screen.setCursor(3+Rowchange,5);
      Brain.Screen.print("Battery Voltage");
      Brain.Screen.setCursor(3+Rowchange,5+30);
      Brain.Screen.print(Value3);
    }
    if(4+Rowchange <= 12)
    {
      Brain.Screen.setCursor(4+Rowchange,5);
      Brain.Screen.print("Battery Current");
      Brain.Screen.setCursor(4+Rowchange,5+30);
      Brain.Screen.print(Value4);
    }
    if(5+Rowchange <= 12)
    {
      Brain.Screen.setCursor(5+Rowchange,1);
      Brain.Screen.print("BRAIN STATUS");
    }
    if(6+Rowchange <= 12)
    {
      Brain.Screen.setCursor(6+Rowchange,5);
      Brain.Screen.print("Brain Timer");
      Brain.Screen.setCursor(6+Rowchange,5+30);
      Brain.Screen.print(Value6);
    }
    if(7+Rowchange <= 12)
    {
      Brain.Screen.setCursor(7+Rowchange,1);
      Brain.Screen.print("MOTOR STATUS");
    }
    if(8+Rowchange <= 12)
    {
      Brain.Screen.setCursor(8+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(8+Rowchange,10);
      Brain.Screen.print(LM1);
      Brain.Screen.setCursor(8+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(9+Rowchange <= 12)
    {
      Brain.Screen.setCursor(9+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(9+Rowchange,10+30);
      Brain.Screen.print(Value9);
    }
    if(10+Rowchange <= 12)
    {
      Brain.Screen.setCursor(10+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(10+Rowchange,10+30);
      Brain.Screen.print(Value10);
    }
    if(11+Rowchange <= 12)
    {
      Brain.Screen.setCursor(11+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(11+Rowchange,10+30);
      Brain.Screen.print(Value11);
    }
    if(12+Rowchange <= 12)
    {
      Brain.Screen.setCursor(12+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(12+Rowchange,10);
      Brain.Screen.print(LM2);
      Brain.Screen.setCursor(12+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(13+Rowchange <= 12)
    {
      Brain.Screen.setCursor(13+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(13+Rowchange,10+30);
      Brain.Screen.print(Value13);
    }
    if(14+Rowchange <= 12)
    {
      Brain.Screen.setCursor(14+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(14+Rowchange,10+30);
      Brain.Screen.print(Value14);
    }
    if(15+Rowchange <= 12)
    {
      Brain.Screen.setCursor(15+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(15+Rowchange,10+30);
      Brain.Screen.print(Value15);
    }
    if(16+Rowchange <= 12 && LM3 != 0)
    {
      Brain.Screen.setCursor(16+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(16+Rowchange,10);
      Brain.Screen.print(LM3);
      Brain.Screen.setCursor(16+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(17+Rowchange <= 12 && LM3 != 0)
    {
      Brain.Screen.setCursor(17+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(17+Rowchange,10+30);
      Brain.Screen.print(Value17);
    }
    if(18+Rowchange <= 12 && LM3 != 0)
    {
      Brain.Screen.setCursor(18+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(18+Rowchange,10+30);
      Brain.Screen.print(Value18);
    }
    if(19+Rowchange <= 12 && LM3 != 0)
    {
      Brain.Screen.setCursor(19+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(19+Rowchange,10+30);
      Brain.Screen.print(Value19);
    }
    if(20+Rowchange <= 12)
    {
      Brain.Screen.setCursor(20+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(20+Rowchange,10);
      Brain.Screen.print(RM1);
      Brain.Screen.setCursor(20+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(21+Rowchange <= 12)
    {
      Brain.Screen.setCursor(21+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(21+Rowchange,10+30);
      Brain.Screen.print(Value21);
    }
    if(22+Rowchange <= 12)
    {
      Brain.Screen.setCursor(22+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(22+Rowchange,10+30);
      Brain.Screen.print(Value22);
    }
    if(23+Rowchange <= 12)
    {
      Brain.Screen.setCursor(23+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(23+Rowchange,10+30);
      Brain.Screen.print(Value23);
    }
    if(24+Rowchange <= 12)
    {
      Brain.Screen.setCursor(24+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(24+Rowchange,10);
      Brain.Screen.print(RM2);
      Brain.Screen.setCursor(24+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(25+Rowchange <= 12)
    {
      Brain.Screen.setCursor(25+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(25+Rowchange,10+30);
      Brain.Screen.print(Value25);
    }
    if(26+Rowchange <= 12)
    {
      Brain.Screen.setCursor(26+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(26+Rowchange,10+30);
      Brain.Screen.print(Value26);
    }
    if(27+Rowchange <= 12)
    {
      Brain.Screen.setCursor(27+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(27+Rowchange,10+30);
      Brain.Screen.print(Value27);
    }
    if(28+Rowchange <= 12 && RM3 != 0)
    {
      Brain.Screen.setCursor(28+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(28+Rowchange,10);
      Brain.Screen.print(RM3);
      Brain.Screen.setCursor(28+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(29+Rowchange <= 12 && RM3 != 0)
    {
      Brain.Screen.setCursor(29+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(29+Rowchange,10+30);
      Brain.Screen.print(Value29);
    }
    if(30+Rowchange <= 12 && RM3 != 0)
    {
      Brain.Screen.setCursor(30+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(30+Rowchange,10+30);
      Brain.Screen.print(Value30);
    }
    if(31+Rowchange <= 12 && RM3 != 0)
    {
      Brain.Screen.setCursor(31+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(31+Rowchange,10+30);
      Brain.Screen.print(Value31);
    }
    if(32+Rowchange <= 12 && Motor1 != 0)
    {
      Brain.Screen.setCursor(32+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(32+Rowchange,10);
      Brain.Screen.print(Motor1);
      Brain.Screen.setCursor(32+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(33+Rowchange <= 12 && Motor1 != 0)
    {
      Brain.Screen.setCursor(33+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(33+Rowchange,10+30);
      Brain.Screen.print(Value33);
    }
    if(34+Rowchange <= 12 && Motor1 != 0)
    {
      Brain.Screen.setCursor(34+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(34+Rowchange,10+30);
      Brain.Screen.print(Value34);
    }
    if(35+Rowchange <= 12 && Motor1 != 0)
    {
      Brain.Screen.setCursor(35+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(35+Rowchange,10+30);
      Brain.Screen.print(Value35);
    }if(36+Rowchange <= 12 && Motor2 != 0)
    {
      Brain.Screen.setCursor(36+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(36+Rowchange,10);
      Brain.Screen.print(Motor2);
      Brain.Screen.setCursor(36+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(37+Rowchange <= 12 && Motor2 != 0)
    {
      Brain.Screen.setCursor(37+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(37+Rowchange,10+30);
      Brain.Screen.print(Value37);
    }
    if(38+Rowchange <= 12 && Motor2 != 0)
    {
      Brain.Screen.setCursor(38+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(38+Rowchange,10+30);
      Brain.Screen.print(Value38);
    }
    if(39+Rowchange <= 12 && Motor2 != 0)
    {
      Brain.Screen.setCursor(39+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(39+Rowchange,10+30);
      Brain.Screen.print(Value39);
    }if(40+Rowchange <= 12 && Motor3 != 0)
    {
      Brain.Screen.setCursor(40+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(40+Rowchange,10);
      Brain.Screen.print(Motor3);
      Brain.Screen.setCursor(40+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(41+Rowchange <= 12 && Motor3 != 0)
    {
      Brain.Screen.setCursor(41+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(41+Rowchange,10+30);
      Brain.Screen.print(Value41);
    }
    if(42+Rowchange <= 12 && Motor3 != 0)
    {
      Brain.Screen.setCursor(42+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(42+Rowchange,10+30);
      Brain.Screen.print(Value42);
    }
    if(43+Rowchange <= 12 && Motor3 != 0)
    {
      Brain.Screen.setCursor(43+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(43+Rowchange,10+30);
      Brain.Screen.print(Value43);
    }if(44+Rowchange <= 12 && Motor4 != 0)
    {
      Brain.Screen.setCursor(44+Rowchange,5);
      Brain.Screen.print("Port");
      Brain.Screen.setCursor(44+Rowchange,10);
      Brain.Screen.print(Motor4);
      Brain.Screen.setCursor(44+Rowchange,13);
      Brain.Screen.print("Status");
    }
    if(45+Rowchange <= 12 && Motor4 != 0)
    {
      Brain.Screen.setCursor(45+Rowchange,10);
      Brain.Screen.print("Temperature");
      Brain.Screen.setCursor(45+Rowchange,10+30);
      Brain.Screen.print(Value45);
    }
    if(46+Rowchange <= 12 && Motor4 != 0)
    {
      Brain.Screen.setCursor(46+Rowchange,10);
      Brain.Screen.print("Current");
      Brain.Screen.setCursor(46+Rowchange,10+30);
      Brain.Screen.print(Value46);
    }
    if(47+Rowchange <= 12 && Motor4 != 0)
    {
      Brain.Screen.setCursor(47+Rowchange,10);
      Brain.Screen.print("Voltage");
      Brain.Screen.setCursor(47+Rowchange,10+30);
      Brain.Screen.print(Value47);
    }

    Lastrowchange = Rowchange;
  }
  return 0;
}