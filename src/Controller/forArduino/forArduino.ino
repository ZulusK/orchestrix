int numOfDevices = 4;
int trigPin[] = {2, 3, 4, 5};
int echoPin[] = {6, 7, 8, 9};
int ledPin[] = {10, 11, 12, 13};

int distance = -1;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numOfDevices; i++) {
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
    pinMode(ledPin[i], OUTPUT);
  }
}

int findDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH) / 58;
}

void loop() {
  
  char buff[100];
  if(Serial.available()){
    int i = 0;
    delay(100);
    while( Serial.available() && i< 99) {
      buff[i++] = Serial.read();
    }
    buff[i++]='\0';
  }
  else return;
  
  int command = atoi(buff);

  if(command == 0){
    int i = 1;
    
    for(; buff[i] != '\0' && buff[i - 1] != ';'; i++);
    int controller = atoi(buff + i);
    
    Serial.print(findDistance(trigPin[controller], echoPin[controller]));
  }
  else{
    int i = 1;
    
    for(; buff[i] != '\0' && buff[i - 1] != ';'; i++);
    int led = atoi(buff + i);
    i++;

    for(; buff[i] != '\0' && buff[i - 1] != ';'; i++);
    int status = atoi(buff + i);

    if(status == 1) digitalWrite(ledPin[led], HIGH);
    else digitalWrite(ledPin[led], LOW);
  }
}
