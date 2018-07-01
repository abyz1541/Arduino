#include <Wire.h>

int c = 0;
#define SLAVE 0x04 // 슬레이브 주소
void setup() {
  Wire.begin(); // Wire 라이브러리 초기화
  Serial.begin(9600); // 직렬 통신 초기화
}
void loop() {
  i2c_communication(); // 슬레이브로 데이터 요구 및 수신 데이터 처리
  delay(1000);
}
void i2c_communication() {
  Wire.requestFrom(SLAVE, 4); // 1 바이트 크기의 데이터 요청
  c = Wire.read(); // 수신 데이터 읽기
  Serial.println(c); // 수신 데이터 출력
}

