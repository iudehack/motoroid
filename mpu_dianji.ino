#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

MPU6050 mpu;
Servo servoMotor;

//accX, accY, accZ 是存储加速度计的 X、Y、Z 轴原始数据的变量。
//gyroX, gyroY, gyroZ 是存储陀螺仪的 X、Y、Z 轴原始数据的变量。
int16_t gyroX, gyroY, gyroZ;
int16_t accX, accY, accZ;

const int servoPin = 9;  // 选择舵机连接到 Arduino 的哪个引脚
const int motorPin = 9; // PWM 的引脚


void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(motorPin, OUTPUT);
  //电机连接
  servoMotor.attach(servoPin);
}

void setSpeed(int speed){
  analogWrite(motorPin, speed);
}


void loop() {
  //读取加速度计和陀螺仪的原始数据，并将这些数据存储在提供的变量中。
  mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

  //通过atan2函数计算在XY平面上的倾斜角度。atan2 返回的角度是弧度，因此乘以 (180 / PI) 将其转换为度数。
  //atan2该函数返回以弧度表示的 y/x 的反正切，弧度区间为 [-pi,+pi]。
  //accAngleX 和 accAngleY 是相对于水平面的倾斜角度
  float accAngleX = atan2(accY, accZ) * 180 / PI;
  float accAngleY = atan2(-accX, accZ) * 180 / PI;
  
  Serial.print("Acc Angle X: ");
  Serial.print(accAngleX);
  Serial.print("\tAcc Angle Y: ");
  Serial.println(accAngleY);

  int servoPositionX = map(accAngleX, -90, 90, 0, 180);  // 舵机位置与角度映射
  int servoPositionY = map(accAngleY, -90, 90, 0, 180);

  Serial.println("速度为：");
  Serial.println(servoPositionX-90);
  setSpeed(50);
  delay(1500);
  setSpeed(0);
  // servoMotor.write(servoPositionX);
  // delay(15);  // 等待舵机调整到指定位置

  // servoMotor.write(servoPositionY);
  // delay(15);  // 等待舵机调整到指定位置
}

