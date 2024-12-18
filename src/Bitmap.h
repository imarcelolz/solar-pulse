#pragma once

#include <stdint.h>

#include <iostream>

struct BMPHeader {
  uint16_t fileType;
  uint32_t fileSize;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offsetData;
};

struct BMPInfoHeader {
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bitCount;
  uint32_t compression;
  uint32_t sizeImage;
  int32_t xPixelsPerMeter;
  int32_t yPixelsPerMeter;
  uint32_t colorsUsed;
  uint32_t colorsImportant;
};

struct BMPImage {
  BMPHeader header;
  BMPInfoHeader infoHeader;
  uint8_t* data;
};

class Bitmap {
  BMPImage* image;

 public:
  static Bitmap* fromBuffer(uint8_t* buffer);
  uint8_t* bytes();
  friend std::ostream& operator<<(std::ostream& os, const Bitmap& bitmap);
};
