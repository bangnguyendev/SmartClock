#include <Arduino.h>
#line 1 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
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
/* LIBRARY ARDUINO DEFINE  */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> /* Get data Weather - http */
#include <ESP8266httpUpdate.h> /* Updated OTA */
#include <WiFiClientSecure.h>

#include <time.h>
#include <Wire.h>			   /* LCD I2C https://github.com/johnrickman/LiquidCrystal_I2C */
#include <LiquidCrystal_I2C.h> /* LCD I2C https://github.com/johnrickman/LiquidCrystal_I2C */
#include <EEPROM.h>
#include <ArduinoJson.h> /* ARDUINOJSON_VERSION "6.x.x" */

/* USER DEFINE  */
#include "../../../SmartClock/include/LCD_2004_define.h"	  /* DEFINE MACRO */
#include "../../../SmartClock/include/Macro_define.h"		  /* LCD2004 - CHARACTER LCD */
#include "../../../SmartClock/include/DigiCertGlobalRootCA.h" /* DEFINE DigiCertGlobalRootCA */

#line 33 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void setup();
#line 190 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void loop();
#line 199 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Check_Status_Button();
#line 384 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Reload_Localtime_NTP();
#line 397 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Setup_Local_RealTime();
#line 732 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Choose_location();
#line 931 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Call_Weather_Every_10Min();
#line 952 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Weather_Online_sever();
#line 1032 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void smartConfig_ndb();
#line 1120 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Setup_AlarmClock();
#line 1227 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Set_Hour_Alarm();
#line 1307 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Set_Minute_Alarm();
#line 1395 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Active_Alarm();
#line 1507 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
bool bool_Test_Wifi(void);
#line 1561 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void update_FOTA();
#line 1712 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void Welcome_Smartclock();
#line 33 "d:\\Git_NDB\\SmartClock\\src\\main\\main.ino"
void setup()
{
	/* Initialize Serial. */
	Serial.begin(115200);

	/* Initialize Bell, Led & Button. */
	pinMode(PIN_signal_Bell, OUTPUT);
	digitalWrite(PIN_signal_Bell, 1);

	pinMode(Button_Mode, INPUT);
	digitalWrite(Button_Mode, HIGH);

	delay(10);
	/* Initialize the lcd, Print a message to the LCD. */
	lcd.init();
	lcd.createChar(0, LT);
	lcd.createChar(1, UB);
	lcd.createChar(2, RT);
	lcd.createChar(3, LL);
	lcd.createChar(4, LB);
	lcd.createChar(5, LR);
	lcd.createChar(6, MB);
	lcd.createChar(7, block);
	lcd.backlight();
	lcd.clear();
	delay(500);

	/* Initialize eeprom */
	EEPROM.begin(512);
	Serial.println("\n\n>>>>>>>>>> Read EEPROM \n");
	Serial.printf("Status Alarm: %d (1: ON - 0: OFF) \n", status_Mode_Alarm);
	/* Lấy giờ hẹn từ EEPROM */
	hen_gio = EEPROM.read(index_eeprom_hengio);
	Serial.printf("Var hen_gio: %d \n", hen_gio);

	/* Lấy phút hẹn từ EEPROM */
	hen_phut = EEPROM.read(index_eeprom_henphut);
	Serial.printf("Var hen_phut: %d \n", hen_phut);

	/* Lấy vị trí từ EEPROM */
	value_Location_EEPROM = EEPROM.read(index_eeprom_location_eeprom);
	Serial.printf("Var value_Location_EEPROM: %d \n\n", value_Location_EEPROM);

	Serial.println(">>>>>>>>>> READ SSID PASS EEROM  \n");
	lcd.setCursor(0, 0);
	lcd.print("Found saved wifi!");

	/* read data Wifi from eeprom */
	/* for ssid and pass */
	Serial.println("Reading EEPROM ssid ......");
	String esid = "";
	for (int i = 0; i < index_eeprom_SSID; ++i)
	{
		esid += char(EEPROM.read(i));
	}
	Serial.print(">>>>> SSID: ");
	Serial.println(esid);

	lcd.setCursor(0, 1);
	lcd.print("ID Wifi:");
	for (int b = 0; b < 9; b++)
	{
		/* Check khi nao toi ki tu trang thi ngat khoi viec in */
		if (esid[b] != esid[index_eeprom_SSID - 1])
		{
			lcd.print(esid[b]);
			delay(100);
		}
		else
		{
			break;
		}
	}
	lcd.print("...");
	/* pass se k in ra man hinh lcd */
	Serial.println("\nReading EEPROM pass ......");
	String epass = "";
	for (int i = 32; i < index_eeprom_PASS; ++i)
	{
		epass += char(EEPROM.read(i));
	}
	Serial.print(">>>>> PASS: <Done>");
	// Serial.println(epass);
	Serial.println("\n");
	/* nho check lai dieu kien cho nay khi < 1 */
	if (esid.length() > ESP_NB_ONE)
	{
		WiFi.mode(WIFI_STA);
		WiFi.begin(esid.c_str(), epass.c_str());

		if (bool_Test_Wifi()) /* Nếu kết nối được wifi */
		{
			lcd.createChar(1, traitim);
			Serial.println("");
			Serial.println("Wifi ConnectionSuccessful!!!");

			for (int i = 0; i < 20; i++)
			{
				lcd.setCursor(i, 1);
				lcd.write(1); // chay ki tu trai tim
				delay(140);
			}
			lcd.setCursor(0, 2);
			lcd.print("ConnectionSuccessful");
			lcd.setCursor(0, 3);
			lcd.print("Start connecting!");
			delay(1500);
		}
		else //! KHÔNG THỂ KẾT NỐI
		{
			lcd.setCursor(0, 2);
			lcd.print("WL_CONNECT_FAILED...");
			lcd.setCursor(0, 3);
			lcd.print("--------oOOo--------");
			delay(1000);
			/* vào tìm kết nối wifi*/
			Serial.println("WL_CONNECT_FAILED !!!");
			Serial.println("Yêu cầu sử dụng App EspTouch !!!");
			smartConfig_ndb();
		}
	}
	/* nếu SSID nhỏ hơn 0 (tên wifi không đúng)... thì Yêu cầu sử dụng App EspTouch */
	else
	{
		Serial.println("Tên Wifi không đúng hoặc không hợp lệ !!!");
		Serial.println("Yêu cầu sử dụng App EspTouch !!!");
		smartConfig_ndb();
	}
	WiFi.mode(WIFI_STA);
	Serial.println("");
	WiFi.printDiag(Serial);
	// In địa chỉ IP
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("\n");
	
	// Synchronize time useing SNTP. This is necessary to verify that
	// the TLS certificates offered by the server are currently valid.
	/* In cases when NTP is not used, app must set a time manually to check cert validity */
	/* 1. Cập nhật thời gian từ sever vn.pool.ntp.org */
	Reload_Localtime_NTP();

	/* 2. Check firmware coi có cập nhật không?  */
	update_FOTA();

	/* Màn hình khởi tạo chào mừng */
	Serial.println("Chạy màn hình LCD khởi tạo chào mừng");
	Welcome_Smartclock();

	/* truy cap den thoi tiet dia phuong da luu o eeprom */
	Serial.println("Truy cập đến thời tiết địa phương");
	time_dem_thoitiet = millis();
	Weather_Online_sever();
}

void loop()
{
	Check_Status_Button();
	Call_Weather_Every_10Min();
	Setup_Local_RealTime();

	yield(); // disble Soft WDT reset - NodeMCU
}

