#ifndef RWIMAGE_H
#define RWIMAGE_H

#include <vector>

void readPNG(const char* filename, std::vector<unsigned char>& image, int& width, int& height);
void writePNG(const char* filename, const std::vector<unsigned char>& image, int width, int height);
void overlayImages(std::vector<unsigned char>& background, const std::vector<unsigned char>& overlay, int width, int height);

#endif
