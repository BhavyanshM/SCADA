void loop() {
  double Ax, Ay, Az, T, Gx, Gy, Gz;
  
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  
  //divide each with their sensitivity scale factor
  Ax = (double)AccelX/AccelScaleFactor;
  Ay = (double)AccelY/AccelScaleFactor;
  Az = (double)AccelZ/AccelScaleFactor;
  T = (double)Temperature/340+36.53; //temperature formula
  Gx = (double)GyroX/GyroScaleFactor;
  Gy = (double)GyroY/GyroScaleFactor;
  Gz = (double)GyroZ/GyroScaleFactor;

//  Serial.print("Ax: "); Serial.print(Ax);
//  Serial.print("\tAy: "); Serial.print(Ay);
//  Serial.print("\tAz: "); Serial.print(Az);
//  Serial.print("\tT: "); Serial.print(T);
//  Serial.print("\tGx: "); Serial.print(Gx);
//  Serial.print("\tGy: "); Serial.print(Gy);
//  Serial.print("\tGz: "); Serial.println(Gz);

  delay(100);
  mb.task();
}
