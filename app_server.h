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

class app_server {
    
public:
    
    app_server();
    virtual ~app_server();
    
    void run();
    
private:
    
    // startup settings
    int         iServerPort;
    int         iMaxConnections;
    
    // server variables
    int         iConnections;
    bool        alive; 
    
    
    sockaddr_in serv_addr;
    int         listenfd = 0,
                connfd = 0;
    
};

#endif	/* APP_SERVER_H */

