# MatrixClock
8*48点阵钟

接线方法：

| ESP8266	| DS3231 |	点阵 |
| ---- | ---- | ---- |
| GPIO4 |	SCL |	- |
| GPIO5	| SDA |	- |
| GPIO13 |	-	 | DIN |
| GPIO14 |	-	| CLK |
| GPIO15 |	-	 | CS |

更新：
1. 修改NTP获取方法
2. 时区更改为中国
3. 修改读取时间方法,取消原夏令时与冬令时

原文地址：https://github.com/schreibfaul1/ESP8266-LED-Matrix-Clock
