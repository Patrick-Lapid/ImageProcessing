#include <iostream>
#include <fstream>
#include "tgaImage.h"

using namespace std;

tgaImage* getImage(string fileName);
void test(); // tests output file to example file
void multiply(tgaImage* top, tgaImage* bottom); // multiplies two images together
void subtract(tgaImage* top, tgaImage* bottom); // subtracts two images together
void screen(tgaImage* top, tgaImage* bottom); // screens two images together
void overlay(tgaImage* top, tgaImage* bottom); // overlays two images together
void writeImage(tgaImage* image, string fileName); // writes image to output file

int main() {
    // Using multiply blending mode to combine "layer1.tga" with "pattern1.tga"
    tgaImage* layer1 = getImage("input/layer1.tga");
    tgaImage* pattern1 = getImage("input/pattern1.tga");
    multiply(layer1, pattern1);
    writeImage(layer1, "output/part1.tga");
    delete layer1;
    delete pattern1;
    // Using subtract blending mode to combine "layer2.tga" with "car.tga"
    tgaImage* layer2 = getImage("input/layer2.tga");
    tgaImage* car = getImage("input/car.tga");
    subtract(layer2, car);
    writeImage(layer2, "output/part2.tga");
    // Using Multiply blending mode on "layer1.tga" and with "pattern2.tga" and using
    // the screen blending mode on the result + "text.tga"
    delete layer2;
    delete car;
    layer1 = getImage("input/layer1.tga");
    tgaImage* pattern2 = getImage("input/pattern2.tga");
    tgaImage* text = getImage("input/text.tga");
    multiply(layer1, pattern2);
    screen(text, layer1);
    writeImage(text, "output/part3.tga");
    delete pattern2;
    delete text;
    delete layer1;
    // Using Multiply blending mode on "layer2.tga" with "circles.tga" and using
    // the subtract blending mode on the result + "pattern2.tga"
    layer2 = getImage("input/layer2.tga");
    tgaImage* circles = getImage("input/circles.tga");
    pattern2 = getImage("input/pattern2.tga");
    multiply(layer2, circles);
    subtract(pattern2, layer2);
    writeImage(pattern2, "output/part4.tga");
    delete layer2;
    delete circles;
    delete pattern2;
    // Using the Overlay blending mode on "layer1.tga" and "pattern1.tga"
    layer1 = getImage("input/layer1.tga");
    pattern1 = getImage("input/pattern1.tga");
    overlay(pattern1, layer1);
    writeImage(pattern1, "output/part5.tga");
    delete layer1;
    delete pattern1;
    // Adding 200 to the green channel of "car.tga"
    car = getImage("input/car.tga");
    int temp = 0;
    for(int i = 1; i < (car->dim + 1); i+=3){
        temp = (int)car->imgData[i] + 200;
        if(temp > 255)
            temp = 255;
        car->imgData[i] = (unsigned char) temp;
    }
    writeImage(car, "output/part6.tga");
    delete car;
    // Multiplying the red channel by 4 and blue channel by 0 of "car.tga"
    car = getImage("input/car.tga");
    // multiplies red channel by 4 and blue channel by 0
    for(int i = 2; i < (car->dim + 1); i+=3){
        temp = (int)car->imgData[i] * 4;
        if(temp > 255)
            temp = 255;
        car->imgData[i] = (unsigned char) temp;
        car->imgData[i-2] = 0;
    }
    writeImage(car, "output/part7.tga");
    delete car;
    // 
    car = getImage("input/car.tga");
    tgaImage* r = new tgaImage(car);
    tgaImage* g = new tgaImage(car);
    tgaImage* b = new tgaImage(car);
    // Loads each channel into their own files of "car.tga"
    for(int i = 0; i < (car->dim + 1); i+=3){
        r->imgData[i] = car->imgData[i+2];
        r->imgData[i+1] = car->imgData[i+2];
        r->imgData[i+2] = car->imgData[i+2];
        g->imgData[i] = car->imgData[i+1];
        g->imgData[i+1] = car->imgData[i+1];
        g->imgData[i+2] = car->imgData[i+1];
        b->imgData[i] = car->imgData[i];
        b->imgData[i+1] = car->imgData[i];
        b->imgData[i+2] = car->imgData[i];
    }
    writeImage(r, "output/part8_r.tga");
    writeImage(g, "output/part8_g.tga");
    writeImage(b, "output/part8_b.tga");
    delete r;
    delete g;
    delete b;
    delete car;
    // Loading three files and combining each channel into one file "part9.tga"
    tgaImage* layer_red = getImage("input/layer_red.tga");
    tgaImage* layer_green = getImage("input/layer_green.tga");
    tgaImage* layer_blue = getImage("input/layer_blue.tga");
    tgaImage* combined = new tgaImage(layer_red);
    // combines three files into one
    for(int i = 0; i < (layer_red->dim + 1); i+=3){
        combined->imgData[i] = layer_blue->imgData[i];
        combined->imgData[i+1] = layer_green->imgData[i];
        combined->imgData[i+2] = layer_red->imgData[i];
    }
    writeImage(combined, "output/part9.tga");
    delete layer_red;
    delete layer_green;
    delete layer_blue;
    delete combined;
    // Rotates "text2.tga" 180 degrees (flipping it upside down)
    tgaImage* text2 = getImage("input/text2.tga");
    tgaImage* flipped = new tgaImage(text2);
    // Flips image 180 degrees
    for(int x = 0; x < text2->dim; x+=3){
        flipped->imgData[x] = text2->imgData[text2->dim - x - 3];
        flipped->imgData[x+1] = text2->imgData[text2->dim - x - 2];
        flipped->imgData[x+2] = text2->imgData[text2->dim - x - 1];
    }
    writeImage(flipped, "output/part10.tga");
    delete text2;
    delete flipped;
    // Extra Credit
    car = getImage("input/car.tga");
    circles = getImage("input/circles.tga");
    pattern1 = getImage("input/pattern1.tga");
    text = getImage("input/text.tga");
    // Creates left and right columns into their own images
    tgaImage* left = new tgaImage(car);
    tgaImage* right = new tgaImage(pattern1);
    left->header.height *= 2;
    right->header.height *= 2;
    left->setDim();
    right->setDim();
    for(int x = 0; x < text->dim; x++){
        left->imgData[x] = text->imgData[x];
    }
    int iter = 0;
    for(int x = text->dim; x < left->dim; x++){
        left->imgData[x] = car->imgData[iter];
        iter++;
    }
    for(int x = 0; x < pattern1->dim; x++){
        right->imgData[x] = pattern1->imgData[x];
    }
    iter = 0;
    for(int x = pattern1->dim; x < right->dim; x++){
        right->imgData[x] = circles->imgData[iter];
        iter++;
    }
    tgaImage* extra = new tgaImage(right);
    extra->header.width *= 2;
    extra->setDim();
    iter = 0;
    // Combines left and right images into one large image
    for(int x = 0; x < extra->dim; x += (left->header.width * 6)){
        for(int y =0; y < left->header.width*3; y++){
            extra->imgData[x+y] = left->imgData[y+iter];
        }
        for(int y =0; y < right->header.width*3; y++){
            extra->imgData[x+y + left->header.width*3] = right->imgData[y+iter];
        }
        iter += (left->header.width*3);
    }
    writeImage(extra, "output/extra.tga");
    delete car;
    delete circles;
    delete pattern1;
    delete text;
    delete left;
    delete right;
    delete extra;
    test();
    return 0;
}
// Reads in image given file name and image ptr
tgaImage* getImage(string fileName){
    tgaImage *image = new tgaImage();
    ifstream inStream(fileName, ios::binary);
    inStream.read(&image->header.idLength, sizeof(image->header.idLength));
    inStream.read(&image->header.colorMapType, sizeof(image->header.colorMapType));
    inStream.read(&image->header.dataTypeCode, sizeof(image->header.dataTypeCode));
    inStream.read((char *)&image->header.colorMapOrigin, sizeof(image->header.colorMapOrigin));
    inStream.read((char *)&image->header.colorMapLength, sizeof(image->header.colorMapLength));
    inStream.read(&image->header.colorMapDepth, sizeof(image->header.colorMapDepth));
    inStream.read((char *) &image->header.xOrigin, sizeof(image->header.xOrigin));
    inStream.read((char *)&image->header.yOrigin, sizeof(image->header.yOrigin));
    inStream.read((char *) &image->header.width, sizeof(image->header.width));
    inStream.read((char *)&image->header.height, sizeof(image->header.height));
    inStream.read(&image->header.bitsPerPixel, sizeof(image->header.bitsPerPixel));
    inStream.read(&image->header.imageDescriptor, sizeof(image->header.imageDescriptor));
    image->setDim();
    inStream.read((char *)image->imgData, image->dim);
    inStream.close();
    return image;
}
// Writes out image given file name and image ptr
void writeImage(tgaImage* image, string fileName){
    ofstream outStream(fileName, ios::binary);
    outStream.write((char *) &image->header.idLength, sizeof(image->header.idLength));
    outStream.write(&image->header.colorMapType, sizeof(image->header.colorMapType));
    outStream.write(&image->header.dataTypeCode, sizeof(image->header.dataTypeCode));
    outStream.write((char *)&image->header.colorMapOrigin, sizeof(image->header.colorMapOrigin));
    outStream.write((char *)&image->header.colorMapLength, sizeof(image->header.colorMapLength));
    outStream.write(&image->header.colorMapDepth, sizeof(image->header.colorMapDepth));
    outStream.write((char *) &image->header.xOrigin, sizeof(image->header.xOrigin));
    outStream.write((char *)&image->header.yOrigin, sizeof(image->header.yOrigin));
    outStream.write((char *) &image->header.width, sizeof(image->header.width));
    outStream.write((char *)&image->header.height, sizeof(image->header.height));
    outStream.write(&image->header.bitsPerPixel, sizeof(image->header.bitsPerPixel));
    outStream.write(&image->header.imageDescriptor, sizeof(image->header.imageDescriptor));
    outStream.write((char *)image->imgData, image->dim);
}

