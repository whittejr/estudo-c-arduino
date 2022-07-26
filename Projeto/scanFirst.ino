#include <LiquidCrystal_I2C.h>
#include <RFID.h>
#include <SPI.h>
#include <Keypad.h>

// definições lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// buzzer
const int buzzer = 6;

// definições RFID
#define RST_PIN 5
#define SS_PIN 53
RFID rfid(SS_PIN, RST_PIN);
String tagUID = "7A 19 AC 15";
String rfidCard;


// senha
String senha = "1234";
String tempSenha;
boolean passChangeMode = false;
boolean passChanged = false;
boolean maxTry = false;
boolean rfidMode = false;
boolean activated = true;
boolean menuMode = false;
boolean passTry = false;
int cont = 0;

// leds
int vermelho = 2;
int verde = 3;
int azul = 4  ;

// definições keypad
const byte LINHAS = 4;
const byte COLUNAS = 4;

//lampada
byte lamp[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01110,
  B01110
};

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

void entrarSenha();

void setup()
{
  Serial.begin(9600);
  
  SPI.begin();
  rfid.init();

  pinMode(buzzer, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(1, lamp);
  olaMundo();
}

void loop()
{
  lcd.setCursor(3, 0);
  lcd.print("Aproxime o");
  lcd.setCursor(4, 1);
  lcd.print("Cartao...");
  
  while (rfidMode == false)
  {
    if (rfid.isCard())
    {
      if (rfid.readCardSerial())
      {
        rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
        
        Serial.println(rfidCard);
        if (rfidCard == "122 25 172 21")
        {
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print("Bem Vindo!");
            lcd.setCursor(3, 1);
            lcd.print("Alessandro!");
            digitalWrite(azul, HIGH);
            tone(buzzer, 1500);   
            delay(700);   
            noTone(buzzer);
            digitalWrite(azul, LOW);
            rfidCard = "";
            lcd.clear();
            lcd.home();
            rfidMode = true;
        }
        else {
          lcd.clear();
          lcd.print(" Acesso Negado ");
          analogWrite(vermelho, 200);
          tone(buzzer, 500);   
          delay(700);
          noTone(buzzer);
          digitalWrite(vermelho, LOW);
          lcd.clear();
          rfidCard = "";
          loop();

        }
      }
    }
  }
  lcd.clear();
  menuMode = true;
  
  while (menuMode == true)
  {
    lcd.setCursor(0, 0);
    lcd.print("A - Acesso");
    lcd.setCursor(0, 1);
    lcd.print("B - Trocar senha");
    
    keypressed = keypad.getKey();
    if (keypressed == 'A')
    {
      entrarSenha();
    }
    else if (keypressed == 'B')
    {
      trocarSenha();
    }
  }
  lcd.clear();
  
  passTry = true;
  while (passTry == true)
  {
    lcd.setCursor(1, 0);
    lcd.print("Caixa aberta");
  }
}


void entrarSenha()
{
  int k = 1;
  tempSenha = "";
  activated = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" *** ACESSO *** ");
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.blink();
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
    if (k > 7 || keypressed == '#')
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
        lcd.noBlink();
        correctPass();
      }
      else if (tempSenha != senha)
      {
        if (cont != 2)
        {
          lcd.noBlink();
          wrongPass();
          cont++;
          tempSenha = "";
          k = 1;
          lcd.blink();
        }
        else
        {
          lcd.noBlink();
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("Limite");
          lcd.setCursor(4, 1);
          lcd.print("Atingido.");
          analogWrite(vermelho, 100);
          tone(buzzer, 500);   
          delay(1000);
          noTone(buzzer);
          digitalWrite(vermelho, LOW);
          cont = 0;
          lcd.home();
          lcd.clear();
          activated = false;
          rfidMode = false;
        }
      }
    }
  }
}

  void correctPass()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acesso Liberado!");
  analogWrite(verde, 200);
  tone(buzzer, 1500);   
  delay(700);
  noTone(buzzer);
  digitalWrite(verde, LOW);
  activated = false;
  lcd.clear();
  menuMode = false;
}

void wrongPass()
{
  lcd.clear();
  lcd.print("Senha Incorreta");
  lcd.setCursor(0, 3);
  lcd.print("Tente Novamente");
  analogWrite(vermelho, 200);
  tone(buzzer, 500);   
  delay(700);
  noTone(buzzer);
  digitalWrite(vermelho, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" *** ACESSO *** ");
  lcd.setCursor(0, 1);
  lcd.print(">");
}

void trocarSenha()
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
    if (i > 7 || keypressed == '#')
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

      if (senha == tempSenha)
      {
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

void olaMundo()
{
  for (int i = 0; i < 4; i++)
  {
    lcd.setCursor(1, 0);
    lcd.print("Escola Tecnica");
    lcd.setCursor(4, 1);
    lcd.print("Electra");
    delay(500);
    lcd.clear();
    delay(500);
    i++;
   }
   lcd.setCursor(0,0);
   lcd.write(1);
   delay(2000);
}