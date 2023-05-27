void refresh_yiyan(){//暂时用不到，有数据更新可以全部刷新屏幕
  display.setPartialWindow(235, 458, 563, 20);
  display.firstPage();
  do {
   yiyan_get();
  } while (display.nextPage());
  display.powerOff();
}


void refresh_weibo(){ //暂时用不到，有数据更新可以全部刷新屏幕
  weibo_get();
  display.setPartialWindow(200, 80, 384, 368);
  display.firstPage();
  do {
   weibo_show();
  } while (display.nextPage());
  display.powerOff();
}

void refresh_todo(){ //
  todo_old = todo_new;
  todo_get(millis());
  int num = todo_new.compareTo(todo_old);  //将新获取的值与旧的进行对比，定义mun为对比结果
  Serial.println("对比结果2:");
  Serial.println(num);  //打印对比结果方便调试
  if (num == 0)         //如果todo_old值跟todo_new一样那啥也不做
  {
    display.powerOff();
    Serial.println("结果一样，不刷新");  
    Serial.println("内存剩余:");
    Serial.println(ESP.getFreeHeap());  
  } else {
  Serial.println(todo_new);
  Serial.println(todo_old);
  todo_old = todo_new;
  display.setPartialWindow(592, 80, 208, 368);
  display.firstPage();
  do {
   todo_show();
  } while (display.nextPage());
  display.powerOff();
}
}

void refresh_all(){
  weibo_get();
  todo_get(millis());
  display.setFullWindow();
  display.firstPage(); 
  display.fillScreen(GxEPD_WHITE);
  do {
  
  displaymain();
  tianqi_get();
  time_get();
  yiyan_get();
  time_get();
  weibo_show();
  todo_show();
  } while (display.nextPage());
  display.powerOff();
}


