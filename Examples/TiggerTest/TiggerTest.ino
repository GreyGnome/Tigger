#include <ooPinChangeInt.h> // necessary otherwise we get undefined reference errors.
#include <Tigger.h>

#define DELAY 150
#define PINA 5
                    // pin,  trigger, resistor, minimum delay
Tigger myTigger=Tigger(PINA, FALLING, HIGH,     DELAY        );

void setup()
{
  // 9600 is so 1988...
  Serial.begin(115200); Serial.println("---------------------------------------"); 
}

uint8_t count=0, newcount=0;
void loop()
{
  long startTime; long mymillis; long elapsed;
  newcount=myTigger.getCountNoReset();
  if (count != newcount) {
    count=newcount;
    startTime=myTigger.getStartTime(); mymillis=myTigger.getMillis(); elapsed=mymillis-startTime;
    Serial.print("Clicks: "); Serial.print(count, DEC);
    Serial.print(" Start: "); Serial.print(startTime, DEC); Serial.print(" millis: "); Serial.print(mymillis, DEC);
    Serial.print(" elapsed: "); Serial.print(elapsed, DEC);
    Serial.println();
  }
}


