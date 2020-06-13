const int inputs[] = {8, 9}; //left, right
const int insize = 2; //THIS CANNOT EXCEED 8

void setup() {
  Serial.begin(115200);
  for(int i=0; i<insize; i++)
    pinMode(inputs[i], INPUT_PULLUP);
}

void loop() {
  uint8_t payload = 0;
  for(int i=0; i<insize; i++){
    payload <<= 1;
    if(!digitalRead(inputs[i]))
      payload |= 1;
  }
  Serial.write(payload /*+ '0'*/);
  //Serial.println();
  delayMicroseconds(4166); //1sec / 240
}

/*
 * Serial protocol:
 * 115200 baud
 * single byte
 * each bit is the status of if it's on or off
*/
