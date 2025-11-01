#ifndef e_config_page_h
#define e_config_page_h

#include <Arduino.h>
// #include <GyverDS3231.h>
#include <SettingsGyver.h>

#include "e_global.h"

void build(sets::Builder& b);
void update(sets::Updater& upd);

#endif