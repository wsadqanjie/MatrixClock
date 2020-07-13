void initWifi()
{
  Serial.println("");
  Serial.print(F("Connecting to "));
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  if(WIFI_SSID){
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      reconnections ++;
      if(reconnections == 21){
        Serial.println(F("Can not connect to WiFi"));
        delay(1000);
        return;
      }
      delay(500);
    }
    reconnections = 0;
    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
  }else{
    Serial.println(F("WiFi is not set"));
  }
  
}
