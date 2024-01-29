#include "IRremote.h" //IR remote library needs be installed first


//depends on which pin you plug your IR receiver/DC motor
#define ENABLE 5 
#define DIRA 3
#define DIRB 4

int level = 0;
int i;
int receiver = 11; 

IRrecv irrecv(receiver);
decode_results results;

void translateIR(){
  switch(results.value)

  {
    //turns off fan
  case 0xFFA25D: 
  Serial.println("POWER");
  analogWrite(ENABLE, 0);
  break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    //turns on fan (max speed)
  case 0xFF629D: 
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  analogWrite(ENABLE, 255 );
  Serial.println("VOL+"); 
  break;

  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    //lowers fan speed by 75
  case 0xFFE01F: 
  Serial.println("DOWN");    
  level -= 75;
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW); 
  analogWrite(ENABLE, level);  
  Serial.println("UP");  
  break;
   //uses fan's half speed
  case 0xFFA857: 
  Serial.println("VOL-"); 
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW); 
  analogWrite(ENABLE, 153);  
  break;
     //increases fan speed by 75
  case 0xFF906F: 
  level += 75;
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW); 
  analogWrite(ENABLE, level);  
  Serial.println("UP");    
  break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR



 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  Serial.println("IR receiver Button Decode ");
  irrecv.enableIRIn();
}

void loop() {

  if(irrecv.decode(&results)){
    translateIR();
    irrecv.resume();
  }

}
   
