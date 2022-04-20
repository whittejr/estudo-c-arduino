
#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Keypad.h> 

//definições RFID
#define RST_PIN         5
#define SS_PIN          53
MFRC522 mfrc522(SS_PIN, RST_PIN);
String tagUID[1] ={"07 85 24 3F"};

//senha
String senha="1234";
String tempSenha;

boolean passChangeMode = false;
boolean passChanged = false;
boolean activated = false;

//definições keypad
const byte LINHAS = 4;
const byte COLUNAS = 4;

//definições lcd
int Contrast = 100;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int cont = 0;

char keypressed;
char keys [LINHAS] [COLUNAS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[LINHAS] = {22, 23, 24, 25};
byte colPins[COLUNAS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, LINHAS, COLUNAS);

void timer();
void setup()
{
    Serial.begin(9600);
    mfrc522.PCD_Init();   // Init MFRC522
    SPI.begin();
  
    analogWrite(6,Contrast);
    lcd.begin(16, 2);
    lcd.clear();

    //lcd.setCursor(0,0);
    //lcd.print("A - Inserir senha");
    //lcd.setCursor(0,1);
    //lcd.print("B - Trocar senha");
  
    //timer();
    //lcd.setCursor(0,0);
    //lcd.print("Aproxime a sua");
    //lcd.setCursor(0,1);
    //lcd.print("tag p/ Leitura!");
}
  
void loop()
{
 
    lcd.setCursor(0,0);
    lcd.print("A - Inserir senha");
    lcd.setCursor(0,1);
    lcd.print("B - Trocar senha");

    keypressed = myKeypad.getKey();

    if (keypressed =='A')
    {
        void enterPassword();
    }
    else if (keypressed == 'B')
    {
    lcd.clear();
    int i=1;
    tempPassword = "";
    lcd.setCursor(0,0);
    lcd.print("Senha Atual");
    lcd.setCursor(0,1);
    lcd.print(">");
    passChangeMode = true;
    passChanged = true;
      
        while(passChanged)
        {    
            keypressed = myKeypad.getKey();
            if (keypressed != NO_KEY)
            {
                if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' )
                {
                    tempPassword += keypressed;
                    lcd.setCursor(i,1);
                    lcd.print("*");
                    i++;
                }
            }
            if (i > 5 || keypressed == '#')
            {
                tempPassword = "";
                i=1;
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Senha Atual");
                lcd.setCursor(0,1);
                lcd.print(">"); 
            }
            if ( keypressed == '*')
            {
            i=1;
                if (password == tempPassword)
                {
                    tempPassword="";
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Nova Senha");
                    lcd.setCursor(0,1);
                    lcd.print(">");
                    while(passChangeMode)
                    {
                        keypressed = myKeypad.getKey();
                        if (keypressed != NO_KEY)
                        {
                            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                                keypressed == '8' || keypressed == '9' )
                            {
                                tempPassword += keypressed;
                                lcd.setCursor(i,1);
                                lcd.print("*");
                                i++;
                            }   
                        }
                        if (i > 5 || keypressed == '#')
                        {
                            tempPassword = "";
                            i=1;
                            tone(buzzer, 2000, 100);
                            lcd.clear();
                            lcd.setCursor(0,0);
                            lcd.print("Nova Senha");
                            lcd.setCursor(0,1);
                            lcd.print(">");
                        }
                        if ( keypressed == '*')
                        {
                            i=1;
                            tone(buzzer, 2000, 100);
                            password = tempPassword;
                            passChangeMode = false;
                            passChanged = false;
                        }
                    }
                }
            }
        }
    }
}

void enterPassword()
{
    int k=5;
    tempSenha = "";
    activated = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" *** ALARM *** ");
    lcd.setCursor(0,1);
    lcd.print("Pass>");
    
    while(activated)
    {
        keypressed = keypad.getKey();
        if (keypressed != NO_KEY)
        {
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' )
            {
                tempSenha += keypressed;
                lcd.setCursor(k,1);
                lcd.print("*");
                k++;
            }
        }
        if (k > 9 || keypressed == '#')
        {
            tempSenha = "";
            k=5;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" *** ALARM *** ");
            lcd.setCursor(0,1);
            lcd.print("Pass>");
        }
        if ( keypressed == '*')
        {
            if ( tempSenha == senha )
            {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Access Granted!");
            }
            else if (tempSenha != senha)
            {
                lcd.setCursor(0,1);
                lcd.print("Wrong! Try Again");
                delay(2000);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print(" *** ALARM *** ");
                lcd.setCursor(0,1);
                lcd.print("Pass>");
            }
        }
    }
}


    
      