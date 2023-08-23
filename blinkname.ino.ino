const int inputButton = 2;        // Pin number for the input button
int currentButtonState = 0;      // Current state of the button (pressed or not)
int previousButtonState = HIGH;   // Previous state of the button (initialized as HIGH)
bool nameFlashing = false;        // Flag to indicate whether the name is flashing
int charIndex = 0;                // Index to track the character being flashed

char customInput[100];            // Array to store custom input
int inputPosition = 0;            // Position within the input array

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // Set the built-in LED pin as output
  pinMode(inputButton, INPUT_PULLUP); // Set the input button pin with pull-up resistor
  Serial.begin(9600);             // Initialize serial communication
  Serial.println("TANMAYA");       // Print a message on serial communication
}

// Function to represent a dot in Morse code
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to represent a dash in Morse code
void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to encode a letter into Morse code
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
    // Other cases for different letters
    // ...
    default:
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
I've added comments to explain the purpose of each variable, function, and section of the code. This should help you understand the flow and functionality of the program better.




User
give the whole code with comments
ChatGPT
Certainly! Here's the complete code with comments explaining each part:

cpp
Copy code
const int inputButton = 2;        // Pin number for the input button
int currentButtonState = 0;      // Current state of the button (pressed or not)
int previousButtonState = HIGH;   // Previous state of the button (initialized as HIGH)
bool nameFlashing = false;        // Flag to indicate whether the name is flashing
int charIndex = 0;                // Index to track the character being flashed

char customInput[100];            // Array to store custom input
int inputPosition = 0;            // Position within the input array

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // Set the built-in LED pin as output
  pinMode(inputButton, INPUT_PULLUP); // Set the input button pin with pull-up resistor
  Serial.begin(9600);             // Initialize serial communication
  Serial.println("TANMAYA");       // Print a message on serial communication
}

// Function to represent a dot in Morse code
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to represent a dash in Morse code
void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to encode a letter into Morse code
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
    case 'a':
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
  // Read the current state of the input button
  currentButtonState = digitalRead(inputButton);

  // Check if the button was pressed (transition from HIGH to LOW)
  if (currentButtonState == LOW && previousButtonState == HIGH) {
    // Toggle the nameFlashing flag and reset the charIndex
    nameFlashing = !nameFlashing;
    charIndex = 0;
  }

  // Update the previousButtonState with the currentButtonState
  previousButtonState = currentButtonState;

  // If nameFlashing is true, perform Morse code flashing
  if (nameFlashing) {
    // Check if there's a character to encode and flash
    if (customInput[charIndex] != '\0') {
      char letter = customInput[charIndex];
      // Encode the character in Morse code
      morseEncryption(letter);
      // Delay to distinguish between dots and dashes
      delay(1000);

      // Move to the next character
      charIndex++;
    } else {
      // No more characters to encode, stop flashing
      nameFlashing = false;
    }
  } else {
    // If not flashing, turn off the LED
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Check for incoming characters from Serial communication
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    // Check for newline character or input buffer full
    if (incomingChar == '\n' || inputPosition >= sizeof(customInput) - 1) {
      // Terminate the input string and reset inputPosition
      customInput[inputPosition] = '\0';
      inputPosition = 0;

      // Print a message and start flashing the name
      Serial.print("First Name");
      Serial.print(customInput);
      Serial.print(" flashing");
      nameFlashing = true;
    } else {
      // Store the incoming character in the customInput array
      customInput[inputPosition] = incomingChar;
      inputPosition++;
    }
  }
}
