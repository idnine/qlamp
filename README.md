# qlamp
Cue Lamp Project, arduino, serial-communication, XLR mic cable, 

= Setup =
* XLR Cable을 사용할 수 있도록 3pin으로 두 장치를 연결한다.
* 전원은 한쪽에만 공급해도 된다.
* 케이블 길이가 길어져 전원이 부족한 경우 양쪽 모두에 전원을 연결하는 것이 좋다.
* 한쪽 장치에만 전원을 연결할 경우 전류(암페어)가 충분한 것이 좋다.

= 동작 = 
* 대기 중엔 깜빡인다.
* 두 장치가 정상적으로 연결되어야 깜빡인다.
* 깜빡이는 신호는 버튼 쪽에서 보내기 때문에, 디스플레이 쪽에서 깜빡이지 않으면 연결이 끊어진 것이다.
* Stand-by를 누른 상태에서 손을 떼면 취소가 된다.
* Stand-by를 누른 채 Go 버튼을 눌러야 GO 신호가 전송된다.
* GO 버튼만 누르면 동작하지 않는다.
* GO 버튼을 누른채 Stand-by를 눌러도 동작하지 않는다.
* Stand-by를 눌렀다가 GO를 하든 CANCEL을 하든 한번은 Stand-by 버튼에서 손을 떼야 다음 동작이 가능하다.
* GO 신호 두번을 연속으로 보내기 위해서 Stand-by 버튼을 계속 누르고 있으면 GO 신호가 한번만 전송된다.
* GO 신호는 **Stand-by & GO** 로 이루어 진다.

= Installation =
* 버튼과 디스플레이 장치의 아두이노 스케치 파일을 각각 장치에 업로드 한다.
* 버튼과 디스플레이를 연결한다.
* XLR 케이블로 연결한다.

= qLamp - Button =
* BTN-STBY ------- Arduino 7
* BTN-GO --------- Arduino 6
* LED-RED -------- Arduino 5
* LED-GREEN ------ Arduino 4
* XLR GND (1) ---- Arduino +5V
* XLR HOT (2) ---- Arduino GND
* XLR Cold (3) --- Arduino 1

= qLamp - Display =
* MAX-7219 CLK ----- Arduino 7
* MAX-7219 CS ------ Arduino 6
* MAX-7219 DIN ----- Arduino 5
* MAX-7219 VCC ----- Arduino +5V
* MAX-7219 GND ----- Arduino GND
* XLR GND (1) ---- Arduino +5V
* XLR HOT (2) ---- Arduino GND
* XLR Cold (3) --- Arduino 0
