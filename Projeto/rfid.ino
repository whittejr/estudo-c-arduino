#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Keypad.h>

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

// definições keypad
const byte LINHAS = 4;
const byte COLUNAS = 4;

// definições lcd
int Contrast = 100;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int cont = 0;
int maxCont = 3;
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

void codeEntry();
void timer();
void setup()
{
	Serial.begin(9600);
	mfrc522.PCD_Init();
	SPI.begin();

	analogWrite(6, Contrast);
	lcd.begin(16, 2);
	lcd.clear();

	// lcd.setCursor(0,0);
	// lcd.print("A - Inserir senha");
	// lcd.setCursor(0,1);
	// lcd.print("B - Trocar senha");

	// timer();
	// lcd.setCursor(0,0);
	// lcd.print("Aproxime a sua");
	// lcd.setCursor(0,1);
	// lcd.print("tag p/ Leitura!");
}

void loop()
{
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
		lcd.print(" *** ALARM *** ");
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
				lcd.print(" *** ALARM *** ");
				lcd.setCursor(0, 1);
				lcd.print(">");
			}
			if (keypressed == '*')
			{
				if (tempSenha == senha)
				{
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Access Granted!");
					delay(3000);
					activated = 0;
				}
				else if (tempSenha != senha)
				{
					if (cont != 2)
					{
						lcd.setCursor(0, 1);
						lcd.print("Wrong! Try Again");
						delay(3000);
						lcd.setCursor(0, 0);
						lcd.print(" *** ACESSO *** ");
						lcd.setCursor(0, 1);
						lcd.print(">");
						lcd.clear();
						cont++;
					}
					else if (tempSenha != senha)
					{
						if (cont != 2)
						{
							lcd.clear();
							lcd.setCursor(0, 0);
							lcd.print("Tente Novamente");
							delay(2000);
							lcd.setCursor(0, 0);
							lcd.print(" *** ACESSO *** ");
							lcd.setCursor(0, 1);
							lcd.print(">");
							cont++;

							tempSenha = "";
							k = 1;
						}
						else
						{
							lcd.clear();
							lcd.home();
							lcd.print("Limite Atingido.");
							delay(3000);
							// timer();
							rfid_func();
						}
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
}

void enterPassword()
{
	int k = 1;
	tempSenha = "";
	activated = true;
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" *** ALARM *** ");
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
		if (k > 9 || keypressed == '#')
		{
			tempSenha = "";
			k = 5;
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print(" *** ACESSO *** ");
			lcd.setCursor(0, 1);
			lcd.print("Pass>");
		}
		if (keypressed == '*')
		{
			if (tempSenha == senha)
			{
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Access Granted!");
				delay(3000);
				activated = 0;
			}
			else if (tempSenha != senha)
			{
				if (cont != 2)
				{
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Tente Novamente");
					delay(2000);
					lcd.setCursor(0, 0);
					lcd.print(" *** ACESSO *** ");
					lcd.setCursor(0, 1);
					lcd.print(">");
					cont++;

					tempSenha = "";
					k = 1;
				}
				else
				{
					lcd.clear();
					lcd.home();
					lcd.print("Limite Atingido.");
					delay(3000);
					// timer();
					rfid_func();
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
	}

	void rfid_func()
	{
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

		boolean tagVerificada = false;

		lcd.clear();
		lcd.home();
		conteudo.toUpperCase();

		for (int indice = 0; indice < sizeof(tagUID); indice++)
		{
			if (conteudo.substring(1) == tagUID[0]) // UID 1
			{
				lcd.print("Ola!");
				lcd.setCursor(0, 1);
				lcd.println("Acesso Liberado!");

				// tag encontrada
				tagVerificada = true;

				delay(3000);
				setup();
				conteudo = "";
			}
		}

		if ((tagVerificada == false) && (conteudo != ""))
		{

			lcd.print("Usuario Negado!");
			lcd.setCursor(0, 1);
			lcd.println("Acesso Negado!  ");

			delay(3000);
			setup();
			conteudo = "";
		}
	}
