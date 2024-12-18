#include "Bitmap.h"

Bitmap* Bitmap::fromBuffer(uint8_t* buffer) {
  //   BMPImage* image = reinterpret_cast<BMPImage*>(buffer);
  BMPHeader* header = reinterpret_cast<BMPHeader*>(buffer);
  BMPInfoHeader* infoHeader = reinterpret_cast<BMPInfoHeader*>(buffer + sizeof(BMPHeader));

  BMPImage* image = new BMPImage();
  image->header = *header;
  image->infoHeader = *infoHeader;

  Bitmap* bitmap = new Bitmap();
  bitmap->image = image;

  return NULL;
}

uint8_t* Bitmap::bytes() {
  return this->image->data;
}

std::ostream& operator<<(std::ostream& os, const Bitmap& bitmap) {
  if (bitmap.image == NULL) {
    os << "No BMP image loaded." << std::endl;
    return os;
  }

  os << "BMP Info Header:" << std::endl;
  os << "Size: " << bitmap.image->infoHeader.size << std::endl;
  os << "Width: " << bitmap.image->infoHeader.width << std::endl;
  os << "Height: " << bitmap.image->infoHeader.height << std::endl;
  os << "Planes: " << bitmap.image->infoHeader.planes << std::endl;
  os << "Bit Count: " << bitmap.image->infoHeader.bitCount << std::endl;
  os << "Compression: " << bitmap.image->infoHeader.compression << std::endl;
  os << "Size Image: " << bitmap.image->infoHeader.sizeImage << std::endl;
  os << "X Pixels Per Meter: " << bitmap.image->infoHeader.xPixelsPerMeter << std::endl;
  os << "Y Pixels Per Meter: " << bitmap.image->infoHeader.yPixelsPerMeter << std::endl;
  os << "Colors Used: " << bitmap.image->infoHeader.colorsUsed << std::endl;
  os << "Colors Important: " << bitmap.image->infoHeader.colorsImportant << std::endl;

  return os;
}