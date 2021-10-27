int incomingByte = 0; // for incoming serial data
int delayVal=1000; // to manage the delay
int numberOfTimesToLoop  =5;
  int pin1 = 13;
  int pin2 = 12;
  int pin3 = 11;
  
// the setup function runs once when you press reset or power the board
void setup() {

  int interrupt_pin = 2;
  // initialize digital pins 11,12,13 as output, and the reset pin as input.
  pinMode(pin1, OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(interrupt_pin,INPUT_PULLUP); // setting the interrupt pin to high by default

  //Part C
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),changeDelay,LOW); // if the pin becomes low, then an interrupt has occured
  Serial.begin(9600); // setting the baud rate to 9600
}

// the loop function runs over and over again forever
void loop() {
// PArt B1, B2
if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.parseInt(); // read what came through the serial port
    Serial.println(incomingByte);
    if(incomingByte >=0 && incomingByte<=7) // it must be a number between 0 and 9, the ascii equivalent of which is 48 to 55
    { 
      int i = incomingByte; // offset to 0
        int ctr =0; // number of times to loop counter
        while(ctr<numberOfTimesToLoop) 
        {
          if(ctr==0) // if it is the first time, then loop from the input value until 7
          //B3
          blinkLed(i,7); // blinkLed takes the starting and ending value and loops between tehm
          else
          blinkLed(0,7); // else loop from 0 to 7 in the other loops
          ctr++; // increment to ctr.
        }
        //B5
        blinkLed(0,(i-1)); // after the 5th loop, we still need to go from 0 to the digit that was inputted -1
        exit(0);
        
    }
    else //mistake in the entry. Throw an error message
    {
      Serial.print(incomingByte); 
      Serial.println(" is not a valid entry");
    }
    while(Serial.available()){Serial.read();}
 
}
}

void changeDelay() // this is the function that will be called if the interrupt pin is pressed
{
  delayVal=500;
}

void blinkLed(int i,int j) // the counter function
{
    for(i;i<=j;i++) // loop from the starting value to the last value -- they are between 0 and 7 (both included)
    { 
/*
 * What is needed is 
 * 13   12  11
 * ------------
 * 0    0   0
 * 0    0   1
 * 0    1   0
 * 0    1   1
 * 1    0   0
 * 1    0   1
 * 1    1   0
 * 1    1   1
*/
      
    if(i%2==1) // toggle for every value (pin 11)
    digitalWrite(pin3, HIGH);   // turn the LED on 
    else
    digitalWrite(pin3, LOW);    // turn the LED off by making the voltage LOW

    
    if((i>>1)%2==1)//if(i==2 || i==3 || i==6 ||i==7) // for values 2,3,6,7 
    digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
    else
    digitalWrite(pin2, LOW);    // turn the LED off by making the voltage LOW

    
    if((i>>2)%2==1)//if(i>3)// for all values above 4
    digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    else
    digitalWrite(pin1, LOW);    // turn the LED off by making the voltage LOW
    //B4
    delay(delayVal);
    }
}
