//Declaring Variables
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4;
unsigned long timer_1, timer_2, timer_3, timer_4;

//Setup routine
void setup(){
  //Arduino (Atmega) pins default to inputs, so they don't need to be explicitly declared as inputs
  PCICR |= (1 << PCIE0);                                                                // set PCIE0 to enable PCMSK0 scan for port 8
  PCICR |= (1 << PCIE2);

  PCMSK0 |= (1 << PCINT0);                                                               // set PCINT0 (digital input 8) to trigger an interrupt on state change.
  PCMSK2 |= (1 << PCINT23);                                                              // set PCINT23 (digital input 7) to trigger an interrupt on state change.
  PCMSK2 |= (1 << PCINT20);                                                              // set PCINT20 (digital input 4) to trigger an interrupt on state change.
  PCMSK2 |= (1 << PCINT18);
  Serial.begin(9600); 
}

//Main program loop
void loop(){
  delay(250);
  print_signals();
}

//This routine is called every time input 8, 9, 10 or 11 changed state
ISR(PCINT2_vect){
  //Channel 1=========================================
  if(PIND & B00000100){                                        //Is input 2 high?
    if(last_channel_1 == 0){                                   //Input 2 changed from 0 to 1
      last_channel_1 = 1;                                      //Remember current input state
      timer_1 = micros();                                      //Set timer_1 to current_time/////////
    }
  }
  else if(last_channel_1 == 1){                                //Input 2 is not high and changed from 1 to 0
    last_channel_1 = 0;                                        //Remember current input state
    receiver_input_channel_1 = micros() - timer_1;         //Channel 1 is current_time - timer_1
  }
  //Channel 2=========================================
  if(PIND & B00010000 ){                                       //Is input 4 high?
    if(last_channel_2 == 0){                                   //Input 4 changed from 0 to 1
      last_channel_2 = 1;                                      //Remember current input state
      timer_2 = micros();                                  //Set timer_2 to current_time
    }
  }
  else if(last_channel_2 == 1){                                //Input 4 is not high and changed from 1 to 0
    last_channel_2 = 0;                                        //Remember current input state
    receiver_input_channel_2 = micros() - timer_2;         //Channel 2 is current_time - timer_2
  }
  //Channel 3=========================================
  if(PIND & B10000000 ){                                       //Is input 7 high?
    if(last_channel_3 == 0){                                   //Input 7 changed from 0 to 1
      last_channel_3 = 1;                                      //Remember current input state
      timer_3 = micros();                                  //Set timer_3 to current_time
    }
  }
  else if(last_channel_3 == 1){                                //Input 7 is not high and changed from 1 to 0
    last_channel_3 = 0;                                        //Remember current input state
    receiver_input_channel_3 = micros() - timer_3;         //Channel 3 is current_time - timer_3

  }
}

//This routine is called every time input 8
ISR(PCINT0_vect){
  //Channel 4=========================================
  if(PINB & B00000001 ){                                       //Is input 8 high?
    if(last_channel_4 == 0){                                   //Input 8 changed from 0 to 1
      last_channel_4 = 1;                                      //Remember current input state
      timer_4 = micros();                                  //Set timer_4 to current_time
    }
  }
  else if(last_channel_4 == 1){                                //Input 8 is not high and changed from 1 to 0
    last_channel_4 = 0;                                        //Remember current input state
    receiver_input_channel_4 = micros() - timer_4;         //Channel 4 is current_time - timer_4
  }
}
//Subroutine for displaying the receiver signals
void print_signals(){
  Serial.print("Roll:");
  if(receiver_input_channel_1 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_1 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_1);
  
  Serial.print("  Pitch:");
  if(receiver_input_channel_2 - 1480 < 0)Serial.print("^^^");
  else if(receiver_input_channel_2 - 1520 > 0)Serial.print("vvv");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_2);
  
  Serial.print("  Throttle:");
  if(receiver_input_channel_3 - 1480 < 0)Serial.print("vvv");
  else if(receiver_input_channel_3 - 1520 > 0)Serial.print("^^^");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_3);
  
  Serial.print("  Yaw:");
  if(receiver_input_channel_4 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_4 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.println(receiver_input_channel_4);
}
