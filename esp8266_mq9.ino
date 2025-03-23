/* 
 * ESP8266 z czujnikiem MQ-9 - Zaawansowany monitoring powietrza
 * Wersja z jednostkami mg/m³ i indeksem jakości powietrza
 */

const int mq9Pin = A0;  // Pin analogowy ESP8266

// Stałe do konwersji ppm na mg/m³ (dla 25°C i 1 atm)
const float CO_MOLECULAR_WEIGHT = 28.01;   // CO: 28.01 g/mol
const float LPG_MOLECULAR_WEIGHT = 44.1;   // LPG (propan): 44.1 g/mol
const float CH4_MOLECULAR_WEIGHT = 16.04;  // Metan: 16.04 g/mol

void setup() {
  Serial.begin(115200);
  Serial.println("\nInicjalizacja systemu...");
  
  // Rozgrzewanie czujnika
  for(int i = 30; i > 0; i--){
    Serial.print("Rozgrzewanie: ");
    Serial.print(i);
    Serial.println(" s");
    delay(1000);
  }
  Serial.println("Status: Gotowy\n");
}

float ppm_to_mgm3(float ppm, float molecular_weight) {
  return (ppm * molecular_weight) / 24.45; // Konwersja ppm → mg/m³
}

String get_aqi_category(int aqi) {
  if(aqi <= 50) return "Bardzo Dobry";
  else if(aqi <= 100) return "Dobry";
  else if(aqi <= 150) return "Umiarkowany";
  else if(aqi <= 200) return "Niezadowalający";
  else if(aqi <= 300) return "Zły";
  else return "Krytyczny";
}

void loop() {
  int rawValue = analogRead(mq9Pin);
  float voltage = rawValue * (3.3 / 1023.0);

  // Kalibracja (przykładowe wartości - wymaga dostrojenia!)
  float co_ppm = map(rawValue, 0, 1023, 2, 1000);     // Zakres dla CO
  float lpg_ppm = map(rawValue, 0, 1023, 1, 500);     // Zakres dla LPG
  float ch4_ppm = map(rawValue, 0, 1023, 1, 20000);   // Zakres dla metanu

  // Konwersja do mg/m³
  float co_mgm3 = ppm_to_mgm3(co_ppm, CO_MOLECULAR_WEIGHT);
  float lpg_mgm3 = ppm_to_mgm3(lpg_ppm, LPG_MOLECULAR_WEIGHT);
  float ch4_mgm3 = ppm_to_mgm3(ch4_ppm, CH4_MOLECULAR_WEIGHT);

  // Obliczanie indeksu AQI (uproszczony)
  int aqi = constrain(map(rawValue, 0, 1023, 0, 500), 0, 500);

  Serial.println("========== MONITOR POWIETRZA ==========");
  Serial.print("ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Napięcie: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  
  Serial.println("\n[STĘŻENIA GAZÓW]");
  Serial.print("CO:     ");
  Serial.print(co_ppm, 1);
  Serial.print(" ppm  | ");
  Serial.print(co_mgm3, 2);
  Serial.println(" mg/m³");
  
  Serial.print("LPG:    ");
  Serial.print(lpg_ppm, 1);
  Serial.print(" ppm  | ");
  Serial.print(lpg_mgm3, 2);
  Serial.println(" mg/m³");
  
  Serial.print("Metan:  ");
  Serial.print(ch4_ppm, 1);
  Serial.print(" ppm  | ");
  Serial.print(ch4_mgm3, 2);
  Serial.println(" mg/m³");

  Serial.println("\n[INDEKS JAKOŚCI POWIETRZA]");
  Serial.print("AQI: ");
  Serial.print(aqi);
  Serial.print(" (");
  Serial.print(get_aqi_category(aqi));
  Serial.println(")");

  Serial.println("________________________________________\n");
  delay(2500);
}
