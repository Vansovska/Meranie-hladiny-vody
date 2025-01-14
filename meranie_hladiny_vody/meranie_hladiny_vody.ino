// Definovanie pinov pre senzor, LED diódy, vzdialenosti v cm 
#define TRIG_PIN  23 // ESP32 pin GPIO23 pripojí ultr.senzor TRIG pin
#define ECHO_PIN  22 // ESP32 pin GPIO22 pripojí ultr.senzor ECHO pin
#define RED_LED_PIN   17 // ESP32 pin GPIO17 pripojí červenú LED pin červenú
#define GREEN_LED_PIN  16  // ESP32 pin GPIO16 pripojí zelenú LED pin
#define DISTANCE_THRESHOLD_1 15 // cm (pre červenúLED)
#define DISTANCE_THRESHOLD_2  110 // cm (pre zelenú LED)

// premenné
float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);       // inicializovať sériový port
  pinMode(TRIG_PIN, OUTPUT); // nastavenie ESP32 pin do výstupného režimu
  pinMode(ECHO_PIN, INPUT);  // nastavenie ESP32 pin do vstupného režimu
  pinMode(RED_LED_PIN, OUTPUT);  // nastavenie červenej LED do výstupného režimu
  pinMode(GREEN_LED_PIN, OUTPUT);  // nastavenie zelenej LED do výstupného režimu
}

void loop() {
  // generovať 10-mikrosekundový impulz na pin TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // meranie trvanie pulzu z pin ECHO
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // výpočet zdialenosti
  distance_cm = 0.01715 * duration_us;

  if (distance_cm < DISTANCE_THRESHOLD_1) {
    digitalWrite(RED_LED_PIN, HIGH);   // zapnutá červenú LED
    digitalWrite(GREEN_LED_PIN, LOW);  // vypnutá zelená LED
  }
  else if (distance_cm > DISTANCE_THRESHOLD_2) {
    digitalWrite(RED_LED_PIN, LOW);    // vypnutá červená LED
    digitalWrite(GREEN_LED_PIN, HIGH); // zapnutá zelená LED
  }
  else {
    digitalWrite(RED_LED_PIN, LOW);    // vypnutá červená LED
    digitalWrite(GREEN_LED_PIN, LOW);  // vypnutá zelená LED
  }

  // zobraziť hodnotu na Serial Monitor
  Serial.print("Vzdialenosť: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(2000); // meranie po 2 min.
}
