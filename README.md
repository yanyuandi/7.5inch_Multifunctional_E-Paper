## 桌面多功能E-paper
![image](jpg/109A0671.jpg)

### 项目简介
此项目使用ESP32驱动7.5寸三色墨水屏显示丰富的信息，如果感兴趣，请继续阅读，下文介绍如何使用此项目代码<br>
- **B站视频演示地址：[点击观看视频](https://www.baidu.com/)**<br>
- <a target="_blank" href="https://qm.qq.com/cgi-bin/qm/qr?k=OCk2mwPC4yZn-BBJlH2ehWT-2sHfC7Os&jump_from=webapi&authKey=iFtohDmv6OI7O5aD/0ogd6mODvY5vr837fherj6ruuDCK94UM5KrjicZ2cFO5dHB"><img border="0" src="http://pub.idqqimg.com/wpa/images/group.png" alt="墨水屏DIY交流群" title="墨水屏DIY交流群"></a>QQ交流群：1051455459


### 需要的环境
- 一个远程服务器，需要安装LNMP环境，同时安装thinkPHP6.1
- 一个域名，用来转化各种api以及访问更新待办事件的上位机页面
- Arduino IDE

### 使用的硬件
- ESP32 WROVER开发板以及屏幕转接板 （闲鱼搜记得带马扎 可以购买现成pcb）
- 一块7.5寸三色墨水屏（使用GxEPD2_750c_Z08驱动）
- 3.7v锂电池

### 7.5inch_Multifunctional_E-Paper文件夹
此文件夹中为驱动墨水屏主要代码，包含了
