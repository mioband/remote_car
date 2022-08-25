#include <Arduino.h>


/* Analog pins */
#define U_ACCUM     GPIO_NUM_36
#define I_CDC       GPIO_NUM_39
/* LEDs */
#define LED_2       GPIO_NUM_26
#define LED_3       GPIO_NUM_27
/* UART pins */
#define UART_TX     GPIO_NUM_18
#define UART_RX     GPIO_NUM_17


uint8_t buf_command[4];


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


void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial1.begin(115200, SERIAL_8N1, UART_RX, UART_TX, false);
    while(!Serial1);

    pinMode(U_ACCUM, ANALOG);
    pinMode(I_CDC, ANALOG);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
}


void loop() {
    /* TEST */
    buf_command[0] = 'T';
    buf_command[1] = 'l';
    buf_command[2] = 0;
    buf_command[3] = 127;
    send_bytes();
    delay(5000);

    buf_command[2] = 1;
    buf_command[3] = 255;
    send_bytes();
    delay(5000);
    send_stop();
    delay(200);
    
    buf_command[1] = 'r';
    send_bytes();
    delay(5000);

    buf_command[2] = 0;
    buf_command[3] = 127;
    send_bytes();
    delay(5000);
    send_stop();
    delay(200);

    buf_command[0] = 'B';
    buf_command[1] = 'l';
    send_bytes();
    delay(5000);

    buf_command[2] = 1;
    buf_command[3] = 255;
    send_bytes();
    delay(5000);
    send_stop();
    delay(200);

    buf_command[1] = 'r';
    send_bytes();
    delay(5000);

    buf_command[2] = 0;
    buf_command[3] = 127;
    send_bytes();
    delay(5000);
    send_stop();
    delay(200);

    send_beep();
    delay(4000);
}
