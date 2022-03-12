/*                                                                                                                                                               
      _____          ____  _____   ______         _____           _____   ______         _____     ____   ____  _____      _____      ______  _____   ______   
 ___|\     \    ____|\   \|\    \ |\     \    ___|\    \         |\    \ |\     \    ___|\    \   |    | |    ||\    \    /    /| ___|\     \|\    \ |\     \  
|    |\     \  /    /\    \\\    \| \     \  /    /\    \         \\    \| \     \  /    /\    \  |    | |    || \    \  /    / ||     \     \\\    \| \     \ 
|    | |     ||    |  |    |\|    \  \     ||    |  |____|         \|    \  \     ||    |  |____| |    | |    ||  \____\/    /  /|     ,_____/|\|    \  \     |
|    | /_ _ / |    |__|    | |     \  |    ||    |    ____          |     \  |    ||    |    ____ |    | |    | \ |    /    /  / |     \--'\_|/ |     \  |    |
|    |\    \  |    .--.    | |      \ |    ||    |   |    |         |      \ |    ||    |   |    ||    | |    |  \|___/    /  /  |     /___/|   |      \ |    |
|    | |    | |    |  |    | |    |\ \|    ||    |   |_,  |         |    |\ \|    ||    |   |_,  ||    | |    |      /    /  /   |     \____|\  |    |\ \|    |
|____|/____/| |____|  |____| |____||\_____/||\ ___\___/  /|         |____||\_____/||\ ___\___/  /||\___\_|____|     /____/  /    |____ '     /| |____||\_____/|
|    /     || |    |  |    | |    |/ \|   ||| |   /____ / |         |    |/ \|   ||| |   /____ / || |    |    |    |`    | /     |    /_____/ | |    |/ \|   ||
|____|_____|/ |____|  |____| |____|   |___|/ \|___|    | /          |____|   |___|/ \|___|    | /  \|____|____|    |_____|/      |____|     | / |____|   |___|/
  \(    )/      \(      )/     \(       )/     \( |____|/             \(       )/     \( |____|/      \(   )/         )/           \( |_____|/    \(       )/  
   '    '        '      '       '       '       '   )/                 '       '       '   )/          '   '          '             '    )/        '       '   
                                                    '                                      '                                             '                     
*/
#include <ESP8266WiFi.h>
#include <Wire.h>					/* LCD I2C https://github.com/johnrickman/LiquidCrystal_I2C */
#include <LiquidCrystal_I2C.h>		/* LCD I2C https://github.com/johnrickman/LiquidCrystal_I2C */
LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void custom0(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(0);
	lcd.write(1);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
}

void custom1(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(1);
	lcd.write(2);
	lcd.print(" ");
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(7);
	lcd.write(4);
}

void custom2(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(6);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(4);
}

void custom3(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(6);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(4);
	lcd.write(5);
}

void custom4(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(3);
	lcd.write(4);
	lcd.write(7);
	lcd.setCursor(x, y + 1);
	lcd.print(" ");
	lcd.print(" ");
	lcd.write(7);
}

void custom5(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(3);
	lcd.write(6);
	lcd.write(6);
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(4);
	lcd.write(5);
}

void custom6(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(0);
	lcd.write(6);
	lcd.write(6);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
}

void custom7(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(1);
	lcd.write(1);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.print(" ");
	lcd.print(" ");
	lcd.write(7);
}

void custom8(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(0);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
}

void custom9(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(0);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.print(" ");
	lcd.write(4);
	lcd.write(5);
}
void customA(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(255);
}

void customB(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(6);
	lcd.write(5);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(6);
	lcd.write(2);
}

void customC(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(1);
	lcd.write(1);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(4);
}

void customD(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(1);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(4);
	lcd.write(5);
}

void customE(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(6);
	lcd.write(6);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(4);
	lcd.write(4);
}

void customF(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(6);
	lcd.write(6);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
}

