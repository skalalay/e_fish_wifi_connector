#include "e_global.h"

void init_db() {
    db.begin();  // прочитать данные из файла
    // для работы в таком режиме очень пригодится метод init():
    // создаёт запись соответствующего типа и записывает "начальные" данные,
    // если такой записи ещё нет в БД

    db.init(kk::WIFI_mode, 1);
    db.init(kk::STA_ssid, "KNT_TEST");
    db.init(kk::STA_password, "633633633e");
    db.init(kk::STA_ip, "192.168.1.116");
    db.init(kk::STA_gateway, "192.168.1.1");
    db.init(kk::STA_subnet, "255.255.255.0");
}