/* 
 * File:   app_server.cpp
 * Author: dan
 * 
 * Created on May 27, 2015, 3:50 PM
 */

#include "app_server.h"
#include "app_settings.h"
#include "ocr_parser.h"

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

// <editor-fold desc="Static variables" defaultstate="collapsed">
const char app_server::CMD_STOP[MAX_CMD_SIZE]                         = "STOP";
const char app_server::CMD_LIST_SERVER_PARAMS[MAX_CMD_SIZE]           = "LIST";
const char app_server::CMD_START_OCR_PROCESS[MAX_CMD_SIZE]            = "STARTOCR";

const char app_server::RES_OK[MAX_RES_SIZE]                           = "OK";
const char app_server::RES_GEN_ERROR[MAX_RES_SIZE]                    = "ERROR";
const char app_server::RES_UNKNOWN_COMMAND[MAX_RES_SIZE]              = "CMDINVALID";

const char app_server::RES_NO_INPUT_IMAGE[MAX_RES_SIZE]               = "NOIMG";
const char app_server::RES_NO_INPUT_TEMPLATE[MAX_RES_SIZE]            = "NOIMGS";
const char app_server::RES_NO_IMAGE_SIZE[MAX_RES_SIZE]                = "NOTMPL";
const char app_server::RES_NO_TEMPLATE_SIZE[MAX_RES_SIZE]             = "NOTMPLS";
const char app_server::RES_NO_PID[MAX_RES_SIZE]                       = "NOPID";
// </editor-fold>

