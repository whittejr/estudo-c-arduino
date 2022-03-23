#include <LiquidCrystal.h>  
#include <Keypad.h>

//#define buzzer 5;
int cont = 0;
//string senha = "";
int pass = 1234;

int Contrast = 100;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const byte LINHAS= 4;
const byte COLUNAS= 4;

char keymap[LINHAS][COLUNAS]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[LINHAS] = {22, 23, 24, 25};
byte colPins[numCols] = {26, 27, 28, 29};

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, LINHAS, COLUNAS);

void setup()
{
    Serial.begin(9600);
  
    analogWrite(6,Contrast);
    lcd.begin(16, 2);   
    lcd.clear(); 

    lcd.write("Acesso!");
    delay(500);
    //senha = "";   
}

void loop()
{
    int tentativa;

    char key = myKeypad.getKey();

    if (key != NO_KEY)
    {
        Serial.println(key);
        lcd.setCursor(cont,1);
        lcd.write("*");
        senha = senha + key;
        cont++;
    }
    
    for (tentativa = 0; tentativa < 3; tentativa++)
    {
        println("Digite a senha: ");
        scanf("%d", &key);
        
        if (key != pass)
        {
            println("Senha Incorreta.\n\n");
        }
        else
        {
            unlocked();
            return 0;
        }
    }
}

void unlocked()
{
    printf("Acesso liberado!\n");
}

void digiteSenha()
{
     printf("Digite a senha: ");
     scanf("%d", &key);
}

void qtdSenha()
{
    for (tentativa = 0; tentativa < 3; tentativa++)
    {
        println("Digite a senha: ");
        scanf("%d", &key);
        
        if (key != pass)
        {
            println("Senha Incorreta.\n\n");
        }
        else
        {
            unlocked();
            return 0;
        }
    }
}