const int red = 9;
const int yellow = 7;
const int green = 8;
const int button = 2;

volatile bool pedestrianCrossing = false;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(button), request, RISING);
}

void loop() {
  if (pedestrianCrossing) {
    handlePedestrian();
    return;
  }

  Serial.println("no pedestrian");
  digitalWrite(green, HIGH);
  delay(2500);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(1500);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(2500);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}

void request() {
  pedestrianCrossing = true;
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  Serial.println("pedestrian!!");
}

void handlePedestrian() {
  delay(6000); 
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  pedestrianCrossing = false;
}
