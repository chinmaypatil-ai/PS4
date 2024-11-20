#include <PS4Controller.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x08  // I2C Address
int8_t ps4data[3];          // Correctly sized array for 3 values

void setup() {
  Wire.begin();        // Join I2C bus as Master
  PS4.begin();         // Initialize PS4 controller
  Serial.begin(115200);
}

void loop() {
  if (PS4.isConnected()) {
    // Read PS4 controller data
    int8_t lx = PS4.LStickX();  // Left Stick X
    int8_t ly = PS4.LStickY();  // Left Stick Y

    // Deadzone adjustments
    if (abs(lx) <= 10) lx = 0;
    if (abs(ly) <= 10) ly = 0;

    // Fill data array
    ps4data[0] = lx;
    ps4data[1] = ly;
    ps4data[2] = map(PS4.R2Value() - PS4.L2Value(), -255, 255, -127, 127);

    // Send data via I2C
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write((uint8_t*)ps4data, sizeof(ps4data));  // Send entire array
    Wire.endTransmission();

    // Print data for debugging
    Serial.println((String)ps4data[0] + " " + ps4data[1] + " " + ps4data[2]);
  }

  delay(100);  // Add a small delay for stability
}
