# ESP8266 z czujnikiem MQ-9 - Zaawansowany monitoring powietrza

Ten projekt umożliwia monitorowanie stężenia tlenku węgla (CO), LPG oraz metanu (CH4) z konwersją jednostek do mg/m³ i uproszczonym wyliczeniem indeksu jakości powietrza (AQI). Wykorzystuje ESP8266 i czujnik gazu MQ-9.

---

## 🎯 **Funkcje projektu:**

- Pomiar stężenia CO, LPG i CH4 w ppm i mg/m³
- Uproszczony wskaźnik AQI z klasyfikacją jakości powietrza
- Podgląd danych przez port szeregowy (Serial Monitor)
- W przyszłości będzie możliwość wyświetlania na ekranie `OLED`
---

## 🔧 **Wymagane komponenty:**

- ESP8266 (np. NodeMCU/Wemos D1 Mini)
- Czujnik gazu MQ-9
- Płytka stykowa i przewody połączeniowe
- Komputer z zainstalowanym Arduino IDE
### Opcjonalnie:
- Obudowa 3d
- Chęci :)

---

## ⚡ **Podłączenie czujnika:**

| MQ-9 Pin | ESP8266 Pin |
|----------|-------------|
| VCC      | 3.3V        |
| GND      | GND         |
| AO       | A0          |
| DO       |Niepodłączone|

---

## 💻 **Instalacja oprogramowania:**

