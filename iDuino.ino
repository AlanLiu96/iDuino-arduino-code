#include <Servo.h> 
#include <SoftwareSerial.h>
#include <assert.h>

#define LED (0)
#define SERVO (1)
#define SOUND_OUT (2)
#define DC_MOTOR (3)

// int LED = 13;  // Most Arduino boards have an onboard LED on pin 13
Servo myServo11;    // Create servo object to control the servo
Servo myServo10;    // Create servo object to control the servo

SoftwareSerial BLE_Shield(4,5);  // Configure the Serial port to be on pins D4 and D5. This
                                 // will match the jumpers on the BLE Shield (RX -> D4 & TX /> D5).

char c;  // input from the bluetooth 

int LEDPins[13]; 
int ServoPins[13];
int SoundPin[13];

void setup() {
	for(int i=6; i<14; i++){
	    pinMode(i, OUTPUT);
	}

	for(int i=0; i<2; i++){
	    pinMode(i, INPUT);
	}
  // pinMode(LED, OUTPUT);     // Set pin as an output
  // digitalWrite(LED, HIGH);  // Turn on LED (ie set to HIGH voltage)
  
  myServo11.attach(11);
  myServo10.attach(10);        // Attach the servo object to pin 10
  myServo11.write(0);         // Initialize servo position to 0
  myServo10.write(0);         // Initialize servo position to 0
  BLE_Shield.begin(9600);   // Setup the serial port at 9600 bps. This is the BLE Shield default baud rate.



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

	// int bit1;
	// int bit2;
	// int bit3;
	// int bit4;
	// int bit5;
	// int bit6;
	// int bit7;
	// int bit8;

	int component;
	int pin;
	int value;

	// See if new position data is available
	if(BLE_Shield.available()) {
		// myservo.write(BLE_Shield.read());  // Write position to servo
		c = BLE_Shield.read(); 
	}

	// bit8= bitRead(c,0);
	// bit7= bitRead(c,1);
	// bit6= bitRead(c,2);
	// bit5= bitRead(c,3);
	// bit4= bitRead(c,4);
	// bit3= bitRead(c,5);
	// bit2= bitRead(c,6);
	// bit1= bitRead(c,7);

    pin= (c >> 4);// right shift 4 spots 

    if (pin > 3){
    	pin = pin + 2; 
    }
    
    assert(pin <= 13);// pin cant be greater than 13

    component = ((c << 4) >> 6); 
    // component 0 = LED
    // 1 = Servo
    // 2 = Sound Out
    // (?) 3 = DC Motor 


    value = ((c <<6)>>6); 
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

    switch (component) {
        case LED:
          if (value >= 1)
          	LEDPins[pin] = 1;
          else
          	LEDPins[pin] = -1;
          break;
        case SERVO: // CHANGE this in the future, can't just use the one servo I instantiated 
          switch (value) {
              case 1:
               	ServoPins[pin]=1;
                break;
              case 2:
                ServoPins[pin]=2;
                break;
              default:
                ServoPins[pin]=-1; 
          }
          break;
        case SOUND_OUT:
          switch (value) {
              case 1:// low tone
              	SoundPin[pin]=1; 
                break;
              case 2:// high tone
                SoundPin[pin]=2;
                break;
              default:
              	SoundPin[pin]=-1;
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
    switch (ServoPins[10]) {
          case 1:
            myServo10.write(0);
            break;
          case 2:
            myServo10.write(180);
            break;
          default:
            myServo10.write(0);//go to left all the way even if no command is given!  
      }

    switch (ServoPins[11]) {
          case 1:
            myServo11.write(0);
            break;
          case 2:
            myServo11.write(180);
            break;
          default:
            myServo11.write(0);//go to left all the way even if no command is given!  
      }


	switch (SoundPin[12]) {
              case 1:// low tone
              	analogWrite(12, 20); // consider making a beep(wait) script, instead of this 
                break;
              case 2:// high tone
                analogWrite(12, 200);
                break;
              default:
                analogWrite(12, 0); // dont play anything 
          }



}