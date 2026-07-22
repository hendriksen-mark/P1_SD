#ifndef __SMART_METER_ADAPTER_H__
#define __SMART_METER_ADAPTER_H__

#pragma once

#define TELEGRAM_LINE_SIZE 75

#include <HardwareSerial.h>
#include "MeterReading.h"
#include "SmartMeterLineParser.h"

enum class SmartMeterState {
   idle,
   settingUpSerial,
   receiving
};

class SmartMeterAdapter {
  public:
    SmartMeterAdapter(
      HardwareSerial& smartMeter,
      SmartMeterLineParser& smartMeterLineParser,
      MeterReading& meterReading
    ):
      _smartMeter(smartMeter),
      _smartMeterLineParser(smartMeterLineParser),
      _meterReading(meterReading),
      _lastTelegramCharacter('\0'), // Oplossing voor de CWE-398 waarschuwing
      _state(SmartMeterState::idle),  // Voorkom de volgende potentiële waarschuwing (pas de beginstatus aan indien nodig)
      _telegramIndex(0),
      _serialMode(1), // Default to 1, can be changed later
      _telegramLine{0} // Initialize the telegram line buffer to zero
    {}

    void receive(const MeterReadingCallback& onMeterReading);
    void setupSerialAndBaudrate(uint8_t serialMode);
    bool isReceiving() { return _state == SmartMeterState::receiving; };

  private:

    HardwareSerial& _smartMeter;
    SmartMeterLineParser& _smartMeterLineParser;
    MeterReading& _meterReading;
    
    char _lastTelegramCharacter;
    char _telegramLine[TELEGRAM_LINE_SIZE];
    size_t _telegramIndex = 0;

    // detect baudrate and check receiving data correct
    uint8_t _serialMode = 1;
    SmartMeterState _state{SmartMeterState::idle};
};

#endif
