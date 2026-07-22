#ifndef __POWERBAAS_H__
#define __POWERBAAS_H__

#pragma once

#include <HardwareSerial.h>

#include "MeterReading/MeterReading.h"
#include "MeterReading/SmartMeterAdapter.h"
#include "MeterReading/SmartMeterLineParser.h"

#include "../custom_log.h"


class Powerbaas {
  public:
    Powerbaas():
      _smartMeterAdapter(Serial1, _smartMeterLineParser, _meterReading),
      _onMeterReading([](const MeterReading& meterReading) {})
    {}

    void setup();
    void receive();

    void onMeterReading(const MeterReadingCallback& onMeterReading) {
        _onMeterReading = onMeterReading;
    }

  private:
    MeterReading _meterReading{"",0,0,0,0,0,0};
    SmartMeterLineParser _smartMeterLineParser;
    SmartMeterAdapter _smartMeterAdapter;

    MeterReadingCallback _onMeterReading;
};

#endif
