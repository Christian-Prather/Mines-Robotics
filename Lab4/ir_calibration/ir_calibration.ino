/// Basic calibration program for IR sensor
int irSensor = A1;
int pushButton = 2;

void setup()
{
    pinMode(pushButton, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Setup Complete..");
}

void loop()
{
    Serial.println("Waiting...");
    while (digitalRead(pushButton) == 1)
        ; // wait for button push
    while (digitalRead(pushButton) == 0)
        ; // wait for button release

    double averageValue = 0;
    for (int i = 0; i < 5; i++)
    {
          averageValue += analogRead(irSensor);
          delay(250);

    }
    averageValue = averageValue / 5;
    Serial.print("Sensor Reading: ");
    Serial.println(averageValue);
}
