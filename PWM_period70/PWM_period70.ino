
int outPin=9;
int On=35;
int Total=70;

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(outPin,OUTPUT);
}

void loop() {     
  digitalWrite(outPin,HIGH);
  delayMicroseconds(On);
  digitalWrite(outPin,LOW);
  delayMicroseconds(Total-On);
}
