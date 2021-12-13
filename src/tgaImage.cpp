//
// Created by Patrick on 11/6/2021.
//
#include "tgaImage.h"
void tgaImage::setDim() {
    this->dim = header.width*header.height*3;
    this->imgData = new unsigned char[dim];
}

tgaImage::tgaImage(tgaImage* image){
    this->header.idLength = image->header.idLength;
    this->header.colorMapType = image->header.colorMapType;
    this->header.dataTypeCode = image->header.dataTypeCode;
    this->header.colorMapOrigin = image->header.colorMapOrigin;
    this->header.colorMapLength = image->header.colorMapLength;
    this->header.colorMapDepth = image->header.colorMapDepth;
    this->header.xOrigin = image->header.xOrigin;
    this->header.yOrigin = image->header.yOrigin;
    this->header.width = image->header.width;
    this->header.height = image->header.height;
    this->header.bitsPerPixel = image->header.bitsPerPixel;
    this->header.imageDescriptor = image->header.imageDescriptor;
    this->setDim();
    for(int x = 0; x < this->dim; x++){
        imgData[x] = 0;
    }
}