
void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);



void yiyan_show(const char *yiyan) {

  u8g2Fonts.setFont(u8g2_font_wqy16_t_gb2312);
  int16_t dd = (u8g2Fonts.getUTF8Width(yiyan));  
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);    
  text12(yiyan, (553-dd)/2 + 240, 462,GxEPD_BLACK,GxEPD_WHITE);  
}

void yiyan_get() {

  HTTPClient http;  // 声明HTTPClient对象 
  http.begin("http://一言.php");//这里更换php文件夹中的一言.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    http.end();
    Serial.println("一言获取失败");
    return;
  }
 
  String jsoninput = http.getString();
  StaticJsonDocument<100> filter;
  filter["hitokoto"] = true;
  filter["from_who"] = true;

  StaticJsonDocument<500> doc;

  DeserializationError error = deserializeJson(doc, jsoninput, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  http.end();
 //const char* hitokoto = doc["hitokoto"]; // "眼睛为她下着雨，心却为她打着伞，这就是爱情。 "
 //const char* who = doc["from_who"]; // "d"
  
  String hitokoto = doc["hitokoto"]; // "眼睛为她下着雨，心却为她打着伞，这就是爱情。 "
  String who = doc["from_who"]; // "d"
  if (who == "null") {
  who = "--佚名";
  }
  String combined = hitokoto + "  " + who;
  const char* yiyan = combined.c_str();
  //Serial.println(yiyan);

  Serial.println("一言获取成功!");  

  yiyan_show(yiyan);
}