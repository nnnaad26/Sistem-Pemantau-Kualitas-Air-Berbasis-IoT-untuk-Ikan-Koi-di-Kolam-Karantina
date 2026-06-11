void setupHeater() {
  pinMode(heater1, OUTPUT);
  pinMode(heater2, OUTPUT);
  digitalWrite(heater1, 1);
  digitalWrite(heater2, 1);
}