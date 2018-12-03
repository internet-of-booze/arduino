#include <WebUSB.h>
#include <Servo.h>


/**
 * Creating an instance of WebUSBSerial will add an additional USB interface to
 * the device that is marked as vendor-specific (rather than USB CDC-ACM) and
 * is therefore accessible to the browser.
 *
 * The URL here provides a hint to the browser about what page the user should
 * navigate to to interact with the device.
 */
WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/rgb");

Servo SugarServo; // create servo object for sugarcone servo;
Servo LighterServo; // create servo object for lighter/fire servo;

#define Serial WebUSBSerial

int color[3];
int colorIndex;

void setup() {
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
  colorIndex = 0;
  
  SugarServo.attach(9);
  LighterServo.attach(10);
}

void loop() {
  if (Serial && Serial.available()) {
    color[colorIndex++] = Serial.read();
    if (colorIndex == 3) {
      //sugarservoval = map(color[0], 0, 255, 0, 180);
      
      SugarServo.write(color[0]/2);
      LighterServo.write(color[1]/2);
      analogWrite(11, color[2]); // Pump power output

      Serial.print("Set LED to ");
      Serial.print(color[0]);
      Serial.print(", ");
      Serial.print(color[1]);
      Serial.print(", ");
      Serial.print(color[2]);
      Serial.print(".\r\n");
      Serial.flush();

      colorIndex = 0;
    }
  }
}
