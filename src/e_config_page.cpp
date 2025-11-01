#include "e_config_page.h"

extern GyverDBFile db;
extern SettingsGyver sett;
extern Data_var var_data;
// extern GyverDS3231 ds3231;

void build(sets::Builder& b) {
    {
        static bool sw_dt = 0;
        static bool sww = 0;
        static int8_t flag_dt = 0;   // флаг открытия настроек даты и время
        static int8_t flag_tcp = 0;  // флаг открытия настроек tcp

        b.Label("lbl_1"_h, "wifi_fish", "tests");
        // b.Label("lbl_1"_h, "d00010002", var_data.time_from_rtc);        

        // if (b.Switch("sw_dt"_h, "Время и Дата", &sw_dt)) {
        //     if (sw_dt) flag_dt = 1;
        //     else flag_dt = 0;
        //     b.reload();  // перезагрузить вебморду по клику на свитч
        // }

        if (flag_dt) {
            // b.Date("Дата", &var_data.date_for_rtc);
            // b.Time("Время", &var_data.time_for_rtc);

            // b.DateTime(" ", &var_data.date_time_for_rtc);

            // if (b.Button("btn_dt"_h, "Синхронизировать", sets::Colors::Red)) {
            //     Serial.println("Button btn_dt");
            //     // ds3231.setTime(var_data.date_for_rtc + var_data.time_for_rtc);
            //     ds3231.setTime(var_data.date_time_for_rtc);
            // }
        }

        if (b.Switch("sw1"_h, "WIFI", &sww)) {
            if (sww) flag_tcp = 1;
            else flag_tcp = 0;
            b.reload();  // перезагрузить вебморду по клику на свитч
        }

        if (flag_tcp) {
            b.Input(kk::STA_ssid, "SSID");
            b.Input(kk::STA_password, "Password");
            b.Input(kk::STA_ip, "IP address");
            b.Input(kk::STA_gateway, "Gateway");
            b.Input(kk::STA_subnet, "Subnet mask");
            if (b.Button("btn1"_h, "Сохранить и перезагрузить", sets::Colors::Red)) {
                Serial.println("Button 1");
                db[kk::WIFI_mode] = 2;
                db.update();
                delay(2000);
                ESP.restart();
            }
        }
    }
}

void update(sets::Updater& upd) {
    // upd.update("lbl_1"_h, var_data.time_from_rtc);
    // upd.update("fl1"_h, Temp1);
    // upd.update("sw1"_h, sww);
}