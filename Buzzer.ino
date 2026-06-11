void beep() {
  digitalWrite(buzzer, 1);
  delay(300);
  digitalWrite(buzzer, 0);
  delay(300);
}

void beepConnecting() {
  digitalWrite(buzzer, 1);
  delay(200);
  digitalWrite(buzzer, 0);
}