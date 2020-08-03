#include <iostream>
#include <fstream>
#include <cstdint>

//2,4,2,2,4
struct BMPFileReader
{
    char id[2];
    uint32_t size;
    uint16_t res1;
    uint16_t res2;
    uint32_t offset;
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
                    << "\nHeight: " << bmpfh.height << "\n";
   }
    else
    {
        std::cerr << "Invalid BMPimages/invalid.bmp\n";
    }
    
    


    
    
}