/*  
 * CONFIGURATION 
 ***********************************/
#define MAXDRY 80
#define DRYRANGE 50
#define VALVE 1000
/* END OF CONFIGURATION AREA */

/* misc */
int ledPin = 13,
    value,
    aux = 0,
    control = 0, 
    flag = 1;

/* soil moisture sensor */
int moisturePin = A1;

/* water valve */
int relayPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); /* keep relay open */
}

void loop() {
  value = analogRead(moisturePin); /* read moisture level */

  if (value < MAXDRY) { /* if soil is dry */
    if (flag) { /* blink led */
      digitalWrite(ledPin, HIGH);
      flag = 0;
    } else {
      digitalWrite(ledPin, LOW);
      flag = 1;
    }
    delay(10000); /* wait for some time */

    if (aux > 10) { /* see if is really dry or was just an error */
      digitalWrite(relayPin, LOW);
      delay(VALVE); /* keep the valve open */
      digitalWrite(relayPin, HIGH);
      aux = 0;
    } else {
      aux++;
    }
    
  } else if (value < (MAXDRY + DRYRANGE)) { /* if the soil is about to became dry */
    if (flag) { /* blink led */
      digitalWrite(ledPin, HIGH);
      flag = 0;
    } else {
      digitalWrite(ledPin, LOW);
      flag = 1;
    }
    delay(700);

    control++; /* aux shouldn't be acumulate from errors. we need some control */
  } else {
    control++;
  }

  if (control == 5) { /* renew aux value */
    aux = control = 0;
  }
  
}
