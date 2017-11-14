/*  
 * PINS DEFINITIONS 
 ***********************************/
int sensorPin = A0,
    output,
    aux = 0,
    control = 0,
    relayPin = 8;
/* END OF PINS DEFINITIONS */

/*  
 * CONFIGURATION 
 ***********************************/
#define MAXDRY 850
#define ACCEPTEDRANGE 50
#define VALVE 20000
#define COOLDOWN 10000
/* END OF CONFIGURATION AREA */


void setup() {
  Serial.begin(9600); /* initialize serial information */
  //pinMode(ledPin, OUTPUT); /* for future led feature */
  pinMode(relayPin, OUTPUT); /* initialize relayPin... */
  digitalWrite(relayPin, HIGH); /* ...and keep it open */
  Serial.println("[ - ] Reading sensor data: ");
}

void loop() {
  
  output = analogRead(sensorPin); /* read moisture value */

  Serial.print("[-] Current moisture: "); /* print some information */
  Serial.println(output);
  Serial.print("[-] Aux value: ");
  Serial.println(aux);
  Serial.print("[-] Control value: ");
  Serial.println(control);
  
  if (output > MAXDRY) { /* check if need water */
    if (aux > 10) { /* keep some control against wrong readings */
      digitalWrite(relayPin, LOW); /* water the plant! */
      Serial.println("[!] Watering the plant!");
      delay(VALVE); /* delay to keep watering the plant */
      digitalWrite(relayPin, HIGH);
      aux = 0; /* control adjust */
    }else {
      Serial.println("[!] NEED WATER");
      aux++;
    }
    delay(COOLDOWN); /* wait some time */
  } else if (output > (MAXDRY - ACCEPTEDRANGE)) { /* if is about to became dry */
      Serial.println("[!] Your plant is about to need water!");
      control++;
      /* blink leds.... */
      /* some delay. */
  } else { /* if is far from need water... */
    //digitalWrite(relayPin, HIGH);
    delay(COOLDOWN); /* just wait to read againg */
    control++;
  }

  /* aux can accumulate some wrong reading, here i clean it up */
  if (control == 5) {
    aux = control = 0;  
  }
}
