/* Arduino Calculator, created using 16x2 LCD Display, Arduino Uno,
and a 4x4 keypad developed using the concept of button matrix*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Define keypad layout, 4 rows and 4 columns
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '/'},
  {'C', '0', '=', '*'}
};

// Define the keypad pin configurations
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int firstNum = 0;
int secondNum = 0;
char operatr = ' ';
bool opSelected = false;

void setup()
{
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Welcome");
  lcd.setCursor(2, 1);
  delay(2000);  // Delay for 2 seconds
  lcd.clear();  // Clear the screen
  lcd.setCursor(0, 0);
  
  // Display welcome message
  lcd.print("Arduino Calc");
  lcd.setCursor(0, 1);
  lcd.print("by Abdul");
  delay(2000); 
  lcd.clear();  // Clear the screen
  lcd.setCursor(0, 0);  // Set cursor to the first row to receive input
}

void loop()
{
  char newKey = myKeypad.getKey();
  
  if (newKey != NO_KEY) {
    if (newKey == 'C') {
      // Clear the LCD and reset variables
      lcd.clear();
      lcd.setCursor(0, 0);
      firstNum = 0;
      secondNum = 0;
      operatr = ' ';
      opSelected = false;
    } else if (newKey == '+' || newKey == '-' || newKey == '*' || newKey == '/') {
      // Select operation if not already selected
      if (!opSelected) {
        operatr = newKey;
        opSelected = true;
        lcd.print(newKey);
      }
    } else if (newKey == '=') {
      // Perform calculation when equals key is pressed
      if (opSelected) {
        float result;
        switch (operatr) {
          case '+':
            result = firstNum + secondNum;
            break;
          case '-':
            result = firstNum - secondNum;
            break;
          case '*':
            result = firstNum * secondNum;
            break;
          case '/':
            if (secondNum != 0) {
              result = firstNum / (float)secondNum;
            } else {
              result = 0;  // Handle division by zero
            }
            break;
          default:
            result = 0;
            break;
        }
        // Display the result on the LCD
        lcd.clear();
        lcd.setCursor(8, 1);
        if (result == (int)result) {
          lcd.print((int)result);  // Print as integer if the result is an integer
        } else {
          lcd.print(result);  // Print as float if the result is a float
        }
        firstNum = (int)result;  // Store the result for further operations
        secondNum = 0;
        operatr = ' ';
        opSelected = false;
      }
    } else {
      // Update numbers based on key presses
      if (!opSelected) {
        firstNum = firstNum * 10 + (newKey - '0');
        lcd.print(newKey);
      } else {
        secondNum = secondNum * 10 + (newKey - '0');
        lcd.print(newKey);
      }
    }
  }
}
