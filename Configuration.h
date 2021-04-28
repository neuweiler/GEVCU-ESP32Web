/*
 * Configuration.h
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

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include "FSHandler.h"

class Configuration {
public:
	Configuration();
	virtual ~Configuration();
	void load();

	StaticJsonDocument<1000> doc;

	const char *wifiSsid;
	const char *wifiPassword;
	const char *wifiAddress;
	const char *wifiGateway;
	const char *wifiNetmask;

	const char *wifiSsidRemote;
	const char *wifiPasswordRemote;
	uint16_t wifiReconnectInterval;

	uint16_t currentUpdateInterval;
	const char *currentUpdateHost;
	uint16_t currentUpdatePort;
	const char *currentUpdateUri;

	uint8_t pinWifiLed;
};

extern Configuration config;

#endif /* CONFIGURATION_H_ */
