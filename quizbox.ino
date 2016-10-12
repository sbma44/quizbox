#include <Adafruit_NeoPixel.h>

#define NEOPIN 9
#define NEOPIXEL_LENGTH 24
#define BRIGHTNESS 255 // set max brightness (0-255)
#define BEEP 3

#define NUM_BUTTONS 4
#define BUTTON_A 2
#define BUTTON_B 4
#define BUTTON_C 7
#define BUTTON_D 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_LENGTH, NEOPIN, NEO_GRB + NEO_KHZ800); // strip object

uint8_t BUTTONS[] = { BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D };
uint32_t COLORS[] = { strip.Color(255, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 0, 255), strip.Color(255, 255, 0) };

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  uint32_t blank = strip.Color(0, 0, 0);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor((i + NEOPIXEL_LENGTH) % NEOPIXEL_LENGTH, c);
    strip.show();
    delay(wait);
  }
}

void fill(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor((i + NEOPIXEL_LENGTH) % NEOPIXEL_LENGTH, c);
  }
  strip.show();
}

void beep() {
  for (int i = 0; i < 3; i++) {
    analogWrite(BEEP, 0);
    delay(50);
    analogWrite(BEEP, 255);
    delay(50);
  }
}

void setup() {
  
  Serial.begin(115200);
  Serial.println("starting...");

 
  pinMode(BEEP, OUTPUT);
  beep();
  analogWrite(BEEP, 255);
  Serial.println("* initialized buzzer");

  for (uint8_t i=0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
  Serial.println("* initialized buttons");
  
  pinMode(NEOPIN, OUTPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
  delay(500);
  colorWipe(strip.Color(255, 255, 255), 30); // Yellow
  delay(500);
  colorWipe(strip.Color(0, 0, 0), 30); 
  Serial.println("* initialized LEDs");
}

void loop() {
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    Serial.print(i);
    if (digitalRead(BUTTONS[i]) == LOW) {  
      Serial.println("low");
      fill(COLORS[i]);
      beep();
      Serial.print("- detected button press ");
      Serial.println(i);
      delay(3000);
      
      colorWipe(strip.Color(0, 0, 0), 50);
    }
    else {
      Serial.println("high");
    }
  }
}

