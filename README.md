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
- 此文件夹中为驱动墨水屏主要代码，包含了获取天气日期微博热搜等数据代码以及显示代码，需要使用arduino编译，编译之前注意头文件引用的库，没有的需要单独安装。<br>

- 代码需要修改每个get***.ino文件中的api地址，例如  


``` python
http.begin(Client, "http://日期.php");
``` 

中需要修改http后面地址，修改为你自己实际的地址，例如http://yoursit.com/time.php  

### html文件夹
- 此文件中包含了提交待办事件的上位机网页，将此文件上传到服务器Nginx的网站目录，域名解析到此目录后用域名访问  
- 文件夹中需要修改db.php中的  

``` PHP
$conn = new mysqli('你的服务器数据库地址', 'root', '数据库密码', '数据表名');
``` 
- 可以成功访问后会看到下图所示页面  
![image](jpg/微信截图_20230527181852.jpg)
- 页面中可以进行待办事件的添加、删除、标记为重要、取消重要、标记为已完成、标记为未完成等动作，每个动作都能实时同步到数据库中  

### PHP文件夹
- 此文件中为没有使用thinkPHP框架的PHP文件  
- todo.sql需要上传到MySQL数据库中  
- 一言的php对一言api进行了筛选优化，去掉了过于短或者过于长的句子，并给作者的前面加了破折号  
- 微博的php对微博api进行了筛选，只保留了热点事件跟后面的label部分，并且限制到只获取34条微博热搜  
- 宜忌的php限制了获取到的数据的字数，防止显示超出范围，php文件中的秘钥需要到https://market.topthink.com/my/api网站申请

### thinkphp6文件夹
- 此文件中的php文件需要放到thinkPHP框架中  
- 
