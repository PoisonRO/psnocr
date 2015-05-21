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

#include "ocr_parser.h"

using namespace std;
using namespace Magick;
/*
 * 
 */

//http://www.imagemagick.org/Magick++/Image.html
int main(int argc, char** argv) 
{
    
    
    Magick::InitializeMagick(*argv);
    
    /*Magick::Image main_img("/home/dan/Desktop/magick_images/Untitled.png");
    
    main_img.crop(Geometry(100,100,0,0));
    
    
    main_img.write("/home/dan/Desktop/magick_images/Untitled_smen.png");*/
    
    OCR_Parser    *settings;
    
    settings = new OCR_Parser();
    
    settings->load_config("/home/dan/Desktop/magick_images/f.xml");
    settings->loadImage("/home/dan/Desktop/magick_images/Untitled.png");
    settings->process_ocr();
    
    delete settings;
    
    return 0;
}

