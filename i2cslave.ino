#include <Wire.h>

#define SLAVE_ADDRESS 0x08  // I2C Address
int8_t ps4data[3];          // Array to store received data

void setup() {       
  Wire.begin(SLAVE_ADDRESS);         // Join I2C bus as Slave
  Wire.onReceive(receiveEvent);      // Register event for receiving data
  Serial.begin(115200);
}

void loop() {
  // Nothing here, everything is handled in receiveEvent
}

void receiveEvent(int bytes) {
  int i = 0;  // Index for ps4data array

  while (Wire.available() && i < sizeof(ps4data)) {
    ps4data[i] = Wire.read();  // Read one byte into the array
    i++;
  }

  // Print received data for debugging
  Serial.print("Received Data: ");
  Serial.print((String)ps4data[0] + " " + ps4data[1] + " " + ps4data[2]);

  
  Serial.println();
}
