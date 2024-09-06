#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

int main(void){
  //std::cout << "hello world\n";
  std::fstream pic;
  pic.open("./imageFiles/tree.bmp", std::fstream::binary | std::fstream::in);
  if (!pic){
    return 1;
  }
  // get length of file:
  pic.seekg(0, pic.end);
  int length = pic.tellg();
  pic.seekg(0, pic.beg);
  char *buffer = new char[length];
  pic.read(buffer, length);
  for (int i = 0; i < 14; i++){
    char c = buffer[i];
    if(c < 32 || c > 126){
    int val = 0;
    val |= c;
    std::cout<< std::hex << "0x" << std::setw(2) << std::setfill('0') << val << " "<<std::dec;
    }else{
      std::cout<<buffer[i]<<' ';
    }
  }
  std::cout<<std::endl;

  size_t pixOffset = 0;
  for (int i = 0; i < 4; i++){
    pixOffset |= (buffer[10+i] << (8*i)); 
  }
  std::cout<< "pixel array offset: "<< pixOffset << std::endl;

  //get DIB header size
  int dibSize = 0;
  for (int i = 0; i < 4; i++){
    dibSize |= (buffer[14+i] << (8*i)); 
  }
  std::cout<< "dibSize: "<< dibSize << std::endl;
  //get pixel width and height and bit depth 
  int width = 0, height = 0, depth = 0;
  for (int i = 0; i < 4; i++){
    width |= (buffer[18+i] << (8*i)); 
  }
  for (int i = 0; i < 4; i++){
    height |= (buffer[22+i] << (8*i)); 
  }
  for (int i = 0; i < 2; i++){
    depth |= (buffer[28+i] << (8*i)); 
  }
  std::cout<< "width: "<< width <<std::endl;
  std::cout<< "height: "<< height <<std::endl;
  std::cout<< "depth: "<< depth <<std::endl;

  //get compression type
  int compressionType = 0;
  for (int i = 0; i < 4; i++){
    compressionType |= (buffer[30+i] << (8*i)); 
  }
  std::cout<< "comp: "<< compressionType <<std::endl;

  //resolutions
  unsigned int vertRes = 0, horRes = 0;
  for (int i = 0; i < 4; i++){
    horRes |= (buffer[38+i] << (8*i)); 
  }
  for (int i = 0; i < 4; i++){
    vertRes |= (buffer[42+i] << (8*i)); 
  }
  std::cout<< "horizontal resolution: "<< horRes <<std::endl;
  std::cout<< "vertical resolution: "<< vertRes <<std::endl;
  int numColorsInPalette = 0;
  for (int i = 0; i < 4; i++){
    numColorsInPalette |= (buffer[46+i] << (8*i)); 
  }
  std::cout<< "colors: "<< numColorsInPalette <<std::endl;
  int rowSize = std::ceil(((float)depth*width)/32)*4;
  std::cout << "rowSize: " << rowSize<< std::endl;
  unsigned int mapSize = 0;
  for (int i = 0; i < 4; i++){
    mapSize |= (buffer[34+i] << (8*i)); 
  }
  size_t pixelArrSize = rowSize * height;
  std::cout << "calculated pixel Array Size: " << pixelArrSize<< std::endl;
  std::cout << "stored pixel Array Size: " << mapSize<< std::endl;
  unsigned char* pixels = new unsigned char[pixelArrSize];

  //pixel SHIT
  
  return 0;
}