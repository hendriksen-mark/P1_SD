#ifndef P1_H
#define P1_H

#pragma once

#include <Powerbaas.h>
#include <WebServer.h>
#include <HTTPUpdateServer.h>

#include "functions.h"
#include "config.h"
#include "file_manager.h"

void P1_setup();
void P1_loop();
String determine_p1_file_name(const char *timestamp);
String formatTime(const char *input);

#endif // P1_H