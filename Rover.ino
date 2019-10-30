#define threshold 50
#define maxVal 330
int motorLeft = 11;
int motorRight = 3;
int sensorLeft = 2;
int sensorMiddle = 4;
int sensorRight = 6;
float rightDist, middleDist, leftDist, acelMotorLeft, acelMotorRight,
      factorL, factorR, distL, distR;

float aceleration(long sensorValue, float factor = 1)
{
	return 100 * factor * ((sensorValue * 0.01)/(maxVal * 0.01));
}


long readUltrasonicDistance(int pin)
{
  	long ret;
    pinMode(pin, OUTPUT); 
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
  
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);    
  
    return pulseIn(pin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(motorRight, OUTPUT);
  pinMode(motorLeft, OUTPUT);
}

void loop() 
{
  leftDist = 0.01723 * readUltrasonicDistance(sensorLeft);
  middleDist = 0.01723 * readUltrasonicDistance(sensorMiddle);
  rightDist = 0.01723 * readUltrasonicDistance(sensorRight);
  
  if(middleDist > (maxVal*0.80))
  {
    if(leftDist < threshold && rightDist > threshold)
    {
        distL = (leftDist + middleDist)/2;
      	distR = rightDist;
      	factorL = 1;
      	factorR = 1; 
    }
    else if(rightDist < threshold && leftDist > threshold)
    {
      	distL = leftDist;
      	distR = (rightDist + middleDist)/2;
      	factorL = 1;
      	factorR = 1;
    }
    else
    {
      	distL = leftDist;
      	distR = rightDist;
      	factorL = 1;
      	factorR = 1;
    }
  }
  else if(middleDist > (maxVal*0.40))
  {
    if(leftDist < threshold && rightDist > threshold)
    {
        distL = (leftDist + middleDist)/2;
      	distR = rightDist;
      	factorL = 1/3;
      	factorR = 1; 
    }
    else if(rightDist < threshold && leftDist > threshold)
    {
      	distL = leftDist;
      	distR = (rightDist + middleDist)/2;
      	factorL = 1;
      	factorR = 1/3;
    }
    else
    {
      	distL = leftDist;
      	distR = rightDist;
      	factorL = 1;
      	factorR = 1;
    }
  }
  else
  {
    if(leftDist < threshold && rightDist > threshold)
    {
        distL = (leftDist + middleDist);
      	distR = rightDist;
      	factorL = 0.35;
      	factorR = 1; 
    }
    else if(rightDist < threshold && leftDist > threshold)
    {
      	distL = leftDist;
      	distR = (rightDist + middleDist);
      	factorL = 1;
      	factorR = 0.35;
    }
    else if(rightDist > threshold && leftDist > threshold && leftDist > rightDist) 
    {
      	distL = leftDist;
      	distR = rightDist;
      	factorL = 1;
      	factorR = 0;
    }
    else if(rightDist > threshold && leftDist > threshold && leftDist < rightDist) 
    {
      	distL = leftDist;
      	distR = rightDist;
      	factorL = 0;
      	factorR = 1;
    }
    else
    {
      	distL = leftDist;
      	distR = rightDist;
      	factorL = 0;
      	factorR = 0;
    }
  }
  
  acelMotorRight = aceleration(distL, factorL);
  acelMotorLeft = aceleration(distR, factorR);
  
  analogWrite(motorLeft, acelMotorLeft);
  analogWrite(motorRight, acelMotorRight);
  
}
