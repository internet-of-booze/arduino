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

Servo NozzleServo; // create servo object for sugarcone servo;

#define Serial WebUSBSerial

int color[3];
int colorIndex;

void setup() {
  pinMode(5, OUTPUT);

  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
  colorIndex = 0;
  
  NozzleServo.attach(10);
}

void loop() {
  if (Serial && Serial.available()) {
    color[colorIndex++] = Serial.read();
    if (colorIndex == 3) {
      
      NozzleServo.write(map(color[0], 0, 255, 10, 160));
      analogWrite(5, map(color[1], 0, 255, 0, 255)); // Pump power output

      Serial.print("Nozzle Angle: ");
      Serial.print(map(color[0], 0, 255, 10, 160));
      Serial.print(", Pump Strength: ");
      Serial.print(color[1]);
      Serial.print(", AUX: ");
      Serial.print(color[2]);
      Serial.print(".\r\n");
      Serial.flush();

      colorIndex = 0;
    }
  }
}
