#include <avr/io.h>
float RESISTANCE = 10000.0;


int main(){
  //Serial.begin(19200);
  initADC();
  DDRF &= ~(1 << PIN0);
  ADCSRA |= (1 << ADEN);
  PORTF |= (1 << PIN0); // aktiverer pull-up resistor

  while(1){
    float RID = voltageToResistance();
    //Serial.print("R_ID:     ");
    //Serial.println(RID, 3);
  }
}

//Funksjon som gjør en enkel spenningsdeling for å beregne R_ID.
float voltageToResistance(){
  float Vin = readAnalogPin(0)*(5.0/1024.0);
  float CurrentRID = Vin / RESISTANCE;

  return (5-Vin)/CurrentRID;
}

// Funksjon som aksesserer en spesifik analog pinne og gjør analog spenning om til digital verdi 10 bit.
int readAnalogPin(uint8_t pin)
{
  // Velger pinne det skal leses analoge data fra
  ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);
  
  // Starter å konvertere analog data til binær.
  ADCSRA |= (1 << ADSC);
  
  // Venter til datene er klare
  while (ADCSRA & (1 << ADSC));
  
  // Leser av ADC registeret og returnerer 10 bit -> Verdi på 0-1023
  return ADC;
}

// Funksjon for å initiere ADC.
void initADC(){
  // Setter referanse verdi på analog pinnene til 5V
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);
  
  // Setter ADC prescaler til 128
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Starter ADC modul
  ADCSRA |= (1 << ADEN);
}