const int ledQuantity = 10;
const int length = 11; // Change this to Port value
const int delayValue = 200;
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
    for (int i = 0; i < length; i++)
    {
        if (i >= ledQuantity)
        {
            Serial.print("Only " + String(ledQuantity) + " values are allowed");
            break;
        }
        else
        {
            bool bufferHasData = (bool) random(2); // Change this to Port value
            if(bufferHasData)
                Serial.println("Value for " + String(i) + " has data.");
            else
                Serial.println("Value for " + String(i) + " doesn't has data.");
            data[i].hasData = bufferHasData;
        }
    }
}

void applyData()
{
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
