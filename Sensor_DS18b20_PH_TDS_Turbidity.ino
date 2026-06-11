void bacaDataSensor() {
  DS18B20.requestTemperatures();
  tempC = DS18B20.getTempCByIndex(0);

  int16_t phRaw = ads.readADC_SingleEnded(1);
  float phVoltage = (phRaw * 3.3) / 32767.0;  // konversi ADC 16-bit ke volt
  phVoltage /= 6.0;                           // pembagi tegangan sensor pH

  // Data kalibrasi pH dalam array
  const int n = 3;
  float adcValues[n] = { 16510.0, 14134.0, 127102.0 };
  float pHValues[n] = { 4.00, 6.86, 9.18 };

  // Hitung regresi linier untuk semua titik
  float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
  for (int i = 0; i < n; i++) {
    sumX += adcValues[i];
    sumY += pHValues[i];
    sumXY += adcValues[i] * pHValues[i];
    sumX2 += adcValues[i] * adcValues[i];
  }

  float ph_m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
  float ph_c = (sumY - ph_m * sumX) / n;
  ph = ph_m * phRaw + ph_c;  // YANG BISA DIGANTI
  if (ph < 0) ph = 0;

  // Kalibrasi Turbidity
  int16_t turbiRaw = ads.readADC_SingleEnded(2);
  // Data kalibrasi:
  // 8.32 NTU = 11400 raw
  // 0.91 NTU = 11979 raw
  float turb_m = (8.32 - 0.91) / (11400.0 - 11979.0);  // slope
  float turb_c = 8.32 - turb_m * 11485.0;              // intercept
  turbidity = turb_m * turbiRaw + turb_c;
  if (turbidity < 0) turbidity = 0;  // pastikan tidak negatif
  turbidity = turbidity + 1.5;       // YANG BISA DIGANTI

  // Kalibrasi TDS
  int16_t tdsRaw = ads.readADC_SingleEnded(3);
  // Data kalibrasi:
  // 500ppm = 5276 raw
  // 138ppm = 1552 raw
  float tds_m = (500.0 - 138.0) / (5276.0 - 1552.0);  // slope
  float tds_c = 500.0 - tds_m * 5276.0;               // intercept
  tds = tds_m * tdsRaw + tds_c;                       // YANG BISA DIGANTI
  if (tds < 0) tds = 0;                               // pastikan tidak negatif

  Serial.println("Suhu      : " + String(tempC));
  Serial.println("PH        : " + String(phRaw));
  Serial.println("PH (PH)   : " + String(ph));
  Serial.println("Turbidity Raw   : " + String(turbiRaw));
  Serial.println("Turbidity (NTU) : " + String(turbidity));
  Serial.println("TDS Raw   : " + String(tdsRaw));
  Serial.println("TDS (ppm) : " + String(tds));
  Serial.println("-----------------------------");
}
