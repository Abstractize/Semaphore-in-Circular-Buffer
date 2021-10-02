const int ledQuantity = 10;
const int length = 10; // Change this to Port value
const int delayValue = 200;

int ledsOn = 0;

struct Data
{
  bool hasData = false;
  int pin;
};

Data data[length];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < length; i++)
  {
    if (i >= ledQuantity)
    {
      Serial.println("Only " + String(ledQuantity) + " values are allowed");
      break;
    }
    else
    {
      data[i].pin = i;
      pinMode(i, OUTPUT);
    }
  }
  pinMode(10, INPUT);
}

void loop()
{
  getData();
  delay(delayValue);
  applyData();
  delay(delayValue);
}

void getData()
{
  if (Serial.available() > 0) {
    int tail = Serial.parseInt();
    int head = Serial.parseInt();
    for (int i = 0; i < length; i++)
    {
      if (head - tail > 0) {
        if (i >= tail && i <= head)
          data[i].hasData = true;
        else
          data[i].hasData = false;
      }
      else {
        if (i >= tail || i <= head)
          data[i].hasData = true;
        else
          data[i].hasData = false;
      }
    }
  }
}

void applyData()
{
  bool input = digitalRead(10);
  if (input)
    Serial.write("s");
  for (int i = 0; i < length; i++)
  {
    if (i >= ledQuantity)
    {
      Serial.println("Only " + String(ledQuantity) + " values are allowed");
      break;
    }
    else
    {
      if (data[i].hasData)
        digitalWrite(i, HIGH);
      else
        digitalWrite(i, LOW);
    }
  }
}