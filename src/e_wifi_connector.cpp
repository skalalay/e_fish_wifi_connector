#include "e_wifi_connector.h"

extern GyverDBFile db;

EWifiConnector::EWifiConnector() {
    // const char* AP_ip, const char* AP_subnet, const char* AP_ssid, const char* AP_password
}

//---------------------------------------------------------------------------------------------
EWifiConnector::EWifiConnector(Button* btn) {
    _btn = btn;
    // _oled_1 = oled_1;
    _tmr = new TimerMs(1000);
    _tmr->setPeriodMode();
    _button_polling = true;  // включаем опрос кнопки
}

//---------------------------------------------------------------------------------------------
// Если кнопка нажата - останавливаем вывод на все дисплеи
bool EWifiConnector::stopAllDisplayShow() {
    if (_btn_state) return true;  // 1 - вывод запрещен
    else return false;            // 0 - вывод разрешен
}

//---------------------------------------------------------------------------------------------
void EWifiConnector::timeUntilReset() {
    if (!_btn_state) return;

    // switch на каждую секунду, что бы можно было каждую секунду делать, что хочешь
    switch (_cnt_time_for_reset) {
        case 1: {
            Serial.print("10\n");
        } break;
        case 2: {
            Serial.print("9\n");
        } break;
        case 3: {
            Serial.print("8\n");
        } break;
        case 4: {
            Serial.print("7\n");
        } break;
        case 5: {
            Serial.print("6\n");
        } break;
        case 6: {
            // выключаем опрос кнопки и больше не включаем
            // пишем епром и через 5 секунд перезагрузка
            db[kk::WIFI_mode] = 1;
            db.update();
            _button_polling = false;
            Serial.print("5\n");
        } break;
        case 7: {
            Serial.print("4\n");
        } break;
        case 8: {
            Serial.println(db[kk::WIFI_mode]);
            Serial.print("3\n");
        } break;
        case 9: {
            Serial.print("2\n");
        } break;
        case 10: {
            Serial.print("1\n");
        } break;
        case 11: {
            Serial.print("0\n");
        } break;
        case 12: {
            Serial.print("0\n");
            ESP.restart();
        } break;
    }
    _cnt_time_for_reset++;
}

//---------------------------------------------------------------------------------------------
void EWifiConnector::startTimerToReset() {
    _tmr->start();
}

//---------------------------------------------------------------------------------------------
void EWifiConnector::stopTimerToReset() {
    _tmr->stop();
}

//---------------------------------------------------------------------------------------------
void EWifiConnector::tick() {
    _btn->tick();

    if (_button_polling) {
        if (_btn->press()) {
            Serial.println("press");
            _btn_state = true;
            _cnt_time_for_reset = 1;
            _tmr->start();
        }
        // if (_btn->hold()) Serial.println("hold");
        if (_btn->release()) {
            Serial.println("release");
            _btn_state = false;
            _tmr->stop();
            // _oled_1->clear();
            // _oled_1->update();
        }
    }

    if (_tmr->tick()) timeUntilReset();
}

//---------------------------------------------------------------------------------------------
void EWifiConnector::AP_Start() {
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    ia_AP_ip.fromString(_AP_ip);
    ia_AP_subnet.fromString(_AP_subnet);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ia_AP_ip, ia_AP_ip, ia_AP_subnet);
    WiFi.softAP(_AP_ssid, _AP_password);
}
//---------------------------------------------------------------------------------------------
void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
    Serial.println("Connected To The WiFi Network");
    // two_oled_show.wifi_mode(2, "Connected");
}

void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    // two_oled_show.wifi_mode(2, WiFi.localIP().toString().c_str());
}

void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
    Serial.println("Disconnected From WiFi Network");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(wifi_info.wifi_sta_disconnected.reason);

    WiFi.disconnect();

    Serial.println("Trying to Reconnect");

    Serial.println(db[kk::STA_ssid].c_str());
    Serial.println(db[kk::STA_password].c_str());

    WiFi.begin(db[kk::STA_ssid].c_str(), db[kk::STA_password].c_str());
    Serial.println("Connecting to WiFi Network ..");
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::STA_static_ip_Start() {
    WiFi.mode(WIFI_STA);
    WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(WiFi_Disconnected_Handler, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    // Настраивает статический IP-адрес
    Serial.println(_STA_ip);

    ia_STA_ip.fromString(_STA_ip);
    ia_STA_gateway.fromString(_STA_gateway);
    ia_STA_subnet.fromString(_STA_subnet);
    ia_STA_primary_dns.fromString(_STA_primaryDNS);
    ia_STA_secondar_dns.fromString(_STA_secondaryDNS);

    // Serial.println(ia_STA_ip);

    //    IPAddress primaryDNS(8, 8, 8, 8);

    if (!WiFi.config(ia_STA_ip, ia_STA_gateway, ia_STA_subnet, ia_STA_primary_dns, ia_STA_secondar_dns)) {
        Serial.println("STA Failed to configure");
    }

    WiFi.begin(_STA_ssid, _STA_password);
    Serial.println("Connecting to WiFi Network ..");
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::STA_dinamic_ip_Start() {
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_static_ip(const char* STA_ip) {
    _STA_ip = STA_ip;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_static_gateway(const char* STA_gateway) {
    _STA_gateway = STA_gateway;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_static_subnet(const char* STA_subnet) {
    _STA_subnet = STA_subnet;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_static_primary_dns(const char* STA_primaryDNS) {
    _STA_primaryDNS = STA_primaryDNS;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_static_secondary_dns(const char* STA_secondaryDNS) {
    _STA_secondaryDNS = STA_secondaryDNS;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_ssid(const char* STA_ssid) {
    _STA_ssid = STA_ssid;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_sta_password(const char* STA_password) {
    _STA_password = STA_password;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_ap_ip(const char* AP_ip) {
    _AP_ip = AP_ip;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_ap_subnet(const char* AP_subnet) {
    _AP_subnet = AP_subnet;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_ap_ssid(const char* AP_ssid) {
    _AP_ssid = AP_ssid;
}
//---------------------------------------------------------------------------------------------
void EWifiConnector::set_ap_password(const char* AP_password) {
    _AP_password = AP_password;
}