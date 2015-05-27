/* 
 * File:   app_server.cpp
 * Author: dan
 * 
 * Created on May 27, 2015, 3:50 PM
 */

#include "app_server.h"
#include "app_settings.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

app_server::app_server() 
{
    alive = true;
    iConnections = 0;
    
    // read xml settings;
    iServerPort = std::stoi(app_settings::Instance()->getSetting(app_settings::SERVER_PORT));
    iMaxConnections = std::stoi(app_settings::Instance()->getSetting(app_settings::MAX_SERVER_CONNECTIONS));
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    // LOG socket retrieve
    
    memset(&serv_addr,'0',sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(iServerPort);
    
    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    
    if (listen(listenfd,10) == -1) {
        alive = false;
    }
}

app_server::~app_server() 
{
    
}

void app_server::run() 
{
    do {
        
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
  
        std::string sendBuff = "Message from server";
        
        write(connfd, sendBuff.c_str(), sendBuff.length());
 
        close(connfd);    
        sleep(1);
        
    } while (alive);
}