void multiply(tgaImage* top, tgaImage* bottom){
    float temp = 0;
    for(int i = 0; i < top->dim; i++){
        temp = (((float)top->imgData[i] / 255) * ((float)bottom->imgData[i] / 255) * 255.0) + 0.5;
        top->imgData[i] = (unsigned char)temp;
    }
}

void subtract(tgaImage* top, tgaImage* bottom){
    int temp = 0;
    for(int i = 0; i < top->dim; i++){
        temp = ((int)bottom->imgData[i] - (int)top->imgData[i]);
	// clamps to max value
        if(temp > 255)
            temp = 255;
        else if(temp < 0)
            temp = 0;
        top->imgData[i] = (unsigned char)temp;
    }
}

void screen(tgaImage* top, tgaImage* bottom){
    float temp = 0;
    for(int i = 0; i < top->dim; i++){
        temp = ((1 - (1 - ((float)top->imgData[i] / 255)) * (1 - ((float)bottom->imgData[i] / 255))) * 255.0) + 0.5;
        top->imgData[i] = (unsigned char)temp;
    }
}

void overlay(tgaImage* top, tgaImage* bottom){
    float temp = 0;
    for(int i = 0; i < top->dim; i++){
        if(((float)top->imgData[i] / 255) > 0.5){
            temp = ((1 - 2*(1 - ((float)top->imgData[i] / 255)) * (1 - ((float)bottom->imgData[i] / 255))) * 255.0) + 0.5;
            top->imgData[i] = (unsigned char)temp;
        }else{
            temp = (2 * ((float)top->imgData[i] / 255) * ((float)bottom->imgData[i] / 255) * 255.0) + 0.5;
            top->imgData[i] = (unsigned char)temp;
        }
    }
}

