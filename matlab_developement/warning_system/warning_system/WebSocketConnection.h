#ifndef _WEB_SOCKET_CONNECTION_H_
#define _WEB_SOCKET_CONNECTION_H_

#include "Arduino.h"
#undef min
#undef max
#include <string>
#include <map>

#if defined(ARDUINO_WIFI_LIB_101)
	#include "WiFi101.h"
#elif defined(ARDUINO_WIFI_LIB_NINA)
	#include "WiFiNINA.h"
#endif

const uint16_t MAX_WS_BUFFER_SIZE = 1024;

class WebSocketServer;

class WebSocketConnection
{
public:
    WebSocketConnection();
    virtual ~WebSocketConnection();

    void run();
	void setServer(WiFiServer* server);
    bool sendWebSocketData(const char *buf);
	bool getWebSocketData(String* dataBuf);
	void closeWebSocket(void);

private:
    bool handleHTTP(char* buf, int size);
    bool handleWebSocket(const char* buf, int size);
    bool sendUpgradeResponse(char* key);

	WiFiServer* mTCPSocketServer; 
	WiFiClient mConnection;
    bool isWebSocket;
    bool mPrevFin;
	String subData;
};

#endif
