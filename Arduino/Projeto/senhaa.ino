#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
#include <Keypad.h> 


const byte LINHAS = 4;
const byte COLUNAS = 4;

int Contrast = 5;

int cont = 0;
String senha = "";

char keys [LINHAS] [COLUNAS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[LINHAS] = {22, 23, 24, 25};//pinos das linhas
byte colPins[COLUNAS] = {26, 27, 28, 29};//pinos das colunas

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, LINHAS, COLUNAS);


void setup(){
   Serial.begin(9600);
   lcd.begin(COLUNAS,LINHAS);
   analogWrite(6,Contrast);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.write("Digite sua senha:");
   senha="";
   }
  
void loop(){
  
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    lcd.setCursor(cont,1);  
    lcd.write("*");
    senha = senha + key;
    cont++;
    
    if (cont==4) {
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.write("Digite a senha:");
    Serial.print(senha);
    cont=0;
      
      if(senha == "4321"){
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.write("Senha correta");
      delay(2000);
      setup();
      }
      
 else{
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.write("Senha incorreta");
    delay(2000);
    setup();
     }
    }
  }
}