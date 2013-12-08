#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include <FreeImage.h>

class ImageLoader {
public:
    ImageLoader() {

    }

    void loadImage(const char *filename, GLuint *texture) {
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
            glTexImage2D(GL_TEXTURE, 0, GL_BGR, w, h, 0, GL_BGR, GL_TEXTURE_2D, pixels);
            glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        }
    }

};

#endif
