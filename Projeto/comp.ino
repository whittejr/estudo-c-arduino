#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Keypad.h>

// definições lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// buzzer
const int buzzer = 5;

// definições RFID
#define RST_PIN 5
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN);
String tagUID[1] = {"07 85 24 3F"};

// senha
String senha = "1234";
String tempSenha;
boolean passChangeMode = false;
boolean passChanged = false;
boolean activated = false;
int cont = 0;
int maxCont = 3;

// leds
int vermelho = 2;
int verde = 3;
int azul = 4  ;

// definições keypad
const byte LINHAS = 4;
const byte COLUNAS = 4;

char keypressed;
char keys[LINHAS][COLUNAS] =
    {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

byte rowPins[LINHAS] = {22, 23, 24, 25};
byte colPins[COLUNAS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, LINHAS, COLUNAS);

void timer();
void setup()
{
  Serial.begin(9600);
  mfrc522.PCD_Init();
  SPI.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);

  lcd.init();
}

void loop()
{
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("A - Acesso");
  lcd.setCursor(0, 1);
  lcd.print("B - Trocar senha");

  keypressed = keypad.getKey();
  if (keypressed == 'A')
  {
    int k = 1;
    tempSenha = "";
    activated = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" *** ACESSO *** ");
    lcd.setCursor(0, 1);
    lcd.print(">");

    while (activated)
    {
      keypressed = keypad.getKey();
      if (keypressed != NO_KEY)
      {
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9')
        {
          tempSenha += keypressed;
          lcd.setCursor(k, 1);
          lcd.print("*");
          k++;
        }
      }
      if (k > 5 || keypressed == '#')
      {
        tempSenha = "";
        k = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" *** ACESSO *** ");
        lcd.setCursor(0, 1);
        lcd.print(">");
      }
      if (keypressed == '*')
      {
        if (tempSenha == senha)
        {
          correctPass();
        }
        else if (tempSenha != senha)
        {
          if (cont != 2)
          {
            wrongPass();
            cont++;
            tempSenha = "";
            k = 1;
          }
          else
          {
            lcd.clear();
            lcd.print("Limite Atingido.");
            analogWrite(vermelho, 50);
            tone(buzzer, 500);   
            delay(1500);
            noTone(buzzer);
            digitalWrite(vermelho, LOW);
            cont = 0;
            lcd.home();
            timer();
          }
        }
      }
    }
  }
  else if (keypressed == 'B')
  {
    lcd.clear();
    int i;
    tempSenha = "";
    lcd.setCursor(0, 0);
    lcd.print("Senha Atual");
    lcd.setCursor(0, 1);
    lcd.print(">");
    passChangeMode = true;
    passChanged = true;

    while (passChanged)
    {
      keypressed = keypad.getKey();
      if (keypressed != NO_KEY)
      {
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9')
        {
          tempSenha += keypressed;
          lcd.setCursor(i, 1);
          lcd.print("*");
          i++;
        }
      }
      if (i > 5 || keypressed == '#')
      {
        tempSenha = "";
        i = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Senha Atual");
        lcd.setCursor(0, 1);
        lcd.print(">");
      }
      if (keypressed == '*')
      {
        i = 1;

        while (tempSenha != senha)
        {
          tempSenha = "";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Senha Incorreta");
          lcd.setCursor(0, 0);
          lcd.print("Senha Atual");
          lcd.setCursor(0, 1);
          lcd.print(">");
        }
          
          tempSenha = "";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Nova Senha");
          lcd.setCursor(0, 1);
          lcd.print(">");

          while (passChangeMode)
          {
            keypressed = keypad.getKey();
            if (keypressed != NO_KEY)
            {
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9')
              {
                tempSenha += keypressed;
                lcd.setCursor(i, 1);
                lcd.print("*");
                i++;
              }
            }
            if (i > 5 || keypressed == '#')
            {
              tempSenha = keypressed - 1;
              i = 1;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Nova Senha");
              lcd.setCursor(0, 1);
              lcd.print(">");
            }
            if (keypressed == '*')
            {
              i = 1;
              senha = tempSenha;
              passChangeMode = false;
              passChanged = false;
            }
          }
        }
      }
    }
  }
}

void timer()
{
  int i = 16;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Acesso negado.");

  do
  {
    i--;
    lcd.setCursor(7, 1);
    lcd.print(i);
    delay(1000);
  } while (i != 10);

  if (i == 10)
  {
    do
    {
      i--;
      lcd.setCursor(7, 1);
      lcd.print("0");
      lcd.print(i);
      delay(1000);
    } while (i != 1);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime a sua");
  lcd.setCursor(0, 1);
  lcd.print("tag p/ Leitura!");

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona o cartão / tag
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String conteudo = "";
  byte letra;

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();
  if (conteudo.substring(1) == "07 85 24 3F") // UID 1 - Chaveiro
  {
    Serial.println("Ola FILIPEFLOP !");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ola FILIPEFLOP !");
    lcd.setCursor(0, 1);
    lcd.print("Acesso liberado!");
    delay(3000);
  }

  else if (conteudo.substring(1) != "07 85 24 3F") // UID 2 - Cartao
  {
    Serial.println("Ola Cartao !");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ola Cartao !");
    lcd.setCursor(0, 1);
    lcd.print("Acesso Negado !");
    delay(3000);
  }
}

void wrongPass()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tente Novamente");
  analogWrite(vermelho, 50);
  tone(buzzer, 500);   
  delay(1000);
  noTone(buzzer);
  digitalWrite(vermelho, LOW);
  lcd.setCursor(0, 0);
  lcd.print(" *** ACESSO *** ");
  lcd.setCursor(0, 1);
  lcd.print(">");
}

void correctPass()
{
  analogWrite(verde, 50);
  tone(buzzer, 2200);   
  delay(1000);
  noTone(buzzer);
  digitalWrite(verde, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acesso Liberado!");
  delay(3000);
  activated = 0;
  lcd.clear();
}
