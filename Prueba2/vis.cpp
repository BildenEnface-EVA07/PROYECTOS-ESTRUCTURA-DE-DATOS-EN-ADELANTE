#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ios>


//2,4,2,2,4
struct BMPFileReader
{
    char id[2];
    uint32_t size;
    uint16_t res1;
    uint16_t res2;
    uint32_t offset;
    //fileinfoheader tamaño = 24 bytes
    uint32_t sizeh;
    uint32_t widht;
    uint32_t height;
    uint16_t planes;
    uint16_t cpp;
    uint32_t compress_method;
    uint32_t size2;
    uint32_t resolx;
    uint32_t resoly;
    uint32_t Numberofcolors;
    uint32_t bmp_imp_colors;
    uint32_t extra[17];
}__attribute__((packed));

struct BMPFileHeader
{
    char id[2];
    uint32_t size;
    uint16_t res1;
    uint16_t res2;
    uint32_t offset;
}__attribute__((packed));

struct BMPFileInfoHearder
{
    //fileinfoheader tamaño = 24 bytes
    uint32_t sizeh;
    uint32_t widht;
    uint32_t height;
    uint16_t planes;
    uint16_t cpp;
    uint32_t compress_method;
    uint32_t size2;
}__attribute__((packed));

int main(int argc,char *argv[])
{
    //std::cout << sizeof(BMPFileReader);
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "<input file\n>";
        return 1;
    }

    std::ifstream in(argv[1]);

    if (!in.is_open())
    {
        std::cerr << "Error al cargar el BMP" << argv[1] << "\n";
        return 2;
    }
    
    

    BMPFileReader bmpfh;
    in.read(reinterpret_cast<char*>(&bmpfh),sizeof(BMPFileReader));
    if (in.gcount() != sizeof(BMPFileReader))
    {
        std::cerr << "Invalid BMP\n";
        return 2;
    }
    if (bmpfh.id[0] == 0x42 && bmpfh.id[1] == 0x4d)
    {
        std::cout << "Valid BMP\n";
        std::cout << "Size: " << bmpfh.size << "\n"
                    << "Offset: " <<bmpfh.offset <<"\n"
                    <<"Size: " << bmpfh.sizeh << "\nWidth: " << bmpfh.widht
                    << "\nHeight: " << bmpfh.height << "\nPaleta de colores: "
                    << bmpfh.planes << "\nColors per Pixel: " << bmpfh.cpp << "\n";
   }

   if (bmpfh.Numberofcolors > 0)
   {
       int i = 0;
       std:: cerr << "Not suported\n";
       unsigned pofs = sizeof(BMPFileHeader) + bmpfh.sizeh;
       in.seekg(pofs);
       std::vector<uint32_t> palete(bmpfh.Numberofcolors); 
       in.read(reinterpret_cast<char*>(palete.data()),palete.size()*sizeof(uint32_t));
       if (in.gcount() != palete.size()*sizeof(uint32_t))
    {
        std::cerr << "Invalid BMP\n";
        return 2;
    }
       /*for(auto c : palete)
       {
           std::cout << i++ <<" : "<< std::hex << c << "\n";
           
       }*/
   }
   

   size_t rowsize = ((bmpfh.cpp * bmpfh.widht + 31) / 32) * 4;
   std::vector<std::vector<uint8_t>> imagerow(bmpfh.height);

    //posicionamiento
    in.seekg(bmpfh.offset);
    /*char pixel[3];
    in.read(pixel, sizeof(pixel));
    if (in.gcount() != sizeof(pixel))
    {
        std::cerr << "Invalid BMP\n";
        return 2;
    }
    
    std::cout << std::hex
          << static_cast<int>(pixel[0]) << " "
          << static_cast<int>(pixel[1]) << " "
          << static_cast<int>(pixel[2]) << " "
          << static_cast<int>(pixel[3]) << " "
          << static_cast<int>(pixel[4]) << " "
          << static_cast<int>(pixel[5]) << "\n ";*/

    for (int i = 0; i < bmpfh.height; i++)
    {
        imagerow[i].resize(rowsize);
        in.read(reinterpret_cast<char*>(imagerow[i].data()),rowsize);

        if (in.gcount() != rowsize)
        {
            std::cerr << "Error reading BMP Pixel data\n";
            return 2;
        }
        
    }
    in.close();
    bmpfh.size = bmpfh.sizeh + bmpfh.size2;
    bmpfh.planes = 0;
    bmpfh.cpp = 24;

    std::ofstream out;
    out.open("new.bmp",std::ios::out | std::ios::app |std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "Error al crear el BMP\n";
        return 2;
    }
    
    out.write(reinterpret_cast<char*>(&bmpfh),sizeof(BMPFileReader));
    out.close();

    return 0;
}