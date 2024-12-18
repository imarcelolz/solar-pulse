#include "Bitmap.h"

#include <gtest/gtest.h>

#include <fstream>

std::vector<uint8_t> readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file");
  }
  return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

TEST(BitmapTest, FromBuffer) {
  std::vector<uint8_t> buffer = readFile("path/to/your/image.bmp");
  Bitmap* bitmap = Bitmap::fromBuffer(buffer.data());
  ASSERT_NE(bitmap, nullptr);
  ASSERT_NE(bitmap->bytes(), nullptr);

  EXPECT_EQ(bitmap->image->header.fileType, 0x4D42);
  EXPECT_GT(bitmap->image->infoHeader.width, 0);
  EXPECT_GT(bitmap->image->infoHeader.height, 0);
  EXPECT_GT(bitmap->image->infoHeader.bitCount, 0);

  delete bitmap;
}

TEST(BitmapTest, PrintInfoHeader) {
  std::vector<uint8_t> buffer = readFile("path/to/your/image.bmp");
  Bitmap* bitmap = Bitmap::fromBuffer(buffer.data());
  ASSERT_NE(bitmap, nullptr);

  std::ostringstream oss;
  oss << *bitmap;
  std::string output = oss.str();

  EXPECT_NE(output.find("Width: "), std::string::npos);
  EXPECT_NE(output.find("Height: "), std::string::npos);
  EXPECT_NE(output.find("Bit Count: "), std::string::npos);

  delete bitmap;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}