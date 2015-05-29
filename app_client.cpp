/* 
 * File:   app_client.cpp
 * Author: dan
 * 
 * Created on May 27, 2015, 5:05 PM
 */

#include <string>

#include "app_client.h"
#include "app_settings.h"
#include "app_server.h"
#include <arpa/inet.h>

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

app_client::app_client() 
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0 ) {
        // error
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(std::stoi(app_settings::Instance()->getSetting(app_settings::SERVER_PORT)));
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int yes = 1;
    if ( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
    {
         std::cout << "setsockopt";
    }
    
    if(connect(sockfd,(const sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    {
        std::cout << "unable to connect";
    }
}

app_client::~app_client() {
}

void app_client::sendListCommand() {
    
    app_server::RequestHeader reqHdr;
    app_server::ResponseHeader resHdr;
    
    char *szResponse = NULL;
    
    strncpy(reqHdr.szCommand,app_server::CMD_LIST_SERVER_PARAMS,sizeof(reqHdr.szCommand));
    
    write(sockfd,&reqHdr,sizeof(reqHdr));
    read(sockfd,&resHdr,sizeof(resHdr));
    
    std::cout << resHdr.szStatusCode << '\n';
    
    if (resHdr.iDataSize > 0) {
        
        szResponse = new char[resHdr.iDataSize+1];
        read(sockfd,szResponse,resHdr.iDataSize);
    
        std::cout << szResponse;
        delete [] szResponse;
    }
}

void app_client::sendStopCommand() {
    app_server::RequestHeader reqHdr;
    app_server::ResponseHeader resHdr;
    
    char *szResponse = NULL;
    
    strncpy(reqHdr.szCommand,app_server::CMD_STOP,sizeof(reqHdr.szCommand));
    
    write(sockfd,&reqHdr,sizeof(reqHdr));
    read(sockfd,&resHdr,sizeof(resHdr));
    
    std::cout << resHdr.szStatusCode << '\n';
    
    if (resHdr.iDataSize > 0) {
        
        szResponse = new char[resHdr.iDataSize+1];
        read(sockfd,szResponse,resHdr.iDataSize);
    
        std::cout << szResponse;
        delete [] szResponse;
    }
}

void app_client::sendOCRInfo(std::string szInputTemplate,std::string szInputImage)
{
    app_server::RequestHeader reqHdr = { 0 };
    app_server::ResponseHeader resHdr = { 0 };
    
    char *szResponse = NULL;
    
    FILE *fTemplate = fopen(szInputTemplate.c_str(),"r");
    fseek(fTemplate,0,SEEK_END);
    reqHdr.iOCRTemplateSize = ftell(fTemplate);
    rewind(fTemplate);
    
    FILE *fImage = fopen(szInputImage.c_str(),"r");
    fseek(fImage,0,SEEK_END);
    reqHdr.iOCRImageSize = ftell(fImage);
    rewind(fImage);
    
    strncpy(reqHdr.szCommand,app_server::CMD_START_OCR_PROCESS,sizeof(reqHdr.szCommand));
    strcpy(reqHdr.szTemplateName,szInputTemplate.c_str());
    strcpy(reqHdr.szImageName,szInputImage.c_str());
    reqHdr.iProcessID = 10;
    
    write(sockfd,&reqHdr,sizeof(reqHdr));
    
    // read template file and send it to server
    
    char buffer[256];
    void *pBuffer = buffer;
    int bytes_read;
    int bytes_written;
    
    while (1) {
        
        bytes_read = fread(buffer,sizeof(char),sizeof(buffer),fTemplate);
        
        if (bytes_read <= 0)
            break;
        
        while (bytes_read > 0) {
            bytes_written = write(sockfd,pBuffer,bytes_read);
            if (bytes_written <= 0)
                break;
            bytes_read -= bytes_written;
            pBuffer += bytes_written;
        }
    }
    
    fclose(fTemplate);
    
    while (1) {
        
        bytes_read = fread(buffer,sizeof(char),sizeof(buffer),fImage);
        
        if (bytes_read <= 0)
            break;
        
        while (bytes_read > 0) {
            bytes_written = write(sockfd,pBuffer,bytes_read);
            if (bytes_written <= 0)
                break;
            bytes_read -= bytes_written;
            pBuffer += bytes_written;
        }
    }
    
    read(sockfd,&resHdr,sizeof(resHdr));
    
    std::cout << resHdr.szStatusCode << '\n';
    
    if (resHdr.iDataSize > 0) {
        
        szResponse = new char[resHdr.iDataSize+1];
        read(sockfd,szResponse,resHdr.iDataSize);
        
        std::cout << szResponse;
        delete [] szResponse;
    }
}
