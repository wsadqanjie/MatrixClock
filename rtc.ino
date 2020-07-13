unsigned char dec2bcd(unsigned char x) { //value 0...99
  unsigned char z, e, r;
  e = x % 10;
  z = x / 10;
  z = z << 4;
  r = e | z;
  return (r);
}
unsigned char bcd2dec(unsigned char x) { //value 0...99
  int z, e;
  e = x & 0x0F;
  z = x & 0xF0;
  z = z >> 4;
  z = z * 10;
  return (z + e);
}

void rtc_init(unsigned char sda, unsigned char scl) {
  Wire.begin(sda, scl);
  rtc_Write(controlREG, 0x00);
}

unsigned char rtc_Read(unsigned char regaddress) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(regaddress);
  Wire.endTransmission();
  Wire.requestFrom((unsigned char) DS3231_ADDRESS, (unsigned char) 1);
  return (Wire.read());
}

void rtc_Write(unsigned char regaddress, unsigned char value) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(regaddress);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned char rtc_second() {
  return (bcd2dec(rtc_Read(secondREG)));
}
unsigned char rtc_minute() {
  return (bcd2dec(rtc_Read(minuteREG)));
}
unsigned char rtc_hour() {
  return (bcd2dec(rtc_Read(hourREG)));
}
unsigned char rtc_week() {
  return (bcd2dec(rtc_Read(WKREG)));
}
unsigned char rtc_day() {
  return (bcd2dec(rtc_Read(dateREG)));
}
unsigned char rtc_month() {
  return (bcd2dec(rtc_Read(monthREG)));
}
unsigned char rtc_year() {
  return (bcd2dec(rtc_Read(yearREG)));
}
void rtc_second(unsigned char t_sec) {
  rtc_Write(secondREG, (dec2bcd(t_sec)));
}
void rtc_minute(unsigned char t_min) {
  rtc_Write(minuteREG, (dec2bcd(t_min)));
}
void rtc_hour(unsigned char t_hour) {
  rtc_Write(hourREG, (dec2bcd(t_hour)));
}
void rtc_week(unsigned char wk) {
  rtc_Write(WKREG, (dec2bcd(wk)));
}
void rtc_day(unsigned char t_day) {
  rtc_Write(dateREG, (dec2bcd(t_day)));
}
void rtc_month(unsigned char t_month) {
  rtc_Write(monthREG, (dec2bcd(t_month)));
}
void rtc_year(unsigned char t_year) {
  rtc_Write(yearREG, (dec2bcd(t_year)));
}

void rtc_set(tm* tt) {
  rtc_second((unsigned char) tt->tm_sec);
  rtc_minute((unsigned char) tt->tm_min);
  rtc_hour((unsigned char) tt->tm_hour);
  rtc_day((unsigned char) tt->tm_mday);
  rtc_month((unsigned char) tt->tm_mon + 1);
  rtc_year((unsigned char) tt->tm_year - 100);
  rtc_week((unsigned char) tt->tm_wday);
}

float rtc_temp() {
  float t = 0.0;
  unsigned char lowByte = 0;
  signed char highByte = 0;
  lowByte = rtc_Read(tempLSBREG);
  highByte = rtc_Read(tempMSBREG);
  lowByte >>= 6;
  lowByte &= 0x03;
  t = ((float) lowByte);
  t *= 0.25;
  t += highByte;
  return (t); // return temp value
}

void rtc2tm() {
  unsigned short T_week, T_year, T_month, T_day, T_hour, T_minute, T_second;

  T_week = rtc_week();//周
  if(T_week > 6)T_week = 0;
  T_year = rtc_year();//年
  if (T_year > 99)T_year = 0;
  T_month = rtc_month();//月
  if (T_month > 12)T_month = 0;
  T_day = rtc_day();//日
  if (T_day > 31)T_day = 0;
  T_hour = rtc_hour();//时
  if (T_hour > 23)T_hour = 0;
  T_minute = rtc_minute();//分
  if (T_minute > 59) T_minute = 0;
  T_second = rtc_second();//秒
  if (T_second > 59)T_second = 0;

  TM.WK = T_week;          // 周So=0, Mo=1, Di=2 ...
  TM.year1 = T_year % 10;  // 年
  TM.year2 = T_year / 10;
  TM.year12 = T_year;
  TM.mon1 = T_month % 10; // 月
  TM.mon2 = T_month / 10;
  TM.mon12 = T_month;
  TM.day1 = T_day % 10;   // 日
  TM.day2 = T_day / 10;
  TM.day12 = T_day;
  TM.hour1 = T_hour % 10; // 时
  TM.hour2 = T_hour / 10;
  TM.hour12 = T_hour;
  TM.min1 = T_minute % 10; // 分
  TM.min2 = T_minute / 10;
  TM.min12 = T_minute;
  TM.sec1 = T_second % 10; // 秒
  TM.sec2 = T_second / 10;
  TM.sec12 = T_second;
}
