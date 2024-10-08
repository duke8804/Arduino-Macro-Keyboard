#include "Keyboard.h"
#include "Mouse.h"

// Define pins for each button
const int buttonPin1 = 1;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 6;
const int buttonPin5 = 7;
const int buttonPin6 = 8;
const int buttonPin7 = 9;
const int buttonPin8 = 10;
const int buttonPin9 = 18;
const int buttonPin10 = 19;
const int buttonPin11 = 20;
const int buttonPin12 = 21;

// Variables to track the state of each button
bool buttonPin1Active = false;
bool lastButtonState1 = HIGH;

bool buttonPin2Active = false;
bool lastButtonState2 = HIGH;

bool buttonPin3Active = false;
bool lastButtonState3 = HIGH;

bool buttonPin4Active = false;
bool lastButtonState4 = HIGH;

bool buttonPin5Active = false;
bool lastButtonState5 = HIGH;

bool buttonPin6Active = false;
bool lastButtonState6 = HIGH;

bool buttonPin7Active = false;
bool lastButtonState7 = HIGH;

bool buttonPin8Active = false;
bool lastButtonState8 = HIGH;

bool buttonPin9Active = false;
bool lastButtonState9 = HIGH;

bool buttonPin10Active = false;
bool lastButtonState10 = HIGH;

bool buttonPin11Active = false;
bool lastButtonState11 = HIGH;

bool buttonPin12Active = false;
bool lastButtonState12 = HIGH;

unsigned long previousMillis = 0; // To track time for non-blocking delay
int randomInterval = 0;

void setup() {
  // Initialize button pins as inputs with pullup resistors
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);
  pinMode(buttonPin11, INPUT_PULLUP);
  pinMode(buttonPin12, INPUT_PULLUP);

  // Start the Keyboard and Mouse libraries
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // Handle button states
  // toggleButton(buttonPin1, lastButtonState1, buttonPin1Active, holdWKey, releaseWKey);
  // pressButton(buttonPin2, lastButtonState2, password1);
  // randomPressButton(buttonPin1, lastButtonState1, buttonPin1Active, holdWKey, releaseWKey);
  pressButton(buttonPin1, lastButtonState1, password1);
  pressButton(buttonPin2, lastButtonState2, password2);
  pressButton(buttonPin3, lastButtonState3, password2);
  toggleButton(buttonPin4, lastButtonState4, buttonPin4Active, holdWKey, releaseWKey);
  pressButton(buttonPin5, lastButtonState5, password2);
  toggleButton(buttonPin6, lastButtonState6, buttonPin6Active, holdLeftMouseButton, releaseLeftMouseButton);
  pressButton(buttonPin7, lastButtonState7, password2);
  pressButton(buttonPin8, lastButtonState8, password2);
  pressButton(buttonPin9, lastButtonState9, password2);
  pressButton(buttonPin10, lastButtonState10, password2);
  pressButton(buttonPin11, lastButtonState11, password2);
  randomPressButton(buttonPin12, lastButtonState12, buttonPin12Active, holdLeftMouseButton, releaseLeftMouseButton);

  // A small delay to avoid bouncing issues
  delay(10);
}

void randomPressButton(int buttonPin, bool &lastButtonState, bool &actionActive, void (*pressAction)(), void (*releaseAction)()) {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);

  // Check if the button has been pressed and released
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle the action's active state
    actionActive = !actionActive;

    // If the action is activated, set the random interval
    if (actionActive) {
      randomInterval = random(100, 351); // Set initial random interval
      previousMillis = millis();         // Initialize timing
    } else {
      releaseAction();  // Ensure release action is called when deactivated
    }
  }

  // If the action is active, perform the press and release actions at random intervals
  if (actionActive) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= randomInterval) {
      // Alternate between press and release actions
      static bool isPressed = false;
      if (isPressed) {
        releaseAction();
      } else {
        pressAction();
      }
      isPressed = !isPressed;

      // Set the next random interval and reset the timer
      randomInterval = random(200, 351);
      previousMillis = currentMillis;
    }
  }

  // Update the lastButtonState to the current state
  lastButtonState = buttonState;
}


// Function to handle button press for toggling actions
void toggleButton(int buttonPin, bool &lastButtonState, bool &actionActive, void (*activateAction)(), void (*deactivateAction)()) {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);

  // Check if the button has been pressed and released
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle the action's active state
    actionActive = !actionActive;

    if (actionActive) {
      activateAction(); // Call the activation function
    } else {
      deactivateAction(); // Call the deactivation function
    }
  }

  // Update the lastButtonState to the current state
  lastButtonState = buttonState;
}

// Function to handle button press for single actions
void pressButton(int buttonPin, bool &lastButtonState, void (*action)()) {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);

  // Check if the button has been pressed
  if (buttonState == LOW && lastButtonState == HIGH) {
    action(); // Call the action function
  }

  // Update the lastButtonState to the current state
  lastButtonState = buttonState;
}

// Function to enter the text "nope"
void password1() {
  Keyboard.print("nope");
}

// Function to enter the text "noneya"
void password2() {
  Keyboard.print("noneya");
}

// Function to press and hold the left mouse button
void holdLeftMouseButton() {
  Mouse.press(MOUSE_LEFT);
}

// Function to release the left mouse button
void releaseLeftMouseButton() {
  Mouse.release(MOUSE_LEFT);
}

// Function to hold down the 'W' key
void holdWKey() {
  Keyboard.press('w');
}

// Function to release the 'W' key
void releaseWKey() {
  Keyboard.release('w');
}

// A dummy function to use when no action is needed
void doNothing() {
  // Do nothing
}
