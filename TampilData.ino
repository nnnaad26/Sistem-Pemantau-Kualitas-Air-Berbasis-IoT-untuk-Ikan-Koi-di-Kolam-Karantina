void tampilNilaiSensor() {
  display.setCursor(0, 0);
  display.print("Suhu      :");
  display.setCursor(0, 13);
  display.print("PH        :");
  display.setCursor(0, 26);
  display.print("Turbidity :");
  display.setCursor(0, 39);
  display.print("TDS       :");

  // Bersihkan area nilai + satuan, pastikan area cukup lebar (sekitar 60 pixel)
  display.fillRect(70, 0, 60, 10, SH110X_BLACK);   // Suhu (nilai + °C)
  display.fillRect(70, 13, 60, 10, SH110X_BLACK);  // pH (nilai saja)
  display.fillRect(70, 26, 60, 10, SH110X_BLACK);  // Turbidity (nilai + NTU)
  display.fillRect(70, 39, 60, 10, SH110X_BLACK);  // TDS (nilai + PPM)

  // Tampilkan nilai dan satuan sesuai kebutuhan
  display.setCursor(70, 0);
  display.print(tempC, 2);
  display.print(" ");
  display.write(247);
  display.print("C");
  display.setCursor(70, 13);
  display.print(ph, 2);
  display.setCursor(70, 26);
  display.print(turbidity, 1);
  display.print(" NTU");
  display.setCursor(70, 39);
  display.print(tds, 1);
  display.print(" PPM");

  // Update OLED
  display.display();

  // Serial output (tidak diubah)
  // Serial.println("Suhu      : " + String(tempC) + " °C");
  // Serial.println("PH        : " + String(ph));
  // Serial.println("Turbidity : " + String(turbidity) + " NTU");
  // Serial.println("TDS       : " + String(tds) + " PPM");
  // Serial.println("-----------------------------");
}
