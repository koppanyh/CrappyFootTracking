const int inputs[] = {8, 9}; //what pins to use for left, right
const int insize = 2; //THIS CANNOT EXCEED 8
const int frequency = 240; //how many times per second to send data

const int microTime = 1000000 / frequency; //microseconds to achieve data frequency
unsigned long start; //when did the calculation loop start
int times[insize]; //an array for keeping track of debouncing info
int count; //the number of data collection samples in a period

void setup() {
  Serial.begin(115200);
  for(int i=0; i<insize; i++) //use pullups so external resistors not required
    pinMode(inputs[i], INPUT_PULLUP);
  start = micros(); //begin timing sequence
}

void loop() {
  if((micros() - start) >= microTime){ //calculate and send results when ready
    start = micros(); //start time here to not cut into the next 1/240 sec period
    uint8_t payload = 0;
    count /= 2;
    for(int i=0; i<insize; i++){ //make it true if it was on more than half of the collection period
      payload <<= 1;
      if(times[i] >= count)
        payload |= 1;
      times[i] = 0; //clear times for next round
    }
    count = 0; //clear count for next round
    Serial.write(payload);
    //Serial.println(payload /*+ '0'*/);
  } else{ //else just keep collecting data
    count++;
    for(int i=0; i<insize; i++){ //just keep track of how many times it was on
      if(!digitalRead(inputs[i]))
        times[i]++;
    }
  }
}

/*
 * Serial protocol:
 * 115200 baud
 * single byte
 * each bit is the status of if it's on or off
 * arrives 240 times a second
*/
