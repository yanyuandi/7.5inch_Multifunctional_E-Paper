#include <GxEPD2_3C.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <WiFiManager.h>
#include "jpg.h"
#include <ArduinoJson.h>
#include <OneButton.h>
#include <driver/adc.h>
#include "esp_adc_cal.h"

#define BATTERY_PIN ADC1_CHANNEL_3  // 电池电压采样引脚
#define R1 220000.0                 // 电阻R1的阻值，单位为欧姆
#define R2 100000.0                 // 电阻R2的阻值，单位为欧姆
#define V_MIN 3.3                   // 电池电压最小值，单位为伏特
#define V_MAX 4.2                   // 电池电压最大值，单位为伏特


#define NORMAL_FONT u8g2_font_wqy16_t_gb2312  //设置NORMAL_FONT默认字体

#define TZ 8      // 时区偏移值，以 UTC+8 为例
#define DST_MN 0  // 夏令时持续时间（分钟）

#define TZ_SEC ((TZ)*3600)     // 时区偏移值（秒）
#define DST_SEC ((DST_MN)*60)  // 夏令时持续时间（秒）

#define REFRESH_BUTTON_PIN 34
OneButton REFRESHButton(REFRESH_BUTTON_PIN, true);

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT / 2> display(GxEPD2_750c_Z08(/*CS=D8*/ 4, /*DC=D3*/ 27, /*RST=D4*/ 26, /*BUSY=D2*/ 25)); 
void yiyan_get();
void refresh_all();
void refresh_10s();
void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("开始配网");
  peiwang();
}
void REFRESHButtonClick() {
 
  Serial.println("开始刷新");
  refresh_all();
}

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);  // 设置ADC分辨率为12位

  SPI.end();  
  SPI.begin(13, 14, 14, 4); 

  display.init(115200, true, 2, false);
  display.setRotation(0);  //  0 是横向
  u8g2Fonts.begin(display);
  u8g2Fonts.setFontDirection(0);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.setFont(NORMAL_FONT);

  // 配置ADC
  adc1_config_width(ADC_WIDTH_BIT_12);                      // 采样位数为12位
  adc1_config_channel_atten(BATTERY_PIN, ADC_ATTEN_DB_11);  // 采样电压范围为0-3.9V

  logo_show();  //显示正在连接wifi开机画面

  delay(5000);

  WiFiManager wifiManager;

  Serial.println("连接结果:");
  Serial.println(WiFi.waitForConnectResult());  
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("桌面多功能E-paper");  //wifiManager自动配网开始
  Serial.println("连接结果2:");
  Serial.println(WiFi.waitForConnectResult());
   if (time(nullptr) < 1000000000) {
    // 如果没有获取过时间，重新获取时间
    uint8_t i = 0;
    configTime(TZ_SEC, DST_SEC, "ntp1.aliyun.com", "ntp2.aliyun.com");
    while ((time(nullptr) < 1000000000) & (i < 20)) {
      i++;
      Serial.print(".");
      delay(500);
    }
    Serial.println("时间同步成功");
  }
  REFRESHButton.attachClick(REFRESHButtonClick);
  refresh_all();
}

void loop() {

  refresh_10s();
  REFRESHButton.tick();
  time_t now = time(nullptr);
  struct tm *ltm = localtime(&now);
  if (ltm->tm_min == 0 && (ltm->tm_hour % 2 == 0) && ltm->tm_sec == 10) {
    Serial.print("开始刷新所有内容，两小时一次刷新\n");

    refresh_all();
    delay(5000);
  }
}


float read_battery_voltage() {
  uint32_t adc_value = adc1_get_raw(BATTERY_PIN);           // 读取ADC采样值
  float voltage = adc_value * 3.9 / 4095 * (R1 + R2) / R2;  // 计算电压值
  return voltage;
}

float get_battery_level(float voltage) {
  if (voltage <= V_MIN) {
    return 0;  // 电量低于警戒线
  } else if (voltage >= V_MAX) {
    return 100;  // 电量满格
  } else {
    return (voltage - V_MIN) / (V_MAX - V_MIN) * 100;  // 电量百分比
  }
}
