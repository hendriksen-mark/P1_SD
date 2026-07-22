#ifndef CONFIG_H
#define CONFIG_H

#pragma once

// ============================================
// General Configuration
// ============================================
#ifndef BASE_PORT
#define BASE_PORT 80
#endif

#ifndef SD_MISO_PIN
#define SD_MISO_PIN MISO
#endif
#ifndef SD_MOSI_PIN
#define SD_MOSI_PIN MOSI
#endif
#ifndef SD_SCLK_PIN
#define SD_SCLK_PIN SCK
#endif
#ifndef SD_CS_PIN
#define SD_CS_PIN 10 // Chip Select pin for SD card
#endif
#ifndef DEVICE_NAME
#define DEVICE_NAME "P1_SD"
#endif

#define P1_FILE_REGEX "%.2s-%.2s-%.2s.csv"
#define P1_TIMESTAMP_REGEX "%.2s-%.2s-%.2s %.2s:%.2s:%.2s"

#define LOG_FILE_NAME "/log.txt"
#define LOG_MAX_FILE_SIZE_BYTES (1300 * 1024) // ~1.30 MB
#define MAX_UPLOAD_SIZE (300 * 1024)

// ============================================
// LOG Server Configuration
// ============================================
#define LOG_SERVER_PORT 2001
#define MAX_LOG_CONNECTIONS 1    // Log clients (reduced to fit socket limit)
#define LOG_CLIENT_TIMEOUT 60000 // 60 seconds in milliseconds (longer for log clients)

// ============================================
// NTP Time Configuration
// ============================================
#define NTP_ENABLED true            // Enable NTP time synchronization
#define NTP_SERVER "pool.ntp.org"   // NTP server to use
#define NTP_UPDATE_INTERVAL 3600000 // Update every hour (3600 seconds)
#define NTP_TIMEZONE_OFFSET 1       // UTC+1 for Netherlands (CET)
#define NTP_DST_OFFSET 1            // Additional hour for DST (CEST)
#define NTP_TIMEOUT 10000           // 10 second timeout for NTP requests

#endif // CONFIG_H
