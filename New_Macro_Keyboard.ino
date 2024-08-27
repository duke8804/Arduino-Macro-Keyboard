#include "Keyboard.h"
#include "Mouse.h"


// Define pins for each button
const int buttonPin1 = 4;
const int buttonPin2 = 9;
const int buttonPin3 = 5;
const int buttonPin4 = 8;
const int buttonPin5 = 6;
const int buttonPin6 = 7;

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

void setup() {
  // Initialize button pins as inputs with pullup resistors
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);

  // Start the Keyboard and Mouse libraries
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // Handle button states
  // toggleButton(buttonPin#, lastButtonState#, buttonPin#Active, holdfunction, releasefunction);
  // pressButton(buttonPin#, lastButtonState#, function);
  toggleButton(buttonPin1, lastButtonState1, buttonPin1Active, holdWKey, releaseWKey);
  pressButton(buttonPin2, lastButtonState2, password1);
  pressButton(buttonPin3, lastButtonState3, password2);
  pressButton(buttonPin4, lastButtonState4, doNothing);
  pressButton(buttonPin5, lastButtonState5, doNothing);
  pressButton(buttonPin6, lastButtonState6, doNothing);

  // A small delay to avoid bouncing issues
  delay(10);
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