void Check_Status_Button()
{
	if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
	{
		delay(500); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
		{
			lcd.clear();
			unsigned long startTime = millis(); // giá trị ban đầu được gán bằng giá trị hiện tại của millis
			Serial.printf("digitalRead(Button_Mode): %d \n", digitalRead(Button_Mode));

			while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
			{
				Serial.printf("Thời gian đè giữ nút nhấn: %d ms\n", (millis() - startTime));
				couter_Mode = (millis() - startTime) / 1000;
				couter_Mode = couter_Mode / 1 % 10;
				lcd.setCursor(0, 0);
				lcd.print("Couter: ");
				lcd.print(couter_Mode);
				lcd.print(" seconds  ");
				if (couter_Mode < 1)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode Selection      ");
				}
				/* vao mode OTA */
				else if (couter_Mode >= 7)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Update OTA ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
				}
				/* vao mode setup wifi */
				else if (couter_Mode >= 5)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Wifi Change");
					lcd.setCursor(0, 2);
					lcd.print("         Update OTA ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
				}
				/* vao mode setup vi tri thoi tiet */
				else if (couter_Mode >= 3)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Location   ");
					lcd.setCursor(0, 2);
					lcd.print("         Wifi Change");
					lcd.setCursor(0, 3);
					lcd.print("         Update OTA ");
				}
				/* vao mode setup bao thuc */
				else if (couter_Mode >= 1)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Alarm      ");
					lcd.setCursor(0, 2);
					lcd.print("         Location   ");
					lcd.setCursor(0, 3);
					lcd.print("         Wifi Change");
				}
				yield(); // disble Soft WDT reset - NodeMCU
			};
			Serial.printf("couter_Mode: ");
			Serial.println(couter_Mode);
			/* Update FOTA mode*/
			if (couter_Mode >= 7)
			{
				/* Update FOTA mode*/
				lcd.clear();
				customU(0, 0);
				delay(200);
				customP(3, 0);
				delay(200);
				customD(3 + 3, 0);
				delay(200);
				customA(3 + 3 + 3, 0);
				delay(200);
				customT(3 + 3 + 3 + 3, 0);
				delay(200);
				customE(3 + 3 + 3 + 3 + 3, 0);
				delay(200);

				customF(4, 2);
				delay(200);
				custom0(4 + 4, 2);
				delay(200);
				customT(4 + 4 + 4, 2);
				delay(200);
				customA(4 + 4 + 4 + 5, 2);
				delay(1000);
				/* Hien thi message tu Update OTA */
				update_FOTA();
			}
			/* vao mode setup wifi */
			else if (couter_Mode >= 5)
			{
				/* vao mode setup wifi */
				lcd.clear();
				customS(4, 0);
				delay(100);
				customE(4 + 4, 0);
				delay(100);
				customT(4 + 4 + 4, 0);

				delay(100);
				customW(2, 2);
				delay(100);
				customI(2 + 3 + 2, 2);
				delay(100);
				customF(2 + 3 + 4 + 2, 2);
				delay(100);
				customI(2 + 3 + 4 + 4 + 2, 2);
				delay(1000);
				smartConfig_ndb();
				lcd.clear();
			}
			/* vao mode setup vi tri thoi tiet */
			else if (couter_Mode >= 3)
			{
				lcd.clear();
				customL(0, 0);
				delay(100);
				custom0(0 + 4, 0);
				delay(100);
				customC(0 + 4 + 4, 0);
				delay(100);
				customA(0 + 4 + 4 + 4, 0);

				customT(4, 2);
				delay(100);
				customI(4 + 4, 2);
				delay(100);
				custom0(4 + 4 + 4, 2);
				delay(100);
				customN(4 + 4 + 4 + 4, 2);

				delay(1000);
				lcd.clear();
				/* Chon vi tri doc gia tri thoi tiet */
				Choose_location();
				/* Lay gia tri thoi tiet tai vi tri da chon */
				Weather_Online_sever();
				lcd.clear();
			}
			/* vao mode setup bao thuc */
			else if (couter_Mode >= 1)
			{
				lcd.clear();
				customS(4, 0);
				delay(100);
				customE(4 + 4, 0);
				delay(100);
				customT(4 + 4 + 4, 0);

				customA(0, 2);
				delay(100);
				customL(0 + 4, 2);
				delay(100);
				customA(0 + 4 + 4, 2);
				delay(100);
				customR(0 + 4 + 4 + 4, 2);
				delay(100);
				customM(0 + 4 + 4 + 4 + 4, 2);
				delay(1000);
				lcd.clear();
				Setup_AlarmClock();
				lcd.clear();
			}
		}
	}
}

/*
██╗      ██████╗  ██████╗ █████╗ ██╗  ████████╗██╗███╗   ███╗███████╗    ███╗   ██╗████████╗██████╗
██║     ██╔═══██╗██╔════╝██╔══██╗██║  ╚══██╔══╝██║████╗ ████║██╔════╝    ████╗  ██║╚══██╔══╝██╔══██╗
██║     ██║   ██║██║     ███████║██║     ██║   ██║██╔████╔██║█████╗      ██╔██╗ ██║   ██║   ██████╔╝
██║     ██║   ██║██║     ██╔══██║██║     ██║   ██║██║╚██╔╝██║██╔══╝      ██║╚██╗██║   ██║   ██╔═══╝
███████╗╚██████╔╝╚██████╗██║  ██║███████╗██║   ██║██║ ╚═╝ ██║███████╗    ██║ ╚████║   ██║   ██║
╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝    ╚═╝  ╚═══╝   ╚═╝   ╚═╝
*/
void Reload_Localtime_NTP()
{
	configTime(7 * 3600, 0, "vn.pool.ntp.org", "time.nist.gov");
	Serial.println("Update Time <<< - >>> vn.pool.ntp.org \n");
	while (!time(nullptr))
	{
		Serial.println("\nWaiting for time");
		Serial.print(".");
		delay(1000);
		yield(); // disble Soft WDT reset - NodeMCU
	}
}

