//
// Created by Patrick on 11/6/2021.
//

#ifndef PROJECT3_TGAIMAGE_H
#define PROJECT3_TGAIMAGE_H


class tgaImage {
public:
    struct Header{
        char  idLength;
        char  colorMapType;
        char  dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char  colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char  bitsPerPixel;
        char  imageDescriptor;
    };
    Header header;
    tgaImage(){};
    tgaImage(tgaImage* image);
    ~tgaImage(){delete [] imgData;};
    unsigned char *imgData = nullptr;
    int dim = 0;
    void setDim();

};

#endif //PROJECT3_TGAIMAGE_H
