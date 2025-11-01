#include <Arduino.h>
#include <WiFi.h>

#include "e_global.h"
Data_var var_data;      // Структура переменных
Data_const const_data;  // Структура констант

#include <GyverDBFile.h>
#include <LittleFS.h>
GyverDBFile db(&LittleFS, "/data.db");

#include <SettingsGyver.h>
SettingsGyver sett("Настройки", &db);

#include <EncButton.h>
// можно управлять кнопкой и дисплеем из main и из класса
Button btn(const_data.btn_pin, INPUT_PULLUP, HIGH);  // кнопка ресета

#include "e_config_page.h"
#include "e_wifi_connector.h"
EWifiConnector wc(&btn);

void setup() {
    Serial.begin(115200);
    Serial.println("START");

    delay(2000);

    // базу данных запускаем до подключения к точке
    LittleFS.begin(true);
    init_db();

    delay(2000);

    // uint16_t device_mode = 2;
    if (db[kk::WIFI_mode].toInt() == 1)  // 1 - точка доступа (AP)
    {
        Serial.print("AP_Start\n");

        // two_oled_show.wifi_mode(1, "AP Start");

        wc.set_ap_ip(const_data.AP_ip);
        wc.set_ap_subnet(const_data.AP_subnet);
        wc.set_ap_ssid(const_data.AP_ssid);
        wc.set_ap_password(const_data.AP_password);
        wc.AP_Start();

    } else if (db[kk::WIFI_mode].toInt() == 2)  // 2 - станция (STA)
    {
        Serial.print("STA_Start\n");

        // two_oled_show.wifi_mode(2, "STA Start");

        wc.set_sta_static_ip(db[kk::STA_ip].c_str());
        wc.set_sta_static_gateway(db[kk::STA_gateway].c_str());
        wc.set_sta_static_subnet(db[kk::STA_subnet].c_str());
        wc.set_sta_ssid(db[kk::STA_ssid].c_str());
        wc.set_sta_password(db[kk::STA_password].c_str());
        wc.STA_static_ip_Start();
    }

    // ======== SETTINGS ========
    sett.begin();
    sett.onBuild(build);
    sett.onUpdate(update);

    db.dump(Serial);
}

void loop() {
    sett.tick();
    wc.tick();

    delay(10);
}