void Setup_Local_RealTime()
{
	/* Mỗi năm mới sẽ reload lại thời gian tren NTP một lần */
	if ((thang == 12) && (ngay == 31))
	{
		if ((gio == 12) && (phut == 00))
		{
			if (giay < 10)
			{
				Serial.println("\nCập nhật thời gian mỗi năm.");
				Reload_Localtime_NTP();
			}
		}
	}

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer_NAM, 80, "%Y", timeinfo);
	strftime(buffer_THANG, 80, "%m", timeinfo);
	strftime(buffer_NGAY, 80, "%d", timeinfo);
	strftime(buffer_THU, 80, " %A ", timeinfo);
	strftime(buffer_thu_be, 80, " %w ", timeinfo);
	strftime(buffer_N_T_N, 80, "%d %B %Y", timeinfo);
	strftime(buffer_GIO, 80, "%H", timeinfo);
	strftime(buffer_PHUT, 80, "%M", timeinfo);
	strftime(buffer_GIAY, 80, "%S", timeinfo);
	strftime(buffer_sent_serial, 80, "%H:%M:%S %d-%B-%Y", timeinfo);

	nam = atoi(buffer_NAM);
	thang = atoi(buffer_THANG);
	ngay = atoi(buffer_NGAY);
	thu = atoi(buffer_thu_be);
	gio = atoi(buffer_GIO);
	phut = atoi(buffer_PHUT);
	giay = atoi(buffer_GIAY);

	if (nam < 2022) /*neu nam duoi 2022 cua nghia la time chua dc update */
	{
		/* lcd hien thi chu UPDATE TIME */
		Serial.println("\nThoi gian chua update.");
		lcd.clear();
		Serial.println("\nHien thi UPDATE TIME trên LCD.");
		lcd.createChar(1, UB);
		customU(0, 0);
		delay(200);
		customP(3, 0);
		delay(200);
		customD(3 + 3, 0);
		delay(200);
		customA(3 + 3 + 3, 0);
		delay(200);
		customT(3 + 3 + 3 + 3, 0);
		delay(200);
		customE(3 + 3 + 3 + 3 + 3, 0);
		delay(200);

		customT(4, 2);
		delay(200);
		customI(4 + 4, 2);
		delay(200);
		customM(4 + 4 + 4, 2);
		delay(200);
		customE(4 + 4 + 4 + 5, 2);
		delay(200);
		delay(1000);
		lcd.clear();
	}
	else /* lam viec binh thuong */
	{
		static int only_Delete_Once = 0;
		if ((giay % 5 == 0) && (only_Delete_Once == 0))
		/* cu moi 5 giay xoa 2 line tren 1 lan */
		{
			Serial.printf("Bây giờ là: %s \n", buffer_sent_serial);
			lcd.setCursor(0, 0);
			lcd.print("                    ");
			lcd.setCursor(0, 1);
			lcd.print("                    ");
			only_Delete_Once++;
		}
		else if (giay % 5 != 0)
		{
			/* code */
			only_Delete_Once = 0;
		}

		if (giay / 1 % 10 < 5)
		/* moi che do hien thi 5 giay */
		{
			if ((ngay == DAY_BangNguyen) && (thang == MON_BangNguyen))
			{
				lcd.setCursor(0, 0);
				lcd.print("Bang Nguyen! ");
				lcd.print("HPBD!");
				static int age_of_mrbang;
				age_of_mrbang = nam - 1994;
				lcd.setCursor(0, 1);
				lcd.print("Bang tron ");
				lcd.print(age_of_mrbang);
				lcd.print(" tuoi.");
				Serial.println("Sanh thần Bằng :3");
			}
			else
			{
				lcd.setCursor(0, 0);
				lcd.write(0);
				/* canh giua chu bang cach demso ki tu */
				/* Sunday Monday Friday*/
				if ((thu == 0) || (thu == 1) || (thu == 5))
				{
					lcd.setCursor(6, 0);
					lcd.print(buffer_THU);
				}
				/* Tuesday   */
				else if (thu == 2)
				{
					lcd.setCursor(5, 0);
					lcd.print(buffer_THU);
				}
				/* Thursday Saturday  */
				else if ((thu == 4) || (thu == 6))
				{
					lcd.setCursor(5, 0);
					lcd.print(buffer_THU);
				}
				/* Wednesday  */
				else if (thu == 3)
				{
					lcd.setCursor(4, 0);
					lcd.print(buffer_THU);
				}
				/* */
				lcd.setCursor(19, 0);
				lcd.write(2);

				lcd.setCursor(0, 1);
				lcd.write(3);

				/*  *___XX_May_2019____* */
				if (thang == 5)
				{
					lcd.setCursor(4, 1);
					lcd.print(buffer_N_T_N);
				}
				/*  *___XX_June_2019___*
				July  */
				else if ((thang == 6) || (thang == 7))
				{
					lcd.setCursor(4, 1);
					lcd.print(buffer_N_T_N);
				}
				/*  *__XX_March_2019___*
				April  */
				else if ((thang == 3) || (thang == 4))
				{
					lcd.setCursor(3, 1);
					lcd.print(buffer_N_T_N);
				}
				/*  *__XX_August_2019__* */
				else if (thang == 8)
				{
					lcd.setCursor(3, 1);
					lcd.print(buffer_N_T_N);
				}
				/*  *_XX_January_2019__*
				October */
				else if ((thang == 10) || (thang == 1))
				{
					lcd.setCursor(2, 1);
					lcd.print(buffer_N_T_N);
				}
				/*  *_XX_February_2019_*
				November December  */
				else if ((thang == 11) || (thang == 2) || (thang == 12))
				{
					lcd.setCursor(2, 1);
					lcd.print(buffer_N_T_N);
				}
				/* *_XX_September_2019* */
				else if (thang == 9)
				{
					lcd.setCursor(2, 1);
					lcd.print(buffer_N_T_N);
				}
				lcd.setCursor(19, 1);
				lcd.write(5);
			}
		}
		else
		/* hien thi thoi tiet */
		{
			if (temp == 0)
			{
				lcd.setCursor(0, 0);
				lcd.print("WL_CONNECTION_LOST");
				lcd.setCursor(0, 1);
				lcd.print("time.nist.gov LOST");
			}
			else
			{

				lcd.setCursor(0, 0);
				lcd.write(0);
				lcd.print(hen_gio / 10 % 10);
				lcd.print(hen_gio / 1 % 10);
				lcd.print(":");
				lcd.print(hen_phut / 10 % 10);
				lcd.print(hen_phut / 1 % 10);
				lcd.setCursor(6, 0);
				lcd.write(2);
				lcd.write(4);
				lcd.write(0);
				lcd.print("  H: ");
				lcd.print(humidity);
				lcd.print("%");
				lcd.setCursor(19, 0);
				lcd.write(2);

				lcd.setCursor(0, 1);
				lcd.write(3);
				if (value_Location_EEPROM == 0)
				{
					lcd.print("TpHcm"); /* chuyen thanh location */
				}
				else if (value_Location_EEPROM == 1)
				{
					lcd.print("VgTau"); /* chuyen thanh location */
				}
				else if (value_Location_EEPROM == 2)
				{
					lcd.print("DaLat"); /* chuyen thanh location */
				}
				else if (value_Location_EEPROM == 3)
				{
					lcd.print("TpHue"); /* chuyen thanh location */
				}
				lcd.setCursor(6, 1);
				lcd.write(5);
				lcd.write(1);
				lcd.write(3);
				lcd.print("T: ");
				lcd.print(temp);
				lcd.print("*C");
				lcd.write(5);
			}
		}
		/*
			HIỂN THỊ FONT SỐ LỚN


		  000000000          888888888               1111111    222222222222222
		00:::::::::00      88:::::::::88            1::::::1   2:::::::::::::::22
	  00:::::::::::::00  88:::::::::::::88         1:::::::1   2::::::222222:::::2
	 0:::::::000:::::::08::::::88888::::::8        111:::::1   2222222     2:::::2
	 0::::::0   0::::::08:::::8     8:::::8           1::::1               2:::::2
	 0:::::0     0:::::08:::::8     8:::::8 ::::::    1::::1               2:::::2
	 0:::::0     0:::::0 8:::::88888:::::8  ::::::    1::::1            2222::::2
	 0:::::0 000 0:::::0  8:::::::::::::8   ::::::    1::::l       22222::::::22
	 0:::::0 000 0:::::0 8:::::88888:::::8            1::::l     22::::::::222
	 0:::::0     0:::::08:::::8     8:::::8           1::::l    2:::::22222
	 0:::::0     0:::::08:::::8     8:::::8           1::::l   2:::::2
	 0::::::0   0::::::08:::::8     8:::::8 ::::::    1::::l   2:::::2
	 0:::::::000:::::::08::::::88888::::::8 :::::: 111::::::1112:::::2       222222
	  00:::::::::::::00  88:::::::::::::88  :::::: 1::::::::::12::::::2222222:::::2
		00:::::::::00      88:::::::::88           1::::::::::12::::::::::::::::::2
		  000000000          888888888             11111111111122222222222222222222


		*/
		/* hien thi gio font so lon */
		printDigits(gio / 10 % 10, 0, 2);
		printDigits(gio / 1 % 10, 4, 2);
		/* hien thi dau 2 cham gio & phut */
		if (giay % 2 == 0)
		{
			lcd.setCursor(8, 2);
			lcd.write(1);
			lcd.setCursor(8, 3);
			lcd.write(4);
		}
		else
		{
			lcd.setCursor(8, 2);
			lcd.write(4);
			lcd.setCursor(8, 3);
			lcd.write(1);
		}
		/* hien thi phut font so lon */
		printDigits(phut / 10 % 10, 10, 2);
		printDigits(phut / 1 % 10, 14, 2);
		/* hien thi giay */
		lcd.setCursor(17, 3);
		lcd.print(":");
		lcd.print(buffer_GIAY);

		/* Qua khung giờ mới là tingting  */
		if ((phut == 0) && (giay < 3))
		{
			digitalWrite(PIN_signal_Bell, ESP_NB_ON);
		}
		else
		{
			digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
		}
		/* Báo thức */
		if ((hen_gio == gio) && (hen_phut == phut) &&
			(giay < 3) && (status_Mode_Alarm == ESP_NB_ON))
		{
			Active_Alarm();
			status_Mode_Alarm = ESP_NB_OFF;
		}
		else
		{
			digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
			/* Bật trang thai báo thức của Active_Alarm */
			status_Mode_Alarm = ESP_NB_ON;
		}
	}
}

