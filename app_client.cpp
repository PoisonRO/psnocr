/* 
 * File:   app_client.cpp
 * Author: dan
 * 
 * Created on May 27, 2015, 5:05 PM
 */

#include <string>

#include "app_client.h"
#include "app_settings.h"
#include <arpa/inet.h>


#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

app_client::app_client() 
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0 ) {
        // error
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(std::stoi(app_settings::Instance()->getSetting(app_settings::SERVER_PORT)));
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(sockfd,(const sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    {
      // error
    }
}

app_client::~app_client() {
}

void app_client::sendCommand(){
    int n=0;
    char recvBuff[1024];
    
    while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
      recvBuff[n] = 0;
      if(fputs(recvBuff, stdout) == EOF)
    {
      printf("\n Error : Fputs error");
    }
      printf("\n");
    }
 
  if( n < 0)
    {
      printf("\n Read Error \n");
    }
}

