#include <SPI.h>
#include <SD.h>

const int MAXSIZE=128; //макс размер буфера
int buf [MAXSIZE]; // создание массиа

int bS; // сколько элементов в массиве уже есть
long tt, batDel;
File f;

void setup() {
pinMode(A2, OUTPUT); //светодиод зеленый
pinMode(A1, OUTPUT); //светодиод красный

pinMode (A0, INPUT); //AD8232
pinMode (10, OUTPUT); //PORTB 2 - SPI SD SS
pinMode(11, OUTPUT); //PORTB 3 - SPI SD MOST
pinMode(12, INPUT); //PORTB 4 - SPI SD MISO
pinMode(13, OUTPUT); //PORTB 5 - SPI SD SCK
tt=O;
bS:0;
batDel=0;
SD.begin(10);
f=SD.open("ecg.txt",FILE_WRITE);
}

long readVcc() {
long result;
ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); delay(2);
ADCSRA |= _BV(ADSC)
while (bit_is_set(ADCSRA,ADSC));
result = ADCL;
result |= ADCH<<8;
result = (1.1*1023.0*1000) / result;
return result;
}
void loop() {
 buf[bS++]=analogRead (AQ); //считываем значение, записываем в буфер и увеличиваем bS
 
 if(buf[bS-1]>=900) //если значение напряжения > или = 900, загорается зелёный светодиод
 digitalWrite (A2,HIGH);
 else
 digivalWrite (A2,LOW);
 if (batDel<=0) { //если время до мигания красного светодиода истекло
 batDel=(int) (S00+readVcc()); //задаём время до следующего мигания красного светодиода
 //чем ниже ёмкость, тем меньше время, т.е. мигать светодиод начинает чаще
 digitalWrite(A1, HIGH); //зажигаем красный светодиод
 }
 if (bS==MAXSIZE) {
   for(int i=0; i<bS; ++i, tt+=10){
      f.print (tt);
      f.print(' ')
      f.println(buf[i]}; //выводим буфер в файл
   }
   bS=0;
   f.flush(); //выгрузка данных в файл, чтобы они не удалились
 }else
  delay(10)
 batDel-=10; //уменьшаем счетчик времени до следующего мигания
 digitalWrite(A1,LOW); //гасим красный светодиод
}
