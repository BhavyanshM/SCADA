void setup() {
  Serial.begin(115200);
  Wire.begin(sda, scl);
  MPU6050_Init();

//  WiFi.begin("E10BAC", "3HW155W001F44");
  mb.config("E10BAC", "3HW155W001F44");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(LED_BUILTIN, OUTPUT);
  mb.addHreg(100, 0xABCD);
}
