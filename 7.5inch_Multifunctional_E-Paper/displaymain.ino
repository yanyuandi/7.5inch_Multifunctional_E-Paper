#include "font.c"
void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void peiwang() {
  //display.clearScreen();
  display.setFullWindow();
  display.firstPage();   
  display.fillScreen(GxEPD_WHITE);
  do {  
    
  u8g2Fonts.setFont(logo_24_35);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  int16_t ww = (u8g2Fonts.getUTF8Width("Multifunctional E-Paper Desktop"));   
  u8g2Fonts.drawUTF8((800-ww)/2, 180, "Multifunctional E-Paper Desktop"); // 在透明背景上绘制文本

  u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
  int16_t aa = (u8g2Fonts.getUTF8Width("WIFI连接失败"));
  int16_t bb = (u8g2Fonts.getUTF8Width("请用手机或者笔记本连接下面wifi进行配网"));
  int16_t cc = (u8g2Fonts.getUTF8Width("SSID:桌面多功能E-paper"));
  int16_t dd = (u8g2Fonts.getUTF8Width("Design by YYD"));
  int16_t ee = (u8g2Fonts.getUTF8Width("配置成功后请耐心等待,获取到天气等所有数据后进行刷新"));


  text12("WIFI连接失败", (800-aa)/2, 230, GxEPD_BLACK, GxEPD_WHITE);  
  text12("请用手机或者笔记本连接下面wifi进行配网", (800-bb)/2, 253, GxEPD_BLACK, GxEPD_WHITE);  
  text12("SSID:桌面多功能E-paper", (800-cc)/2, 275, GxEPD_BLACK, GxEPD_WHITE);  
  text12("Design by YYD", (800-dd)/2, 451, GxEPD_BLACK, GxEPD_WHITE);  
  text12("配置成功后请耐心等待,获取到天气等所有数据后进行刷新", (800-ee)/2, 297, GxEPD_BLACK, GxEPD_WHITE);  

  } while (display.nextPage());
  display.powerOff();






}
void logo_show() {

  display.setFullWindow();
  display.firstPage(); 
  display.fillScreen(GxEPD_WHITE);
  do {
  
  display.drawInvertedBitmap(0, 0, logo_BW, 800, 480, GxEPD_BLACK);
  display.drawInvertedBitmap(0, 0, logo_R, 800, 480, GxEPD_RED);

  u8g2Fonts.setFontMode(1); // 设置透明模式
  u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2Fonts.setForegroundColor(GxEPD_WHITE);
  u8g2Fonts.drawUTF8(557, 462, "WIFI正在连接中......"); // 在透明背景上绘制文本



  } while (display.nextPage());
  display.powerOff();




}
void displaymain() {


    display.drawFastHLine(0, 78, 800, GxEPD_BLACK);
    display.drawFastHLine(0, 455, 800, GxEPD_BLACK);
    display.drawFastVLine(195, 24, 456, GxEPD_BLACK);
    display.drawFastVLine(586, 24, 431, GxEPD_BLACK);
    display.fillRect(0, 0, 800, 24, GxEPD_RED);
    display.fillRect(0, 456, 195, 25, GxEPD_BLACK);
    text12("桌面多功能E-Paper", 10, 7, GxEPD_WHITE, GxEPD_RED);
    display.drawBitmap(370, 3, dingmid, 80, 17, GxEPD_WHITE);
    display.drawInvertedBitmap(10, 462, weizhi, 9, 12, GxEPD_WHITE);
    text12("北京", 24, 462, GxEPD_WHITE, GxEPD_BLACK);

    //电量部分
    float voltage = read_battery_voltage();  // 读取电池电压
    float level = get_battery_level(voltage);  // 计算电量百分比
    // 使用 String 构造函数将 float 转换为 String
    String dianya = String(voltage, 2);  // 保留 2 位小数
    String dianliang2 = String(level, 0);  // 保留 2 位小数
    String dianliang = "电池电压:" + dianya + "V" + " " + "电量:" + dianliang2 + "%";
    const char* diandian = dianliang.c_str();
    text12(diandian, 56, 462, GxEPD_WHITE, GxEPD_BLACK);

    display.drawInvertedBitmap(326, 34, weiboBW, 131, 34, GxEPD_BLACK);
    display.drawInvertedBitmap(326, 34, weiboR, 131, 34, GxEPD_RED);

    display.drawInvertedBitmap(628, 34, daibanBW, 131, 34, GxEPD_BLACK);
    display.drawInvertedBitmap(628, 34, daibanR, 131, 34, GxEPD_RED);

    display.fillRoundRect(202, 460, 31, 16, 2, GxEPD_RED);
    text12("一言", 205, 462, GxEPD_WHITE, GxEPD_RED);

    display.drawInvertedBitmap(0, 278, yyd_bw, 161, 177, GxEPD_BLACK);
    display.drawInvertedBitmap(0, 278, yyd_r, 161, 177, GxEPD_RED);

    display.drawInvertedBitmap(592, 8, refresh, 14, 12, GxEPD_WHITE);
    time_t now = time(nullptr);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));
    //const char* timeChar = timeStr;
    String shijian = timeStr;
    String timesst = "更新于" + shijian;
    const char* timeChar = timesst.c_str();
    text12(timeChar, 610, 8, GxEPD_WHITE, GxEPD_RED);


   if (WiFi.status() == WL_CONNECTED) {
     display.drawBitmap(781, 8, digital_ok, 16, 13, GxEPD_WHITE);      

   } else {
     display.drawBitmap(781, 8, digital_no, 16, 13, GxEPD_WHITE);      
   }

}
