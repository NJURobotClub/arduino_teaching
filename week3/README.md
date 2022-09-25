---
cover: ../.gitbook/assets/93172222_p0_master1200.jpg
coverY: 108.17120622568095
---

# Week3

## 一 任务

* 熟练arduino烧录程序步骤
* 学会使用超声波测距模块_HC-SR04_
* 利用超声波实现对键盘任意按键的控制

## 二 器材

* 超声波模块\*1
* Arduino Nano 板 \*1
* USB-micro数据线\*1
* 面板板、排针、杜邦线

## 三 模块介绍——HC-SR04

#### 1、Introduction

> HC-SR04超声波测距模块可提供**2cm-400cm**的非接触式距离感测功能，测距精度可高达3mm；

#### 2、 Basic

超声波模块基本工作原理如下：

> （1） 采用IO口“TRIG”触发测距（需给至少**10us**的高电平信号）；
>
> （2） 模块自动发送若干方波，自动监测是否有信号返回；
>
> （3） 若有信号返回，通过IO口“ECHO”输出一个高电平，其持续时间为超声波从发射到返回的时间。

Q1：若假设声速为340m/s，超声波返回时间为T，那么测量距离S为多少？

（See the answer below this page.）

## 四 模块应用实战

现在让我们一起来看看如何使用超声波模块吧！

### 1、初始化

首先我们先初始化管脚以及一些变量，此处我们选择了Nano芯片的第10、11管脚：

```c
const int trigPin1 = 11;   
const int echoPin1 = 10;    
long duration; //超声波返回的时间
int distance;  //距离

void setup() 
{
  Serial.begin(9600);    //初始化串口的通信波特率，无需理解 
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);   
}
```

> 有地方看不懂了？那就翻翻上周的代码吧！（Google也行）

### 2、主函数

我们先跳过处理超声波数据的函数，来看看我们的main函数（也就是loop函数）

```c
void loop()
{
  distance = 0;
  find_distance(); 
  Serial.print(distance); //打印distance到缓冲区
  Serial.print("\n");
  delay(250);
}
```

这里，我们用 find\_distance()来代表超声波信号处理函数，该函数会改变全局变量distance的值从而反馈给我们一个超声波测量的距离，然后我们将该值print出来。

```c
Serial.print(distance); //打印distance到缓冲区
```

注意这个函数，属于Arduino库自带函数。我们将括号里的变量输出到了输出缓冲区，在程序运行时可以打开软件的 “串口监视器” 进行查看，如下图（程序运行时该窗口也会自动跳出来）。

接下来，我们需要告诉超声波模块该工作了；并告诉nano板要准备接收来自超声波的信号，对返回的时间进行处理，最终计算出距离。

### 3、超声波信号处理函数

我们直接看看代码：

```c
void find_distance (void){ //返回距离以cm为单位 
  //给予超声波一个高电平
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);         //想想这里为啥是10us（上文提到过）
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 5000);// 让nano板接收超声波模块信号，并每次最多等5000us
  r = 0.34 * duration / 2;    
  distance = r / 100.00;
  delay(50);
}
```

这里一开始先给超声波一个高电平**HIGH**信号，然后用 **pulseIn()** 函数让nano板准备接收超声波返回的信号，该函数返回的单位为us。最后，我们通过简单计算得出distance的值。

Q2：pulseIn()函数里的 “5000” 代表的是nano板最多等待超声波模块5000us，如果超时，就返回0。那么我们的超声波模块这里设置的最大测距范围是多大？

（See the answer below this page.）

###

## 五\* 应用延伸：操控键盘

### 1、环境要求

通过上文的学习，我们已经可以将现实世界的信号转化为屏幕上的数字了。从现实到数字，这一步已经可以解决我们现实中的绝大多数问题。接下来，我们将通过一个简单小例子来迈出更大的一步：用超声波来隔空控制我们的键盘。（也许你已经在百团大战上玩过我们社团展台的该游戏了）

> 环境需求：Python3.6.0及以上
>
> 软件需求：任何的Python IDE都行（或者用系统自带的cmd） eg.Pycharm

Arduino

（本节实例演示均在Python 3.7 的 Pycharm2020 软件中运行）

> Tips：如果你的电脑还没有python环境，请参考如下网址进行配置：
>
> **https://www.runoob.com/python/python-install.html**

在安配置好python环境后，我们还需要安装几个本次实例需要用的package；

如果你是win10系统，请打开电脑的cmd命令行操作窗口（mac系统请在启动台中打开终端），依次键入如下命令进行安装.

```
pip install Serial
pip install pyautogui
pip install time
```

### 2、代码示例

目标：每当有物体在超声波模块上方**1cm—25cm**时，电脑自动按下**右键**，即"right"键.

First，我们先要打开 **Arduino IDE** 拷入以下代码进入nano板：

```c
/*
 * gesture control program for controlling certain functions in windows pc
 * Code by BalaAppu
 * Website: www.electronicshub.org
 */

const int trigPin = 11; 
const int echoPin = 10;  

long duration;                               
int distance; 
float r;

////////////////////////////////

void find_distance (void)                   
{ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 5000);
  r = 3.4 * duration / 2;                  
  distance = r / 100.00;
  delay(50);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  delay (1000);
    
}

void loop()
{
  distance = 0;
  find_distance(); 
  if(distance <= 25 && distance >= 1){ 
      Serial.write("right");
       Serial.print("\n");
  } 
  Serial.print(distance);
  Serial.print("\n");
  delay(250);
}
```

然后，需要在arduino界面找到你连接的端口号，这里我们示例的端口号为COM5.

接着，我们打开**任意的 Python IDE** 在电脑上运行如下python程序：

```python
from serial import Serial  
import pyautogui 
import time

Arduino_Serial = Serial('COM5', 9600)  //这里的COM请在

while 1:
    incoming_data = str(Arduino_Serial.readline())  # read the serial data and print it as line
    print(incoming_data)  # print the incoming Serial data

    if 'left' in incoming_data:
        pyautogui.keyDown('left')
        time.sleep(0.1)
        pyautogui.keyUp('left')
    elif 'right' in incoming_data:
        pyautogui.keyDown('right')
        time.sleep(0.1)
        pyautogui.keyUp('right')

    incoming_data = ""  # clears the data
```

试试看！将手放在超声波上，让后鼠标点击任意一段文字，就可以发现电脑的光标在不断右移。

### 3、延伸思考

如果我们想完成对其他按键的控制该如何修改？

没错！只需要将拷入nano板代码中的 \*\*Serial.write("right")\*\*函数参数改成你想要的按键就行了！

那多个按键的控制？只需要添加多个超声波，代码和参数稍作CRTL+C/V即可实现！

> 试试看！去4399找个单按键的小游戏玩玩！
>
> 如果断网，可以选择Chrome浏览器中的自带小恐龙游戏（ Chrome中输入_chrome_://_dino_/，空格键操控）。
>
> 如果你觉得反应不灵敏，可以尝试着调节代码中的delay()函数的时间，以获取更好的游戏体验。

参考答案

A1: S = 340 \* T / 2

A2：MAX\_distance = 340 \* 0.005 / 2= 0.85m
