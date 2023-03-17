/*
Name: Harguntas Singh Benipal
Date: December 23, 2022
Description: This is the program for the temperature-sensing calculator. I first intizalize all my values and have a large loop that runs once a button on the keypad
is pressed. Inside the loop, there is code for the temperature component where I get my temperature values from reading the Thermistor Pin. The loop coducts all the 
operations and then outputs the result and runs again. 
*/

#include <Keypad.h> //Include the Keypad Library 
#include <LiquidCrystal.h> //Include the LiquidCrystal Library 
 
 LiquidCrystal lcd(0, 1, 2, 3, 4, 5); //Initialize an LCD object
 
 const byte ROWS = 4;  //Four rows
 const byte COLS = 4; //Four columns as this is a 4*4 Keypad
 
 char keys [ROWS] [COLS] = {
 {'1', '2', '3', '+'},
 {'4', '5', '6', '-'},
 {'7', '8', '9', '*'},
 {'.', '0', '=', '/'}
 };  //Defining the keys in the keypad
 
 byte rowPins[ROWS] = {13,12,11,10}; //Connect keypad ROW 0, 1, 2 and 3 to these Arduino pins.
 byte colPins[COLS] = {9,8,7,6}; //Connect keypad COL 0, 1, 2 and 3 to these Arduino pins.
 
 Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  //Create Keypad variable to identify and store the pressed key.
 boolean presentValue = false; 
 boolean next = false;
 boolean final = false;
 String num1, num2;
 float answer;
 char op;
 boolean answerprinted = false;
  //Initialize variables 
 
 void setup() //Method that displays text to LCD Display
 { 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HarguntasBenipal");
  lcd.setCursor(0,1);
  lcd.print("   Calculator");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Mr.Lowe");
  lcd.setCursor(0,1);
  lcd.print("      ISU" );
  delay(3000);
  lcd.clear(); 
 }
 
 void loop()
 {
  int ThermistorPin = 0; 
  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
   //Intitialize temperature sensing variables

  char key = myKeypad.getKey(); //Get what key was pressed
 
  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'||key == '.')) 
  {
   Vo = analogRead(ThermistorPin); //Read input from the thermistor pin
   R2 = R1 * (1023.0 / (float)Vo - 1.0);
   logR2 = log(R2);
   T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
   T = T - 273.15; //Conert it into degrees celsius
 
   lcd.setCursor(0, 1);
   lcd.print(T);  
   lcd.print(" C"); //Output temperature onto LCD Display

   delay(500);
 
 
   if (answerprinted == true) //Check if answer was printed and if so, reset it
   {
    lcd.clear();
    lcd.setCursor(15,0);
    answerprinted = false;  
   }
 
   if (presentValue != true) //Get first number
   {
    num1 = num1 + key;
    int numLength = num1.length();
    lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
    lcd.print(num1);
   }
 
   else //Get second number
   {
    num2 = num2 + key;
    int numLength = num2.length();
    lcd.setCursor(15 - numLength, 1);
    lcd.print(num2);
    final = true;
   }
  }
 
  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')) //Get operation
  {
   if (presentValue == false)
   {
    presentValue = true;
    op = key;
    lcd.setCursor(15,0);
    lcd.print(op);
   }
  }
 
  else if (final == true && key != NO_KEY && key == '=')
  {
   if (op == '+'){ //Addition
   answer = num1.toFloat() + num2.toFloat();
  }
   
 else if (op == '-')
 { //Subtraction
  answer = num1.toFloat() - num2.toFloat(); 
 }
  
 else if (op == '*')
 { //Multiplication
  answer = num1.toFloat() * num2.toFloat(); 
 }

 else if (op == '/')
 { //Division
  answer = num1.toFloat() / num2.toFloat(); 
 }
  
 lcd.clear();
 lcd.setCursor(10,0);
 lcd.autoscroll();
 lcd.print(answer);
 lcd.noAutoscroll();
 answerprinted = true;
 num1 = '\0';
 num2 = '\0';
 final = false;
 presentValue = false; //Reset values
 }
}
