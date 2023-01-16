#include <Keypad.h>
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
 
const byte ROWS = 4;
const byte COLS = 4;
 
char keys [ROWS] [COLS] = {
{'1', '2', '3', '+'},
{'4', '5', '6', '-'},
{'7', '8', '9', '*'},
{'.', '0', '=', '/'}
};
 
byte rowPins[ROWS] = {13,12,11,10};
byte colPins[COLS] = {9,8,7,6};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
boolean presentValue = false;
boolean next = false;
boolean final = false;
String num1, num2;
float answer;
char op;
boolean answerprinted = false;
 
 
 
void setup()
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
//Serial.begin(9600);
 
}
 
 
 
void loop()
{
 
  // lcd.clear();  
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
 
 
 
 
 
//T = (T * 9.0)/ 5.0 + 32.0;
 
 char key = myKeypad.getKey();
 
 
 
 
if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'||key == '.'))
{
 
 Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
 
lcd.setCursor(0, 1);
  //lcd.print("Temp: ");
  lcd.print(T);  
  lcd.print(" C");
 
 
  delay(500);
 
 
if (answerprinted == true)
{
lcd.clear();
lcd.setCursor(15,0);
answerprinted = false;
}
 
if (presentValue != true)
{
num1 = num1 + key;
int numLength = num1.length();
lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
lcd.print(num1);
}
 
else
{
num2 = num2 + key;
int numLength = num2.length();
lcd.setCursor(15 - numLength, 1);
lcd.print(num2);
final = true;
}
}
 
else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
{
if (presentValue == false)
{
presentValue = true;
op = key;
lcd.setCursor(15,0);
lcd.print(op);
}
}
 
else if (final == true && key != NO_KEY && key == '='){
if (op == '+'){
answer = num1.toFloat() + num2.toFloat();
 
}
else if (op == '-'){
answer = num1.toFloat() - num2.toFloat();
 
}
else if (op == '*'){
answer = num1.toFloat() * num2.toFloat();
 
}
else if (op == '/'){
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
presentValue = false;
}
}
