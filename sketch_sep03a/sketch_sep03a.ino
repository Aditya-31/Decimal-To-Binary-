const byte ledPin[]={2,3,4,5,6,7,8,9,10};
//Array of LEDs if Space is to be Saved then we can directly give LEDs as pinMode in Setup
const byte signLed=11;//1 gives indication of Negative value
const byte overFlowLed=13;//to indicate overflow of limit of 8 bits//13 BCOZ of Board's INBUILT LED

void setup() 
{
    Serial.begin(9600);
    // set up all the LEDs as OUTPUT & LOW in order to Provide A Robust Design
    for (byte i = 0; i < sizeof(ledPin); i++) 
    {
        pinMode(ledPin[i], OUTPUT);
       // digitalWrite(ledPin[i],LOW);
       //(In My Testing I didnt find any misbehaving LED So This Can Be skipped or if there is misbehaviour we can remove above comment)
    }
    
    //SignPin
    pinMode(signLed,OUTPUT);
   // digitalWrite(signLed,LOW);
    
    //OVERFLOW Pin
    pinMode(overFlowLed,OUTPUT);
    //digitalWrite(overFlowLed,LOW); 
    
    Serial.println("\n\tDECIMAL TO BINARY CONVERSION PROGRAM:\nLimits: -256 to 256(i.e 8 bit Binary No.)");
}

void loop() 
{
      //byte ctr=0;
      Serial.println("\n\nEnter Decimal Input: ");
    
      int input;
    //AS INPUT IF Taken IN Byte Then It Will Be Limited From 0-255 Only
    //i.e(NEGAVITE DECIMAL CAN'T Be Evaluate)
    //WE CAN USE THE SAME CODE FOR OTHER SYSTEM(HEX,OCT) AS WELL WITH SOME TWEAKS
      
      while (!Serial.available()) {} // ;
      //So as to wait untill further input is provided through Serial Monitor
      input=Serial.parseInt();
      Serial.print("The Binary equivalent of  ");
      Serial.print(input);
      Serial.print(" is: \t");
    
      for (byte i = 0; i < sizeof(ledPin); i++) 
        digitalWrite(ledPin[i],LOW);//By default make each LED O/P as LOW
      digitalWrite(signLed,LOW);
      digitalWrite(overFlowLed,LOW);
      if(input<0)
      {
       // ctr++;
        digitalWrite(signLed,HIGH);
        Serial.print("(SignBit)1\t");  //("-");
      }
    
      if(abs(input)<=256)
      {
        for(byte i=sizeof(ledPin);i;i--)
        //As Byte is Used the loop was going on Continously because after i=0 and i--: i becomes i=255 
          //so we have used i so that it fails on the value i=0
        {
            // By changing the 2 in the "pow" function
           //  we can change the Base of the system.      
            if(abs(input) & round(pow(2,i-1)))
            {
              //ctr++;
              digitalWrite(ledPin[i-1],HIGH);
              Serial.print("1");
              
            //Testing Over Serial Monitor
            /*Serial.print("The LED no ");
              Serial.print(i);
              Serial.println(" is on.");
            */
            }
            else
            Serial.print("0");
        }
      }  
      else
     { 
      //ctr++;
      digitalWrite(overFlowLed,HIGH);
      Serial.println("\nOVERFLOW Ocuured So Can't Predict The Output!!\nLimits are:(-256 to 256)");
     }   
      
      /*Serial.print("\n\nNo of LEDs On: ");
      Serial.println(ctr);
      */
      delay(3000);//Just A Simple Waiting Time for 3 Seconds
        
}
