/* 
 * File:   app_client.h
 * Author: dan
 *
 * Created on May 27, 2015, 5:05 PM
 */

#ifndef APP_CLIENT_H
#define	APP_CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>

class app_client {
    
public:
    
    app_client();
    virtual ~app_client();
    void sendListCommand();
    void sendStopCommand();
    void sendOCRInfo();
private:

    sockaddr_in serv_addr;
    
    int sockfd = 0;
};

#endif	/* APP_CLIENT_H */

