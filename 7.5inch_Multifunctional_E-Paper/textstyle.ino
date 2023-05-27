void text16(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) //16px黑字
{
    bool r2l = false;
    int8_t baseline = 14;
    u8g2Fonts.setFontMode(1);
    u8g2Fonts.setFont(u8g2_font_wqy16_t_gb2312);
    u8g2Fonts.setBackgroundColor(bg_color);
    u8g2Fonts.setForegroundColor(fg_color);
    if (!r2l) {
        u8g2Fonts.drawUTF8(x, y + baseline, str);
    } else {
        int16_t w = u8g2Fonts.getUTF8Width(str);
        int16_t new_x = display.width() - x - w;
        u8g2Fonts.drawUTF8(new_x, y + baseline, str);
    }
}

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK) //16px黑字
{
  bool r2l = false;
  int8_t baseline = 10;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y + baseline, str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}

void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color = GxEPD_WHITE, uint16_t bg_color = GxEPD_BLACK)  //时间天气什么的小字
{
  bool r2l = false;
  int8_t baseline = 42;
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFont(u8g2_font_fub42_tf);
  u8g2Fonts.setBackgroundColor(bg_color);
  u8g2Fonts.setForegroundColor(fg_color);
  if (!r2l) {
    u8g2Fonts.drawUTF8(x, y + baseline, str);
  } else {
    int16_t w = u8g2Fonts.getUTF8Width(str);
    int16_t new_x = display.width() - x - w;
    u8g2Fonts.drawUTF8(new_x, y + baseline, str);
  }
}
