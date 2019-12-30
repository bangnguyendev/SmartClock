#define ESP_NB_ZERO 0
#define ESP_NB_ONE 1
#define ESP_NB_OFF 0
#define ESP_NB_ON 1

#include <ESP8266WiFi.h>
/* Get data Weather - http */
#include <ESP8266HTTPClient.h>
#include <time.h>
#include <Wire.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#if ESP_NB_OFF /* my laptop */
/* LCD  */
#include "D:\Github_NguyenBang\smart_clock_ndb\include\LiquidCrystal_I2C-master\LiquidCrystal_I2C.cpp"
#include "D:\Github_NguyenBang\smart_clock_ndb\include\Character_lcd\Character_LCD.h"
LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
/* ThingSpeak  */
#include "D:\Github_NguyenBang\smart_clock_ndb\include\ThingSpeak\ThingSpeak.cpp"
WiFiClient client;
#else /* company */
/* LCD  */
#include "D:\Git_NDB\smart_clock_ndb\include\LiquidCrystal_I2C-master\LiquidCrystal_I2C.cpp"
#include "D:\Git_NDB\smart_clock_ndb\include\Character_lcd\Character_LCD.H"
LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
/* ThingSpeak  */
#include "D:\Git_NDB\smart_clock_ndb\include\ThingSpeak\ThingSpeak.cpp"
WiFiClient client;
#endif

/* ThingSpeak  */
#define ChannelNumber 947371
#define FieldNumber 1
const char *WriteAPIKey = "9DU3YS7U45KE50OA";
const char *ReadAPIKey = "HZ6V9BBQBVUR8PXI";
/* End data ThingSpeak  */

#define CHUONG_BT 16
#define LED_TT 100
#define Button_Mode 14
/* Ngay sinh nhat DUNG */
#define DAY_DungNguyen 14
/* Thang sinh nhat DUNG */
#define MON_DungNguyen 7

/*index 0 to 31 */
#define index_eeprom_SSID 32
/*index 32 to 95 */
#define index_eeprom_PASS 96
/*index 0 to 95 */
#define index_eeprom_WIFI 96
#define index_eeprom_hengio 97
#define index_eeprom_henphut 98
#define index_eeprom_location_eeprom 99
/*
1584071 DAT LAT
1566083 TP HCM
1565033 TP HUE 
1562414 VUNG TAU
*/
String Location = "1566083";
/* TK duybang14****@gmail.com*/
String API_Key = "15fc2e6f826c6eac50fade5e8ebcaeab";

/*
  %a Abbreviated weekday name 
  %A Full weekday name 
  %b Abbreviated month name 
  %B Full month name 
  %c Date and time representation for your locale 
  %d Day of month as a decimal number (01-31) 
  %H Hour in 24-hour format (00-23) 
  %I Hour in 12-hour format (01-12) 
  %j Day of year as decimal number (001-366) 
  %m Month as decimal number (01-12) 
  %M Minute as decimal number (00-59) 
  %p Current locale's A.M./P.M. indicator for 12-hour clock 
  %S Second as decimal number (00-59) 
  %U Week of year as decimal number,  Sunday as first day of week (00-51) 
  %w Weekday as decimal number (0-6; Sunday is 0) 
  %W Week of year as decimal number, Monday as first day of week (00-51) 
  %x Date representation for current locale 
  %X Time representation for current locale 
  %y Year without century, as decimal number (00-99) 
  %Y Year with century, as decimal number 
  %z %Z Time-zone name or abbreviation, (no characters if time zone is unknown) 
  %% Percent sign 
  You can include text literals (such as spaces and colons) to make a neater display or for padding between adjoining columns. 
  You can suppress the display of leading zeroes  by using the "#" character  (%#d, %#H, %#I, %#j, %#m, %#M, %#S, %#U, %#w, %#W, %#y, %#Y) 
*/
char buffer_NAM[80];
char buffer_THANG[80];
char buffer_NGAY[80];
char buffer_THU[80], buffer_thu_be[80];
char buffer_N_T_N[80];
char buffer_GIO[80];
char buffer_PHUT[80];
char buffer_GIAY[80];
int nam, thang, ngay, thu;
int hen_gio, hen_phut;
int gio, phut, giay;

