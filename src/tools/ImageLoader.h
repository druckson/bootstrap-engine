#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include <fstream>
#include "glmisc.h"
#include <FreeImage.h>
#include "../assets/images/crossnrm.c"
using namespace std;

class ImageLoader {
public:
    ImageLoader() {

    }

    void loadImage(const char *filename, GLuint *texture) {
        ifstream img(filename);
        if (!img) {
            cout << "Texture file doesn't exist" << endl;
            exit(1);
        }

        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
        FIBITMAP *fileData;
        int w, h;
        char *pixels;
        if (format != FIF_UNKNOWN) {
            fileData = FreeImage_Load(format, filename, 0);
            w = FreeImage_GetWidth(fileData);
            h = FreeImage_GetHeight(fileData);
            pixels = (char *)FreeImage_GetBits(fileData);

            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR, GL_UNSIGNED_BYTE, pixels);
        } else {
            cerr << "Failed to load texture" << endl;
            exit(1);
        }
    }

};

#endif
