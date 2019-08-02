
int outPin=5;
int On=5;
int Total=25;

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(outPin,OUTPUT);
}

void loop() {     
  digitalWrite(outPin,HIGH);
  delay(On);
  digitalWrite(outPin,LOW);
  delay(Total-On);
}
