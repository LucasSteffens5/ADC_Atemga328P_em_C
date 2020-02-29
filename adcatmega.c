#include "def_principais.h"

unsigned int temp;

//----------------------------------------------------------------------------------
int main() {
  DDRC = 0x00; // Define todos os pinos do PC como entrada
  PORTC = 0xFE; // Habilita pullup em todos menos no ultimo pino

  DDRB = 0b00111110; // (pin 10 placa bit 6)/ (pin 13 placa bit 3) // (pin 12 placa bit 4 ) (pin 11 bit 5) (pin 9 placa bit 7)
  PORTB = 0b00000000; // sinal alto na saida

  //configura ADC
  ADMUX = 0b11000000; //Tensão interna de ref (1.1V), canal 0
  ADCSRA = 0b11101111; /*habilita o AD, habilita interrupção, modo de conversão
contínua, prescaler = 128*/ // Por causa do clock maximo do ADC   16MHz/195kHz = 82 porem o mais proximo é 128

  ADCSRB = 0x00; //modo de conversão contínua
  set_bit(DIDR0, 0); //desabilita pino PC0 como I/0, entrada do ADC0   // A0 na placa  arduino

  sei(); // lanca a interrupcao

  while (1) {

    if (temp > 200) {
      PORTB = 0b00000100;

    }

    if (temp > 275) {
      PORTB = 0b00100100;
    }

    if (temp > 300) {

      PORTB = 0b00110100;

    }

    if (temp > 325) {
      PORTB = 0b00111100;

    }
    if (temp > 350) {

      PORTB = 0b00111110;
    }


  }

}

ISR(ADC_vect) {
  temp = ADC + (ADC * 19) / 256;

  /* O LM35 apresenta uma saída de 10mV/°C. O valor de leitura do AD é dado por
  ADC = Vin*1024/Vref, como Vref = 1,1V, para converter o valor do AD para graus
  Celsius, é necessário multiplicar o valor ADC por 1100/1024 (considerando uma
  casa decimal antes da vírgula). Utilizando a simplificação matemática e mantendo
  a variável temp com 16 bits, resulta: 1100/1024 = 1 + 19/256 */
}
