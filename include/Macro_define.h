/* PIN kết nối với chuông kêu */
#define PIN_signal_Bell 16
/* PIN kết nối với nút nhấn MODE */
#define Button_Mode 14

/* Define By User NDB */
#define ESP_NB_ZERO 0
#define ESP_NB_ONE 1
#define ESP_NB_OFF 0
#define ESP_NB_ON 1

/* Cài đặt trạng thái nút nhấn PULL_UP OR PULL_DOWN */
#define PULLUP_PULLDOWN 0 // PULL DOWN

/* Cập nhật OTA */
#define ProductKey "ee01b3e6-5101-4b37-8e0e-f53353bf12df"
#define Version "1.0.7"
#define MakeFirmwareInfo(k, v) "&_FirmwareInfo&k=" k "&v=" v "&FirmwareInfo_&"

/* MACRO BLYNK IOT */
#define ESP_NB_BLYNK ESP_NB_OFF
#define BLYNK_TEMPLATE_ID "TMPL85uHU5ks"
#define BLYNK_DEVICE_NAME "Template NDB"
#define BLYNK_AUTH_TOKEN "dHTAaLwA5F-ZdeGAcmXP3ZE54k20Joby"


/*index 0 to 31 */
#define index_eeprom_SSID 32
/*index 32 to 95 */
#define index_eeprom_PASS 96
/*index 96 to 100 */
#define index_eeprom_WIFI 96
#define index_eeprom_hengio 97
#define index_eeprom_henphut 98
#define index_eeprom_location_eeprom 99


/* ===== Open Weather Map =====
    1584071 DAT LAT
    1566083 TP HCM
    1565033 TP HUE
    1562414 VUNG TAU
*/
#define Location_TPHCM "1566083" 
#define Location_DALAT "1584071"
#define Location_TPHUE "1565033"
#define Location_VUTAU "1562414"
String Location = Location_TPHCM;
/* TK duybang14****@gmail.com openweathermap */
String APIKey_openweather = "15fc2e6f826c6eac50fade5e8ebcaeab";
/* bien nhiet do */
float temp;
int humidity;
float pressure;
float wind_speed;
int wind_degree;

/* ===== ThingSpeak ===== */
// Bắt đầu Ver 1.0.6 không sử dụng Thingspeak_Message
#define ESP_NB_THINGSPEAK ESP_NB_OFF
#if ESP_NB_THINGSPEAK
#include <ThingSpeak.h>
/* Channel Smart Clock */
#define ChannelNumber_Smartclock 947371
#define Fiels_Smartclock_Gio 1
#define Fiels_Smartclock_Phut 2
const char *WriteAPIKey_Smartclock = "9DU3YS7U45KE50OA";
const char *ReadAPIKey_Smartclock = "HZ6V9BBQBVUR8PXI";
/* Channel Status Thingspeak */
#define ChannelNumber_Status 951877
const char *WriteAPIKey_Status = "CKFBC2539BDNOTRB";
const char *ReadAPIKey_Status = "JAXYJ6LRKFRA6XTO";
/* Channel View */
#define ChannelNumber_View 947394
const char *WriteAPIKey_View = "0WLGTHFLKRW0GZDJ";
const char *ReadAPIKey_View = "RLQ8HD91AE19S4U3";
/* End data ThingSpeak  */
#endif

/* Cập nhật thời gian từ sever vn.pool.ntp.org */
char buffer_NAM[80];
char buffer_THANG[80];
char buffer_NGAY[80];
char buffer_THU[80], buffer_thu_be[80];
char buffer_N_T_N[80];
char buffer_GIO[80];
char buffer_PHUT[80];
char buffer_GIAY[80];
char buffer_sent_thingspeak[80];
int nam, thang, ngay, thu;
int hen_gio, hen_phut;
int gio, phut, giay;


/* Biến sử dụng trong báo thức */
#define DAY_BangNguyen 14 /* Ngay sinh nhat Bang */
#define MON_BangNguyen 4 /* Thang sinh nhat Bang */
int couter_Mode = 0;
int status_Mode = 0;
int status_Mode_Alarm = ESP_NB_ON;
int value_Location_EEPROM = 0;
unsigned long time_dem_thoitiet;


/* Khai báo cấu hình cho wifi */
const char *ssid = "nguyenduybang";
const char *passphrase = "nguyenduybang";
WiFiClient client;


extern void setup();
extern void loop();
extern void Check_Status_Button();
extern void Setup_Local_RealTime();
#if ESP_NB_THINGSPEAK
extern void Thingspeak_Message();
#endif
extern void Choose_location();
extern void Call_Weather_Every_10Min();
extern void Weather_Online_sever();
extern void smartConfig_ndb();
extern void Setup_AlarmClock();
extern void Set_Hour_Alarm();
extern void Set_Minute_Alarm();
extern void Active_Alarm();
extern void update_FOTA();
extern void Welcome_Smartclock();