/* Chon vi tri doc gia tri thoi tiet
   █████████  █████                                            ████                               █████     ███
  ███░░░░░███░░███                                            ░░███                              ░░███     ░░░
 ███     ░░░  ░███████    ██████   ██████   █████   ██████     ░███   ██████   ██████   ██████   ███████   ████   ██████  ████████
░███          ░███░░███  ███░░███ ███░░███ ███░░   ███░░███    ░███  ███░░███ ███░░███ ░░░░░███ ░░░███░   ░░███  ███░░███░░███░░███
░███          ░███ ░███ ░███ ░███░███ ░███░░█████ ░███████     ░███ ░███ ░███░███ ░░░   ███████   ░███     ░███ ░███ ░███ ░███ ░███
░░███     ███ ░███ ░███ ░███ ░███░███ ░███ ░░░░███░███░░░      ░███ ░███ ░███░███  ███ ███░░███   ░███ ███ ░███ ░███ ░███ ░███ ░███
 ░░█████████  ████ █████░░██████ ░░██████  ██████ ░░██████     █████░░██████ ░░██████ ░░████████  ░░█████  █████░░██████  ████ █████
  ░░░░░░░░░  ░░░░ ░░░░░  ░░░░░░   ░░░░░░  ░░░░░░   ░░░░░░     ░░░░░  ░░░░░░   ░░░░░░   ░░░░░░░░    ░░░░░  ░░░░░  ░░░░░░  ░░░░ ░░░░░

*/
void Choose_location()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Hold Mode Key >= 1s ");
	lcd.setCursor(0, 1);
	lcd.print("TpHCM> VgTau> DaLat>");
	lcd.setCursor(0, 2);
	lcd.print("VgTau> DaLat> TpHue>");
	lcd.setCursor(0, 3);
	lcd.print("DaLat> TpHue> TpHCM>");
	unsigned long dem_10s_stop = millis();
	while (((unsigned long)(millis() - dem_10s_stop) < 10000) && (status_Mode == 0))
	{
		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
		{
			delay(500); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
			if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
			{
				long startTime = millis();							// giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_Mode = (millis() - startTime) / 1000;
					couter_Mode = couter_Mode / 1 % 10;
					lcd.setCursor(0, 0);
					lcd.print("Couter: ");
					lcd.print(couter_Mode);
					lcd.print(" seconds  ");
					if (couter_Mode < 1)
					{
					}
					else if (couter_Mode >= 9)
					{
						/* mode xoay vong nen dem 1 den 9 thi reset */
						startTime = millis();
						lcd.setCursor(0, 1);
						lcd.print("Loca:    Hue        ");
						lcd.setCursor(0, 2);
						lcd.print("         HCMC       ");
						lcd.setCursor(0, 3);
						lcd.print("         VungTau    ");
					}
					else if (couter_Mode >= 7)
					{
						value_Location_EEPROM = 3;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> Hue        ");
						lcd.setCursor(0, 2);
						lcd.print("         HCMC       ");
						lcd.setCursor(0, 3);
						lcd.print("         VungTau    ");
					}
					else if (couter_Mode >= 5)
					{
						value_Location_EEPROM = 2;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> DaLat      ");
						lcd.setCursor(0, 2);
						lcd.print("         Hue        ");
						lcd.setCursor(0, 3);
						lcd.print("         HCMC       ");
					}
					else if (couter_Mode >= 3)
					{
						value_Location_EEPROM = 1;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> VungTau    ");
						lcd.setCursor(0, 2);
						lcd.print("         DaLat      ");
						lcd.setCursor(0, 3);
						lcd.print("         Hue        ");
					}
					else if (couter_Mode >= 1)
					{
						value_Location_EEPROM = 0;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> HCMC       ");
						lcd.setCursor(0, 2);
						lcd.print("         VungTau    ");
						lcd.setCursor(0, 3);
						lcd.print("         DaLat      ");
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
				Serial.printf("couter_Mode: ");
				Serial.println(couter_Mode);
				if (couter_Mode < 1)
				{
				}
				else if (couter_Mode >= 7)
				{
					value_Location_EEPROM = 3;
					lcd.setCursor(0, 0);
					lcd.print("Location Selection: ");
					lcd.setCursor(0, 1);
					lcd.print("         Hue        ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
					customT(0, 2);
					delay(100);
					customP(0 + 4, 2);
					delay(100);
					customH(0 + 4 + 4, 2);
					delay(100);
					customU(0 + 4 + 4 + 4, 2);
					delay(100);
					customE(0 + 4 + 4 + 4 + 4, 2);
					delay(800);
				}
				else if (couter_Mode >= 5)
				{
					value_Location_EEPROM = 2;
					lcd.setCursor(0, 0);
					lcd.print("Location Selection: ");
					lcd.setCursor(0, 1);
					lcd.print("       Dat Lat      ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
					customD(0, 2);
					delay(100);
					customA(0 + 4, 2);
					delay(100);
					customL(0 + 4 + 4, 2);
					delay(100);
					customA(0 + 4 + 4 + 4, 2);
					delay(100);
					customT(0 + 4 + 4 + 4 + 4, 2);
					delay(800);
				}
				else if (couter_Mode >= 3)
				{
					value_Location_EEPROM = 1;
					lcd.setCursor(0, 0);
					lcd.print("Location Selection: ");
					lcd.setCursor(0, 1);
					lcd.print("      Vung Tau      ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
					customV(0, 2);
					delay(100);
					customG(0 + 4, 2);
					delay(100);
					customT(0 + 4 + 4, 2);
					delay(100);
					customA(0 + 4 + 4 + 4, 2);
					delay(100);
					customU(0 + 4 + 4 + 4 + 4, 2);
					delay(800);
				}
				else if (couter_Mode >= 1)
				{
					value_Location_EEPROM = 0;
					lcd.setCursor(0, 0);
					lcd.print("Location Selection: ");
					lcd.setCursor(0, 1);
					lcd.print("        TPHCM       ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
					customT(0, 2);
					delay(100);
					customP(0 + 4, 2);
					delay(100);
					customH(0 + 4 + 4, 2);
					delay(100);
					customC(0 + 4 + 4 + 4, 2);
					delay(100);
					customM(0 + 4 + 4 + 4 + 4, 2);
					delay(800);
				}
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	status_Mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_location_eeprom, value_Location_EEPROM);
	EEPROM.commit();
	Serial.print("value_Location_EEPROM duoc set eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_location_eeprom));
	/* Chuông báo ok */
	digitalWrite(PIN_signal_Bell, ESP_NB_ON);
	delay(300);
	digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
}

/* Hàm gọi thời tiết mỗi 10 phút một lần */
void Call_Weather_Every_10Min()
{
	if ((unsigned long)(millis() - time_dem_thoitiet) > 60 * 10 * 1000) // 10 phut/ lan
	{
		time_dem_thoitiet = millis();
		Weather_Online_sever();
	}
}

/* Lấy giá trị thời tiết tại vị trí đã chọn
   Sử dụng hàm API riêng để dùng cho nút nhấn MODE
.--.      .--.    .-''-.     ____   ,---------. .---.  .---.     .-''-.  .-------.
|  |_     |  |  .'_ _   \  .'  __ `.\          \|   |  |_ _|   .'_ _   \ |  _ _   \
| _( )_   |  | / ( ` )   '/   '  \  \`--.  ,---'|   |  ( ' )  / ( ` )   '| ( ' )  |
|(_ o _)  |  |. (_ o _)  ||___|  /  |   |   \   |   '-(_{;}_). (_ o _)  ||(_ o _) /
| (_,_) \ |  ||  (_,_)___|   _.-`   |   :_ _:   |      (_,_) |  (_,_)___|| (_,_).' __
|  |/    \|  |'  \   .---..'   _    |   (_I_)   | _ _--.   | '  \   .---.|  |\ \  |  |
|  '  /\  `  | \  `-'    /|  _( )_  |  (_(=)_)  |( ' ) |   |  \  `-'    /|  | \ `'   /
|    /  \    |  \       / \ (_ o _) /   (_I_)   (_{;}_)|   |   \       / |  |  \    /
`---'    `---`   `'-..-'   '.(_,_).'    '---'   '(_,_) '---'    `'-..-'  ''-'   `'-'
*/
void Weather_Online_sever()
{
	if (value_Location_EEPROM == 0)
	{
		Location = Location_TPHCM;
		Serial.println("\nĐịa điểm lấy data thời tiết: Location_TPHCM\n");
	}
	else if (value_Location_EEPROM == 1)
	{
		Location = Location_VUTAU;
		Serial.println("\nĐịa điểm lấy data thời tiết: Location_VUTAU\n");
	}
	else if (value_Location_EEPROM == 2)
	{
		Location = Location_DALAT;
		Serial.println("\nĐịa điểm lấy data thời tiết: Location_DALAT\n");
	}
	else if (value_Location_EEPROM == 3)
	{
		Location = Location_TPHUE;
		Serial.println("\nĐịa điểm lấy data thời tiết: Location_TPHUE\n");
	}
	else // Nếu lần đầu tiên khởi động chưa setup vị trí thì mặc định là TPHCM
	{
		Location = Location_TPHCM;
		Serial.println("\nĐịa điểm lấy data thời tiết: Location_TPHCM\n");
	}

	if (WiFi.status() == WL_CONNECTED) // Check WiFi connection status
	{
		HTTPClient http; // Declare an object of class HTTPClient

		// specify request destination
		http.begin(client_wifi, "http://api.openweathermap.org/data/2.5/weather?id=" + Location + "&APPID=" + APIKey_openweather);

		int httpCode = http.GET(); // send the request

		if (httpCode > 0) // check the returning code
		{
			String payload = http.getString(); // Get the request response payload
			// Serial.println(payload);
			DynamicJsonDocument jsonBuffer(1024);

			auto error = deserializeJson(jsonBuffer, payload);
			if (error) {
				Serial.print(F("deserializeJson() failed with code "));
				Serial.println(error.c_str());
				return;
			}

			temp = (float)(jsonBuffer["main"]["temp"]) - 273.15;		 // get temperature in °C
			humidity = jsonBuffer["main"]["humidity"];				 // get humidity in %
			pressure = (float)(jsonBuffer["main"]["pressure"]) / 1000; // get pressure in bar
			wind_speed = jsonBuffer["wind"]["speed"];					 // get wind speed in m/s
			wind_degree = jsonBuffer["wind"]["deg"];					 // get wind degree in °

			// print data
			Serial.printf("Temperature = % .2f°C\n", temp);
			Serial.printf("Humidity = % d % %\n", humidity);
			Serial.printf("Pressure = % .3f bar\n", pressure);
			Serial.printf("Wind speed = % .1f m / s\n", wind_speed);
			Serial.printf("Wind degree = % d°\n\n", wind_degree);
		}
		http.end(); // Close connection
		yield();	// disble Soft WDT reset - NodeMCU
	}
	else
	{
		Serial.println("Wifi không có Internet !\n");
	}
}

/*
							  __                      _____
   _________ ___  ____ ______/ /_   _________  ____  / __(_)___ _
  / ___/ __ `__ \/ __ `/ ___/ __/  / ___/ __ \/ __ \/ /_/ / __ `/
 (__  ) / / / / / /_/ / /  / /_   / /__/ /_/ / / / / __/ / /_/ /
/____/_/ /_/ /_/\__,_/_/   \__/   \___/\____/_/ /_/_/ /_/\__, /
														/____/
*/
void smartConfig_ndb()
{
	lcd.createChar(1, UB);
	// Mode wifi là station
	WiFi.mode(WIFI_STA);
	WiFi.beginSmartConfig();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Begin SmartConfig!!!");
	int dem = 100;
	while (1)
	{
		delay(1000);
		dem--;
		Serial.printf("Thời gian chờ kết nối còn: %d\n", dem);
		lcd.setCursor(0, 1);
		lcd.print("Wait for 100 seconds");
		lcd.setCursor(3, 3);
		lcd.print("=>>");
		printDigits(dem / 10 % 10, 7, 2);
		printDigits(dem / 1 % 10, 11, 2);
		lcd.setCursor(15, 3);
		lcd.print("sec.");
		if (dem == 0) //! neu qua 100s ma chua co ket noi nao thi restart lai esp
		{
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Auto restart.");
			delay(2000);
			ESP.restart();
		}
		// Kiểm tra kết nối thành công in thông báo
		if (WiFi.smartConfigDone())
		{
			lcd.clear();
			Serial.println("SmartConfig Success");
			String qsid = WiFi.SSID();
			String qpass = WiFi.psk();
			lcd.setCursor(0, 0);
			lcd.print("Begin SmartConfig!!!");
			lcd.setCursor(0, 1);
			lcd.print("SmartConfig Success");
			lcd.setCursor(0, 2);
			lcd.print(qsid);
			lcd.setCursor(0, 3);
			lcd.print(qpass);
			/* Chuông báo két nối ok */
			digitalWrite(PIN_signal_Bell, ESP_NB_ON);
			delay(5000);
			if (qsid.length() > 0 && qpass.length() > 0)
			{
				Serial.println("clearing eeprom");
				for (int i = 0; i < 96; ++i)
				{
					EEPROM.write(i, 0);
				}
				Serial.println(qsid);
				Serial.println("");
				Serial.println(qpass);
				Serial.println("");

				Serial.println("Writing eeprom ssid:");
				for (int i = 0; i < (int)qsid.length(); ++i)
				{
					EEPROM.write(i, qsid[i]);
					Serial.print("Wrote: ");
					Serial.println(qsid[i]);
				}
				Serial.println("Writing eeprom pass:");
				for (int i = 0; i < (int)qpass.length(); ++i)
				{
					EEPROM.write(32 + i, qpass[i]);
					Serial.print("Wrote: ");
					Serial.println(qpass[i]);
				}
				EEPROM.commit();
				/* Ngắt chuông báo két nối ok */
				digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Saved ID & Pass Wifi");
				delay(1000);
				break;
			}
		}
	}
}

void Setup_AlarmClock()
{
	unsigned long dem_10s_stop = millis();
	while (((unsigned long)(millis() - dem_10s_stop) < 10000) && (status_Mode == 0))
	{
		lcd.setCursor(0, 0);
		lcd.print("Mode >= 1s SetHours ");
		lcd.setCursor(0, 1);
		lcd.print("Mode >= 3s SetMinute");
		/* hien thi gio font so lon */
		printDigits(hen_gio / 10 % 10, 1, 2);
		printDigits(hen_gio / 1 % 10, 5, 2);
		/* hien thi dau 2 cham gio & phut */
		Serial.println((millis() - dem_10s_stop));
		lcd.setCursor(9, 2);
		lcd.write(4);
		lcd.setCursor(9, 3);
		lcd.write(1);

		/* hien thi phut font so lon */
		printDigits(hen_phut / 10 % 10, 11, 2);
		printDigits(hen_phut / 1 % 10, 15, 2);

		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
		{
			delay(500); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
			if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
			{
				long startTime = millis();							// giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_Mode = (millis() - startTime) / 1000;
					couter_Mode = couter_Mode / 1 % 10;
					lcd.setCursor(0, 0);
					lcd.print("Couter: ");
					lcd.print(couter_Mode);
					lcd.print(" seconds  ");
					if (couter_Mode < 1)
					{
						lcd.setCursor(0, 1);
						lcd.print("Mode Selection      ");
					}
					else if (couter_Mode >= 5)
					{
						lcd.setCursor(0, 1);
						lcd.print("Out Mode            ");
					}
					else if (couter_Mode >= 3)
					{
						lcd.setCursor(0, 1);
						lcd.print("===>>>> Set Minute  ");
					}
					else if (couter_Mode >= 1)
					{
						lcd.setCursor(0, 1);
						lcd.print(" Set Hours <<<<<<===");
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
				Serial.printf("couter_Mode: ");
				Serial.println(couter_Mode);
				if (couter_Mode < 1)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode Selection");
				}
				else if (couter_Mode >= 5)
				{
					/* Out mode */
					delay(1500);
					/* set = 1 de out Mode */
					status_Mode = 1;
				}
				else if (couter_Mode >= 3)
				{
					/* set = 1 de vao while */
					status_Mode = 1;
					Set_Minute_Alarm();
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
				}
				else if (couter_Mode >= 1)
				{
					/* set = 1 de vao while */
					status_Mode = 1;
					Set_Hour_Alarm();
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
				}
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	status_Mode = 0;
	/* Chuông báo ok */
	digitalWrite(PIN_signal_Bell, ESP_NB_ON);
	delay(300);
	digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
}

void Set_Hour_Alarm()
{
	unsigned long dem_nhay = 0;
	unsigned long time_dem_baothuc = millis();
	unsigned long dem_10s_stop_g = millis();
	while (((unsigned long)(millis() - dem_10s_stop_g) < 10000) && (status_Mode == 1))
	{
		/* tao hieu ung nhay nhay so */
		dem_nhay = (unsigned long)(millis() - time_dem_baothuc);
		if (dem_nhay < 300)
		{
			lcd.setCursor(1, 2);
			lcd.print("       ");
			lcd.setCursor(1, 3);
			lcd.print("       ");
		}
		else if (dem_nhay <= 700)
		{
			/* hien thi gio font so lon */
			printDigits(hen_gio / 10 % 10, 1, 2);
			printDigits(hen_gio / 1 % 10, 5, 2);
		}
		else if (dem_nhay > 700)
		{
			time_dem_baothuc = millis();
		}
		Serial.printf("couter_Mode: ");
		Serial.println(dem_nhay);

		lcd.setCursor(9, 2);
		lcd.write(4);
		lcd.setCursor(9, 3);
		lcd.write(1);

		/* hien thi phut font so lon */
		printDigits(hen_phut / 10 % 10, 11, 2);
		printDigits(hen_phut / 1 % 10, 15, 2);

		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
		{
			delay(50); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
			if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
			{
				hen_gio++;
				if (hen_gio >= 24)
				{
					hen_gio = 0;
				}
				long startTime = millis();
				while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop_g = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_Mode = (millis() - startTime) / 1000;
					/* hien thi gio font so lon */
					printDigits(hen_gio / 10 % 10, 1, 2);
					printDigits(hen_gio / 1 % 10, 5, 2);
					if (couter_Mode >= 2)
					{
						lcd.setCursor(19, 0);
						lcd.write(7);
						status_Mode = 0;
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	status_Mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_hengio, hen_gio);
	EEPROM.commit();
	Serial.print("hen_gio duoc set eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_hengio));
}

void Set_Minute_Alarm()
{
	unsigned long time_dem_baothuc = millis();
	unsigned long dem_nhay = 0;
	unsigned long dem_10s_stop_P = millis();
	while (((unsigned long)(millis() - dem_10s_stop_P) < 10000) && (status_Mode == 1))
	{
		/* hien thi gio font so lon */
		printDigits(hen_gio / 10 % 10, 1, 2);
		printDigits(hen_gio / 1 % 10, 5, 2);

		/* hien thi dau 2 cham gio & phut */
		lcd.setCursor(9, 2);
		lcd.write(4);
		lcd.setCursor(9, 3);
		lcd.write(1);

		dem_nhay = (unsigned long)(millis() - time_dem_baothuc);
		if (dem_nhay < 300)
		{
			lcd.setCursor(11, 2);
			lcd.print("       ");
			lcd.setCursor(11, 3);
			lcd.print("       ");
		}
		else if (dem_nhay <= 700)
		{
			/* hien thi phut font so lon */
			printDigits(hen_phut / 10 % 10, 11, 2);
			printDigits(hen_phut / 1 % 10, 15, 2);
		}
		else if (dem_nhay > 700)
		{
			time_dem_baothuc = millis();
		}

		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
		{
			delay(50); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
			if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
			{
				hen_phut++;
				if (hen_phut >= 60)
				{
					hen_phut = 0;
				}
				long startTime = millis();
				while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop_P = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_Mode = (millis() - startTime) / 1000;
					/* hien thi phut font so lon */
					printDigits(hen_phut / 10 % 10, 11, 2);
					printDigits(hen_phut / 1 % 10, 15, 2);
					if (couter_Mode >= 2)
					{
						lcd.setCursor(19, 0);
						lcd.write(7);
						status_Mode = 0;
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	status_Mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_henphut, hen_phut);
	EEPROM.commit();
	Serial.printf("hen_phut duoc set eeprom: %d \n", EEPROM.read(index_eeprom_henphut));
}

/*
   █████████             █████     ███                                   █████████   ████
  ███░░░░░███           ░░███     ░░░                                   ███░░░░░███ ░░███
 ░███    ░███   ██████  ███████   ████  █████ █████  ██████            ░███    ░███  ░███   ██████   ████████  █████████████
 ░███████████  ███░░███░░░███░   ░░███ ░░███ ░░███  ███░░███           ░███████████  ░███  ░░░░░███ ░░███░░███░░███░░███░░███
 ░███░░░░░███ ░███ ░░░   ░███     ░███  ░███  ░███ ░███████            ░███░░░░░███  ░███   ███████  ░███ ░░░  ░███ ░███ ░███
 ░███    ░███ ░███  ███  ░███ ███ ░███  ░░███ ███  ░███░░░             ░███    ░███  ░███  ███░░███  ░███      ░███ ░███ ░███
 █████   █████░░██████   ░░█████  █████  ░░█████   ░░██████  █████████ █████   █████ █████░░████████ █████     █████░███ █████
░░░░░   ░░░░░  ░░░░░░     ░░░░░  ░░░░░    ░░░░░     ░░░░░░  ░░░░░░░░░ ░░░░░   ░░░░░ ░░░░░  ░░░░░░░░ ░░░░░     ░░░░░ ░░░ ░░░░░

*/
void Active_Alarm()
{
	lcd.clear();
	unsigned long dem_nhay = 0;
	unsigned long dem_30s_stop = millis();
	unsigned long time_dem_baothuc = millis();

	while (((unsigned long)(millis() - dem_30s_stop) < 30000) &&
		   (status_Mode_Alarm == ESP_NB_ON))
	{
		dem_nhay = (unsigned long)(millis() - time_dem_baothuc);
		if (dem_nhay < 300)
		{
			lcd.clear(); // tạo hiệu ứng nháy màn hình lcd
		}
		else if (dem_nhay <= 800)
		{
			/* hien thi gio font so lon */
			customA(0, 0);
			customL(0 + 4, 0);
			customA(0 + 4 + 4, 0);
			customR(0 + 4 + 4 + 4, 0);
			customM(0 + 4 + 4 + 4 + 4, 0);
			/* hien thi gio font so lon */
			printDigits(hen_gio / 10 % 10, 1, 2);
			printDigits(hen_gio / 1 % 10, 5, 2);
			/* hien thi dau 2 cham gio & phut */

			lcd.setCursor(9, 2);
			lcd.write(4);
			lcd.setCursor(9, 3);
			lcd.write(1);

			/* hien thi phut font so lon */
			printDigits(hen_phut / 10 % 10, 11, 2);
			printDigits(hen_phut / 1 % 10, 15, 2);
			/* hien thi so goc trai dem giay xoa nut*/
			lcd.setCursor(19, 3);
			lcd.print(" ");
		}
		else if (dem_nhay > 700)
		{
			time_dem_baothuc = millis();
		}

		/* Check đè phím MODE hơn 2 giây thì thoát, không kêu chuông nữa */
		digitalWrite(PIN_signal_Bell, ESP_NB_ON);
		if (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // nếu nút bấm ở mức cao
		{
			delay(500); /* Check chống dội phím - chắc chắn phải là do người nhấn nút */
			if (digitalRead(Button_Mode) == PULLUP_PULLDOWN)
			{
				unsigned long startTime = millis();					// giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == PULLUP_PULLDOWN) // đợi cho nút bấm được giữ
				{
					/* hien thi gio font so lon */
					customA(0, 0);
					customL(0 + 4, 0);
					customA(0 + 4 + 4, 0);
					customR(0 + 4 + 4 + 4, 0);
					customM(0 + 4 + 4 + 4 + 4, 0);
					/* hien thi gio font so lon */
					printDigits(hen_gio / 10 % 10, 1, 2);
					printDigits(hen_gio / 1 % 10, 5, 2);

					/* hien thi dau 2 cham gio & phut */
					lcd.setCursor(9, 2);
					lcd.write(4);
					lcd.setCursor(9, 3);
					lcd.write(1);

					/* hien thi phut font so lon */
					printDigits(hen_phut / 10 % 10, 11, 2);
					printDigits(hen_phut / 1 % 10, 15, 2);
					/*==============================*/
					Serial.printf("Đang đè nút tắt báo thức %d ms \n", millis() - startTime);
					couter_Mode = (millis() - startTime) / 1000;
					couter_Mode = couter_Mode / 1 % 10;

					/* đè phím MODE hơn 2 giây thì thoát, không kêu chuông nữa */
					if (couter_Mode >= 2)
					{
						status_Mode_Alarm = ESP_NB_OFF;
						lcd.setCursor(19, 3);
						lcd.write(4);
						digitalWrite(PIN_signal_Bell, ESP_NB_OFF);
					}
					else if (couter_Mode < 2)
					{
						lcd.setCursor(19, 3);
						lcd.print(couter_Mode);
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	lcd.clear();
}

/*
 ███████████                   █████       █████   ███   █████  ███     ██████   ███
░█░░░███░░░█                  ░░███       ░░███   ░███  ░░███  ░░░     ███░░███ ░░░
░   ░███  ░   ██████   █████  ███████      ░███   ░███   ░███  ████   ░███ ░░░  ████
	░███     ███░░███ ███░░  ░░░███░       ░███   ░███   ░███ ░░███  ███████   ░░███
	░███    ░███████ ░░█████   ░███        ░░███  █████  ███   ░███ ░░░███░     ░███
	░███    ░███░░░   ░░░░███  ░███ ███     ░░░█████░█████░    ░███   ░███      ░███
	█████   ░░██████  ██████   ░░█████        ░░███ ░░███      █████  █████     █████
   ░░░░░     ░░░░░░  ░░░░░░     ░░░░░          ░░░   ░░░      ░░░░░  ░░░░░     ░░░░░

*/
bool bool_Test_Wifi(void)
{
	int c = 0;
	Serial.println("");
	Serial.println("Waiting for Wifi to connect");
	Serial.println("=========  Note =========");
	Serial.println("WL_NO_SHIELD        = 255");
	Serial.println("WL_IDLE_STATUS      = 0");
	Serial.println("WL_NO_SSID_AVAIL    = 1");
	Serial.println("WL_SCAN_COMPLETED   = 2");
	Serial.println("WL_CONNECTED        = 3");
	Serial.println("WL_CONNECT_FAILED   = 4");
	Serial.println("WL_CONNECTION_LOST  = 5");
	Serial.println("WL_WRONG_PASSWORD   = 6");
	Serial.println("WL_DISCONNECTED     = 7");
	Serial.println("========================");
	while (c < 40)
	{
		Serial.println("");
		if (WiFi.status() == WL_CONNECTED)
		{
			/* Chuông báo ok */
			digitalWrite(PIN_signal_Bell, 0);
			delay(1500);
			digitalWrite(PIN_signal_Bell, 1);
			return true;
		}
		/* Chuông báo ok */
		digitalWrite(PIN_signal_Bell, 0);
		delay(300);
		digitalWrite(PIN_signal_Bell, 1);
		delay(300);
		Serial.print(WiFi.status());
		Serial.print(" -> ");
		c++;
	}
	Serial.println("");
	Serial.println("Connect timed out, opening AP");
	return false;
}

/* Cập nhật OTA
 █████  █████               █████            █████                   ███████    ███████████   █████████
░░███  ░░███               ░░███            ░░███                  ███░░░░░███ ░█░░░███░░░█  ███░░░░░███
 ░███   ░███  ████████   ███████   ██████   ███████    ██████     ███     ░░███░   ░███  ░  ░███    ░███
 ░███   ░███ ░░███░░███ ███░░███  ░░░░░███ ░░░███░    ███░░███   ░███      ░███    ░███     ░███████████
 ░███   ░███  ░███ ░███░███ ░███   ███████   ░███    ░███████    ░███      ░███    ░███     ░███░░░░░███
 ░███   ░███  ░███ ░███░███ ░███  ███░░███   ░███ ███░███░░░     ░░███     ███     ░███     ░███    ░███
 ░░████████   ░███████ ░░████████░░████████  ░░█████ ░░██████     ░░░███████░      █████    █████   █████
  ░░░░░░░░    ░███░░░   ░░░░░░░░  ░░░░░░░░    ░░░░░   ░░░░░░        ░░░░░░░       ░░░░░    ░░░░░   ░░░░░
			  ░███
			  █████
			 ░░░░░
*/
void update_FOTA()
{
	Serial.println("\n>>>>>>>>>>> Update FOTA \n");
	Serial.println("Check firmware coi có bản cập nhật không? ");

	lcd.clear();
	/* màn hình hiển thị trên LCD 2004 */
	lcd.setCursor(0, 0);
	lcd.print("Version Firmware:   ");

	lcd.setCursor(0, 1);
	lcd.print(FirmwareVer);
	lcd.print(" - ");
	lcd.print(CHIPID);

	lcd.setCursor(0, 2);
	lcd.print("Checking for updates");

	/* hiển thị loading . . . */
	lcd.setCursor(0, 3);
	lcd.print("...");
	Serial.printf(">>> Device: %d MHz \n", ESP.getCpuFreqMHz());
	Serial.printf(">>> Version Firmware: %s \n", FirmwareVer);
	Serial.printf(">>> ID ESP: ");
	Serial.println(CHIPID);
	Serial.printf(">>> Boot Mode: %d \n", ESP.getBootMode());
	Serial.printf(">>> Free Sketch Space: %d \n", ESP.getFreeSketchSpace());

	WiFiClientSecure client;
	client.setTrustAnchors(&cert);
	if (!client.connect(host, httpsPort))
	{
		Serial.println(">>> raw.githubusercontent.com - Connection failed");
		Serial.println(">>> Sever bị nghẻn, quá tải...");
		Serial.println(">>> Hoặc thiết bị của bạn chưa được cho phép cập nhật trên hệ thống...");
		Serial.println(">>> Check cập nhật ở thời điểm khác...");
		Serial.printf(">>> Phiên bản hiện tại là %s \n", FirmwareVer);
		return;
	}

	client.print(String("GET ") + URL_fw_Version + " HTTP/1.1\r\n" +
				 "Host: " + host + "\r\n" +
				 "User-Agent: BuildFailureDetectorESP8266\r\n" +
				 "Connection: close\r\n\r\n");

	// Check nội dung từ file Version 	
	while (client.connected())
	{
		String line = client.readStringUntil('\n');
		if (line == "\r")
		{
			Serial.println(">>> Headers received");
			break;
		}
	}

	String payload = client.readString(); // Get the request response payload
	Serial.println(payload);
	DynamicJsonDocument jsonBuffer(1024);

	auto error = deserializeJson(jsonBuffer, payload);
	if (error) {
		Serial.print(F("deserializeJson() failed with code "));
		Serial.println(error.c_str());
		return;
	}

	String author_prod = jsonBuffer["author"];
	String version_prod = jsonBuffer["main"]["version"];

	// serializeJson(jsonBuffer, Serial);

	if (version_prod.equals(FirmwareVer))
	{
		Serial.println(">>> Device already on latest firmware version");
		lcd.setCursor(0, 2);
		lcd.print("The current version ");
		lcd.setCursor(0, 2);
		lcd.print("      is the latest.");
		lcd.setCursor(0, 3);
		lcd.print("> > > > > > > > > > ");
		delay(1500);
	}
	else
	{
		Serial.print(">>> New firmware detected: ");
		Serial.println(version_prod);
		lcd.setCursor(0, 2);
		lcd.print("NewFirmware detected");
		lcd.setCursor(0, 2);
		lcd.print(FirmwareVer);
		lcd.print(" -> ");
		lcd.print(version_prod);
		// The line below is optional. It can be used to blink the LED on the board during flashing
		// The LED will be on during download of one buffer of data from the network. The LED will
		// be off during writing that buffer to flash
		// On a good connection the LED should flash regularly. On a bad connection the LED will be
		// on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
		// value is used to put the LED on. If the LED is on with HIGH, that value should be passed
		ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

		// Add optional callback notifiers
		ESPhttpUpdate.onStart(update_started);
		ESPhttpUpdate.onEnd(update_finished);
		ESPhttpUpdate.onProgress(update_progress);
		ESPhttpUpdate.onError(update_error);

		t_httpUpdate_return ret = ESPhttpUpdate.update(client, URL_fw_Bin);

		switch (ret)
		{
		case HTTP_UPDATE_FAILED:
			Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
			Serial.println(">>> Sever bị nghẻn, quá tải...");
			Serial.println(">>> Hoặc thiết bị của bạn chưa được cho phép cập nhật trên hệ thống...");
			Serial.println(">>> Check cập nhật ở thời điểm khác...");
			Serial.printf(">>> Phiên bản hiện tại là %s \n", FirmwareVer);
			lcd.setCursor(0, 3);
			lcd.print("> Skip updated...ERR");
			delay(2000);
			break;

		case HTTP_UPDATE_NO_UPDATES:
			Serial.println("HTTP_UPDATE_NO_UPDATES");
			Serial.println(">>> The current version is the latest.");
			lcd.setCursor(0, 2);
			lcd.print("The current version ");
			lcd.setCursor(0, 2);
			lcd.print("      is the latest.");
			lcd.setCursor(0, 3);
			lcd.print("> > > > > > > > > > ");
			delay(1500);
			break;

		case HTTP_UPDATE_OK:
			Serial.println("HTTP_UPDATE_OK");
			break;
		}
	}
	lcd.clear();
	Serial.println("\n<<<<<<<<<< Done Check FOTA \n");
}

/*
__      __          _                                               _       ___     ___
\ \    / / ___     | |     __      ___    _ __     ___      o O O  | |     / __|   |   \
 \ \/\/ / / -_)    | |    / _|    / _ \  | '  \   / -_)    o       | |__  | (__    | |) |
  \_/\_/  \___|   _|_|_   \__|_   \___/  |_|_|_|  \___|   TS__[O]  |____|  \___|   |___/
_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| {======|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'
*/
void Welcome_Smartclock()
{
	lcd.clear();
	delay(100);
	/* chay full trai tim */
	lcd.createChar(1, traitim);
	for (int i = 0; i < 11; i++)
	{
		lcd.setCursor(i, 0);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(i, 1);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(i, 2);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(i, 3);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(19 - i, 0);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(19 - i, 1);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(19 - i, 2);
		lcd.write(1); // chay ki tu trai tim
		lcd.setCursor(19 - i, 3);
		lcd.write(1); // chay ki tu trai tim
		delay(100);
	}
	/* xoa nhung cho viet ten Bang CUTE*/

	lcd.setCursor(0, 0);
	lcd.print("                    ");
	lcd.setCursor(0, 1);
	lcd.print("                ");

	lcd.setCursor(0, 2);
	lcd.print("                    ");
	lcd.setCursor(5, 3);
	lcd.print("               ");

	/* viet ten Bang CUTE*/
	{
		/* xoa trai tim dua ve binh thuong */
		lcd.createChar(1, UB);
		/* =============================== */

		customB(0, 0);
		delay(100);
		customA(4, 0);
		delay(100);
		customN(4 + 4, 0);
		delay(100);
		customG(4 + 4 + 5, 0);
		delay(100);

		customH(4, 2);
		delay(100);
		customI(4 + 4, 2);
		delay(100);
		customE(4 + 4 + 4, 2);
		delay(100);
		customN(4 + 4 + 4 + 4, 2);
		delay(100);

		delay(1500);
		lcd.clear();
		delay(100);
	}
}

