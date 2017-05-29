int numOfDevices = 4;
int trigPin[] = {2, 3, 4, 5};
int echoPin[] = {6, 7, 8, 9};
int ledPin[] = {10, 11, 12, 13};

void setup() {
  for (int i = 0; i < numOfDevices; i++) {
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
    pinMode(ledPin[i], OUTPUT);
  }
  delay(2000);
  Serial.begin(115200);
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
    buff[0] = '\0';
    for(int i = 0; i < 4; i++){
      int distance[4];
      for(int i = 0; i < 4; i++){
        distance[i] = findDistance(trigPin[i],echoPin[i]) > 30 ? 0 : 1;
      }
      sprintf(buff, "%i%i%i%i", distance[0],distance[1],distance[2],distance[3]);
    }
    Serial.print(buff);
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
