#include <vector>

// 定义 DataItem 结构体
struct DataItem {
  String word;
  String label_name;
};

// 定义全局的向量，用于存储 DataItem 数据
std::vector<DataItem> data_items;





void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void weibo_show(){


  int8_t i = 0;
  uint16_t x = 0;
  uint16_t y = 0;
  for (const auto& item : data_items) {

    // 判断 i 是否大于等于 19，然后设置 x 的值
    if (i >= 17) {
      x = 401;
      y = 92 + (i-17) * (12 + 9);
    } else {
      x = 207;
      y = 92 + i * (12 + 9);
    }
    
    String data_item_word = item.word;
    String word_with_index = String(i + 1) + "." + data_item_word;  // Combine the index and word with the prefix, as a UTF-8-encoded string
    const char *data_item_word1 = word_with_index.c_str();
    if (data_item_word != 0) {

      display.fillRect(x, y-5, 180, 19 + 9, GxEPD_WHITE);
      text12(data_item_word1, x, y,GxEPD_BLACK,GxEPD_WHITE);  // Insert the UTF-8 string into the buffer using buf_ins_text16hei()
      //Serial.println(data_item_word1);
      //display.drawFastHLine(x, y + 24, 232, GxEPD_BLACK);
    }
    String label_name = item.label_name;
    const char *data_item_label_name = label_name.c_str();

    std::string data_item_label_name1 = data_item_label_name;
    if (!data_item_label_name1.empty()) {

     
     int16_t aa = (u8g2Fonts.getUTF8Width(data_item_word1));
     display.fillRoundRect(x + aa + 2, y - 1, 14, 14, 2, GxEPD_RED);
     text12(data_item_label_name, x + aa + 3, y,GxEPD_WHITE,GxEPD_RED);
   }

    i++;

    
    
  }






}

void weibo_get() {

  HTTPClient http;  // 声明HTTPClient对象

  http.begin("http://微博.php");//这里更换php文件夹中的微博.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();

  //Serial.printf("time: %8d\n", ESP.getFreeHeap());
  //Serial.println("微博获取状态码");
  //Serial.println(httpCode);

  //Serial.println(http.getString());
  String jsoninput = http.getString();
  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    http.end();
    return;
  }
  DynamicJsonDocument doc(8000);

  DeserializationError error = deserializeJson(doc, jsoninput);

  if (error) {
    Serial.print(F("微博 deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  http.end();
  data_items.clear();

  
  for (JsonObject data_item : doc["data"].as<JsonArray>()) {

    DataItem item;
    item.word = data_item["word"].as<String>();
    item.label_name = data_item["label_name"].as<String>();
    data_items.push_back(item);    
      }

  Serial.println("微博获取成功！");
}