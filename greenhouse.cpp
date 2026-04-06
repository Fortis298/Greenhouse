#include <LiquidCrystal.h>
#include <DHT.h>
#include <math.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int ra = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(ra, en, d4, d5, d6, d7);

byte tempIcon[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01110,
  0b01010,
  0b10001,
  0b10001,
  0b01110
};

byte waterIcon[8] = {
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

byte sunIcon[8] = {
  0b00100,
  0b10101,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00100,
  0b00000
};

byte sproutIcon[8] = {
  0b00000,
  0b10000,
  0b11011,
  0b01110,
  0b00100,
  0b00100,
  0b00100,
  0b11111
};

char hello[] = "HELLO!";
char byProject[] = "Project, by";
char creators[] = "Uzetyx, Fortis";

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  
  for (int i = 0; hello[i] != '\0'; i++) {
    lcd.print(hello[i]);
    delay(200);
  }
  
  delay(2000);
  lcd.clear();
  
  for (int i = 0; byProject[i] != '\0'; i++) {
    lcd.print(byProject[i]);
    delay(100);
  }
  
  lcd.setCursor(0, 1);
  
  for (int i = 0; creators[i] != '\0'; i++) {
    lcd.print(creators[i]);
    delay(100);
  }
  
  delay(2000);
  lcd.clear();
  
  lcd.createChar(0, tempIcon);
  lcd.createChar(1, waterIcon);
  lcd.createChar(2, sunIcon);
  lcd.createChar(3, sproutIcon);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  int light = analogRead(A0);
  int soilMoisture = analogRead(A2);
  
  float percentLight = light / 1023.0 * 100;
  float percentSoilMoisture = soilMoisture / 1023.0 * 100;
  
  lcd.setCursor(0, 0);
  
  if (isnan(temp) || isnan(hum)) {
    lcd.print("ERROR: DHT11    ");
  } else {
    lcd.write(byte(0));
    lcd.print(":");
    lcd.print(temp, 1);
    lcd.print("C ");
    lcd.write(byte(1));
    lcd.print(":");
    lcd.print(hum, 1);
    lcd.print("%   ");
  }
  
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  lcd.print(":");
  lcd.print(percentLight, 1);
  lcd.print("% ");
  lcd.write(byte(3));
  lcd.write(byte(1));
  lcd.print(":");
  lcd.print(percentSoilMoisture, 1);
  lcd.print("%  ");
  
  
  delay(1000);
}
