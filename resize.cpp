// Project UID af1f95f547e44c8ea88730dfb185559d
// p2-cv.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include "processing.h"
using namespace std;

void print_error()
{
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;

}

int main( int argc, char *argv[])
{
    if (argc < 4 || argc > 5)
    {
        print_error();
        return 1;
    }
    if (stoi(argv[3]) <= 0 )
    {
        print_error();
        return 1;
    }
    if (argc > 4 && stoi(argv[4]) <= 0)
    {
        print_error();
        return 1;
    }
    ifstream fin(argv[1]);
    if (!fin)
    {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    Image* img = new Image;
    Image_init(img, fin);

    if (stoi(argv[3]) > Image_width(img))
    {
        print_error();
        delete img;
        return 1;
    }
    if (argc > 4 && stoi(argv[4]) > Image_height(img))
    {
        print_error();
        delete img;
        return 1;
    }

    if (argc > 4)
    {
        seam_carve(img, stoi(argv[3]), stoi(argv[4]));
    }
    else
    {
        seam_carve(img, stoi(argv[3]), Image_height(img));
    }
    ofstream fout(argv[2]);
    if (!fout)
    {
        cout << "Error opening file: " << argv[2] << endl;
        delete img;
        return 1;
    }
    Image_print(img, fout);
    delete img;
}

