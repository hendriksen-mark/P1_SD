#include "P1.h"

HTTPUpdateServer httpUpdateServer;

WebServer server_P1(BASE_PORT);

Powerbaas powerbaas;

String determine_p1_file_name(const char *timestamp)
{
    char output[13];
    snprintf(output, sizeof(output), P1_FILE_REGEX, timestamp, timestamp + 2, timestamp + 4);
    return String(output);
}

String formatTime(const char *input)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), P1_TIMESTAMP_REGEX, input, input + 2, input + 4, input + 6, input + 8, input + 10);

    return String(buffer);
}

void handleNotFound_P1()
{ // default webserver response for unknow requests
    String message;
    message.reserve(200); // Pre-allocate to reduce memory fragmentation
    message = "File Not Found\n\n";
    message += "URI: ";
    message += server_P1.uri();
    message += "\nMethod: ";
    message += (server_P1.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server_P1.args();
    message += "\n";
    for (uint8_t i = 0; i < server_P1.args(); i++)
    {
        message += " " + server_P1.argName(i) + ": " + server_P1.arg(i) + "\n";
    }
    REMOTE_LOG_DEBUG("from:", server_P1.client().remoteIP().toString(), "not found:", server_P1.uri(), "args:", server_P1.args());
    server_P1.send(404, "text/plain", message);
}

void P1_setup()
{
    server_P1.onNotFound(handleNotFound_P1);
    server_P1.on("/", []()
                 {
        server_P1.sendHeader("Location", "/files", true);
        server_P1.send(302, "text/plain", ""); });
    server_P1.begin();
    setup_file(server_P1);
    httpUpdateServer.setup(&server_P1);

    powerbaas.onMeterReading([](const MeterReading &meterReading)
                             {
    String log_file_name = determine_p1_file_name(meterReading.timestamp);
    initializeCSVFile(log_file_name.c_str(), "timestamp;powerUsage;powerDeliverHigh;powerDeliverLow;powerReturnHigh;powerReturnLow;gas;voltageL1;voltageL2;voltageL3;currentL1;currentL2;currentL3;powerL1;powerL2;powerL3\n");
    String message = formatTime(meterReading.timestamp) + ";" +
                     String(meterReading.powerUsage) + ";" +
                     String(meterReading.powerDeliverHigh) + ";" +
                     String(meterReading.powerDeliverLow) + ";" +
                     String(meterReading.powerReturnHigh) + ";" +
                     String(meterReading.powerReturnLow) + ";" +
                     String(meterReading.gas) + ";" +
                     String(meterReading.voltageL1, 2) + ";" +
                     String(meterReading.voltageL2, 2) + ";" +
                     String(meterReading.voltageL3, 2) + ";" +
                     String(meterReading.currentL1, 2) + ";" +
                     String(meterReading.currentL2, 2) + ";" +
                     String(meterReading.currentL3, 2) + ";" +
                     String(meterReading.powerL1) + ";" +
                     String(meterReading.powerL2) + ";" +
                     String(meterReading.powerL3) + "\n"; });
    powerbaas.setup();
}

void P1_loop()
{
    powerbaas.receive();
}
