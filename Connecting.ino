void drawThickArc(int x0, int y0, int radius, int thickness, int startAngle, int endAngle) {
  for (int r = radius; r > radius - thickness; r--) {
    for (float angle = startAngle; angle <= endAngle; angle += 2.0) {
      float rad = angle * 3.1415926 / 180.0;
      int x = x0 + r * cos(rad);
      int y = y0 - r * sin(rad);
      display.drawPixel(x, y, SH110X_WHITE);
    }
  }
}
void showConnecting() {
  display.clearDisplay();

  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2 - 8;

  drawThickArc(centerX, centerY, 20, 2, 45, 135);  // busur terluar
  drawThickArc(centerX, centerY, 15, 2, 45, 135);
  drawThickArc(centerX, centerY, 10, 2, 45, 135);
  drawThickArc(centerX, centerY, 5, 2, 45, 135);  // busur terdalam

  String text = "Connecting to";
  String blynk = "Blynk";
  int16_t x1, y1;
  uint16_t w, h;

  // Hitung posisi tengah untuk "Connecting to..."
  display.getTextBounds(text + "...", 0, 0, &x1, &y1, &w, &h);
  int textY = centerY + 10;
  display.setCursor((SCREEN_WIDTH - w) / 2, textY);
  display.print(text + "...");

  // Hitung posisi tengah untuk "Blynk"
  display.getTextBounds(blynk, 0, 0, &x1, &y1, &w, &h);
  int textYB = centerY + 23;
  display.setCursor((SCREEN_WIDTH - w) / 2, textYB);
  display.print(blynk);

  display.display();
}
