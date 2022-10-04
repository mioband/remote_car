// #include <Arduino.h>


// /* Analog pins */
// #define U_ACCUM     GPIO_NUM_36
// #define I_CDC       GPIO_NUM_39
// /* LEDs */
// #define LED_2       GPIO_NUM_26
// #define LED_3       GPIO_NUM_27
// /* UART pins */
// #define UART_TX     GPIO_NUM_18
// #define UART_RX     GPIO_NUM_17


// uint8_t buf_command[10];


// void led_test(void) {
//     digitalWrite(LED_2, 1);
//     digitalWrite(LED_3, 1);
//     delay(200);
//     digitalWrite(LED_2, 0);
//     digitalWrite(LED_3, 0);
//     delay(200);
// }


// void send_bytes(void) {
//     for (uint8_t i = 0; i < sizeof(buf_command); i++) {
//         Serial1.write(buf_command[i]);
//     }
// }

// void send_stop(void) {
//     Serial1.print('S');
//     for (uint8_t i = 1; i < sizeof(buf_command); i++) {
//         Serial1.write('0');
//     }
// }


// void send_beep(void) {
//     Serial1.print('Z');
//     for (uint8_t i = 1; i < sizeof(buf_command); i++) {
//         Serial1.write('0');
//     }
// }

// void send_rotate(void) {
//     Serial1.print('R');
//     for (uint8_t i = 1; i < sizeof(buf_command); i++) {
//         Serial1.write('0');
//     }
// }


// void setup() {
//     Serial.begin(115200);
//     while(!Serial);
//     Serial1.begin(115200, SERIAL_8N1, UART_RX, UART_TX, false);
//     while(!Serial1);

//     pinMode(U_ACCUM, ANALOG);
//     pinMode(I_CDC, ANALOG);
//     pinMode(LED_2, OUTPUT);
//     pinMode(LED_3, OUTPUT);
// }


// void loop() {
//     /* TEST */
//     buf_command[0] = 'B';
//     buf_command[1] = 0;
//     buf_command[2] = 50;
//     buf_command[3] = 0;
//     buf_command[4] = 50;
//     buf_command[5] = 'T';
//     buf_command[6] = 1;
//     buf_command[7] = 50;
//     buf_command[8] = 1;
//     buf_command[9] = 50;
//     send_bytes();
//     delay(5000);

//     // buf_command[2] = 1;
//     // buf_command[3] = 255;
//     // send_bytes();
//     // delay(5000);
//     // send_stop();
//     // delay(200);
    
//     // buf_command[1] = 'r';
//     // send_bytes();
//     // delay(5000);

//     // buf_command[2] = 0;
//     // buf_command[3] = 127;
//     // send_bytes();
//     // delay(5000);
//     // send_stop();
//     // delay(200);

//     // buf_command[0] = 'B';
//     // buf_command[1] = 'l';
//     // send_bytes();
//     // delay(5000);

//     // buf_command[2] = 1;
//     // buf_command[3] = 255;
//     // send_bytes();
//     // delay(5000);
//     // send_stop();
//     // delay(200);

//     // buf_command[1] = 'r';
//     // send_bytes();
//     // delay(5000);

//     // buf_command[2] = 0;
//     // buf_command[3] = 127;
//     // send_bytes();
//     // delay(5000);
//     // send_stop();
//     // delay(200);

//     // send_beep();
//     // delay(4000);
// }

#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

#include <Arduino.h>
#include <AsyncUDP.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <string>
#include <iterator>
#include <numeric>
#include <iterator>
#include <cstdint>

typedef struct struct_message
{
  int id;
  int x;
  int y;
  int t;
  int q;
  int w;
} struct_message;

struct_message myData;

struct_message board1;
struct_message board2;

struct_message boardsStruct[2] = {board1, board2};

///////////////////////////////////////////////////////////////
uint8_t flag = 0;

constexpr uint8_t UART_TX_PIN = GPIO_NUM_17;
constexpr uint8_t UART_RX_PIN = GPIO_NUM_16;
constexpr uint32_t UART_BAUD = 38400;

int buff_char[6];

/* Analog pins */
#define U_ACCUM     GPIO_NUM_36
#define I_CDC       GPIO_NUM_39
/* LEDs */
#define LED_2       GPIO_NUM_26
#define LED_3       GPIO_NUM_27
/* UART pins */
#define UART_TX     GPIO_NUM_18
#define UART_RX     GPIO_NUM_17


uint8_t buf_command[11];


void led_test(void) {
    digitalWrite(LED_2, 1);
    digitalWrite(LED_3, 1);
    delay(200);
    digitalWrite(LED_2, 0);
    digitalWrite(LED_3, 0);
    delay(200);
}


void send_bytes(void) {
    for (uint8_t i = 0; i < sizeof(buf_command); i++) {
        Serial1.write(buf_command[i]);
    }
}

void send_stop(void) {
    Serial1.print('S');
    for (uint8_t i = 1; i < sizeof(buf_command); i++) {
        Serial1.write('0');
    }
}


void send_beep(void) {
    Serial1.print('Z');
    for (uint8_t i = 1; i < sizeof(buf_command); i++) {
        Serial1.write('0');
    }
}

void send_rotate(void) {
    Serial1.print('R');
    for (uint8_t i = 1; i < sizeof(buf_command); i++) {
        Serial1.write('0');
    }
}

