//SW Camp_IoT
//Antenna Helper

#include <Stepper.h>
#include "DHT.h"       // DHT.h 라이브러리를 포함한다
#define DHTPIN 2      // DHT핀을 2번으로 정의한다(DATA핀)
#define DHTTYPE DHT11  // DHT타입을 DHT11로 정의한다
DHT dht(DHTPIN, DHTTYPE);  // DHT설정 - dht (디지털2, dht11)
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution,11,12,10,8);
int mercury=0;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(14);  //모터의 회전속도 설정
  
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);      //RGB
  pinMode(5, OUTPUT);      //RGB
  pinMode(9, OUTPUT);      //RGB
}

void loop()
{
  mercury = digitalRead(6);
  int h = dht.readHumidity();  // 변수 h에 습도 값을 저장 
  int t = dht.readTemperature();  // 변수 t에 온도 값을 저장
  
  if(mercury == LOW && h>93 ) //흔들림+우천>>빨강
  {
    analogWrite(3,0);   //
    analogWrite(5,255); //빨강
    analogWrite(9, 0);  //파랑
    Serial.println("경고! : 흔들림이 심하니 조치 요망");
    delay(2000);
  }
    if(mercury == LOW && h<93 ) //흔들림>>자홍
  {
    analogWrite(3, 0);
    analogWrite(5, 255);
    analogWrite(9, 255);
    Serial.println("경고! : 흔들림이 심하니 조치 요망");
    delay(2000);
  } 
  if(mercury == HIGH && h<93) //정상>>흰색
  {
    analogWrite(3,255);
    analogWrite(5,255);
    analogWrite(9,255);
  }
    if(mercury == HIGH && h>93) //우천>>파랑
  {
    analogWrite(3,0);
    analogWrite(5,0);
    analogWrite(9,255);
  }
  
  if(h>93)
  {
    Serial.println("경고! : 우천으로 인한 조치 요망");
    delay(2000);
  }

  int input = Serial.read();
  int num=0;
  
  switch(input)
  {
    //정방향, 360도
    case '1': myStepper.step(stepsPerRevolution); break;  //360
    
    //2줄, 180도
    case '2':
    digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW); 
    myStepper.step(stepsPerRevolution/2); digitalWrite(7,HIGH); delay(1000); digitalWrite(7,LOW);  //180
    myStepper.step(-stepsPerRevolution/2);
    break;
    
      //3줄, 120도
      case '3':
      digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);
      while(num<2)
      {
        myStepper.step(stepsPerRevolution/3); digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);  //120
        num++;
        }
        myStepper.step(-stepsPerRevolution/3);
        myStepper.step(-stepsPerRevolution/3);
        break;
        
        //4줄, 90도
        case '4':
        digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);
        while(num<3)
        {
          myStepper.step(stepsPerRevolution/4); digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);  //90
          num++;
          }
          myStepper.step(-stepsPerRevolution/4);
          myStepper.step(-stepsPerRevolution/4);
          myStepper.step(-stepsPerRevolution/4);
          break;
          
          //5줄, 72도
          case '5':
          digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);
          while(num<4)
        {
          myStepper.step(stepsPerRevolution/5); digitalWrite(7,HIGH); delay(1500); digitalWrite(7,LOW);  //72
          num++;
          }
          myStepper.step(-stepsPerRevolution/5);
          myStepper.step(-stepsPerRevolution/5);
          myStepper.step(-stepsPerRevolution/5);
          myStepper.step(-stepsPerRevolution/5);
          break;
          
          //정방향, 10도
          case '6':
          myStepper.step(stepsPerRevolution/36);
          break;
          //정방향, 30도
          case '7':
          myStepper.step(stepsPerRevolution/12);
          break;   
          //역방향, 10도
          case '8':
          myStepper.step(-stepsPerRevolution/36);
          break;
          //역방향, 30도
          case '9':
          myStepper.step(-stepsPerRevolution/12);
          break;
          //역방향, 60도
          case '10':
          myStepper.step(-stepsPerRevolution/6);
          break;
          
  }
}
