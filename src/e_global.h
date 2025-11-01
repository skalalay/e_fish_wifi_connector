#ifndef e_global_h
#define e_global_h

#include <Arduino.h>
// #include <Datime.h>
#include <GyverDBFile.h>
#include <LittleFS.h>

extern GyverDBFile db;

// #include <SettingsGyver.h>
// SettingsGyver sett("My Settings", &db);

void init_db();

// struct Data_DB {

// };

struct Data_var { // Все переменные
    // float temp_1;

    // String time_from_rtc;
    // Datime dt(ds3231);
    // Datime time_from_rtc;  // время из RTC
    // uint32_t time_from_rtc;  // время из RTC
    // uint32_t date_for_rtc;  // время из вебморды для синронизации RTC
    // uint32_t time_for_rtc;  // время из вебморды для синронизации RTC
    // uint32_t date_time_for_rtc;  // время из вебморды для синронизации RTC    
};

struct Data_const {
    // Данные для конкретного устройства

    const char* AP_ssid = "wifi_fish";
    const char* AP_password = "12345678";
    const char* AP_ip = "192.168.11.1";
    const char* AP_subnet = "255.255.255.0";

    // OLED pins
    const uint8_t oled_sda = 32;
    const uint8_t oled_scl = 33;

    // Button pin
    const uint8_t btn_pin = 14;
};

DB_KEYS(
    kk,
    WIFI_mode,
    STA_ssid,
    STA_password,
    STA_ip,
    STA_gateway,
    STA_subnet);

#endif