app_server::app_server() 
{
    alive = true;
    bAcceptConnections = true;
    iConnections = 0;
    
    // read xml settings;
    iServerPort = std::stoi(app_settings::Instance()->getSetting(app_settings::SERVER_PORT));
    iMaxConnections = std::stoi(app_settings::Instance()->getSetting(app_settings::MAX_SERVER_CONNECTIONS));
    bKeepTemp = app_settings::Instance()->getSetting(app_settings::KEEP_TEMP_FILES) == "true" ? true : false;
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (listenfd < 0) {
        std::cout << "unable to get socket";
    }
    // LOG socket retrieve
    
    memset(&serv_addr,'0',sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(iServerPort);
    
    int yes = 1;
    if ( setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) {
         std::cout << "setsockopt";
    }
    
    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    
    if (listen(listenfd,10) == -1) {
        alive = false;
        bAcceptConnections = false;
        std::cout << "unable to get listen";
    }
    
    // create temp dir
    mkdir(app_settings::Instance()->getSetting(app_settings::TEMP_LOCATION).c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

app_server::~app_server() 
{
    close(listenfd);
}

void app_server::run() 
{
    while (alive) {
        
        if (bAcceptConnections) {
            ProcessRequest();
        }
        
        if (iConnections==0 && bAcceptConnections == false)
            alive = false;
        
        sleep(1);
        
    }
}

void app_server::ProcessRequest() 
{
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    RequestHeader hdrreq;
    
    read(connfd,&hdrreq,sizeof(RequestHeader));
    
    ResponseHeader hdrres;
    std::string responseString;
    
    // <editor-fold desc="Get Parameters Command" defaultstate="collapsed">
    // process list request
    if (strcmp(CMD_LIST_SERVER_PARAMS,hdrreq.szCommand) ==0) {
        strncpy(hdrres.szStatusCode,RES_OK,sizeof(hdrres.szStatusCode));
        
        responseString = "Listen port : ";
        responseString.append(std::to_string(iServerPort));
        responseString.append("\n");
        responseString.append("Max connections : ");
        responseString.append(std::to_string(iMaxConnections));
        responseString.append("\n");
        responseString.append("Connected clients : ");
        responseString.append(std::to_string(iConnections));
        responseString.append("\n");
        
        hdrres.iDataSize = strlen(responseString.c_str());
        
        write(connfd,&hdrres,sizeof(ResponseHeader));
        write(connfd,responseString.c_str(),hdrres.iDataSize);
        
        
    } else
    // </editor-fold>
        
    // <editor-fold desc="Stop Command" defaultstate="collapsed">
    // process stop command
    if (strcmp(CMD_STOP,hdrreq.szCommand) ==0) {
        strncpy(hdrres.szStatusCode,RES_OK,sizeof(hdrres.szStatusCode));
        hdrres.iDataSize = 0;
        write(connfd,&hdrres,sizeof(ResponseHeader));
        bAcceptConnections = false;
    } else
    // </editor-fold>
    
    if (strcmp(CMD_START_OCR_PROCESS,hdrreq.szCommand) ==0) {
        
        // check input parameters
        
        hdrres.iDataSize = 0;
        strncpy(hdrres.szStatusCode,RES_OK,sizeof(hdrres.szStatusCode));
        
        // no input image name sent
        if (strcmp(hdrreq.szImageName," ")==0)
            strncpy(hdrres.szStatusCode,app_server::RES_NO_INPUT_IMAGE,sizeof(hdrres.szStatusCode));
        
        if (strcmp(hdrreq.szTemplateName," ")==0)
            strncpy(hdrres.szStatusCode,app_server::RES_NO_INPUT_TEMPLATE,sizeof(hdrres.szStatusCode));
        
        if (hdrreq.iOCRImageSize==0)
            strncpy(hdrres.szStatusCode,app_server::RES_NO_IMAGE_SIZE,sizeof(hdrres.szStatusCode));
        
        if (hdrreq.iOCRTemplateSize==0)
            strncpy(hdrres.szStatusCode,app_server::RES_NO_TEMPLATE_SIZE,sizeof(hdrres.szStatusCode));
        
        if (hdrreq.iProcessID==0)
            strncpy(hdrres.szStatusCode,app_server::RES_NO_PID,sizeof(hdrres.szStatusCode));
        
        
        // debug
        if (strcmp(hdrres.szStatusCode,RES_OK)==0) {
            
            std::cout << "Template Name : " << hdrreq.szTemplateName << " Image Name : " << hdrreq.szImageName << '\n';

            // begin OCR process
            
            // <editor-fold desc="Transfer Files" defaultstate="collapsed">
            std::string szTempFolder = app_settings::Instance()->getSetting(app_settings::TEMP_LOCATION);
            szTempFolder.append("/PID");
            szTempFolder.append(std::to_string(hdrreq.iProcessID));
            mkdir(szTempFolder.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            chdir(szTempFolder.c_str());
            
            FILE *pFile = fopen(hdrreq.szTemplateName,"w");
            
            unsigned long iTempReadSize = hdrreq.iOCRTemplateSize;
            
            char buffer[256];
            int bytes_read;
            int amount_to_read;
            
            while (iTempReadSize != 0) {
                amount_to_read = iTempReadSize < sizeof(buffer) ? iTempReadSize : sizeof(buffer);
                bytes_read = read(connfd,buffer,amount_to_read); 
                iTempReadSize -= amount_to_read;
                if (bytes_read<=0) {
                    strncpy(hdrres.szStatusCode,app_server::RES_GEN_ERROR,sizeof(hdrres.szStatusCode));
                    break;
                }
                
                fwrite(buffer,sizeof(char),amount_to_read,pFile);
                
            }
            
            
            fclose(pFile);
            
            pFile = fopen(hdrreq.szImageName,"w");
            iTempReadSize = hdrreq.iOCRImageSize;
            
            while (iTempReadSize != 0) {
                amount_to_read = iTempReadSize < sizeof(buffer) ? iTempReadSize : sizeof(buffer);
                bytes_read = read(connfd,buffer,amount_to_read); 
                iTempReadSize -= amount_to_read;
                if (bytes_read<=0) {
                    strncpy(hdrres.szStatusCode,app_server::RES_GEN_ERROR,sizeof(hdrres.szStatusCode));
                    break;
                }
                
                fwrite(buffer,sizeof(char),amount_to_read,pFile);
                
            }
            fclose(pFile);
            // </editor-fold>
        
            OCR_Parser    *ocr = new OCR_Parser();
            
            try {
                ocr->loadImage(hdrreq.szImageName);
                ocr->load_config(hdrreq.szTemplateName);
                ocr->process_ocr();
                responseString = ocr->getResponse();
                hdrres.iDataSize = strlen(responseString.c_str());
            } catch (int e) {
                std::cout << "Exception number : " << e << '\n';
                responseString = "<error>";
                responseString.append(std::to_string(e));
                responseString.append("</error>");
                hdrres.iDataSize = strlen(responseString.c_str());
                
            }
            
            write(connfd,&hdrres,sizeof(ResponseHeader));
            write(connfd,responseString.c_str(), hdrres.iDataSize);
            
            delete ocr;
        }
        
        
    } 
    
    // <editor-fold desc="Unknown command error" defaultstate="collapsed">
    // unknown command
    else {
        strncpy(hdrres.szStatusCode,RES_UNKNOWN_COMMAND,sizeof(hdrres.szStatusCode));
        write(connfd,&hdrres,sizeof(ResponseHeader));
    }
    // </editor-fold>
 
    close(connfd);    
}