void customG(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(1);
	lcd.write(1);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(2);
}

void customH(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(4);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(255);
}

void customI(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(1);
	lcd.write(255);
	lcd.write(1);
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(255);
	lcd.write(4);
}

void customJ(int x, int y)
{
	lcd.setCursor(x + 2, 0);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(4);
	lcd.write(5);
}

void customK(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(4);
	lcd.write(5);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(2);
}

void customL(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(4);
	lcd.write(4);
}

void customM(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(3);
	lcd.write(5);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(254);
	lcd.write(255);
}

void customN(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(2);
	lcd.write(254);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(3);
	lcd.write(5);
}

void customP(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
}

void customQ(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(1);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(255);
	lcd.write(4);
}

void customR(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(6);
	lcd.write(2);
	lcd.setCursor(x, y + 1);
	lcd.write(255);
	lcd.write(254);
	lcd.write(2);
}

void customS(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(8);
	lcd.write(6);
	lcd.write(6);
	lcd.setCursor(x, y + 1);
	lcd.write(4);
	lcd.write(4);
	lcd.write(5);
}

void customT(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(1);
	lcd.write(255);
	lcd.write(1);
	lcd.setCursor(x, y + 1);
	lcd.write(254);
	lcd.write(255);
}

void customU(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(254);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
}

void customV(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(3);
	lcd.write(254);
	lcd.write(254);
	lcd.write(5);
	lcd.setCursor(x + 1, y + 1);
	lcd.write(2);
	lcd.write(8);
}

void customW(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(255);
	lcd.write(254);
	lcd.write(254);
	lcd.write(255);
	lcd.setCursor(x, y + 1);
	lcd.write(3);
	lcd.write(8);
	lcd.write(2);
	lcd.write(5);
}

void customX(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
	lcd.setCursor(x, y + 1);
	lcd.write(8);
	lcd.write(254);
	lcd.write(2);
}

void customY(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(3);
	lcd.write(4);
	lcd.write(5);
	lcd.setCursor(x + 1, y + 1);
	lcd.write(255);
}

void customZ(int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(1);
	lcd.write(6);
	lcd.write(5);
	lcd.setCursor(x, y + 1);
	lcd.write(8);
	lcd.write(7);
	lcd.write(4);
}

void letters1(int x, int y)
{
	customA(x, y);
	x = x + 4;
	customB(x, y);
	x = x + 4;
	customC(x, y);
	x = x + 4;
	customD(x, y);
	x = x + 4;
	customE(x, y);
	x = x + 4;
	delay(500);
}

void printDigits(int digits, int x, int y)
{
	switch (digits)
	{
	case 0:
		custom0(x, y);
		break;
	case 1:
		custom1(x, y);
		break;
	case 2:
		custom2(x, y);
		break;
	case 3:
		custom3(x, y);
		break;
	case 4:
		custom4(x, y);
		break;
	case 5:
		custom5(x, y);
		break;
	case 6:
		custom6(x, y);
		break;
	case 7:
		custom7(x, y);
		break;
	case 8:
		custom8(x, y);
		break;
	case 9:
		custom9(x, y);
		break;
	}
}

/* Khai báo Charater LCD font chữ lớn */
byte LT[8] =
	{
		B00111,
		B01111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111};
byte UB[8] =
	{
		B11111,
		B11111,
		B11111,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000};
byte RT[8] =
	{

		B11100,
		B11110,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111};
byte LL[8] =
	{

		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B01111,
		B00111};
byte LB[8] =
	{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B11111,
		B11111,
		B11111};
byte LR[8] =
	{
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11110,
		B11100};
byte MB[8] =
	{
		B11111,
		B11111,
		B11111,
		B00000,
		B00000,
		B00000,
		B11111,
		B11111};
byte block[8] =
	{
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111,
		B11111};
byte traitim[] = {
	B00000,
	B00000,
	B01010,
	B11111,
	B11111,
	B01110,
	B00100,
	B00000};
