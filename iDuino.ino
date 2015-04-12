#include <Servo.h> 
#include <SoftwareSerial.h>
#include <assert.h>

#define LED (0)
// int LED = 13;  // Most Arduino boards have an onboard LED on pin 13
Servo myServo11;    // Create servo object to control the servo
Servo myServo10;    // Create servo object to control the servo

SoftwareSerial BLE_Shield(4,5);  // Configure the Serial port to be on pins D4 and D5. This
                                 // will match the jumpers on the BLE Shield (RX -> D4 & TX /> D5).

char c;  // input from the bluetooth 

int thisNoteA;
int thisNoteB;

int LEDPins[13]; 
int ServoPins[13];
int SoundPin[13];
int ENABLE_BLUETOOTH = 1;
int size;

const char one = 1;
const char two = 2;
const char three = 3;
const char ten = 10;
const char eleven = 11;

// MELODY STUFF


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin (12)
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};



// END MELODY STUFF





void setup() {

  thisNoteA = 0;
  thisNoteB = 0;
	for(int i=6; i<12; i++){
	    pinMode(i, OUTPUT);
	}
	for(int i=0; i<4; i++){
	    pinMode(i, OUTPUT);
	}

  // pinMode(LED, OUTPUT);     // Set pin as an output
  // digitalWrite(LED, HIGH);  // Turn on LED (ie set to HIGH voltage)
  
  myServo11.attach(11);
  myServo10.attach(10);        // Attach the servo object to pin 10
  myServo11.write(0);         // Initialize servo position to 0
  myServo10.write(0);         // Initialize servo position to 0
  
  if (ENABLE_BLUETOOTH) {
  	BLE_Shield.begin(9600);}   // Setup the serial port at 9600 bps. This is the BLE Shield default baud rate. 
  else{
  	Serial.begin(9600);
    
  }



	for(int i=0; i<13; i++){ // im being super lazy and making it 13 times, so that the index value cooresponds to pin
	    LEDPins[i]=-1;
	}
	
	for(int i=0; i<13; i++){
	    ServoPins[i]=-1;
	}
	
	for(int i=0; i<13; i++){
	    ServoPins[i]=-1;
	}

}

void loop() {

	char component;
	char pin;
	char value;

	// See if new position data is available
	if (ENABLE_BLUETOOTH) {
		if(BLE_Shield.available()) {
		// myservo.write(BLE_Shield.read());  // Write position to servo
			c = BLE_Shield.read(); 
		}
	}
	else{
	    if (Serial.available() > 0) {
          // read the incoming byte:
          // c = Serial.read();
          // c = B10000101;
          c = B10000101;
        }	
	}
	// bit8= bitRead(c,0);
	// bit7= bitRead(c,1);
	// bit6= bitRead(c,2);
	// bit5= bitRead(c,3);
	// bit4= bitRead(c,4);
	// bit3= bitRead(c,5);
	// bit2= bitRead(c,6);
	// bit1= bitRead(c,7);

    pin= ((c & B11110000) >> 4);// right shift 4 spots 

    if (pin > 3){
    	pin = pin + 2; 
    }
    
    assert(pin <= 13);// pin cant be greater than 13

    component = ((c & B00001100) >>2); 
    // component 0 = LED
    // 1 = Servo
    // 2 = Sound Out
    // (?) 3 = DC Motor 


    value = (c & B00000011); 
    // 0 = off
    // 1 = on / servo right/ low tone
    //2 = servo left / high tone

	//TODO:  Instead of setting outputs, set varaibles, then use those to call the outputs
	// make these arrays with currently active, then put in or take out with command. 
	// ex. LEDpin
	// ex. Servo Pin
	// Audio 

    // switch case with component 
    // LED
    // SERVO
    // SOUND_OUT PIEZO


    Serial.print("RAW SERIAL: ");
    Serial.println(c);
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("Component: ");
    Serial.println(component);

    if (component == one){
      Serial.print("SERVO!!!!");
    }

    Serial.print("Value: ");
    Serial.println(value);

    switch (component) {
        case LED:
          if (value >= 1){
          	LEDPins[pin] = 1;
          }
          else{
          	LEDPins[pin] = -1;
          }
          break;
        case one: //SERVO // CHANGE this in the future, can't just use the one servo I instantiated 
          Serial.print("I'm in the servo case");
          if (pin == ten){// pin isnt actually ten???? 
            switch (value) {
                case one: //1
                 	ServoPins[10]=1;
                  Serial.print("IM TELING IT TO MOVE LEFT ON PIN ");
                  Serial.println(pin);
                  break;
                case two: //2
                  Serial.print("IM TELING IT TO MOVE right ON PIN ");
                  ServoPins[10]=2;
                  break;
                default:
                  ServoPins[10]=-1; 
            }
          }
          else{
            switch (value) {
                case one: //1
                  ServoPins[11]=1;
                  Serial.print("IM TELING IT TO MOVE LEFT ON PIN ");
                  Serial.println(pin + '0' - 3);
                  break;
                case two: //2
                  Serial.print("IM TELING IT TO MOVE right ON PIN ");
                  ServoPins[11]=2;
                  break;
                default:
                  ServoPins[11]=-1; 
            }
          }
          break;
        case two: // SOUND OUT
          switch (value) {
              case one: // low tone
              	SoundPin[12]=1; 
                break;
              case two: // high tone
                SoundPin[12]=2;
                break;
              default:
              	SoundPin[12]=-1;
                analogWrite(pin, 0); // turn it off
          }
          break;  
        default:
        	Serial.println("invalid component");
          // component is invalid  
    }

    updateSensors();
}

