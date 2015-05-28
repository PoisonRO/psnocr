/* 
 * File:   app_server.h
 * Author: dan
 *
 * Created on May 27, 2015, 3:50 PM
 */

#ifndef APP_SERVER_H
#define	APP_SERVER_H

// server socket includes

#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CMD_SIZE 10
#define MAX_RES_SIZE 11

class app_server {
    
public:
    
    // Known Commands
    static const    char CMD_STOP[MAX_CMD_SIZE];
    static const    char CMD_LIST_SERVER_PARAMS[MAX_CMD_SIZE];
    static const    char CMD_START_OCR_PROCESS[MAX_CMD_SIZE];
    
    // Responses
    static const    char RES_OK[MAX_RES_SIZE];
    static const    char RES_GEN_ERROR[MAX_RES_SIZE];
    static const    char RES_UNKNOWN_COMMAND[MAX_RES_SIZE];
    
    app_server();
    virtual ~app_server();
    
    void run();
    
    struct RequestHeader {
        char                szCommand[MAX_CMD_SIZE];
        unsigned long       iDataSize;
    };
    
    struct ResponseHeader {
        char                szStatusCode[MAX_RES_SIZE];
        unsigned long       iDataSize;
    };
    
private:
    
    void ProcessRequest();
    
    // startup settings
    int         iServerPort;
    int         iMaxConnections;
    
    // server variables
    int         iConnections;
    bool        alive; 
    bool        bAcceptConnections;
    
    sockaddr_in serv_addr;
    int         listenfd = 0,
                connfd = 0;
    
};

#endif	/* APP_SERVER_H */

