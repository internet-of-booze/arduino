// WEB USB LIBRARY
#include <WebUSB.h>

// SERVO DRIVER LIBRARY
#include <Servo.h>

// ADAFRUIT GRAPHICS LIBRARY
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>

// ADAFRUIT SSD 1306 DISPLAY DRIVER
// for 0.91 OLED S2C display
#include <Adafruit_SSD1306.h>
#include <splash.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
double count=0;

/*
 * PIN connection:
 * pin connection see: https://www.arduino.cc/en/Reference/Wire
 * for UNO: SDA to A4, SCL to A5
 * for Mega2560: SDA to 20, SCL to 21
 * for Leonardo: SDA to 2, SCL to 3
 * for Due: SDA to 20, SCL to 21
 * VCC to 5V
 * GND to GND :-)
 */


// this is the Width and Height of Display which is 128 xy 32 
#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  128 


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



/**
 * Creating an instance of WebUSBSerial will add an additional USB interface to
 * the device that is marked as vendor-specific (rather than USB CDC-ACM) and
 * is therefore accessible to the browser.
 *
 * The URL here provides a hint to the browser about what page the user should
 * navigate to to interact with the device.
 */


//WebUSB WebUSBSerial(1 /* https:// */, "internet-of-booze-xmas.firebaseapp.com");
WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/rgb");

Servo NozzleServo; // create servo object for sugarcone servo;

#define Serial WebUSBSerial

int serialinput[3];
int serialinputIndex;
int FADE;

void setup() {
  FADE = 1;
  NozzleServo.write(115);

  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  display.println("-> USB");
  display.display();
  delay(500);
  display.setTextSize(1);
  display.println("Follow instructions");
  display.println("in Chrome popup.");
  display.display();

  
  pinMode(5, OUTPUT);

  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Serial Comms connected. Setup...\r\n");
  Serial.flush();
  serialinputIndex = 0;
  NozzleServo.attach(10);

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,5);
  display.println("HEATR");
  display.display();
}

void loop() {
 
  if (Serial && Serial.available()) {
    serialinput[serialinputIndex++] = Serial.read();
    if (serialinputIndex == 3) {
      
      NozzleServo.write(map(serialinput[0], 0, 255, 115, 20));
      analogWrite(5, map(serialinput[1], 0, 255, 0, 255)); // Pump power output

      Serial.print("Nozzle Angle: ");
      Serial.print(map(serialinput[0], 0, 255, 10, 160));
      Serial.print(", Pump Strength: ");
      Serial.print(serialinput[1]);
      Serial.print(", AUX: ");
      
      Serial.print(serialinput[2]);
      Serial.print(".\r\n");
      Serial.flush();
      serialinputIndex = 0;
    }
  }
}