AsyncUDP udp;
String s;
///////////////////////////////////////////////////////////////

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
  char macStr[18];
  //////////////////////////////////////////////////////////////
  // Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  // Serial.println(macStr);
  /////////////////////////////////////////////////////////////
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id - 1].x = myData.x;
  // boardsStruct[myData.id - 1].y = myData.y;
  //  Serial.printf("x value: %d \n", boardsStruct[myData.id - 1].x);
  //  Serial.printf("y value: %d \n", boardsStruct[myData.id - 1].y);
  //  Serial.println();
  ////////////////////////////////////////////////////////////////////
  flag = 0;

  //  buff_char[0] = 'S';
  // buff_char[1] = boardsStruct[myData.id - 1].x;
  // buff_char[2] = myData.x[1];
  // buff_char[3] = myData.x[2];
  // buff_char[4] = myData.x[3];
  // buff_char[5] = myData.x[4];

  //------------------------------------------------------для майнкрафт

  // buff_char[0] = 'S';
  buff_char[0] = myData.x;
  buff_char[1] = myData.y;
  buff_char[2] = myData.t;
  buff_char[3] = myData.q;
  buff_char[4] = myData.w;
  buff_char[5] = myData.id;

  flag = 1;
  for (int i = 0; i < 6; ++i)
  {
    Serial.print(buff_char[i]);
    Serial.print(',');
  }
  Serial.println();
  Serial.println(buf_command[2]);
  Serial.println(buf_command[7]);
  ////////////////////////////////////////////////////////////////////
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  /////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("ESPNow receiver Demo");
  esp_now_register_recv_cb(OnDataRecv);
  Serial1.begin(115200, SERIAL_8N1, UART_RX, UART_TX, false);
  while(!Serial1);

  pinMode(U_ACCUM, ANALOG);
  pinMode(I_CDC, ANALOG);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void loop()
{
    // Serial.print("ESP Board MAC Address:  ");
    // Serial.println(WiFi.macAddress());
    if (buff_char[4] == 1) {
        buf_command[10] = 1;
    }
    else if (buff_char[4] == 0) {
        buf_command[10] = 0;
    }
    if (buff_char[1] > 2) {
        if (buff_char[0] == 1) {
            if (buff_char[2] == 1) {
                // buf_command[0] = 'B';
                // buf_command[1] = 1;
                // buf_command[2] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9)))); // left back
                // buf_command[3] = 1;
                // buf_command[4] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9)); // right back
                // Serial.println(buf_command[4]);
                // buf_command[5] = 'T';
                // buf_command[6] = 0;
                // buf_command[7] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9))));; // left forward
                // buf_command[8] = 0;
                // buf_command[9] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9)); // right forward
                // Serial.println(buf_command[9]);
                buf_command[0] = 'B';
                buf_command[1] = 1;
                buf_command[2] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9)))); // left back
                buf_command[3] = 1;
                buf_command[4] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9)); // right back
                Serial.println(buf_command[4]);
                buf_command[5] = 'T';
                buf_command[6] = 0;
                buf_command[7] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9)); // right forward
                buf_command[8] = 0;
                buf_command[9] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9))));; // left forward
                Serial.println(buf_command[9]);
            }
            if (buff_char[2] == 0) {
                buf_command[0] = 'B';
                buf_command[1] = 1;
                buf_command[2] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9)); 
                buf_command[3] = 1; 
                buf_command[4] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9))));
                buf_command[5] = 'T';
                buf_command[6] = 0;
                buf_command[7] = (buff_char[1] * 10 * (1 + (1 - float((9 - (float)buff_char[3])/9))));
                buf_command[8] = 0;
                buf_command[9] = (buff_char[1] * 10 * float((9 - (float)buff_char[3])/9));
            }
        }
        if (buff_char[0] == 0) {
            buf_command[0] = 'B';
            buf_command[1] = 0;
            buf_command[2] = buff_char[1] * 10;
            buf_command[3] = 0;
            buf_command[4] = buff_char[1] * 10;
            buf_command[5] = 'T';
            buf_command[6] = 1;
            buf_command[7] = buff_char[1] * 10;
            buf_command[8] = 1;
            buf_command[9] = buff_char[1] * 10;
        }
    }
    else if (buff_char[1] <= 2) {
        if (buff_char[2] == 0) {
            buf_command[0] = 'B';
            buf_command[1] = 1;
            buf_command[2] = buff_char[3] * 10;
            buf_command[3] = 0;
            buf_command[4] = buff_char[3] * 10;
            buf_command[5] = 'T';
            buf_command[6] = 1;
            buf_command[7] = buff_char[3] * 10;
            buf_command[8] = 0;
            buf_command[9] = buff_char[3] * 10;
        }
        if (buff_char[2] == 1) {
            buf_command[0] = 'B';
            buf_command[1] = 0;
            buf_command[2] = buff_char[3] * 10;
            buf_command[3] = 1;
            buf_command[4] = buff_char[3] * 10;
            buf_command[5] = 'T';
            buf_command[6] = 0;
            buf_command[7] = buff_char[3] * 10;
            buf_command[8] = 1;
            buf_command[9] = buff_char[3] * 10;
        }
    }
    // buf_command[0] = 'B';
    // buf_command[1] = 1;
    // buf_command[2] = 200;
    // buf_command[3] = 1;
    // buf_command[4] = 50;
    // buf_command[5] = 'T';
    // buf_command[6] = 0;
    // buf_command[7] = 200;
    // buf_command[8] = 0;
    // buf_command[9] = 50;
    send_bytes();
    delay(100);
}

