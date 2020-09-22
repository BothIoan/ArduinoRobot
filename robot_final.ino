#include <Servo.h>

////BUZZER DEFINES

    #define sAudioPin 7
    
    #define NOTE_G4 392
    #define NOTE_C4 262
    #define NOTE_A5 880
    #define NOTE_B5 988
    #define NOTE_C5 523
    #define NOTE_D5 587
    #define NOTE_E5 659

    #define NOTE_SUSTAIN 100

////MOTOR DEFINES

    // Pins of motor 1
    #define m00 5
    #define m01 6

    // Pins of motor 2
    #define m10 3
    #define m11 11

    #define left 0
    #define right 1

    //This setup means that there are 3 steps of speed both forward and backwards
    #define maxSpeed 180  //must be multiple of speedIncrement, no more than 190
    #define speedIncrement 60

    //current speed of each motor
    int speedL = 0;  //must be multiple of speedIncrement
    int speedR = 0;  //must be multiple of speedIncrement

////SERVO DEFINES

    #define servoPin 8

    #define servoMax 180  //must be multiple of servoIncrement, no more than 180
    #define servoMin 0
    #define servoIncrement 15

    Servo srv;
    int degrees = 90;  //must be multiple of servoIncrement

////LASER DEFINES

    #define laserPin 2
    #define receiverPin 4
    #define startingHealth 1

    int laserState = -1;

    int robotHealth = startingHealth;

void setup() 
{
    //configuration of motor pins as output, initially 0
    pinMode (m00, OUTPUT);
    pinMode (m01, OUTPUT);
    pinMode (m10, OUTPUT);
    pinMode (m11, OUTPUT);

    //0 initial speed
    digitalWrite(m00, 0);
    digitalWrite(m01, 0);
    digitalWrite(m10, 0);
    digitalWrite(m11, 0);

    //laser pins configuration
    pinMode(laserPin, OUTPUT);
    digitalWrite(laserPin, LOW);
    pinMode(receiverPin, INPUT);

    //buzzer setup
    pinMode(sAudioPin, OUTPUT);
    digitalWrite(sAudioPin, LOW);

    //Setup servo
    srv.attach(servoPin);

    Serial.begin(9600);
}

void loop() 
{
    if (isAlive())
    {
        if(Serial.available())
        {  
            char temp = Serial.read();
            
            if(temp == 'a')
            {
                increaseSpeed(left);
            }
            if(temp == 'b')
            {
                decreaseSpeed(left);
            }
            if(temp == 'c')
            {
                increaseSpeed(right);
            }
            if(temp == 'd')
            {
                decreaseSpeed(right);
            }
            if(temp == 'e')
            {
                servoLeft();
            }
            if(temp == 'f')
            {
                servoRight();
            }
            if(temp == 'g' || temp == 'G') //for compatibility with the controller
            {
                laserToggle();
            }
        }
    }
    else
    {
        cry();

        if(Serial.available())
        {
            char temp = Serial.read();

            if(temp == 'h' || temp == 'H') //for compatibility with the controller
            {
                lifeUp();
            }
        }
    }
    
}

void increaseSpeed(int motor)
{
    switch (motor)
    {
        case left:
            if (speedL < maxSpeed) {
                speedL += speedIncrement;
            }
            break;

        case right:
            if (speedR < maxSpeed) {
                speedR += speedIncrement;
            }
            break;
    }

    setMotorSpeed(motor);
}

void decreaseSpeed(int motor)
{
    switch (motor)
    {
        case left:
            if (speedL > -maxSpeed) {
                speedL -= speedIncrement;
            }
            break;

        case right:
            if (speedR > -maxSpeed) {
                speedR -= speedIncrement;
            }
            break;
    }

    setMotorSpeed(motor);
}

void _setMotorSpeed(int m1, int m2, int speed)
{
    digitalWrite(m1, speed);
    digitalWrite(m2, 0);
}

void setMotorSpeed(int motor)
{
    switch (motor)
    {
        case left:
            if (speedL >= 0)
            //makes left motor move forward or stop when speed = 0
            {
                _setMotorSpeed(m00, m01, speedL);
            }
            else
            //makes left motor move backwards
            {
                _setMotorSpeed(m01, m00, -speedL);
            }
            break;

        case right:
            if (speedR >= 0)
            //makes right motor move forward or stop when speed = 0
            {
                _setMotorSpeed(m10, m11, speedR);
            }
            else
            //makes right motor move backwards
            {
                _setMotorSpeed(m11, m10, -speedR);
            }
            break;
    }
}

void servoLeft()
{
    if(degrees < servoMax)
    {
        degrees += servoIncrement;

        delay(50);
        srv.write(degrees);
        delay(50);
        srv.detach();
    }
}

void servoRight()
{
    if(degrees > servoMin)
    {
        degrees -= servoIncrement;

        delay(50);
        srv.write(degrees);
        delay(50);
    }
}

void laserToggle()
{
    laserState = -laserState;

    if (laserState == 1)
    {
        digitalWrite(laserPin, HIGH);
    }
    else
    {
        digitalWrite(laserPin, LOW);
    }
    
}

int isAlive()
{
    if(robotHealth > 0 && digitalRead(receiverPin) == HIGH)
    {
        robotHealth--;
    }

    return robotHealth;
}

void cry()
{
    tone(sAudioPin,NOTE_G4);
    delay(250);
    tone(sAudioPin,NOTE_C4);
    delay(500);
    noTone(sAudioPin);
    delay(500);
}

void laugh()
{
    for(uint8_t nLoop = 0; nLoop < 2; nLoop ++)
    {
        tone(sAudioPin,NOTE_A5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_B5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_C5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_B5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_C5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_D5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_C5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_D5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_E5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_D5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_E5);
        delay(NOTE_SUSTAIN);
        tone(sAudioPin,NOTE_E5);
        delay(NOTE_SUSTAIN);
    }

    noTone(sAudioPin);
}

void lifeUp()
{
    robotHealth = startingHealth;

    laugh();
}