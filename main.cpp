/* 
 * File:   main.cpp
 * Author: dan
 *
 * Created on May 19, 2015, 4:10 PM
 * dependinte : LibMagic++
 *              LibXml++
 */


#include <cstdlib>
#include <Magick++.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <iostream>
#include "app_server.h"
#include "app_client.h"


/*
 * 
 */

//http://www.imagemagick.org/Magick++/Image.html

void start_daemon() {
    pid_t pid,sid;
    
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    /* If we got a good PID, then
        we can exit the parent process. */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Change the file mode mask */
    umask(0);
                
    /* Open any logs here */        
                
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);
        
    /* Change the current working directory */
    if ((chdir("/")) < 0)
        exit(EXIT_FAILURE);
        
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
        
    /* Daemon-specific initialization goes here */
        
    /* The Big Loop */
    while (1) {
    /* Do some task here ... */
           
    sleep(30); /* wait 30 seconds */
    }
}

int main(int argc, char** argv) 
{
    
    /*
    
    OCR_Parser    *settings;
    
    settings = new OCR_Parser();
    
    settings->load_config("/home/dan/Desktop/magick_images/f.xml");
    settings->loadImage("/home/dan/Desktop/magick_images/Untitled.png");
    settings->process_ocr();
    
    delete settings;*/
    
    Magick::InitializeMagick(*argv);
    
    if (argc == 1) {
        std::cout << "Program requires one argument.\n";
        exit(EXIT_SUCCESS);
    }
    
    if (argc > 2) {
        std::cout << "Only the first argument will be used.\n";
    }
    
    //std::string argument = "LISTS";
    
    std::string argument(argv[1]);
    
    app_client *appc;
    
    if (argument == "START") {
        app_server *app = new app_server();
    
        app->run();
    
        delete app;
    }  else 
    if (argument == "STOP") {
        appc = new app_client();
        appc->sendStopCommand();
        delete appc;
    }  else 
    if (argument == "LISTS") {
        appc = new app_client();
        appc->sendListCommand();
        delete appc;
    }  else 
        std::cout << "Invalid argument.\n";
    
    
   
    
    exit(EXIT_SUCCESS);
}

