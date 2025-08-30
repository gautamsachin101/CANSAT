#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

Adafruit_MPU6050 mpu;

RF24 radio(4, 5);  // CE, CSN
const uint64_t address1 = 0xE8E8F0F0E1LL;
int counter = 2;

struct MyData
{
  int counter;
  float acc_x;
  float acc_y;
  float acc_z;

  float gyr_x;
  float gyr_y;
  float gyr_z;
};
MyData data;
void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address1);

  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}  // Add this closing brace


void loop(void)
{
  delay(2000);

  Serial.println("send ...");
  data.counter = counter;

  sensors_event_t a, g;
  mpu.getEvent(&a, &g, NULL);

  data.acc_x = a.acceleration.x;
  data.acc_y = a.acceleration.y;
  data.acc_z = a.acceleration.z;

  data.gyr_x = g.gyro.x;
  data.gyr_y = g.gyro.y;
  data.gyr_z = g.gyro.z;

  Serial.print("acc_x: ");
  Serial.print(data.acc_x);
  Serial.print("acc_y: ");
  Serial.print(data.acc_y);
  Serial.print("acc_z: ");
  Serial.print(data.acc_z);

  Serial.println();
    
  Serial.print("gyro_x: ");
  Serial.print(data.gyr_x);
  Serial.print("gyro_y: ");
  Serial.print(data.gyr_y);
  Serial.print("gyro_z: ");
  Serial.print(data.gyr_z);  

  radio.write(&data, sizeof(MyData));
  Serial.print("counter is ");
  Serial.println(counter);
  counter = counter + 1;
  delay(1000);
}
