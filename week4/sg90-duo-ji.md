# SG90舵机

### 1.0 简介

舵机：是一种**位置（角度）伺服**的驱动器，适用于那些需要角度不断变化并可以保持的伺服控制系统。在高档遥控玩具，如飞机、潜艇模型，遥控机器人中已经得到了普遍应用。本篇通过**官方驱动库和自定义函数**来实现舵机控制。

![舵机结构](https://img-blog.csdnimg.cn/20210207094120658.jpg?x-oss-process=image/watermark,type\_ZmFuZ3poZW5naGVpdGk,shadow\_10,text\_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1ZPUjIzNA==,size\_16,color\_FFFFFF,t\_70#pic\_center)

外形结构：主要是由外壳、无核心马达、四级减速齿轮、电路板和位置检测器所构成。

工作原理：

![工作原理](https://img-blog.csdnimg.cn/20210207135457109.gif#pic\_center)

其工作原理是由接收机或者单片机发出信号给舵机，其内部有一个基准电路，产生周期为20ms，宽度为1.5ms 的基准信号，将获得的直流偏置电压与电位器的电压比较，获得电压差输出。经由电路板上的IC 判断转动方向，再驱动无核心马达开始转动，透过减速齿轮将动力传至摆臂，同时由位置检测器送回信号，判断是否已经到达定位。

![PWM波](https://img-blog.csdnimg.cn/20210207094959632.jpg?x-oss-process=image/watermark,type\_ZmFuZ3poZW5naGVpdGk,shadow\_10,text\_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1ZPUjIzNA==,size\_16,color\_FFFFFF,t\_70#pic\_center)

舵机转动的角度是通过调节PWM「脉冲宽度调制」信号的占空比来实现的。标准的PWM信号的周期固定为20ms，理论上脉宽分布应该在1ms到2ms之间，实际上可由0.5ms到2.5ms之间，脉宽与转角0°—180°相对应。不同厂家不同型号的舵机也会有所差异。

SG90舵机（180°）相关参数见下表：

![参数表](https://img-blog.csdnimg.cn/2021020715034532.png?x-oss-process=image/watermark,type\_ZmFuZ3poZW5naGVpdGk,shadow\_10,text\_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1ZPUjIzNA==,size\_16,color\_FFFFFF,t\_70#pic\_center)

### 2.0 实验材料

Arduino Uno R3开发板 USB数据线 三根公母线 SG90舵机 一台安装Arduino开发环境的电脑

### 3.0 实验步骤

#### 3.1 根据原理图搭建电路

舵机红色线接开发板5V，棕色线接开发板GND，橙色信号线接开发板数字引脚10。

#### 3.2 新建sketch，拷贝如下代码并进行保存编译上传

代码1：

```
#include <Servo.h>            // 调用Servo库

Servo myservo;             // 定义Servo对象来控制
int pos=0;    
void setup(){
  myservo.attach(10);          // 控制线连接数字10
}

void loop(){
  for (pos = 0; pos <= 180; pos ++) {   // 0°到180°
    // in steps of 1 degree
    myservo.write(pos);               // 舵机角度写入
    delay(5);                         // 控制移动速度
  }
  for (pos = 180; pos >= 0; pos --) {   // 从180°到0°
    myservo.write(pos);               // 舵机角度写入
    delay(5);                         // 控制移动速度
  }
}
```

代码2：

```
int servopin = 10; //设置舵机驱动脚到数字口10
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;
void servopulse(int servopin, int myangle) /*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(servopin, HIGH); //将舵机接口电平置高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin, LOW); //将舵机接口电平置低
  delay(20 - pulsewidth / 1000); //延时周期内剩余时间
}
void setup()
{
  pinMode(servopin, OUTPUT); //设定舵机接口为输出接口
  Serial.begin(9600);//设置波特率为9600
  Serial.println("servo=o_seral_simple ready" ) ;
}
void loop()//将0 到9 的数转化为0 到180 角度，并让LED 闪烁相应数的次数
{
  val = Serial.read(); //读取串口收到的数据
  if (val >= '0' && val <= '9') //判断收到数据值是否符合范围
  {
    val = val - '0'; //将ASCII码转换成数值，例'9'-'0'=0x39-0x30=9
    val = val * (180 / 9); //将数字转化为角度，例9*（180/9）=180
    Serial.print("moving servo to ");
    Serial.print(val, DEC);
    Serial.println();
    for (int i = 0; i <= 50; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, val); //引用脉冲函数
    }
  }
}      
```

### 3.3 实验现象

### 4.0 总结

用Arduino 控制舵机的方法有两种，代码1是直接利用Arduino 自带的Servo 函数进行舵机的控制，这种控制方法的优点在于程序编写，缺点是只能控制2 路舵机，因为Arduino 自带函数只能利用数字9、10 接口。代码2是通过Arduino 的普通数字传感器接口产生占空比不同的方波，模拟产生PWM 信号进行舵机定位，控制原理更加清晰。\
Arduino 的驱动能力有限，所以当需要控制1 个以上的舵机时需要外接电源。
