
#include <avr/sleep.h>
#include <avr/interrupt.h>

const int BOTON                         =3;
const int BOTON2                         =0;
const int LEDROJO                       =1;
const int LEDAZUL                       =2;
const int LEDVERDE                      =4;
 int estado=0;
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than cant be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

bool primeravez =true;

long intervalOff=20000;
long previousMillis=0;
unsigned long currentMillis;


void setup() {
  pinMode(BOTON, INPUT);
  pinMode(BOTON2, INPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  // set initial LED state
  analogWrite(LEDVERDE, ledState);
  unsigned long currentMillis= millis();
}






void sleep() {

    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep

    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on

    sei();                                  // Enable interrupts
    } // sleep


ISR(PCINT0_vect) 
    {
  
    //Primero apagamos todos los colores para que no interfieran a la hora de encender un color en concreto.
    analogWrite(LEDAZUL, 0);
    analogWrite(LEDVERDE, 0);
    analogWrite(LEDROJO, 0);
    
     
    for (int k = 0; k < 10; k = k + 1) 
      {
        if (k % 2 == 0) 
          {
            analogWrite(LEDROJO, 255);
          }
        else
          {
            analogWrite(LEDROJO, 0);
          }
        delay(100);
      }
   previousMillis=currentMillis;  // Resetea el timer
   
   
}



void loop() {
  
  currentMillis =millis();
    if( currentMillis - previousMillis > intervalOff)
      {
         analogWrite(LEDAZUL, 0);
         analogWrite(LEDVERDE, 0);
         analogWrite(LEDROJO, 0);
    
         for (int k = 0; k < 10; k = k + 1) 
      {
        if (k % 2 == 0) 
          {
            analogWrite(LEDVERDE, 255);
          }
        else
          {
            analogWrite(LEDVERDE, 0);
          }
        delay(100);
      }
          previousMillis=currentMillis;  // Resetea el timer
          sleep();
      }
    else
      {
  
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(BOTON);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
       {
         previousMillis=currentMillis;  // Resetea el timer
         primeravez = true;
         analogWrite(LEDAZUL, 0);
         analogWrite(LEDVERDE, 0);
         analogWrite(LEDROJO, 0);
         if(estado==4)
         estado=0;
         else
         estado=estado+1;
         }
      }
    }
  }

  // set the LED:
  if(estado==0)
  {
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDROJO, 0);
  analogWrite(LEDAZUL, 0);
  } 
  if(estado==1)
  {
    if( primeravez == true)
    {
    for (int k = 0; k < 20; k = k + 1) 
      {
        if (k % 2 == 0) 
          {
            analogWrite(LEDVERDE, 255);
          }
        else
          {
            analogWrite(LEDVERDE, 0);
          }
        delay(50);
      }
      for(int j=0; j<=255;j++)
     {
        analogWrite(LEDVERDE, j);
        delay(7);
      }
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDROJO, 0);
  analogWrite(LEDAZUL, 0);
  primeravez = false;
  }else
    analogWrite(LEDVERDE, 255);
  analogWrite(LEDROJO, 0);
  analogWrite(LEDAZUL, 0);

  }else if (estado==2)
  {
        if( primeravez == true)
    {
    for (int k = 0; k < 10; k = k + 1) 
      {
        if (k % 2 == 0) 
          {
            analogWrite(LEDROJO, 255);
          }
        else
          {
            analogWrite(LEDROJO, 0);
          }
        delay(100);
      }
      for(int j=0; j<=255;j++)
     {
        analogWrite(LEDROJO, j);
        delay(10);
      }
  analogWrite(LEDROJO, 255);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDAZUL, 0);
  primeravez = false;
  }else
    analogWrite(LEDROJO, 255);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDAZUL, 0);

    }else if (estado==3)
     {

       
         if( primeravez == true)
    {
    for (int k = 0; k < 6; k = k + 1) 
      {
        if (k % 2 == 0) 
          {
            analogWrite(LEDAZUL, 255);
          }
        else
          {
            analogWrite(LEDAZUL, 0);
          }
        delay(100);
      }
  analogWrite(LEDAZUL, 255);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDROJO, 0);
  primeravez = false;
  }else
  
  
  analogWrite(LEDAZUL, 255);
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDROJO, 0);
       
       
       }else if (estado==4)
     {
  analogWrite(LEDVERDE, 255);
  analogWrite(LEDROJO, 200);
  analogWrite(LEDAZUL, 255);
       }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
}
