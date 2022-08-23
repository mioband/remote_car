#include <Arduino.h>
#include "Servo.h"
#include "MPU9250.h"

// #define MPU_TEST
// #define MPU_TEST_v2
// #define ANALOG_TEST
// #define UART_TEST
// #define SERVO_TEST


/* Analog pins */
#define U_ACCUM     GPIO_NUM_36 // input voltage
#define I_CDC       GPIO_NUM_39 // sum current of the motors
/* Servos */
#define SERV_1      GPIO_NUM_25 // first servo control pin
#define SERV_2      GPIO_NUM_33 // second servo control pin
/* LEDs */
#define LED_2       GPIO_NUM_26
#define LED_3       GPIO_NUM_27
/* MPU pins */
#define MPU_INT     GPIO_NUM_16
#define MPU_SDA     GPIO_NUM_22
#define MPU_SCL     GPIO_NUM_21
/* UART pins */
#define UART_TX     GPIO_NUM_18
#define UART_RX     GPIO_NUM_17


MPU9250 IMU(Wire, 0x68);
Servo srv_0;
// Servo srv_1;


void mpu_init(void) {
    Wire.begin(MPU_SDA, MPU_SCL, 100000U);
    int status = IMU.begin();
    if (status < 0) {
      Serial.println("IMU initialization unsuccessful");
      Serial.println("Check IMU wiring or try cycling power");
      Serial.print("Status: ");
      Serial.println(status);
    } else {
      Serial.println("Status: ");
      Serial.println(status);
  
    // setting the accelerometer full scale range to +/-8G 
    IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    // setting DLPF bandwidth to 20 Hz
    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
    // setting SRD to 19 for a 50 Hz update rate
    IMU.setSrd(19);
    }
}


void mpu_read_all_data(void) {
    IMU.readSensor();

    Serial.print(IMU.getAccelX_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelY_mss(), 6);
    Serial.print("\t");
    Serial.print(IMU.getAccelZ_mss(), 6);

    Serial.print("\t");
    Serial.print(IMU.getGyroX_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroY_rads(), 6);
    Serial.print("\t");
    Serial.print(IMU.getGyroZ_rads(), 6);

    Serial.print("\t");
    Serial.print(IMU.getMagX_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagY_uT(), 6);
    Serial.print("\t");
    Serial.print(IMU.getMagZ_uT(), 6);

    Serial.print("\t");
    Serial.println(IMU.getTemperature_C(), 6);
    delay(100);
}


void led_test(void) {
    digitalWrite(LED_2, 1);
    digitalWrite(LED_3, 1);
    delay(200);
    digitalWrite(LED_2, 0);
    digitalWrite(LED_3, 0);
    delay(200);
}


void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial1.begin(115200, SERIAL_8N1, UART_RX, UART_TX, false);
    while(!Serial1);

    mpu_init();

    pinMode(U_ACCUM, ANALOG);
    pinMode(I_CDC, ANALOG);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);

    ledcSetup(1, 50, 16);
    srv_0.attach(SERV_1, 1);
    // ledcSetup(2, 50, 16);
    // srv_1.attach(SERV_2, 2);
}


void loop() {
#if defined(MPU_TEST)
    mpu_read_all_data();
#elif defined(ANALOG_TEST)
    Serial.print("Voltage: ");
    Serial.println(analogRead(U_ACCUM));
    Serial.print("Current: ");
    Serial.println(analogRead(I_CDC));
    Serial.println();
    delay(500);
#elif defined(UART_TEST)
    Serial1.print("L0");
    delay(1000);
    Serial1.print("L1");
    delay(1000);
#elif defined(SERVO_TEST)
    srv_0.write(0);
    // srv_1.write(120);
    delay(1000);
    srv_0.write(120);
    // srv_1.write(0);
    led_test();
    delay(1000);
#endif
}
