#include <ArduinoJson.h>
unsigned long todo_lastMillis = 0;

unsigned long todo_interval = 10 * 1000;  // 待办事件触发时间10s钟，如果有内容更新则上传新内容否则啥也不做

String todo_old = "";  //定义待办事件json初始内容
String todo_new = "";  //定义待办事件json最新内容


// 声明一个结构体，用来存储每个数据项的信息
struct TodoItem {
  const char* isimp;
  const char* thing;
  const char* isdone;
};

// 声明一个数组，用来存储所有数据项的信息
std::vector<TodoItem> todo_items;



void text16(const char* str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text12(const char* str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void todo_show() {
  for (uint8_t j = 0; j < todo_items.size(); j++) {
    if (strcmp(todo_items[j].isimp, "1") == 0) {
      // 显示重要标记
      uint16_t y = 104 + j * (16 + 17);
      uint16_t x = 106 + j * (16 + 17);
      display.fillRoundRect(622, y, 29, 16, 4, GxEPD_RED);
      text12("重要", 625, x, GxEPD_WHITE, GxEPD_RED);
    }

    if (todo_items[j].thing != 0) {
      // 显示待办事项
      uint16_t y = 104 + j * (16 + 17);
      if (strcmp(todo_items[j].isimp, "1") == 0) {
        text16(todo_items[j].thing, 655, y, GxEPD_RED, GxEPD_WHITE);
      } else {
        text16(todo_items[j].thing, 622, y, GxEPD_BLACK, GxEPD_WHITE);
      }
    }

    // 显示完成状态
    display.drawFastHLine(598, 129 + j * (16 + 8 + 8 + 1), 191, GxEPD_BLACK);
    display.drawRoundRect(598, 104 + j * (16 + 17), 16, 16, 4, GxEPD_BLACK);
    if (strcmp(todo_items[j].isdone, "1") == 0) {
      uint16_t y = 104 + j * (16 + 17);
      text16("√", 600, y, GxEPD_BLACK, GxEPD_WHITE);
    }
  }
  Serial.println("todo显示成功!");
}

void todo_get(unsigned long current_millis) {
  todo_lastMillis = current_millis;

  HTTPClient http;  // 声明HTTPClient对象


  http.begin("http://待办.php");//这里更换php文件夹中的待办.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();

  //Serial.printf("time: %8d\n", ESP.getFreeHeap());

  //Serial.println(httpCode);

  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    Serial.println("TODO获取失败");
    http.end();
    return;
  }

  todo_new = http.getString();  //新获取到的json赋值给todo_new

  DynamicJsonDocument doc(6000);



  DeserializationError error = deserializeJson(doc, todo_new);

  if (error) {
    Serial.print(F("update_weather_now_data deserializeJson() failed: "));
    Serial.println(error.f_str());
    //todo_lastMillis = current_millis - todo_interval + 87000;
    return;
  }
  http.end();

  todo_items.clear();


  // 解析JSON数据并存储到数组中  
  for (JsonObject data_item : doc["data"].as<JsonArray>()) {
    const char* data_item_isimp = data_item["isimp"];
    const char* data_item_thing = data_item["thing"];
    const char* data_item_isdone = data_item["isdone"];
    todo_items.push_back({data_item_isimp, data_item_thing, data_item_isdone});
  }
  Serial.println("TODO获取成功!");
}

void refresh_10s() {
  unsigned long current_millis = millis();
  if (current_millis - todo_lastMillis >= todo_interval) {
    refresh_todo();
  }
}
