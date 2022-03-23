void entreSenha()
{
    int k = 5;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("* Acesso *");
    lcd.setCursor(0,1);
    lcd.print("Pass>");

    keypressed = myKeypad.getKey();
    
    if (keypressed != NO_KEY)
    {
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) 
        {
            tempPassword += keypressed;
            lcd.setCursor(k,1);
            lcd.print("*");
            k++;
        }
    }
    
    if (k > 9 || keypressed == '#')
    {
        tempPassword = "";
        k=5;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("* Acesso *");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
    }
    
    if ( keypressed == '*')
    {
        if ( tempPassword == password )
        {
            lcd.setCursor(0,0);
            lcd.print("Acesso liberado.")
            noTone(buzzer);
            //screenOffMsg = 0; 
        }

        else if (tempPassword != password)
        {
            lcd.setCursor(0,1);
            lcd.print("Senha Incorreta.");
            delay(800);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("* Acesso *");
            lcd.setCursor(0,1);
            lcd.print("Pass>");
        }
    }
}

void unlocked()
{
    printf("Acesso liberado!\n");
}