1. **Zainstaluj Arduino IDE:**  
   [Pobierz Arduino IDE](https://www.arduino.cc/en/software)

2. **Dodaj obsługę ESP8266:**  
   W Arduino IDE → "Plik" → "Preferencje" → Dodaj URL:  
   `http://arduino.esp8266.com/stable/package_esp8266com_index.json`  
   Następnie w "Narzędzia" → "Płytka" → "Menedżer płytek", wyszukaj i zainstaluj "ESP8266".

3. **Ustawienia płyty:**  
   Wybierz "Narzędzia" → "Płytka" → "ESP8266 Dev Module"  
   Ustaw:  
   - Flash size: **4MB (32Mb)**  
   - Upload speed: **115200**  
   - Core Debug Level: **None**  

---

## 🚀 **Wgrywanie kodu:**

1. Podłącz ESP8266 do komputera przez USB.
2. Skopiuj kod z pliku `esp8266_mq9.ino` lub `esp8266_mq9_en.ino` (w wersji po angielsku) do Arduino IDE.
3. Kliknij "Wgraj" i zaczekaj na ukończenie kompilacji.
4. Otwórz "Monitor portu szeregowego" i ustaw prędkość na **115200 baud**.

---

## 📊 **Kalibracja:**

Domyślne wartości są przykładowe i mogą wymagać zmian w zależności od czujnika.  
W liniach:

```cpp
float co_ppm = map(rawValue, 0, 1023, 2, 1000);
float lpg_ppm = map(rawValue, 0, 1023, 1, 500);
float ch4_ppm = map(rawValue, 0, 1023, 1, 20000);
```
Ustaw czujnik w środowisku, które ma być monitorowane (np. w pomieszczeniu, na zewnątrz, itp.).
Zacznij kręcić pokrętłem. W zależności od tego, jak zmienia się wartość odczytu, dostosowuj czułość czujnika:
- Jeśli odczyty są za wysokie (czujnik wykazuje wysokie stężenie gazu przy normalnych warunkach), zmniejsz czułość, przekręcając pokrętło w kierunku „niższego” ustawienia.
- Jeśli odczyty są za niskie, zwiększ czułość, przekręcając pokrętło w kierunku „wyższego” ustawienia. Testowanie i optymalizacja
  
### Testuj czujnik w różnych warunkach:

- Przeprowadzaj testy w pomieszczeniach o różnych poziomach zanieczyszczeń, np. w pobliżu urządzeń gazowych, w kuchni itp.
- Porównaj wyniki z innymi metodami pomiaru, jeśli to możliwe (np. używając innego miernika gazów lub monitorując poziom CO w okolicy).
- Dostosuj ustawienia pokrętła w zależności od wyników pomiarów. Jeśli czujnik reaguje zbyt czuło lub za mało, ponownie dostosuj ustawienia.

## 🧠 **Przykład danych w Serial Monitorze:**
![image](https://github.com/user-attachments/assets/719b9327-f257-48c6-baeb-60f4f4f14dc6)

```cpp
========== MONITOR POWIETRZA ==========
ADC: 512 | Napięcie: 1.65 V

[STĘŻENIA GAZÓW]
CO:     250.0 ppm  | 286.35 mg/m³
LPG:    100.0 ppm  | 180.45 mg/m³
Metan:  5000.0 ppm | 3277.12 mg/m³

[INDEKS JAKOŚCI POWIETRZA]
AQI: 120 (Umiarkowany)
________________________________________
```
# Część naukowa:

1. Tlenek węgla (CO):
Bezpieczny poziom (8h):
- ≤ 9 ppm (10 mg/m³) - zalecenie WHO
- ≤ 25 ppm (29 mg/m³) - dopuszczalna ekspozycja krótkotrwała (OSHA)

Niebezpieczne stężenia:
- 50 ppm (57 mg/m³) - objawy zatrucia po 8h
- 800 ppm (916 mg/m³) - śmiertelne w 2h

2. LPG (propan-butan):
Bezpieczny poziom:
- ≤ 1000 ppm (1800 mg/m³) - poziom ostrzegawczy
- 2100 ppm (3780 mg/m³) - dolna granica wybuchowości (LEL)

Dopuszczalna ekspozycja:
- 1000 ppm (1800 mg/m³) - wartość TLV-TWA (8h)

3. Metan (CH₄):
Bezpieczny poziom:
- ≤ 1000 ppm (650 mg/m³) - poziom uznawany za bezpieczny
- 5000 ppm (3250 mg/m³) - dolna granica wybuchowości (5% LEL)

## 🛠️ Tabela jakości powietrza i poziomów bezpieczeństwa

### 🌍 **Indeks Jakości Powietrza (AQI)**

| AQI    | Stan powietrza      | Zalecenia                                    |
|--------|---------------------|-----------------------------------------------|
| 0-50   | **Bardzo dobry**    | Normalna aktywność                            |
| 51-100 | **Dobry**           | Wrażliwe osoby ograniczają aktywność          |
| 101-150| **Umiarkowany**     | Unikaj długiego przebywania na zewnątrz       |
| 151-200| **Niezadowalający** | Używaj maseczki                               |
| 201-300| **Zły**             | Unikaj wychodzenia z domu                     |
| >300   | **Krytyczny**       | Ewakuacja / włącz oczyszczacz powietrza        |

---

### 🔥 **Tabela bezpiecznych wartości dla czujnika MQ-9**

| **Gaz**    | **Bezpieczny poziom** | **Poziom ostrzegawczy** | **Niebezpieczny poziom** |
|------------|-----------------------|------------------------|--------------------------|
| **CO (ppm)**   | < 9                     | 9-35                      | > 35                        |
| **LPG (ppm)**  | < 1000                  | 1000-2000                 | > 2000                      |
| **Metan (ppm)**| < 1000                  | 1000-5000                 | > 5000                      |
| **AQI**        | 0-50                    | 51-150                    | > 150                        |

---
Dodatkowe uwagi:
Normy prawne:
Poziomy NDS (Najwyższe Dopuszczalne Stężenie) w Polsce:
- CO: 20 mg/m³ (8h)
- Propan: 1800 mg/m³

Metan: nie ustalono (traktowany jako gaz obojętny)

MQ-9 może reagować na:
- Alkohol (fałszywe wskazania LPG)
- Dym papierosowy (wpływ na odczyt CO)
- Wilgoć (>95% RH może zakłócać pomiary)
- Zalecenia przy przekroczeniach:
- Natychmiast przewietrz pomieszczenie
- Wyłącz potencjalne źródła gazu
- Użyj profesjonalnego detektora do weryfikacji
- Przy AQI >200 rozważ ewakuację
- Ograniczenia MQ-9:
- Nie wykrywa CO₂!
- Wymaga kalibracji co 6 miesięcy
- Błąd pomiaru: ±15% w warunkach pokojowych
- Wartości orientacyjne - dla precyzyjnych pomiarów wymagane certyfikowane przyrządy pomiarowe.