int couter_mode = 0;
int stt_mode = 0, stt_mode_baothuc = 0;
int xoa_1_lan = 0;
unsigned long time_dem_thoitiet;
int bien_location_eeprom = 0;

/* bien nhiet do */
float temp;
int humidity;
float pressure;
float wind_speed;
int wind_degree;

const char *ssid = "nguyenduybang";
const char *passphrase = "nguyenduybang";

void setup()
{
	Serial.begin(115200);
	time_dem_thoitiet = millis();
	pinMode(CHUONG_BT, OUTPUT);
	pinMode(Button_Mode, INPUT);
	digitalWrite(Button_Mode, LOW);
	delay(10);
	lcd.init(); // initialize the lcd
				// Print a message to the LCD.
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
	///////////////////////////////////////

	EEPROM.begin(512);
	Serial.println(" ");
	Serial.println("Lay gio bao thuc:");
	hen_gio = EEPROM.read(index_eeprom_hengio);
	Serial.print("hen_gio: ");
	Serial.println(EEPROM.read(index_eeprom_hengio));
	hen_phut = EEPROM.read(index_eeprom_henphut);
	Serial.print("hen_phut: ");
	Serial.println(EEPROM.read(index_eeprom_henphut));
	bien_location_eeprom = EEPROM.read(index_eeprom_location_eeprom);
	Serial.print("bien_location_eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_location_eeprom));

	Serial.println("=========ĐỌC SSID PASS TỪ EEROM ĐÃ LƯU!!!====");
	lcd.setCursor(0, 0);
	lcd.print("Found saved wifi!");
	Serial.println("Startup");
	// read eeprom for ssid and pass
	Serial.println("Reading EEPROM ssid");
	String esid = "";
	for (int i = 0; i < index_eeprom_SSID; ++i)
	{
		esid += char(EEPROM.read(i));
	}
	Serial.print("SSID: ");
	Serial.println(esid);

	lcd.setCursor(0, 1);
	lcd.print("ID Wifi:");
	for (int b = 0; b < 9; b++)
	{
		lcd.print(esid[b]);
		delay(100);
	}
	lcd.print("...");
	/* pass se k in ra man hinh lcd */
	Serial.println(" ");
	Serial.println("Reading EEPROM pass");
	String epass = "";
	for (int i = 32; i < index_eeprom_PASS; ++i)
	{
		epass += char(EEPROM.read(i));
	}
	Serial.print("PASS: ");
	Serial.println(epass);
	/* nho check lai dieu kien cho nay khi < 1 */
	if (esid.length() > ESP_NB_ONE)
	{
		WiFi.mode(WIFI_STA);
		WiFi.begin(esid.c_str(), epass.c_str());
		if (testWifi())
		{
			lcd.createChar(1, traitim);
			Serial.println("Vao test wifi ok!");

			for (int i = 0; i < 20; i++)
			{
				lcd.setCursor(i, 1);
				lcd.write(1); //chay ki tu trai tim
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
			lcd.createChar(1, UB);
			//Mode wifi là station
			WiFi.mode(WIFI_STA);
			WiFi.beginSmartConfig();
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Begin SmartConfig!!!");
			int dem = 100;
			while (1)
			{
				delay(1000);
				digitalWrite(LED_TT, !digitalRead(LED_TT));
				dem--;
				Serial.println(dem);
				lcd.setCursor(0, 1);
				lcd.print("Wait for 100 seconds");
				lcd.setCursor(3, 3);
				lcd.print("=>>");
				printDigits(dem / 10 % 10, 7, 2);
				printDigits(dem / 1 % 10, 11, 2);
				lcd.setCursor(15, 3);
				lcd.print("sec.");
				/*neu qua 100s ma chua co ket noi nao thi restart lai esp*/
				if (dem == ESP_NB_ZERO)
				{
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Auto restart.");
					delay(2000);
					ESP.restart();
				}
				/*Kiểm tra kết nối thành công in thông báo*/
				if (WiFi.smartConfigDone())
				{
					Serial.println("SmartConfig Success");
					String qsid = WiFi.SSID();
					String qpass = WiFi.psk();
					lcd.setCursor(0, 1);
					lcd.print("SmartConfig Success");
					lcd.setCursor(0, 2);
					lcd.print(qsid);
					lcd.setCursor(0, 3);
					lcd.print(qpass);
					delay(2000);
					if (qsid.length() > 0 && qpass.length() > 0)
					{
						Serial.println("clearing eeprom");
						for (int i = 0; i < index_eeprom_WIFI; ++i)
						{
							EEPROM.write(i, 0);
						}
						Serial.println(qsid);
						Serial.println("");
						Serial.println(qpass);
						Serial.println("");

						Serial.println("writing eeprom ssid:");
						for (int i = 0; i < qsid.length(); ++i)
						{
							EEPROM.write(i, qsid[i]);
							Serial.print("Wrote: ");
							Serial.println(qsid[i]);
						}
						Serial.println("writing eeprom pass:");
						for (int i = 0; i < qpass.length(); ++i)
						{
							EEPROM.write(32 + i, qpass[i]);
							Serial.print("Wrote: ");
							Serial.println(qpass[i]);
						}
						lcd.clear();
						lcd.setCursor(0, 0);
						lcd.print("Saved ID & Pass Wifi");
						EEPROM.commit();
						delay(1000);
						break;
					}
				}
			}
		}
	}
	WiFi.mode(WIFI_STA);
	Serial.println("");
	WiFi.printDiag(Serial);
	// In địa chỉ IP
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	configTime(7 * 3600, 0, "vn.pool.ntp.org", "time.nist.gov");
	Serial.println("Time >>> vn.pool.ntp.org");
	while (!time(nullptr))
	{
		Serial.println("\nWaiting for time");
		Serial.print(".");
		delay(1000);
		yield(); // disble Soft WDT reset - NodeMCU
	}

	lcd.clear();
	delay(100);
	/* chay full trai tim */
	lcd.createChar(1, traitim);
	for (int i = 0; i < 11; i++)
	{
		lcd.setCursor(i, 0);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(i, 1);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(i, 2);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(i, 3);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(20 - i, 0);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(20 - i, 1);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(20 - i, 2);
		lcd.write(1); //chay ki tu trai tim
		lcd.setCursor(20 - i, 3);
		lcd.write(1); //chay ki tu trai tim
		delay(200);
	}
	/* xoa nhung cho viet ten DUNG CUTE*/
	for (int i = 0; i < 16; i++)
	{
		lcd.setCursor(i, 0);
		lcd.print(" ");
		lcd.setCursor(i, 1);
		lcd.print(" ");
	}
	/* xoa nhung cho viet ten DUNG CUTE*/
	for (int i = 5; i < 20; i++)
	{
		lcd.setCursor(i, 2);
		lcd.print(" ");
		lcd.setCursor(i, 3);
		lcd.print(" ");
	}
	/* viet ten DUNG CUTE*/
	{
		/* xoa trai tim dua ve binh thuong */
		lcd.createChar(1, UB);
		/* =============================== */

		customD(0, 0);
		delay(200);
		customU(4, 0);
		delay(200);
		customN(4 + 4, 0);
		delay(200);
		customG(4 + 4 + 5, 0);
		delay(200);

		customC(5, 2);
		delay(200);
		customU(5 + 4, 2);
		delay(200);
		customT(5 + 4 + 4, 2);
		delay(200);
		customE(5 + 4 + 4 + 4, 2);
		delay(200);

		delay(1500);
		lcd.clear();
		delay(100);
	}
	/* truy cap den thoi tiet dia phuong
	da luu o eeprom
	*/
	Weather_Online_sever();
	ThingSpeak.begin(client);
}

void loop()
{
	kiem_tra_nut_nhan();
	printLocalTime();
	Call_Weather_Every_10Min();
	yield(); // disble Soft WDT reset - NodeMCU
}

/* Func get message on Thingspeak sever */
void Thingspeak_Message()
{
	int statusCode_Thingspeak = 0;
	unsigned long dem_10s_stop = millis();
	while (((unsigned long)(millis() - dem_10s_stop) < 10000) && (stt_mode == 0))
	{
#if ESP_NB_OFF
		statusCode_Thingspeak = ThingSpeak.writeField(ChannelNumber, 1, " meo meo con meo con cho con bo", WriteAPIKey);
		// Check the return code
		if (statusCode_Thingspeak == 200)
		{
			Serial.println("Channel update successful.");
		}
		else
		{
			Serial.println("Problem updating channel. HTTP error code " + String(statusCode_Thingspeak));
		}
#else
		String message_sent_Dung = ThingSpeak.readStringField(ChannelNumber, FieldNumber, ReadAPIKey);
		// Check the status of the read operation to see if it was successful
		statusCode_Thingspeak = ThingSpeak.getLastReadStatus();
		if (statusCode_Thingspeak == 200)
		{
			Serial.println("Đọc dữ liệu ThingSpeak tốt.");
			Serial.println(message_sent_Dung);
		}
		else
		{
			Serial.println("Problem updating channel. HTTP error code " + String(statusCode_Thingspeak));
		}
#endif
		Serial.println(message_sent_Dung);
		int sum_char = message_sent_Dung.length();

		for (int i = 0; i < sum_char; i++)
		{
			if (i > 139)
			{
				lcd.setCursor(i - 140, 3);
			}
			else if (i > 119)
			{
				lcd.setCursor(i - 120, 2);
			}
			else if (i > 99)
			{
				lcd.setCursor(i - 100, 1);
			}
			else if (i > 79)
			{
				lcd.setCursor(i - 80, 0);
			}
			else if (i > 59)
			{
				lcd.setCursor(i - 60, 3);
			}
			else if (i > 39)
			{
				lcd.setCursor(i - 40, 2);
			}
			else if (i > 19)
			{
				lcd.setCursor(i - 20, 1);
			}
			else
			{
				lcd.setCursor(i - 00, 0);
			}
			/*
			"Xin Chao Dung xinh  "
			"dep! Minh den tu    "
			"dong ho thong minh  "
			"nhat vu tru!        "
			*/
			lcd.print(message_sent_Dung[i]);
			if (i == 79)
			{
				delay(1000);
				/* Xoa man hinh 1 de chuan bi chuyen sang man hinh 2 */
				lcd.clear();
			}
			else
			{
				delay(200);
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	stt_mode = 0;
}

void kiem_tra_nut_nhan()
{
	if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
	{
		delay(500); //check chac chan la do ng nhan nut
		if (digitalRead(Button_Mode) == HIGH)
		{
			lcd.clear();
			long startTime = millis(); // giá trị ban đầu được gán bằng giá trị hiện tại của millis
			// Serial.printf("digitalRead(Button_Mode): ");
			// Serial.println(digitalRead(Button_Mode));
			while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
			{
				Serial.println(millis() - startTime);
				couter_mode = (millis() - startTime) / 1000;
				couter_mode = couter_mode / 1 % 10;
				lcd.setCursor(0, 0);
				lcd.print("Couter: ");
				lcd.print(couter_mode);
				lcd.print(" seconds  ");
				if (couter_mode < 1)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode Selection      ");
				}
				else if (couter_mode >= 7)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Message    ");
					lcd.setCursor(0, 2);
					lcd.print("                    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
				}
				/* vao mode setup wifi */
				else if (couter_mode >= 5)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Wifi Change");
					lcd.setCursor(0, 2);
					lcd.print("         Message    ");
					lcd.setCursor(0, 3);
					lcd.print("                    ");
				}
				/* vao mode setup vi tri thoi tiet */
				else if (couter_mode >= 3)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode: >> Location   ");
					lcd.setCursor(0, 2);
					lcd.print("         Wifi Change");
					lcd.setCursor(0, 3);
					lcd.print("         Message    ");
				}
				/* vao mode setup bao thuc */
				else if (couter_mode >= 1)
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
			/* thời gian bằng giá trị hiện tại trừ giá trị ban đầu */
			long duration = millis() - startTime;
			Serial.printf("couter_mode: ");
			Serial.println(couter_mode);
			/* Message mode*/
			if (couter_mode >= 7)
			{
				/* Message mode*/
				lcd.clear();
				delay(100);
				customM(0 + 1, 0);
				delay(100);
				customE(0 + 1 + 5, 0);
				delay(100);
				customS(0 + 1 + 5 + 4, 0);
				delay(100);
				customS(0 + 1 + 5 + 4 + 4, 0);

				customA(6 + 2, 2);
				delay(100);
				customG(6 + 4 + 2, 2);
				delay(100);
				customE(6 + 4 + 4 + 2, 2);
				delay(1000);
				/* Hien thi message tu Thingspeak_Message */
				lcd.clear();
				Thingspeak_Message();
				lcd.clear();
			}
			/* vao mode setup wifi */
			else if (couter_mode >= 5)
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
			else if (couter_mode >= 3)
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
			else if (couter_mode >= 1)
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
				thaydoi_baothuc();
				lcd.clear();
			}
		}
	}
}

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
	int dem_location = 0;
	while (((unsigned long)(millis() - dem_10s_stop) < 10000) && (stt_mode == 0))
	{
		if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
		{
			delay(500); //check chac chan la do ng nhan nut
			if (digitalRead(Button_Mode) == HIGH)
			{
				long startTime = millis();				 // giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_mode = (millis() - startTime) / 1000;
					couter_mode = couter_mode / 1 % 10;
					lcd.setCursor(0, 0);
					lcd.print("Couter: ");
					lcd.print(couter_mode);
					lcd.print(" seconds  ");
					if (couter_mode < 1)
					{
					}
					else if (couter_mode >= 9)
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
					else if (couter_mode >= 7)
					{
						bien_location_eeprom = 3;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> Hue        ");
						lcd.setCursor(0, 2);
						lcd.print("         HCMC       ");
						lcd.setCursor(0, 3);
						lcd.print("         VungTau    ");
					}
					else if (couter_mode >= 5)
					{
						bien_location_eeprom = 2;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> DaLat      ");
						lcd.setCursor(0, 2);
						lcd.print("         Hue        ");
						lcd.setCursor(0, 3);
						lcd.print("         HCMC       ");
					}
					else if (couter_mode >= 3)
					{
						bien_location_eeprom = 1;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> VungTau    ");
						lcd.setCursor(0, 2);
						lcd.print("         DaLat      ");
						lcd.setCursor(0, 3);
						lcd.print("         Hue        ");
					}
					else if (couter_mode >= 1)
					{
						bien_location_eeprom = 0;
						lcd.setCursor(0, 1);
						lcd.print("Loca: >> HCMC       ");
						lcd.setCursor(0, 2);
						lcd.print("         VungTau    ");
						lcd.setCursor(0, 3);
						lcd.print("         DaLat      ");
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
				Serial.printf("couter_mode: ");
				Serial.println(couter_mode);
				if (couter_mode < 1)
				{
				}
				else if (couter_mode >= 7)
				{
					bien_location_eeprom = 3;
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
				else if (couter_mode >= 5)
				{
					bien_location_eeprom = 2;
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
				else if (couter_mode >= 3)
				{
					bien_location_eeprom = 1;
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
				else if (couter_mode >= 1)
				{
					bien_location_eeprom = 0;
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
	stt_mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_location_eeprom, bien_location_eeprom);
	EEPROM.commit();
	Serial.print("bien_location_eeprom duoc set eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_location_eeprom));
}

void printLocalTime()
{
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

	nam = atoi(buffer_NAM);
	thang = atoi(buffer_THANG);
	ngay = atoi(buffer_NGAY);
	thu = atoi(buffer_thu_be);
	gio = atoi(buffer_GIO);
	phut = atoi(buffer_PHUT);
	giay = atoi(buffer_GIAY);

	if (nam < 2019) /*neu nam duoi 2019 cua nghia la time chua dc update */
	{
		/* lcd hien thi chu UPDATE TIME */
		Serial.println(" ");
		Serial.println("Thoi gian chua update.");
		lcd.clear();
		Serial.println(" ");
		Serial.println("Hien thi UPDATE TIME.");
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
		if ((giay % 5 == 0) && (xoa_1_lan == 0))
		/* cu moi 5 giay xoa 2 line tren 1 lan */
		{
			lcd.setCursor(0, 0);
			lcd.print("                    ");
			lcd.setCursor(0, 1);
			lcd.print("                    ");
			xoa_1_lan++;
		}
		else if (giay % 5 != 0)
		{
			/* code */
			xoa_1_lan = 0;
		}

		if (giay / 1 % 10 < 5)
		/* moi che do hien thi 5 giay */
		{
			if ((ngay == DAY_DungNguyen) && (thang == MON_DungNguyen))
			{
				lcd.setCursor(0, 0);
				lcd.print("DUNG Cute!");

				lcd.print("HPBD!");
				static int tuoi_DUNG_cute;
				tuoi_DUNG_cute = nam - 1994;
				lcd.setCursor(0, 1);
				lcd.print("DUNG tron ");
				lcd.print(tuoi_DUNG_cute);
				lcd.print(" tuoi.");
				Serial.println("Sanh thần Trâm ngáo :3");
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
				if (bien_location_eeprom == 0)
				{
					lcd.print("TpHcm"); /* chuyen thanh location */
				}
				else if (bien_location_eeprom == 1)
				{
					lcd.print("VgTau"); /* chuyen thanh location */
				}
				else if (bien_location_eeprom == 2)
				{
					lcd.print("DaLat"); /* chuyen thanh location */
				}
				else if (bien_location_eeprom == 3)
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

		/* qua gio moi la keu  */
		if ((phut == 0) && (giay < 2))
		{
			digitalWrite(CHUONG_BT, 1);
		}
		else if ((ngay == DAY_DungNguyen) && (thang == MON_DungNguyen))
		{
			/*
				xử lý ngắt trong ngày
			*/
			Serial.println("Sanh thần Trâm ngáo :3");
		}
		else if ((hen_gio == gio) && (hen_phut == phut) &&
				 (giay < 2) && (stt_mode_baothuc == 0))
		{
			active_bao_thuc();
			stt_mode_baothuc = 1;
		}
		else
		{
			digitalWrite(CHUONG_BT, 0);
			/* khoa trang thai cua active_bao_thuc */
			stt_mode_baothuc = 0;
		}
	}
}

void Call_Weather_Every_10Min()
{
	if ((unsigned long)(millis() - time_dem_thoitiet) > 60 * 10 * 1000) //10 phut/ lan
	{
		time_dem_thoitiet = millis();
		// Serial.printf("Trang thai WiFi.status(): %d\r\n", WiFi.status());
		Weather_Online_sever();
		// Serial.println("===========================");
	}
	// unsigned long demmm = millis() - time_dem_thoitiet;
	// Serial.printf("Demmm = % d\r\n", demmm);
}

/* Lay gia tri thoi tiet tai vi tri da chon */
void Weather_Online_sever()
{
	if (bien_location_eeprom == 0)
	{
		Location = "1566083";
	}
	else if (bien_location_eeprom == 1)
	{
		Location = "1562414";
	}
	else if (bien_location_eeprom == 2)
	{
		Location = "1584071";
	}
	else if (bien_location_eeprom == 3)
	{
		Location = "1565033";
	}

	if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
	{
		HTTPClient http; //Declare an object of class HTTPClient

		// specify request destination
		http.begin("http://api.openweathermap.org/data/2.5/weather?id=" + Location + "&APPID=" + API_Key);

		int httpCode = http.GET(); // send the request

		if (httpCode > 0) // check the returning code
		{
			String payload = http.getString(); //Get the request response payload

			DynamicJsonBuffer jsonBuffer(512);

			// Parse JSON object
			JsonObject &root = jsonBuffer.parseObject(payload);
			if (!root.success())
			{
				Serial.println(F("Parsing failed !"));
			}

			temp = (float)(root["main"]["temp"]) - 273.15;		 // get temperature in °C
			humidity = root["main"]["humidity"];				 // get humidity in %
			pressure = (float)(root["main"]["pressure"]) / 1000; // get pressure in bar
			wind_speed = root["wind"]["speed"];					 // get wind speed in m/s
			wind_degree = root["wind"]["deg"];					 // get wind degree in °

			// print data
			Serial.printf("Temperature = % .2f°C\r\n", temp);
			Serial.printf("Humidity = % d % %\r\n", humidity);
			// Serial.printf("Pressure = % .3f bar\r\n", pressure);
			// Serial.printf("Wind speed = % .1f m / s\r\n", wind_speed);
			// Serial.printf("Wind degree = % d°\r\n\r\n", wind_degree);
		}
		http.end(); //Close connection
		yield();	// disble Soft WDT reset - NodeMCU
	}
}

void smartConfig_ndb()
{
	lcd.createChar(1, UB);
	//Mode wifi là station
	WiFi.mode(WIFI_STA);
	WiFi.beginSmartConfig();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Begin SmartConfig!!!");
	int dem = 100;
	while (1)
	{
		delay(1000);
		digitalWrite(LED_TT, !digitalRead(LED_TT));
		dem--;
		Serial.println(dem);
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
		//Kiểm tra kết nối thành công in thông báo
		if (WiFi.smartConfigDone())
		{
			Serial.println("SmartConfig Success");
			String qsid = WiFi.SSID();
			String qpass = WiFi.psk();
			lcd.setCursor(0, 1);
			lcd.print("SmartConfig Success");
			lcd.setCursor(0, 2);
			lcd.print(qsid);
			lcd.setCursor(0, 3);
			lcd.print(qpass);
			delay(2000);
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

				Serial.println("writing eeprom ssid:");
				for (int i = 0; i < qsid.length(); ++i)
				{
					EEPROM.write(i, qsid[i]);
					Serial.print("Wrote: ");
					Serial.println(qsid[i]);
				}
				Serial.println("writing eeprom pass:");
				for (int i = 0; i < qpass.length(); ++i)
				{
					EEPROM.write(32 + i, qpass[i]);
					Serial.print("Wrote: ");
					Serial.println(qpass[i]);
				}
				EEPROM.commit();
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Saved ID & Pass Wifi");
				delay(1000);
				ESP.restart();
			}
		}
	}
}

void thaydoi_baothuc()
{
	unsigned long dem_10s_stop = millis();
	while (((unsigned long)(millis() - dem_10s_stop) < 10000) && (stt_mode == 0))
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

		if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
		{
			delay(500); //check chac chan la do ng nhan nut
			if (digitalRead(Button_Mode) == HIGH)
			{
				long startTime = millis();				 // giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_mode = (millis() - startTime) / 1000;
					couter_mode = couter_mode / 1 % 10;
					lcd.setCursor(0, 0);
					lcd.print("Couter: ");
					lcd.print(couter_mode);
					lcd.print(" seconds  ");
					if (couter_mode < 1)
					{
						lcd.setCursor(0, 1);
						lcd.print("Mode Selection      ");
					}
					else if (couter_mode >= 5)
					{
						lcd.setCursor(0, 1);
						lcd.print("Out Mode            ");
						delay(2000);
					}
					else if (couter_mode >= 3)
					{
						lcd.setCursor(0, 1);
						lcd.print("===>>>> Set Minute  ");
					}
					else if (couter_mode >= 1)
					{
						lcd.setCursor(0, 1);
						lcd.print(" Set Hours <<<<<<===");
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
				Serial.printf("couter_mode: ");
				Serial.println(couter_mode);
				if (couter_mode < 1)
				{
					lcd.setCursor(0, 1);
					lcd.print("Mode Selection");
				}
				else if (couter_mode >= 5)
				{
					/* set = 1 de vao while */
					stt_mode = 1;
				}
				else if (couter_mode >= 3)
				{
					/* set = 1 de vao while */
					stt_mode = 1;
					chinh_phut_hen_gio();
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
				}
				else if (couter_mode >= 1)
				{
					/* set = 1 de vao while */
					stt_mode = 1;
					chinh_gio_hen_gio();
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop = millis();
					/* check hanh vi nut nhan */
				}
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	stt_mode = 0;
}

void chinh_gio_hen_gio()
{
	unsigned long dem_nhay = 0;
	unsigned long time_dem_baothuc = millis();
	unsigned long dem_10s_stop_g = millis();
	while (((unsigned long)(millis() - dem_10s_stop_g) < 10000) && (stt_mode == 1))
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
		Serial.printf("couter_mode: ");
		Serial.println(dem_nhay);

		lcd.setCursor(9, 2);
		lcd.write(4);
		lcd.setCursor(9, 3);
		lcd.write(1);

		/* hien thi phut font so lon */
		printDigits(hen_phut / 10 % 10, 11, 2);
		printDigits(hen_phut / 1 % 10, 15, 2);

		if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
		{
			delay(50); //check chac chan la do ng nhan nut
			if (digitalRead(Button_Mode) == HIGH)
			{
				hen_gio++;
				if (hen_gio >= 24)
				{
					hen_gio = 0;
				}
				long startTime = millis();
				while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop_g = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_mode = (millis() - startTime) / 1000;
					/* hien thi gio font so lon */
					printDigits(hen_gio / 10 % 10, 1, 2);
					printDigits(hen_gio / 1 % 10, 5, 2);
					if (couter_mode >= 2)
					{
						lcd.setCursor(19, 0);
						lcd.write(7);
						stt_mode = 0;
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	stt_mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_hengio, hen_gio);
	EEPROM.commit();
	Serial.print("hen_gio duoc set eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_hengio));
}

void chinh_phut_hen_gio()
{
	unsigned long time_dem_baothuc = millis();
	unsigned long dem_nhay = 0;
	unsigned long dem_10s_stop_P = millis();
	while (((unsigned long)(millis() - dem_10s_stop_P) < 10000) && (stt_mode == 1))
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

		if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
		{
			delay(50); //check chac chan la do ng nhan nut
			if (digitalRead(Button_Mode) == HIGH)
			{
				hen_phut++;
				if (hen_phut >= 60)
				{
					hen_phut = 0;
				}
				long startTime = millis();
				while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
				{
					/* khi nhan nut thi set lai time out mode */
					dem_10s_stop_P = millis();
					/* check hanh vi nut nhan */
					Serial.println(millis() - startTime);
					couter_mode = (millis() - startTime) / 1000;
					/* hien thi phut font so lon */
					printDigits(hen_phut / 10 % 10, 11, 2);
					printDigits(hen_phut / 1 % 10, 15, 2);
					if (couter_mode >= 2)
					{
						lcd.setCursor(19, 0);
						lcd.write(7);
						stt_mode = 0;
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	/* set lai gia tri cho su dung lan sau */
	stt_mode = 0;
	/* luu gia tri vao eeprom */
	EEPROM.write(index_eeprom_henphut, hen_phut);
	EEPROM.commit();
	Serial.print("hen_phut duoc set eeprom: ");
	Serial.println(EEPROM.read(index_eeprom_henphut));
}

void active_bao_thuc()
{
	lcd.clear();
	unsigned long dem_nhay = 0;
	unsigned long dem_30s_stop = millis();
	unsigned long time_dem_baothuc = millis();

	while (((unsigned long)(millis() - dem_30s_stop) < 30000) &&
		   (stt_mode_baothuc == 0))
	{
		dem_nhay = (unsigned long)(millis() - time_dem_baothuc);
		if (dem_nhay < 300)
		{
			lcd.clear(); //day thoi
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

		digitalWrite(CHUONG_BT, 1);
		if (digitalRead(Button_Mode) == HIGH) // nếu nút bấm ở mức thấp
		{
			delay(500); //check chac chan la do ng nhan nut
			if (digitalRead(Button_Mode) == HIGH)
			{
				long startTime = millis();				 // giá trị ban đầu được gán bằng giá trị hiện tại của millis
				while (digitalRead(Button_Mode) == HIGH) // đợi cho nút bấm được giữ
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
					Serial.println(millis() - startTime);
					couter_mode = (millis() - startTime) / 1000;
					couter_mode = couter_mode / 1 % 10;

					if (couter_mode >= 2)
					{
						stt_mode_baothuc = 1;
						lcd.setCursor(19, 3);
						lcd.write(4);
						digitalWrite(CHUONG_BT, 0);
					}
					else if (couter_mode < 2)
					{
						lcd.setCursor(19, 3);
						lcd.print(couter_mode);
					}
					yield(); // disble Soft WDT reset - NodeMCU
				};
			}
		}
		yield(); // disble Soft WDT reset - NodeMCU
	}
	lcd.clear();
}

bool testWifi(void)
{
	int c = 0;
	Serial.println("");
	Serial.println("Waiting for Wifi to connect");
	while (c < 40)
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			return true;
		}
		delay(300);
		digitalWrite(LED_TT, !digitalRead(LED_TT));
		Serial.print(WiFi.status());
		/**
			typedef enum {
				WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
				WL_IDLE_STATUS      = 0,
				WL_NO_SSID_AVAIL    = 1,
				WL_SCAN_COMPLETED   = 2,
				WL_CONNECTED        = 3,
				WL_CONNECT_FAILED   = 4,
				WL_CONNECTION_LOST  = 5,
				WL_DISCONNECTED     = 6
			} wl_status_t;
		**/
		c++;
	}
	Serial.println("");
	Serial.println("Connect timed out, opening AP");
	return false;
}

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
