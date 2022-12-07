---
description: 本篇选读
---

# 超声波传感器HC-SR04

本文是有关流行的超声波传感器HC – SR04的指南。我们将解释其工作原理，向您展示其某些功能，并分享一个您可以遵循的Arduino项目示例，以将其集成到您的项目中。我们提供了有关如何连接超声波传感器的示意图，以及与Arduino一起使用的示例程序。



![](<../.gitbook/assets/image (7).png>)

## 描述

HC-SR04超声波传感器像蝙蝠一样使用声纳来确定到物体的距离。它以易于使用的包装提供出色的非接触范围检测，具有高精度和稳定的读数。它带有超声波发射器和接收器模块。



## 特征

以下是HC-SR04超声波传感器的一些功能和规格列表：

* 电源：+ 5V DC
* 静态电流：<2mA
* 工作电流：15mA
* 有效角度：<15°
* 测距距离：2cm – 400 cm / 1“ – 13ft
* 分辨率：0.3厘米
* 测量角度：30度
* 触发输入脉冲宽度：10uS
* 尺寸：45mm x 20mm x 15mm

## 它是如何工作的？

![](<../.gitbook/assets/image (5).png>)

超声波传感器使用声纳来确定到物体的距离。这是发生了什么：

1. 发射器（触发针）发送信号：高频声音。
2. 当信号找到一个物体时，它会被反射并…
3. ……发射器（回波引脚）接收它。

信号发送和接收之间的时间使我们能够计算到物体的距离。这是可能的，因为我们知道声音在空气中的速度。

## HC-SR04超声波传感器引脚

![](<../.gitbook/assets/image (3) (1) (1) (1) (1).png>)

引脚

* VCC：+ 5VDC
* Trig：触发（输入）
* Echo：回声（输出）
* GND：地线

## 带有HC的Arduino – SR04传感器

该传感器在Arduino修补匠中非常受欢迎。因此，在这里我们提供了有关如何在Arduino上使用HC-SR04超声波传感器的示例。在该项目中，超声波传感器在串行监视器中读取并写入到对象的距离。

该项目的目的是帮助您了解该传感器的工作原理。然后，您应该能够在自己的项目中使用此示例。

注意：有一个名为[NewPing](https://playground.arduino.cc/Code/NewPing)的Arduino库，可以在使用此传感器时使您的使用更轻松。

NewPing库：在[此处](https://bitbucket.org/teckel12/arduino-new-ping/get/master.zip)下载库。

## 所需零件

这是遵循下一个教程所需的部分的列表：

* Arduino UNO
* 超声波传感器（HC-SR04）
* 面包板
* 杜邦线

## 原理图

按照下一个示意图将HC-SR04超声波传感器连接到Arduino。

![](<../.gitbook/assets/image (1) (1).png>)

下表显示了您需要建立的连接：

| **超声波传感器HC-SR04** | **Arduino的** |
| ----------------- | ------------ |
| VCC               | 5伏           |
| 触发                | 销11          |
| 回声                | 针脚12         |
| 地线                | 地线           |

## 代码

将以下代码上传到您的Arduino IDE。

```
/*
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
```

## 代码如何工作

首先，您为触发和回显引脚创建变量，称为 TrigPin 和 回声针， 分别。触发引脚连接到数字 针脚11，并且回音针连接到数字 针脚12：

```
int trigPin = 11; 
int echoPin = 12;
```

您还将创建三个long类型的变量： 期间， 厘米和 英寸。这期间变量可节省发射和接收信号之间的时间。这 厘米 变量将以厘米为单位保存距离，并且 英寸 变量将以英寸为单位保存距离。

```
long duration, cm, inches;
```

在里面 setup()，以9600的波特率初始化串行端口，并将触发引脚设置为输出，并将回显引脚设置为输入。

```
//Serial Port begin
Serial.begin (9600);
//Define inputs and outputs
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
```

在里面 loop()，通过发送10微秒的HIGH脉冲来触发传感器。但是，在此之前，请提供一个短的LOW脉冲，以确保获得干净的HIGH脉冲：

```
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
```

然后，您可以从传感器读取信号-一个HIGH脉冲，其持续时间是从信号发送到接收到对象的回波之间的时间（以微秒为单位）。

```
duration = pulseIn(echoPin, HIGH);
```

最后，您只需要将持续时间转换为距离即可。我们可以使用以下公式计算距离：

> 距离=（传播时间/ 2）x声速
>
> 声音速度为：343m / s = 0.0343 cm / uS = 1 / 29.1 cm / uS或以英寸为单位：13503.9in / s = 0.0135in / uS = 1 / 74in / uS

我们需要将 传播时间 乘以2，因为我们必须考虑到声波已发送，撞击物体，然后返回到传感器。

```
cm = (duration/2) / 29.1;
inches = (duration/2) / 74;
```

最后，我们在串行监视器中打印结果：

```
Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();
```

##

##

## NewPing的源代码

您也可以使用NewPing库。文章最后面下载

安装NewPin库后，您可以上传下面提供的代码。

```
#include <NewPing.h>
 
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
 
void setup() {
   Serial.begin(9600);
}
 
void loop() {
   delay(50);
   unsigned int distance = sonar.ping_cm();
   Serial.print(distance);
   Serial.println("cm");
}
```

## 代码如何工作

使用NewPing库获取到对象的距离要简单得多。

首先包括NewPing库：

```
#include <NewPing.h>
```

然后，定义触发和回波引脚。触发引脚连接到Arduino数字针脚11，并回传到 针脚12。您还需要定义MAX\_DISTANCE 变量才能使用该库。

```
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200
```

然后，您创建一个 NewPing 实例称为 sonar：

```
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
```

在里面 setup()，则以9600的波特率初始化串行通信。

```
Serial.begin(9600);
```

最后，在 loop()，要获取距离，您只需使用 ping\_cm（） 上的方法 sonar目的。这将为您提供以厘米为单位的距离。

```
unsigned int distance = sonar.ping_cm();
```

如果您想获得以英寸为单位的距离，则可以使用 sonar.ping\_in（） 反而。

## 故障排除

注意：“如果HC-SR04没有收到回声，则输出永远不会变低。Devantec和Parallax传感器分别在36ms和28ms之后超时。如果您按上述方式使用Pulsin，则没有返回回显，程序将挂起1秒钟，这是Pulsin的默认超时时间。您需要使用timeout参数。

HC-SR04几乎无法工作到10英尺，因此总路径长度为20英尺，路径时间约为20ms，因此请将超时设置为25或30ms以上。

如果您在E和T之间放置一个电阻，比如说2k2，则仅连接到T，您可以仅从一个Arduino引脚使用HC-SR04。查找超声波传感器的单针操作。

另外，如果您将HC-SR04与PicAxe配合使用，则需要将时钟速度提高到至少8MHz，否则它们将看不到回波脉冲的开始，因此脉冲输入将永远不会开始。HC-SR04与BS2配合良好。”
