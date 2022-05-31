//Arduino UNO pins
int E = 13;
int D = 12;
int C = 11;
int DP = 10;
int B = 9;
int A = 8;
int F = 7;
int G = 6;
int left_butt = 5;
int right_butt = 4;
int MOTOR_EN_1_2 = 3;
int MOTOR_IN1 = 2;
int MOTOR_IN2 = 1;
double steps = 4;

//Button states
bool left_state = true;
bool right_state = true;

// Speeds for the motor
double max_speed = 255;
double curr_speed = 0;
int counter = 0;

void Forward_Rev(){
  analogWrite(MOTOR_EN_1_2, curr_speed);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  Serial.println(curr_speed);
}

void Backward_Rev(){
  analogWrite(MOTOR_EN_1_2, curr_speed);
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
}

void zero() {
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
void one() {
  digitalWrite(E, LOW);
  digitalWrite(D, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
void two() {
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void three() {
  digitalWrite(E, LOW);
  digitalWrite(D,HIGH );
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void four() {
  digitalWrite(E, LOW);
  digitalWrite(D, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void setup() {
  
  //7 segment Display pins
  pinMode(E, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
  //Serial monitor
  Serial.begin(9600);

  //Motor pins
  pinMode(MOTOR_EN_1_2, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  //Button pins
  pinMode(left_butt,INPUT_PULLUP);
  pinMode(right_butt,INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool current_left = digitalRead(left_butt);
  bool current_right = digitalRead(right_butt);

  //Increment or decrement steps
  if( current_left == left_state){
      Serial.println("left");
      counter--;
      while(digitalRead(left_butt) == left_state){
      }
  }
  if( current_right == right_state){
      Serial.println("right");
      counter++;
      while(digitalRead(right_butt) == right_state){
      }
  }

  //check if we went overboard
  if(counter>steps){
    counter = steps;
  }
  else if (counter<-steps){
    counter = -steps;
  }

  //Check for every case
  switch(counter){     
     case 0 :
        curr_speed = 0;
        zero();
        break;
     case 1 :
        curr_speed = (1/steps) * max_speed;
        one();
        Forward_Rev();
        break;
     case 2 :
        curr_speed = (2/steps) * max_speed;
        two();
        Forward_Rev();
        break;
     case 3 :
        curr_speed = (3/steps) * max_speed;
        three();
        Forward_Rev();
        break;
     case 4 :
        curr_speed = (4/steps) * max_speed;
        four();
        Forward_Rev();
        break;
     case -1 :
        curr_speed = (1/steps) * max_speed;
        one();
        Backward_Rev();
        break;
     case -2 :
        curr_speed = (2/steps) * max_speed;
        two();
        Backward_Rev();
        break;
     case -3 :
        curr_speed = (3/steps) * max_speed;
        three();
        Backward_Rev();
        break;
     case -4 :
        curr_speed = (4/steps) * max_speed;
        four();
        Backward_Rev();
        break;
  }
}
