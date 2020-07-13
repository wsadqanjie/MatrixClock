const unsigned short InitArr[7][2] = { { 0x0C, 0x00 },    // 显示 off
    { 0x00, 0xFF },    // no LEDtest
    { 0x09, 0x00 },    // BCD off
    { 0x0F, 0x00 },    // normal operation
    { 0x0B, 0x07 },    // start display
    { 0x0A, 0x04 },    // brightness
    { 0x0C, 0x01 }     // display on
};

void max7219_init()
{
  unsigned short i, j;
  for (i = 0; i < 7; i++) {
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = 0; j < anzMAX; j++) {
      SPI.write(InitArr[i][0]);  //register
      SPI.write(InitArr[i][1]);  //value
    }
    digitalWrite(CS, HIGH);
  }
}

void max7219_set_brightness(unsigned short br)  //brightness MAX7219
{
  unsigned short j;
  if (br < 16) {
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = 0; j < anzMAX; j++) {
      SPI.write(0x0A);  //register
      SPI.write(br);    //value
    }
    digitalWrite(CS, HIGH);
  }
}

void clear_Display()   //清屏
{
  unsigned short i, j;
  for (i = 0; i < 8; i++)     //8 rows
  {
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = anzMAX; j > 0; j--) {
      LEDarr[j - 1][i] = 0;       //清除 LEDarr数据
      SPI.write(i + 1);           //当前行
      SPI.write(LEDarr[j - 1][i]);
    }
    digitalWrite(CS, HIGH);
  }
}

void refresh_display() //显示数据
{
  unsigned short i, j;

  for (i = 0; i < 8; i++)     //8 rows
  {
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = anzMAX; j > 0; j--) {
      SPI.write(i + 1);  //current row
      SPI.write(LEDarr[j - 1][i]);
    }
    digitalWrite(CS, HIGH);
  }
}
