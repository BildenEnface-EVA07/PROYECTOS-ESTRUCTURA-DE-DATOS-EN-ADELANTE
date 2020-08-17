#include <iostream>
#include <fstream>
#include <cstdint>
#include "inttypes.h"


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

struct PNGFile
{
    uint8_t id;
    char name[2];
    uint16_t res;
    uint8_t res2;
    uint8_t res3;
}__attribute__((packed));

struct JPEGFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
}__attribute__((packed));

struct GIFFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
    uint8_t id5;
    uint8_t id6;
    uint16_t with;
    uint16_t height;
}__attribute__((packed));

struct TIFFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
}__attribute__((packed));

struct SVGFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
}__attribute__((packed));


class imagenes
{
    public:
    imagenes(){}
    int EvaluationsBMP(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el BMP" << argv << "\n";
            return 3;
        }
        BMPFileReader bmp;
        in.read(reinterpret_cast<char*>(&bmp),sizeof(BMPFileReader));

        if (in.gcount() != sizeof(BMPFileReader))
            {
                std::cerr << "Invalid BMP\n";

            }
        if(bmp.id[0] == 0x42 && bmp.id[1] == 0x4d)
            {
                std::cout << "Este es un Archivo de Imagen BMP\n";
                std::cout << "Width: " << bmp.widht
                    << "\nHeight: " << bmp.height << "\n";
                    return 1;
            }
            else
            {
                return 2;
            }
            
    }


    int EvaluationsPNG(char* argv, int *x, int *y)
    {
        FILE *f=fopen(argv,"rb");
        fseek(f,0,SEEK_END);
        long len=ftell(f);
        fseek(f,0,SEEK_SET);
         if(len<24) 
         {
            fclose(f);
         }
        std::ifstream in(argv);
        unsigned char buf[24]; fread(buf,1,24,f);

        if (buf[0]==0xff && buf[1]==0xd8 && buf[2]==0xff)
        { 
            long pos=2;
            while (buf[2]==0xFF)
            { if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
            pos += 2+(buf[4]<<8)+buf[5];
            if (pos+12>len) break;
            fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);
            }
        }
        

        

        fclose(f);

        if (!in.is_open())
        {
            std::cerr << "Error al cargar el PNG" << argv << "\n";
        }

        PNGFile png;
        in.read(reinterpret_cast<char*>(&png),sizeof(PNGFile));
        if (in.gcount() != sizeof(PNGFile))
        {
            std::cout << "Hubo un error al cargar el archivo PNG\n";
        }
        if (png.name[0] == 0x50 && png.name[1] == 0x4e && png.name[2] == 0x47)
        {
            std::cout <<"Este es un Archivo de Imagen PNG\n";
            if ( buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
    && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
            { 
                *x = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
                *y = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
            }
            return 1;
        }
        else
        {
            return 2;
        }
        //png.name[0] == 0x50 && png.name[1] == 0x4d && png.name[2] == 0x47
    }

    int EvaluationsJPEG(char* argv, int *x, int *y)
    {
        FILE *f=fopen(argv,"rb");
        fseek(f,0,SEEK_END);
        long len=ftell(f);
        fseek(f,0,SEEK_SET);
         if(len<24) 
         {
            fclose(f);
         }
        std::ifstream in(argv);
        unsigned char buf[24]; fread(buf,1,24,f);

        if (buf[0]==0xff && buf[1]==0xd8 && buf[2]==0xff)
        { 
            long pos=2;
            while (buf[2]==0xFF)
            { if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
            pos += 2+(buf[4]<<8)+buf[5];
            if (pos+12>len) break;
            fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);
            }
        }
        

        fclose(f);


        if (!in.is_open())
        {
            std::cerr << "Error al cargar el JPG" << argv << "\n";
        }
        JPEGFile jpg;
        in.read(reinterpret_cast<char*>(&jpg),sizeof(JPEGFile));
        if (in.gcount() != sizeof(JPEGFile))
        {
            std::cout << "NO ES UN JPG File\n";
        }
        if (jpg.id == 0xff && jpg.id2 == 0xd8)
        {
            std::cout <<"Este es un Archivo de Imagen JPG\n";
            if (buf[0]==0xff && buf[1]==0xd8 && buf[2]==0xff)
            { 
                *y = (buf[7]<<8) + buf[8];
                *x = (buf[9]<<8) + buf[10];
            }
            return 1;
        }
        else
        {
            return 2;
        }
        

    }

    int EvaluationsGIF(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el GIF" << argv << "\n";
        }

        GIFFile gif;
        in.read(reinterpret_cast<char*>(&gif),sizeof(GIFFile));
        if (in.gcount() != sizeof(GIFFile))
        {
            std::cout << "NO ES UN GIF File\n";
        }
        if (gif.id == 0x47 && gif.id2 == 0x49 && gif.id3 == 0x46)
        {
            std::cout <<"Este es un Archivo de Imagen GIF\nWidth: " << gif.with 
                      << "\nHeight: " << gif.height << "\n";
                      return 1;
        }
        else
        {
            return 2;
        }
    }

    int EvaluationsTIF(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el TIF" << argv << "\n";
        }

        TIFFile tif;
        in.read(reinterpret_cast<char*>(&tif),sizeof(TIFFile));
        if (in.gcount() != sizeof(TIFFile))
        {
            std::cout << "NO ES UN TIF File\n";
        }
        if (tif.id == 0x49 && tif.id2 == 0x49 && tif.id3 == 0x2a)
        {
            std::cout <<"Este es un Archivo de Imagen TIFF\n";
            return 1;
        }
        else
        {
            return 2;
        }
    }

    int EvaluationsSVG(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el SVG" << argv << "\n";
        }

        SVGFile svg;
        in.read(reinterpret_cast<char*>(&svg),sizeof(SVGFile));
        if (in.gcount() != sizeof(SVGFile))
        {
            std::cout << "NO ES UN SVG File\n";
        }
        if (svg.id == 0x3c && svg.id2 == 0x3f && svg.id3 == 0x78)
        {
            std::cout <<"Este es un Archivo de Imagen SVG\n";
            return 1;
        }
        else
        {
            return 2;
        }

    }

    private:
    

};

