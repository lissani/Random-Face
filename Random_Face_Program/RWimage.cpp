#include <iostream>
#include <vector>
#include "RWimage.h"
#include <png.h>

// 1. 배열과 png 파일을 인자로 받아 png 파일을 배열에 저장하는 함수
void readPNG(const char* filename, std::vector<unsigned char>& image, int& width, int& height) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        std::cerr << "Error: " << filename << " is not a valid PNG file" << std::endl;
        fclose(fp);
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cerr << "Error: png_create_read_struct failed" << std::endl;
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Error: png_create_info_struct failed" << std::endl;
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);

    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    image.resize(width * height * 4);
    std::vector<png_bytep> row_pointers(height);
    for (int y = 0; y < height; ++y)
        row_pointers[y] = &image[y * width * 4];

    png_read_image(png, row_pointers.data());
    fclose(fp);

    png_destroy_read_struct(&png, &info, nullptr);
}

// 2. 배열과 png 파일을 인자로 받아 배열에 저장된 이미지를 png 파일로 저장하는 함수
void writePNG(const char* filename, const std::vector<unsigned char>& image, int width, int height) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cerr << "Error: png_create_write_struct failed" << std::endl;
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Error: png_create_info_struct failed" << std::endl;
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);

    png_set_IHDR(
        png, info, width, height,
        8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    std::vector<png_bytep> row_pointers(height);
    for (int y = 0; y < height; ++y)
        row_pointers[y] = const_cast<png_byte*>(&image[y * width * 4]);

    png_write_image(png, row_pointers.data());
    png_write_end(png, nullptr);

    fclose(fp);

    png_destroy_write_struct(&png, &info);
}

// 3. 이미지가 저장된 배열 두 개를 받아, 배경이 되는 이미지 위로 나머지 배열의 이미지가 그려지도록 한 후 저장
void overlayImages(std::vector<unsigned char>& background, const std::vector<unsigned char>& overlay, int width, int height) {
    for (int i = 0; i < width * height; ++i) {
        // Check if the overlay pixel is not fully transparent (alpha > 0)
        if (overlay[i * 4 + 3] > 0) {
            // Copy the RGB values from the overlay to the background
            for (int j = 0; j < 3; ++j)
                background[i * 4 + j] = overlay[i * 4 + j];
            // Copy the alpha value from the overlay to the background
            background[i * 4 + 3] = overlay[i * 4 + 3];
        }
    }
}

// int main() {
//     // Example Usage
//     const char* backgroundFile = "./ingredients/mirror.png";
//     const char* overlayFile = "./ingredients/male/egg/ldg.png";
//     const char* outputFile = "output12345.png";

//     std::vector<unsigned char> background, overlay;
//     int backgroundWidth, backgroundHeight, overlayWidth, overlayHeight;

//     // 1. Read the background image
//     readPNG(backgroundFile, background, backgroundWidth, backgroundHeight);

//     // 2. Read the overlay image
//     readPNG(overlayFile, overlay, overlayWidth, overlayHeight);

//     // 3. Overlay the images
//     overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));

//     // 4. Write the result to an output file
//     writePNG(outputFile, background, backgroundWidth, backgroundHeight);

//     return 0;
// }