void updateSensors(){

	for(int i=0; i<=3; i++){
	    if (LEDPins[i]==1){
	    	digitalWrite(i, HIGH);
	    }
	    else{
	    	digitalWrite(i, LOW);
	    }
	}

	for(int i=6; i<=9; i++){
	    if (LEDPins[i]==1){
	    	digitalWrite(i, HIGH);
	    }
	    else{
	    	digitalWrite(i, LOW);
	    }
	}
 for(int i=0; i<13; i++){
     if (ServoPins[i]!=-1){
      Serial.print(i);
      Serial.println(" is the Servo pins");}

 }
    switch (ServoPins[10]) {
          case 1:
            myServo10.write(0);
            break;
          case 2:
            myServo10.write(180);
            break;
          default:
            myServo10.write(90);// if its anything else ignore it
      }

    switch (ServoPins[11]) {
          case 1:
            myServo11.write(30);
            break;
          case 2:
            myServo11.write(150);
            break;
          default:
            myServo11.write(90);//go to left all the way even if no command is given!  
      }


	switch (SoundPin[12]) {
              case 1:// low tone
              	sing(1);
                // beepLow(10); // consider making a beep(wait) script, instead of this 
                break;
              case 2:// high tone
                sing(2);
                // beepHigh(10);
                break;
              default:
                analogWrite(12, 0); // dont play anything 
          }


delay(10);

}

// void beepLow(unsigned char delayms){
//   analogWrite(12, 130);      // Almost any value can be used except 0 and 255
//                            // experiment to get the best tone
// }  

// void beepHigh(unsigned char delayms){
//   analogWrite(12, 254);      // Almost any value can be used except 0 and 255
//                            // experiment to get the best tone

// }  


void sing(int s) {
  // iterate over the notes of the melody: 
  if (s == 2) {
    Serial.println(" 'Underworld Theme'");
      size = sizeof(underworld_melody) / sizeof(int);
    
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNoteA];

      buzz(melodyPin, underworld_melody[thisNoteA], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      thisNoteA = thisNoteA += 1; 

      // stop the tone playing:
      if (thisNoteA > size - 2) {
        thisNoteA = 0;
      }

      buzz(melodyPin, 0, noteDuration);

    }

   else {

    Serial.println(" 'Mario Theme'");
      size = sizeof(melody) / sizeof(int);


      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNoteB];

      buzz(melodyPin, melody[thisNoteB], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      thisNoteB = thisNoteB += 1; 

      if (thisNoteB > size - 2) {
        thisNoteB = 0;
      }



      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);

}