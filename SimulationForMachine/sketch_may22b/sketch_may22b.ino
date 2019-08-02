#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
const int pwmPin=2;
const int highTime = 5; //ms
const int lowTime = 20;
const int periodForRot2 = 25; //ms
const int movTime = 1400; //ms
const int NoGoTime = 50;
char receiveMsg[10];
char charBuffer = -1;
char charIndex=0;
char transmitMsg[10];

boolean showMsg = false;

void setup()  
{
  pinMode(pwmPin,OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  
  mySerial.begin(57600);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{   
  if (ReceiveMessage())
  {
    int signalType = compareMessage();
    //delay(50);
    if (signalType!=0){
      messageShow(signalType);
      //delay(50);
      doWork(signalType);
      //delay(50);
      Serial.println("Done!!!");
      //delay(50);
    }
  }
  /*
  if (showMsg)
  {
    for (int i=0;i<10;i++)
    {
      if(receiveMsg[i]!='\0' && receiveMsg[i]!='\n')
        Serial.print(receiveMsg[i]);
      else if(receiveMsg[i]=='\n')
        Serial.print('N');
      else if(receiveMsg[i]=='\0')
        Serial.print('o');
      else
        Serial.print('T');
      receiveMsg[i]='\0';
    }
    Serial.print('\n');
    showMsg=false;
  }*/
}
void doWork(int type){
  if (type==0)
    return ;
  switch(type){
    case 1: 
      Rot2();
      break;
    case 2:
      mov();
      break;
    case 3:
      noGoOK();
      break;
    case 4:
      goOK();
      break;
    case 5:
      readyOK();
      break;
    case 6:
      shutdownOK();
      break;
  }
}
void messageShow(int type){
  if (type==0)
    return ;
  Serial.print("Received message : ");
  switch(type){
    case 1: 
      Serial.println("Rot2");
      break;
    case 2:
      Serial.println("Mov");
      break;
    case 3:
      Serial.println("NoGo");
      break;
    case 4:
      Serial.println("Go");
      break;
    case 5:
      Serial.println("Ready");
      break;
    case 6:
      Serial.println("Shutdown");
      break;
  }
}
int compareMessage(){
  int signalType=0;
  for (int i=0;i<10;i++)
  {
    if (signalType!=0)
      break;
    switch(receiveMsg[i]){
      case 'R':
        if (receiveMsg[i+1]=='o'){
          signalType=1;
          break;
        }
        if (receiveMsg[i+1]=='e'){
          signalType=5;
          break;
        }
      case 'M':
        signalType=2;
        break;
      case 'N':
        signalType=3;
        break;
      case 'G':
        signalType=4;
        break;
      case 'S':
        signalType=6;
        break;
    }
  }
  if(signalType!=0 && signalType!=6)
    mySerial.println("OK");
  delay(5);
  return signalType;
}
bool ReceiveMessage(){
  charIndex=0;
  while(mySerial.available())
  {      
    charBuffer = mySerial.read();
    if ( (charBuffer>=97)&&(charBuffer<=122) || (charBuffer>=65)&&(charBuffer<=90) || (charBuffer>=48)&&(charBuffer<=57) || (charBuffer==10) || (charBuffer=='\0') )
    {
      receiveMsg[charIndex]=charBuffer;
      charIndex++;
      if(charIndex>=10)
        break;
    }
  }
  if (charIndex!=0)
    return true;
  else
    return false;
}
void Rot2()
{
  for(int i=0;i<16;i++)
  {  
    digitalWrite(pwmPin,HIGH);
    delay(highTime);
    digitalWrite(pwmPin,LOW);
    delay(lowTime);
  }
  mySerial.println("RotDone");
}
void mov()
{
  delay(movTime);
  mySerial.println("MovDone");
}
void goOK(){
  delay(NoGoTime);
  mySerial.println("GoDone");
}
void noGoOK(){
  delay(NoGoTime);
  mySerial.println("NoGoDone");
}
void readyOK()
{
  delay(1000);
  mySerial.println("ReadyOK");
}
void shutdownOK()
{
  delay(1000);
  mySerial.println("ShutdownOK");
}