int testFiles(tgaImage* part, tgaImage* example){
    bool same = true;
    for(int x = 0; x < part->dim; x++){
        if(example->imgData[x] != part->imgData[x])
            same = false;
    }
    if(same){
        cout << "Passed!\n";
        return 1;
    }
    else{
        cout << "Failed!\n";
        return 0;
    }
}

void test(){
    tgaImage* part1 = getImage("output/part1.tga");
    tgaImage* part2 = getImage("output/part2.tga");
    tgaImage* part3 = getImage("output/part3.tga");
    tgaImage* part4 = getImage("output/part4.tga");
    tgaImage* part5 = getImage("output/part5.tga");
    tgaImage* part6 = getImage("output/part6.tga");
    tgaImage* part7 = getImage("output/part7.tga");
    tgaImage* part8_r = getImage("output/part8_r.tga");
    tgaImage* part8_g = getImage("output/part8_g.tga");
    tgaImage* part8_b = getImage("output/part8_b.tga");
    tgaImage* part9 = getImage("output/part9.tga");
    tgaImage* part10 = getImage("output/part10.tga");
    tgaImage* extracredit = getImage("output/extra.tga");

    tgaImage* expart1 = getImage("examples/EXAMPLE_part1.tga");
    tgaImage* expart2 = getImage("examples/EXAMPLE_part2.tga");
    tgaImage* expart3 = getImage("examples/EXAMPLE_part3.tga");
    tgaImage* expart4 = getImage("examples/EXAMPLE_part4.tga");
    tgaImage* expart5 = getImage("examples/EXAMPLE_part5.tga");
    tgaImage* expart6 = getImage("examples/EXAMPLE_part6.tga");
    tgaImage* expart7 = getImage("examples/EXAMPLE_part7.tga");
    tgaImage* expart8_r = getImage("examples/EXAMPLE_part8_r.tga");
    tgaImage* expart8_g = getImage("examples/EXAMPLE_part8_g.tga");
    tgaImage* expart8_b = getImage("examples/EXAMPLE_part8_b.tga");
    tgaImage* expart9 = getImage("examples/EXAMPLE_part9.tga");
    tgaImage* expart10 = getImage("examples/EXAMPLE_part10.tga");
    tgaImage* EXextracredit = getImage("examples/EXAMPLE_extracredit.tga");

    int count = 0;
    // adds up passed tests 
    cout << "Test #1...... ";
    count += testFiles(part1, expart1);
    cout << "Test #2...... ";
    count += testFiles(part2, expart2);
    cout << "Test #3...... ";
    count += testFiles(part3, expart3);
    cout << "Test #4...... ";
    count += testFiles(part4, expart4);
    cout << "Test #5...... ";
    count += testFiles(part5, expart5);
    cout << "Test #6...... ";
    count += testFiles(part6, expart6);
    cout << "Test #7...... ";
    count += testFiles(part7, expart7);
    cout << "Test #8a...... ";
    count += testFiles(part8_r, expart8_r);
    cout << "Test #8b...... ";
    count += testFiles(part8_g, expart8_g);
    cout << "Test #8c...... ";
    count += testFiles(part8_b, expart8_b);
    cout << "Test #9...... ";
    count += testFiles(part9, expart9);
    cout << "Test #10...... ";
    count += testFiles(part10, expart10);
    cout << "Test #11...... ";
    count += testFiles(extracredit, EXextracredit);
    cout << count << "/13 Tests passed\n";
    // memory deallocation
    delete part1;
    delete part2;
    delete part3;
    delete part4;
    delete part5;
    delete part6;
    delete part7;
    delete part8_r;
    delete part8_g;
    delete part8_b;
    delete part9;
    delete part10;
    delete expart1;
    delete expart2;
    delete expart3;
    delete expart4;
    delete expart5;
    delete expart6;
    delete expart7;
    delete expart8_r;
    delete expart8_g;
    delete expart8_b;
    delete expart9;
    delete expart10;
    delete extracredit;
    delete EXextracredit;
}

