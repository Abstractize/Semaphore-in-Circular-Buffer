const int ledQuantity = 10;
const int length = 11;

struct Data
{
    bool hasData = false;
    int pin;
};

Data data[length];

void setup()
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
            data[i] = {false, i};
            pinMode(i, OUTPUT);
        }
    }
}

void loop()
{
    getData();
    delay(200);
    applyData();
    delay(200);
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
            bool randomBool = (bool)random(0, 1);
            Serial.print("Random for " + String(i) + " is " + String(ledQuantity));
            data[i].hasData = randomBool;
        }
    }
}

void applyData()
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
            if (data[i].hasData)
                digitalWrite(i, HIGH);
            else
                digitalWrite(i, LOW);
        }
    }
}