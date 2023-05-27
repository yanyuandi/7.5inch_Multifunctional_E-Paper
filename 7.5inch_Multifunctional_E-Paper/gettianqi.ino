#include <HTTPClient.h>


void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);


void tianqi_show(const char *now_temp2, const char *now_text, const char *now_feelsLike3, const char *now_windSpeed2) {

  u8g2Fonts.setFont(u8g2_font_fub42_tf);
  int16_t dd = (u8g2Fonts.getUTF8Width(now_temp2)); 
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);
  text40(now_temp2, (81 - dd) / 2 + 11, 32,GxEPD_BLACK,GxEPD_WHITE);
  text12(now_text, 100, 46,GxEPD_BLACK,GxEPD_WHITE);
  text12(now_windSpeed2, 100, 32,GxEPD_BLACK,GxEPD_WHITE);
  text12(now_feelsLike3, 100, 60,GxEPD_BLACK,GxEPD_WHITE);

}

void tianqi_get() {
 
  HTTPClient http;  // 声明HTTPClient对象
  http.begin("http://天气.php");//这里更换php文件夹中的天气.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    http.end();   
    Serial.println("天气获取失败");
    return;
  }
  
  String jsoninput = http.getString();
  StaticJsonDocument<200> filter;
  filter["code"] = true;

  JsonObject filter_now = filter.createNestedObject("now");
  filter_now["temp"] = true;
  filter_now["text"] = true;
  filter_now["feelsLike"] = true;
  filter_now["windSpeed"] = true;

  StaticJsonDocument<2000> doc;
  
  DeserializationError error = deserializeJson(doc, jsoninput, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print(F("111update_weather_now_data deserializeJson() failed: "));
    Serial.println(error.f_str());
     return;
  }
  http.end();
  const char *code = doc["code"];
  const char *success_code = "200";
  if (strstr(code, success_code) == nullptr) {
    return;
  }
  const char *now_temp1 = doc["now"]["temp"];            // 温度
  const char *now_text = doc["now"]["text"];             // 天气
  const char *now_feelsLike1 = doc["now"]["feelsLike"];  // "体感温度"
  const char *now_windSpeed = doc["now"]["windSpeed"];   // "体感温度"


  String now_feelsLike = now_feelsLike1;
  String B = "体感温度" + now_feelsLike + "°";
  const char *now_feelsLike3 = B.c_str();

  String now_temp = now_temp1;
  String C = now_temp + "°";
  const char *now_temp2 = C.c_str();

  String now_windSpeed1 = now_windSpeed;
  String D = "风速" + now_windSpeed1 + "公里/小时";
  const char *now_windSpeed2 = D.c_str();

 //Serial.println(now_temp1);
 //Serial.println(now_temp2);
 //Serial.println(now_feelsLike1);
 //Serial.println(now_feelsLike3);

  Serial.println("天气获取成功!");  

  tianqi_show(now_temp2, now_text, now_feelsLike3, now_windSpeed2);
}