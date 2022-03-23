#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char initial_password[4] = {'1', '2', '3', '4'};
char password[4];
char key_pressed = 0;
uint8_t i = 0;

const byte LINHAS= 4;
const byte COLUNAS= 4;

char keymap[LINHAS][COLUNAS]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[LINHAS] = {6, 7, 8, 9};
byte colPins[COLUNAS] = {13, A0, A1, A2};

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, LINHAS, COLUNAS);
 
void setup()
{
  
  lcd.begin(16, 2);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("!AREA DE ACESSO!");
  delay(3000);
}
 
void loop()
{
 
  lcd.clear();
  if (key_pressed)
      {
        password[i++] = key_pressed;
        lcd.print("*");
      }
      if (i == 4)
      {
        delay(200);
        if (!(strncmp(password, initial_password, 4)))
        {
          lcd.clear();
          lcd.print("Pass Accepted");
         }
  
}
}