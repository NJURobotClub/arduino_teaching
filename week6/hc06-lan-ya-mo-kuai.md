# HC-06蓝牙模块

## 1.0 简介

### 1.1 基本概念

HC-05和HC-06是较为常用的两种蓝牙模块，二者区别在于HC-05是主从一体机，而HC-06只能工作在从机模式下。

主机：用于向从机下发指令，能够搜索从机并主动建立连接的一方。&#x20;

从机：用于接收主机下发的命令，不能主动建立连接，只能等别人连接自己。

主从一体：能够在主机和从机模式间切换，即可做主机也可作从机。

HC-05和HC-06的硬件相同，都采用CSR (Cambridge Silicon Radio) 公司的BC417143芯片，支持蓝牙2.1+EDR规范，只是芯片內部的控制程序不同。

本次实验采用HC-06。

### 1.2 引脚说明：

HC-06一共有4个引脚：

VCC接+5V供电（可由nano板的+5V输出）

GND接地

RXD为接收引脚（Receive），接nano板的数字引脚

TXD为发射引脚（Transmit），接nano板的数字引脚

<figure><img src="../.gitbook/assets/HC-06模块示意图.png" alt=""><figcaption></figcaption></figure>

### 1.3 AT模式

六引脚的HC-06模块还可以通过将EN使能端置高电平，从而进入AT模式，实现一些基础功能。但由于社团的HC-06模块均为四引脚，在这里不进行实验。如果感兴趣，可以自行将EN端引脚焊上进行测试。

<figure><img src="../.gitbook/assets/HC-06模块背面.png" alt=""><figcaption></figcaption></figure>

下面给出AT模式几条常用命令（中间的+不可省略）：

<figure><img src="../.gitbook/assets/HC-06 AT模式.png" alt=""><figcaption></figcaption></figure>



## 2.0实验材料

HC-06模块、nano板、USB线、手机一部

手机端串口通信软件（安卓端尽量选择app）：

微信小程序搜：HC蓝牙BLE串口助手（安卓、IOS通用）

安卓端app：HC蓝牙助手

{% file src="../.gitbook/assets/HC蓝牙助手.apk" %}

## 3.0实验步骤

## 4.0总结
