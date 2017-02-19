#include <NewPing.h>

/*     Arduino Color Sensing Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define S0 4 // 4
#define S1 5 // 14
#define S2 6 // 12
#define S3 7 // 13
#define sensorOut 8 // 15

int rfrequency = 0;
int gfrequency = 0;
int bfrequency = 0;
int lastLevel = 0;
const float Pi = 3.14159;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  rfrequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(rfrequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
 
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  gfrequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(gfrequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  bfrequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 25,70,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(bfrequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);

  if (rfrequency >= 220 && rfrequency <= 240) {
    if (bfrequency > 95) {
      // Red is close to dark
      Serial.println("Why did you drink RedBull (Blue)? You need more water!");
    } 
  }
  if (rfrequency > 300 && bfrequency > 100) {
    // this is coke
    Serial.println("Why did you drink Coke? You need more water!");  
  }
   if (rfrequency > 20 && rfrequency < 50) {
    if (bfrequency >= 12 && bfrequency < 30) {
      // this is OJ
      Serial.println("Orange Juice in the morning is okay. But you still need more water!");  
    }
  }
  
  
  int pingLevel = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(pingLevel); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  int consumption = volumeConsumed(pingLevel);
  if (consumption > 0) {
     Serial.print("You have dranked ");
     Serial.print(consumption);
     Serial.println("ml of fluids!");
  }
  lastLevel = pingLevel;
  delay(5000);
}

int volumeConsumed(int depth) {
  if (depth <= lastLevel+1) return -1;
  int vol = (depth-lastLevel) * Pi * 3.5 * 3.5;
  return vol;
}

//int volumeRemaining(int depth) {
//  return ;
//}
