#ifndef e_wifi_connector_h
#define e_wifi_connector_h

#include <Arduino.h>
#include <EncButton.h>
//#include <GyverOLED.h>
#include <TimerMs.h>
#include <WiFi.h>

//#include "e_two_oled_show.h"
#include "e_global.h"

// extern ETwoOledShow two_oled_show;

class EWifiConnector {
   public:
    EWifiConnector();
    EWifiConnector(Button* btn);

    void AP_Start();
    void STA_static_ip_Start();
    void STA_dinamic_ip_Start();
    void ap_ip();
    void ap_subnet();
    void ap_ssid();
    void ap_password();
    void sta_static_ip();
    void sta_ssid();
    void sta_password();

    void set_sta_static_ip(const char* STA_ip);
    void set_sta_static_gateway(const char* STA_gateway);
    void set_sta_static_subnet(const char* STA_subnet);
    void set_sta_static_primary_dns(const char* STA_primaryDNS);
    void set_sta_static_secondary_dns(const char* STA_secondaryDNS);
    void set_sta_ssid(const char* STA_ssid);
    void set_sta_password(const char* STA_password);

    void set_ap_ip(const char* AP_ip);
    void set_ap_subnet(const char* AP_subnet);
    void set_ap_ssid(const char* AP_ssid);
    void set_ap_password(const char* AP_password);

    bool stopAllDisplayShow();
    // void displayShow();
    void startTimerToReset();
    void stopTimerToReset();
    void tick();

    const char* _STA_ssid;
    const char* _STA_password;

   private:
    // void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
    // void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
    // void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info);
    const char* _AP_ip;
    const char* _AP_subnet;
    const char* _AP_ssid;
    const char* _AP_password;
    IPAddress ia_AP_ip;
    IPAddress ia_AP_subnet;

    const char* _STA_ip;
    const char* _STA_gateway;
    const char* _STA_subnet;
    const char* _STA_primaryDNS;
    const char* _STA_secondaryDNS;        
    IPAddress ia_STA_ip;
    IPAddress ia_STA_gateway;
    IPAddress ia_STA_subnet;
    IPAddress ia_STA_primary_dns;
    IPAddress ia_STA_secondar_dns;        

    TimerMs* _tmr;
    Button* _btn;
    bool _btn_state = 0;  // состояние кнопки 1 - нажата, 0 - не нажата
    int _cnt_time_for_reset = 1;
    bool _button_polling = 1;  // 1 - опрашиваем кнопку, 0 - не опрашиваем
    void timeUntilReset();
};

#endif