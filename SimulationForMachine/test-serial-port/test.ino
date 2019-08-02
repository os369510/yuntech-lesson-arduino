void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("Goodnight moon!");
}

void loop() // run over and over
{
  if (Serial.available())
  {
    char c=Serial.read();
    Serial.write("I got a message is");
    Serial.println(c);
  }
}

