/*
 * GevcuAdapter.h
 *
 Copyright (c) 2020 Michael Neuweiler

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#ifndef GEVCUADAPTER_H_
#define GEVCUADAPTER_H_

#include "Configuration.h"
#include "ArrayMap.h"
#include "Logger.h"
#include "WebSocket.h"
#include <ArduinoJson.h>

struct DataPoint
{
    char code;
    uint8_t length;
    bool unsignd;
    uint16_t divisor;
    String label;
};

class GevcuAdapter: public WebSocketObserver
{
public:
    GevcuAdapter();
    virtual ~GevcuAdapter();
    void start(Configuration *config);
    void loop();
    void event(String message);
    String getConfigParameter(String key);
private:
    bool processLiveData(char code, uint16_t len, char *data);
    void processInput(char *input);
    DataPoint* findDataPoint(char code);
    void sendDummyUpdate();
    int32_t readInt32(char *data);
    int16_t readInt16(char *data);
    uint16_t readUInt16(char *data);

    Configuration *config;
    ArrayMap<String, String> gevcuConfig;
    StaticJsonDocument<3000> doc;
    char serialBuffer[1024];
    uint16_t bufPos;
    uint8_t dataCount;
    DataPoint dataPoints[255] = {
            { 0, 2, true, 0, "systemState" }, // uint16_t
            { 1, 2, false, 10, "torqueActual" }, // int16_t
            { 2, 2, false, 0, "speedActual" }, // int16_t
            { 3, 2, false, 10, "throttle" }, // int16_t

            { 10, 2, true, 10, "dcVoltage" }, // uint16_t
            { 11, 2, false, 10, "dcCurrent" }, // int16_t
            { 12, 2, false, 0, "acCurrent" }, // int16_t
            { 13, 2, false, 10, "temperatureMotor" }, // int16_t
            { 14, 2, false, 10, "temperatureController" }, // int16_t
            { 15, 2, false, 0, "mechanicalPower" }, // int16_t

            { 20, 4, true, 0, "bitfieldMotor" }, // uint32_t
            { 21, 4, true, 0, "bitfieldBms" }, // uint32_t
            { 22, 4, true, 0, "bitfieldIO" }, // uint32_t

            { 30, 2, true, 10, "dcDcHvVoltage" }, // uint16_t
            { 31, 2, true, 10, "dcDcLvVoltage" }, // uint16_t
            { 32, 2, false, 10, "dcDcHvCurrent" }, // int16_t
            { 33, 2, false, 0, "dcDcLvCurrent" }, // int16_t
            { 34, 2, false, 10, "dcDcTemperature" }, // int16_t

            { 40, 2, true, 10, "chargerInputVoltage" }, // uint16_t
            { 41, 2, true, 100, "chargerInputCurrent" }, // uint16_t
            { 42, 2, true, 10, "chargerBatteryVoltage" }, // uint16_t
            { 43, 2, true, 100, "chargerBatteryCurrent" }, // uint16_t
            { 44, 2, false, 10, "chargerTemperature" }, // int16_t
            { 45, 2, false, 10, "maximumSolarCurrent" }, // int16_t
            { 46, 2, true, 10, "chargeHoursRemain" }, // uint16_t
            { 47, 2, true, 10, "chargeMinsRemain" }, // uint16_t
            { 48, 2, true, 100, "chargeLevel" }, // uint16_t

            { 50, 4, true, 100, "flowCoolant" }, // uint32_t
            { 51, 4, true, 100, "flowHeater" }, // uint32_t
            { 52, 2, true, 0, "heaterPower" }, // uint16_t
            { 53, 2, false, 10, "temperatureBattery1" }, // int16_t
            { 54, 2, false, 10, "temperatureBattery2" }, // int16_t
            { 55, 2, false, 10, "temperatureBattery3" }, // int16_t
            { 56, 2, false, 10, "temperatureBattery4" }, // int16_t
            { 57, 2, false, 10, "temperatureBattery5" }, // int16_t
            { 58, 2, false, 10, "temperatureBattery6" }, // int16_t
            { 59, 2, false, 10, "temperatureCoolant" }, // int16_t
            { 60, 2, false, 0, "temperatureHeater" }, // int16_t
            { 61, 2, false, 10, "temperatureExterior" }, // int16_t

            { 70, 1, true, 0, "powerSteering" }, // bool
            { 71, 1, true, 0, "enableRegen" }, // bool
            { 72, 1, true, 0, "enableHeater" }, // bool
            { 73, 1, true, 0, "enableCreep" }, // bool
            { 74, 2, false, 0, "cruiseControlSpeed" }, // int16_t
            { 75, 1, true, 0, "cruiseControlEnable" }, // bool

            { 80, 2, true, 0, "packResistance" }, // uint16_t
            { 81, 2, true, 0, "packHealth" }, // uint8_t
            { 82, 2, true, 0, "packCycles" }, // uint16_t
            { 83, 2, true, 100, "soc" }, // uint16_t
            { 84, 2, true, 0, "dischargeLimit" }, // uint16_t
            { 85, 2, true, 0, "chargeLimit" }, // uint16_t
            { 86, 1, true, 0, "chargeAllowed" }, // bool
            { 87, 1, true, 0, "dischargeAllowed" }, // bool
            { 88, 2, false, 10, "lowestCellTemp" }, // int16_t
            { 89, 2, false, 10, "highestCellTemp" }, // int16_t
            { 90, 2, true, 10000, "lowestCellVolts" }, // uint16_t
            { 91, 2, true, 10000, "highestCellVolts" }, // uint16_t
            { 92, 2, true, 10000, "averageCellVolts" }, // uint16_t
            { 93, 2, true, 10000, "deltaCellVolts" }, // uint16_t
            { 94, 2, true, 100, "lowestCellResistance" }, // uint16_t
            { 95, 2, true, 100, "highestCellResistance" }, // uint16_t
            { 96, 2, true, 100, "averageCellResistance" }, // uint16_t
            { 97, 2, true, 100, "deltaCellResistance" }, // uint16_t
            { 98, 1, true, 0, "lowestCellTempId" }, // uint8_t
            { 99, 1, true, 0, "highestCellTempId" }, // uint8_t
            { 100, 1, true, 0, "lowestCellVoltsId" }, // uint8_t
            { 101, 1, true, 0, "highestCellVoltsId" }, // uint8_t
            { 102, 1, true, 0, "lowestCellResistanceId" }, // uint8_t
            { 103, 1, true, 0, "highestCellResistanceId" }, // uint8_t
            { 104, 1, true, 0, "bmsTemperature" } // uint8_t*/
    };

};

extern GevcuAdapter gevcuAdapter;

#endif /* GEVCUADAPTER_H_ */
