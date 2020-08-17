#include <iostream>
#include <fstream>
#include <cstdint>
#include "inttypes.h"

struct ZIPFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
}__attribute__((packed));

struct RARFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
    uint8_t id5;
    uint8_t id6;
}__attribute__((packed));

struct GZFile
{
    uint8_t id;
    uint8_t id2;
}__attribute__((packed));

struct BZ2File
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
}__attribute__((packed));

struct XZFile
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
    uint8_t id5;
    uint8_t id6;
}__attribute__((packed));

class compresos
{
    public:
    compresos(){}
    int EvaluationsZIP(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el ZIP" << argv << "\n";
            return 3;
        }

        ZIPFile zip;
        in.read(reinterpret_cast<char*>(&zip),sizeof(ZIPFile));

        if (in.gcount() != sizeof(ZIPFile))
            {
                std::cerr << "Invalid   ZIP\n";

            }
        if(zip.id == 0x50 && zip.id2 == 0x4b && zip.id3 == 0x03 && zip.id4 == 0x04)
            {
                std::cout << "Este es un archivo compreso tipo ZIP\n";
                return 1;
            }
            else
            {
                return 2;
            }
    }

    int EvaluationsRAR(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el RAR" << argv << "\n";
            return 3;
        }

        RARFile rar;
        in.read(reinterpret_cast<char*>(&rar),sizeof(RARFile));

        if (in.gcount() != sizeof(RARFile))
            {
                std::cerr << "Invalid   RAR\n";

            }
        if(rar.id == 0x52 && rar.id2 == 0x61 && rar.id3 == 0x72 && rar.id4 == 0x21 && rar.id5 == 0x1a && rar.id6 == 0x07)
            {
                std::cout << "Este es un archivo compreso tipo RAR\n";
                return 1;
            }
            else
            {
                return 2;
            }
    }

    int EvaluationsGZ(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el GZ" << argv << "\n";
            return 3;
        }

        GZFile gz;
        in.read(reinterpret_cast<char*>(&gz),sizeof(GZFile));

        if (in.gcount() != sizeof(GZFile))
            {
                std::cerr << "Invalid   GZ\n";

            }
        if(gz.id == 0x1f && gz.id2 == 0x8b)
            {
                std::cout << "Este es un archivo compreso tipo GZ\n";
                return 1;
            }
            else
            {
                return 2;
            }

    }

    int EvaluationBZ2(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el BZip2" << argv << "\n";
            return 3;
        }
        BZ2File bz2;
        in.read(reinterpret_cast<char*>(&bz2),sizeof(BZ2File));

        if (in.gcount() != sizeof(BZ2File))
            {
                std::cerr << "Invalid   BZip2\n";

            }
        if(bz2.id == 0x42 && bz2.id2 == 0x5a && bz2.id3 == 0x68)
            {
                std::cout << "Este es un archivo compreso tipo BZIP2\n";
                return 1;
            }
            else
            {
                return 2;
            }
    }

    int  EvaluationsXZ(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el XZip" << argv << "\n";
            return 3;
        }
        XZFile xz;
        in.read(reinterpret_cast<char*>(&xz),sizeof(XZFile));

        if (in.gcount() != sizeof(XZFile))
            {
                std::cerr << "Invalid   XZip\n";

            }
        if(xz.id == 0xfd && xz.id2 == 0x37 && xz.id3 == 0x7a && xz.id4 == 0x58 && xz.id5 == 0x5a && xz.id6 == 0x00)
            {
                std::cout << "Este es un archivo compreso tipo XZIP\n";
                return 1;
            }
            else
            {
                return 2;
            }
    }

    private:

};