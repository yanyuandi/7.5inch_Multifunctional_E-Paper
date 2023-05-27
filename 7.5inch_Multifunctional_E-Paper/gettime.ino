
void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void drawBoldRoundRect(int x, int y, int w, int h, int r, int thickness, uint16_t color) {
  for (int i = 0; i < thickness; i++) {
     display.drawRoundRect(x + i, y + i, w - i * 2, h - i * 2, r, color);
  }
}


void time_show(const char *data_line11,const char *data_ri,const char *ganzhi_shengxiao,const char *data_nongli,const char *xingqi,const char *suit,const char *avoid) {
    drawBoldRoundRect(55,104,85,79,4,2,GxEPD_RED);
    display.fillRoundRect(55,104,85,20,4,GxEPD_RED);

    drawBoldRoundRect(63,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(83,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(103,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(123,96,10,15,0,3,GxEPD_RED);

    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    int16_t aa = (u8g2Fonts.getUTF8Width(data_line11)); 
    text12(data_line11, (85-aa)/2+55, 108,GxEPD_WHITE,GxEPD_RED);

    u8g2Fonts.setFont(u8g2_font_fub42_tf);
    int16_t bb = (u8g2Fonts.getUTF8Width(data_ri)); 
    text40(data_ri, (81-bb)/2+57, 131,GxEPD_BLACK,GxEPD_WHITE);

    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    int16_t cc = (u8g2Fonts.getUTF8Width(ganzhi_shengxiao)); 
    text12(ganzhi_shengxiao, (195-cc)/2, 191,GxEPD_BLACK,GxEPD_WHITE);

    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    int16_t dd = (u8g2Fonts.getUTF8Width(data_nongli)); 
    text12(data_nongli, (91-dd)/2+27, 209,GxEPD_BLACK,GxEPD_WHITE);

    text12(xingqi,118, 209,GxEPD_RED,GxEPD_WHITE);

    display.fillRoundRect(11,230,16,16,4,GxEPD_BLACK);
    display.fillRoundRect(11,254,16,16,4,GxEPD_RED);

    text12("宜",13, 232,GxEPD_WHITE,GxEPD_BLACK);
    text12("忌",13, 256,GxEPD_WHITE,GxEPD_RED);

    text12(suit,33, 232,GxEPD_BLACK,GxEPD_WHITE);
    text12(avoid,33, 256,GxEPD_BLACK,GxEPD_WHITE);


}

void time_get() {

  HTTPClient http;  // 声明HTTPClient对象
  WiFiClient Client;

  http.begin(Client, "http://日期.php");//这里更换php文件夹中的日期.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();

  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    Serial.println("时间获取失败");
    http.end();
    return;
  }

  StaticJsonDocument<250> filter;
  filter["code"] = true;
  JsonObject filter_data = filter.createNestedObject("data");
  filter_data["ri"] = true;
  filter_data["xingqi"] = true;
  filter_data["nongli"] = true;
  filter_data["ganzhi"] = true;
  filter_data["shengxiao"] = true;
  filter_data["line11"] = true;

  StaticJsonDocument<2560> doc;

  DeserializationError error = deserializeJson(doc, http.getString(), DeserializationOption::Filter(filter));

  if (error) {
    Serial.print(F("时间获取 deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  http.end();

  const char *data_line11 = doc["data"]["line11"];        // 日期
  const char *data_nongli = doc["data"]["nongli"];        // 农历
  const char *data_ri = doc["data"]["ri"];                //日
  const char *xingqi = doc["data"]["xingqi"];        // 星期
  String data_ganzhi = doc["data"]["ganzhi"];        // 干支
  String data_shengxiao = doc["data"]["shengxiao"];  // 生肖
  String ganzhi_shengxiao0 = data_ganzhi + "  " + data_shengxiao;
  const char* ganzhi_shengxiao = ganzhi_shengxiao0.c_str();
  //String nongli_xingqi0 = data_nongli + "  " + data_xingqi;
  //const char* nongli_xingqi = nongli_xingqi0.c_str();

  http.begin(Client, "http://忌宜.php");//这里更换php文件夹中的忌宜.php实际地址，具体操作请仔细阅读README.md
  int httpCode2 = http.GET();
  if (httpCode2 != 200) {
  Serial.println(HTTPClient::errorToString(httpCode));
  Serial.println("禁忌获取失败");
  http.end();
  return;
   }
  //Serial.printf("禁忌: %8d\n", ESP.getFreeHeap());
  //Serial.println(httpCode2);
  String jsoninput2 = http.getString();
  //Serial.println(jsoninput2);

  StaticJsonDocument<100> filter2;
  JsonObject filter_data2 = filter2.createNestedObject("data");
  filter_data2["suit"] = true;
  filter_data2["avoid"] = true;

  StaticJsonDocument<2000> doc2;

  DeserializationError error2 = deserializeJson(doc2, jsoninput2, DeserializationOption::Filter(filter2));

  if (error) {
    Serial.print("禁忌获取 deserializeJson() failed: ");
    Serial.println(error2.c_str());
    return;
  }
  http.end();
  const char *suit = doc2["data"]["suit"];        // 日期
  const char *avoid = doc2["data"]["avoid"];        // 农历
  time_show(data_line11, data_ri,ganzhi_shengxiao,data_nongli,xingqi,suit,avoid);
// Serial.println(data_line11);
// Serial.println(data_nongli);
// Serial.println(data_ri);
// Serial.println(data_xingqi);
// Serial.println(data_ganzhi);
// Serial.println(data_shengxiao);
  //Serial.println(suit);
  Serial.println("时间相关获取成功！");
}
