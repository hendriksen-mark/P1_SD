#include "Powerbaas/Powerbaas.h"

void Powerbaas::setup() {

  REMOTE_LOG_DEBUG(("Powerbaas setup:"));

  // try 3 different settings
  for (int serialMode = 0; serialMode < 3; serialMode++) {

    REMOTE_LOG_DEBUG((" > try serial mode %d", serialMode+1));

    _smartMeterAdapter.setupSerialAndBaudrate(serialMode);

    // try for 15 seconds
    for(int seconds = 0; seconds < 15; seconds++) {

      REMOTE_LOG_DEBUG((" > waiting for data... %d seconds", seconds+1));

      _smartMeterAdapter.receive(_onMeterReading);

      // we got readable data!
      if(_smartMeterAdapter.isReceiving()) {

        
        REMOTE_LOG_DEBUG((" > setup complete!"));
        REMOTE_LOG_DEBUG(("===================="));

        return;
      }
      // wait 1 second
      delay(1000);
    }
  }

  // failed!
  REMOTE_LOG_DEBUG((" > setup failed!"));
  REMOTE_LOG_DEBUG(("===================="));
}

void Powerbaas::receive() {
  _smartMeterAdapter.receive(_onMeterReading);
}
