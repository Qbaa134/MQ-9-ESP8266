const int mq9Pin = A0;  


const float CO_MOLECULAR_WEIGHT = 28.01;   
const float LPG_MOLECULAR_WEIGHT = 44.1;   
const float CH4_MOLECULAR_WEIGHT = 16.04;  

void setup() {
  Serial.begin(115200);
  Serial.println("\nSystem Starting...");
  
  // Rozgrzewanie czujnika
  for(int i = 30; i > 0; i--){
    Serial.print("Heating: ");
    Serial.print(i);
    Serial.println(" s");
    delay(1000);
  }
  Serial.println("Status: Ready\n");
}

float ppm_to_mgm3(float ppm, float molecular_weight) {
  return (ppm * molecular_weight) / 24.45; 
}

String get_aqi_category(int aqi) {
  if(aqi <= 50) return "Very Good";
  else if(aqi <= 100) return "Good";
  else if(aqi <= 150) return "Mild";
  else if(aqi <= 200) return "Disappointing";
  else if(aqi <= 300) return "Bad";
  else return "Critical";
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

  Serial.println("========== AIR MONITOR ==========");
  Serial.print("ADC: ");
  Serial.print(rawValue);
  Serial.print(" | VOLTAGE: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  
  Serial.println("\n[GASES CONCENTRATION");
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
  
  Serial.print("Methane:  ");
  Serial.print(ch4_ppm, 1);
  Serial.print(" ppm  | ");
  Serial.print(ch4_mgm3, 2);
  Serial.println(" mg/m³");

  Serial.println("\n[AIR QUALITY INDEX]");
  Serial.print("AQI: ");
  Serial.print(aqi);
  Serial.print(" (");
  Serial.print(get_aqi_category(aqi));
  Serial.println(")");

  Serial.println("________________________________________\n");
  delay(2500);
}
