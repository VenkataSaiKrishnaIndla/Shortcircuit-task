const int red = 9;
const int yellow = 8;
const int green = 7;
const int button = 2;
const int trigPin = 3;
const int echoPin = 4;

bool pedestrianRequest = false;
unsigned long lastVehicleTime =0;
const unsigned long vehicleTimeout =30000; 

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(button), pedestrianPressed, RISING);
  digitalWrite(green, HIGH); 
}

void loop() {
  if (pedestrianRequest) {
    Serial.println("Pedestrian crossing...");

    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(6000); 
   
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);

    pedestrianRequest = false;
    return;
  }

  if (vehicleDetected()) {
    lastVehicleTime = millis();
    normalCycle();
  } 
  
  
  else if (millis() - lastVehicleTime > vehicleTimeout) {
    stayRed();
  } 
  
  else {
    normalCycle();
  }
}

void normalCycle() {
  Serial.println("Normal traffic cycle...");

  digitalWrite(green, HIGH);
  delay(2500); 

  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(1500); 

  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(3000); 

  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}


void stayRed() {
  Serial.println("No vehicle for 30 sec, staying red.");
  
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
}

bool vehicleDetected() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); 
  distance = (duration / 2) / 29.1; 

  Serial.print("Distance: ");
  Serial.println(distance);

  return (distance > 0 && distance < 100); 
}

void pedestrianPressed() {
  pedestrianRequest = true;
}