# Smart Clock
| Release | Release date |
| :----:  | :----:       |
| <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/bangnguyendev/SmartClock"> | <img alt="GitHub Release Date" src="https://img.shields.io/github/release-date/bangnguyendev/SmartClock"> |

## Installing with Boards Manager (More Information)

**Compatibility:** This guide covers installing third-party boards using Boards Manager, introduced in Arduino IDE versions 1.6.4 and later. 

**Preparation:**

1. **Download and install Arduino IDE:** Get the latest version compatible with your system (Windows, Mac OS, Linux 32-bit or 64-bit) from the official Arduino website: [https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)

**Adding ESP8266 Board Package:**

1. **Open Arduino IDE Preferences:** Navigate to **File > Preferences** (or **Arduino > Preferences** on Mac).
2. **Add Boards Manager URL:** In the **Additional Boards Manager URLs** field, paste the following link:

   ```
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```

   You can add multiple URLs separated by commas if needed for other board packages.
3. **Open Boards Manager:** Go to **Tools > Board > Boards Manager**.
4. **Install ESP8266 Platform:** Search for "esp8266" and click the **Install** button.
5. **Select ESP8266 Board (After Installation):** Once installed, choose your specific ESP8266 board from the **Tools > Board** menu.

**Latest Version:**

* Check the latest release version of the ESP8266 Arduino core: Latest release: [https://github.com/esp8266/Arduino/releases/latest/](https://github.com/esp8266/Arduino/releases/latest/)

**Documentation:**

* Refer to the ESP8266 Arduino core documentation for detailed instructions and examples: [invalid URL removed]

**Additional Libraries:**

This section provides links to popular libraries you might find useful for ESP8266 projects:

* **LCD I2C:** [https://github.com/lucasmaziero/LiquidCrystal_I2C](https://github.com/lucasmaziero/LiquidCrystal_I2C)
* **EEPROM ESP8266:** [https://github.com/esp8266/Arduino/blob/master/libraries/EEPROM/EEPROM.h](https://github.com/esp8266/Arduino/blob/master/libraries/EEPROM/EEPROM.h)
* **ArduinoJson:** [https://github.com/bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* **SmartConfig ESP:** [https://www.eeweb.com/smartconfig-how-to-turn-an-esp8266-into-a-smart-home-device/](https://www.eeweb.com/smartconfig-how-to-turn-an-esp8266-into-a-smart-home-device/)

**DigiCert Root Certificates:**

* While not directly related to ESP8266 development, this link provides DigiCert root certificates, which may be necessary for secure communication with certain servers: [https://www.digicert.com/kb/digicert-root-certificates.htm](https://www.digicert.com/kb/digicert-root-certificates.htm)


====================================

## Cài đặt ESP8266 với Boards Manager

**Khả năng tương thích:** Hướng dẫn này áp dụng cho việc cài đặt các bo mạch bên thứ ba bằng Boards Manager, được giới thiệu từ phiên bản Arduino IDE 1.6.4 trở lên.

**Chuẩn bị:**

1. **Tải xuống và cài đặt Arduino IDE:** Truy cập trang web chính thức của Arduino để lấy phiên bản mới nhất tương thích với hệ thống của bạn (Windows, Mac OS, Linux 32 bit hoặc 64 bit): [https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)

**Thêm gói bo mạch ESP8266:**

1. **Mở Preferences trong Arduino IDE:** Truy cập **File > Preferences** (hoặc **Arduino > Preferences** trên Mac).
2. **Thêm URL Boards Manager:** Trong trường **Additional Boards Manager URLs**, dán liên kết sau:

   ```
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```

   Bạn có thể thêm nhiều URL, phân cách bằng dấu phẩy nếu cần thiết cho các gói bo mạch khác.
3. **Mở Boards Manager:** Truy cập **Tools > Board > Boards Manager**.
4. **Cài đặt nền tảng ESP8266:** Tìm kiếm "esp8266" và nhấp vào nút **Install**.
5. **Chọn bo mạch ESP8266 (sau khi cài đặt):** Sau khi cài đặt, chọn bo mạch ESP8266 cụ thể của bạn từ menu **Tools > Board**.

**Phiên bản mới nhất:**

* Kiểm tra phiên bản phát hành mới nhất của ESP8266 Arduino core: Phiên bản mới nhất: [https://github.com/esp8266/Arduino/releases/latest/](https://github.com/esp8266/Arduino/releases/latest/)

**Tài liệu:**

* Tham khảo tài liệu ESP8266 Arduino core để biết hướng dẫn chi tiết và ví dụ: [https://docs.espressif.com/projects/arduino-esp32/en/latest/](https://docs.espressif.com/projects/arduino-esp32/en/latest/)

**Thư viện bổ sung:**

Phần này cung cấp liên kết đến các thư viện phổ biến mà bạn có thể thấy hữu ích cho các dự án ESP8266:

* **LCD I2C:** [https://github.com/lucasmaziero/LiquidCrystal_I2C](https://github.com/lucasmaziero/LiquidCrystal_I2C)
* **EEPROM ESP8266:** [https://github.com/esp8266/Arduino/blob/master/libraries/EEPROM/EEPROM.h](https://github.com/esp8266/Arduino/blob/master/libraries/EEPROM/EEPROM.h)
* **ArduinoJson:** [https://github.com/bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* **SmartConfig ESP:** [https://www.eeweb.com/smartconfig-how-to-turn-an-esp8266-into-a-smart-home-device/](https://www.eeweb.com/smartconfig-how-to-turn-an-esp8266-into-a-smart-home-device/)

**Chứng chỉ gốc DigiCert:**

* Mặc dù không liên quan trực tiếp đến việc phát triển ESP8266, liên kết này cung cấp các chứng chỉ gốc DigiCert, có thể cần thiết cho giao tiếp an toàn với một số máy chủ: [https://www.digicert.com/kb/digicert-root-certificates.htm](https://www.digicert.com/kb/digicert-root-certificates.htm)

