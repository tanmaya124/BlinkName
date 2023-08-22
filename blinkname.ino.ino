const int inputButton = 2;
int currentButtonState = 0;
int previousButtonState = HIGH;
bool nameFlashing = false;
int charIndex = 0;

char customInput[100];
int inputPosition = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inputButton, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("TANMAYA");
}

void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void morseEncryption(char letter) {
  switch (letter) {
       case 't':
      dot();
      dash();
      break;
    case 'a':
      dash();
      dot();
      dot();
      dot();
      break;
    case 'n':
      dash();
      dot();
      dash();
      dot();
      break;
    case 'm':
      dash();
      dot();
      dot();
      break;
    case 'y':
      dot();
      dot();
      dash();
      dot();
      break;
    
     default:
      break;
      break;
  }
}

void loop() {
  currentButtonState = digitalRead(inputButton);

  if (currentButtonState == LOW && previousButtonState == HIGH) {
    nameFlashing = !nameFlashing;
    charIndex = 0;
  }

  previousButtonState = currentButtonState;

  if (nameFlashing) {
    if (customInput[charIndex] != '\0') {
      char letter = customInput[charIndex];
      morseEncryption(letter);
      delay(1000);

      charIndex++;
    } else {
      nameFlashing = false;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '\n' || inputPosition >= sizeof(customInput) - 1) {
      customInput[inputPosition] = '\0';
      inputPosition = 0;
      Serial.print("First Name");
      Serial.print(customInput);
      Serial.print(" flashing");
      nameFlashing = true;
    } else {
      customInput[inputPosition] = incomingChar;
      inputPosition++;
    }
  }
}
