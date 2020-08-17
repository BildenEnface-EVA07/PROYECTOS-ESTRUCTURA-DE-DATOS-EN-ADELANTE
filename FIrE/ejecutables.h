#include <iostream>
#include <fstream>
#include <cstdint>
#include "inttypes.h"

struct WINFileReader
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
    uint8_t machine1;
    uint8_t machine2;
}__attribute__((packed));


struct LINUXFileReader
{
    uint8_t id;
    uint8_t id2;
    uint8_t id3;
    uint8_t id4;
    uint8_t machinetype;
}__attribute__((packed));


class ejecutables
{
    public:
    ejecutables(){}
    int EvaluationsWindows(char* argv)
    {
        std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el Executable" << argv << "\n";
            return 3;
        }
        in.seekg(0x3c);
        uint32_t header;
        in.read(reinterpret_cast<char*>(&header),sizeof(uint32_t));
        in.seekg(header);
        WINFileReader win;
        in.read(reinterpret_cast<char*>(&win),sizeof(WINFileReader));

        if (win.id == 0x50 && win.id2 == 0x45 && win.id3 == 0x00 && win.id4 == 0x00)
        {
            
            std::cout << "Este es una Archivo Ejecutable de Windows de: \n";
            if (win.machine1 == 0x64 && win.machine2 == 0x86)
            {
                std::cout << "Machine Type: 64 bits\n";
            }
            else if (win.machine1 == 0x4c && win.machine2 == 0x01)
            {
                std::cout << "Machine Type: 32 bits\n";
            }
            return 1;
        }
        else
        {
            return 2;
        }
        
        
    }

    int EvaluationsLinux(char* argv)
    {
         std::ifstream in(argv);
        if (!in.is_open())
        {
            std::cerr << "Error al cargar el Executable" << argv << "\n";
            return 3;
        }
        LINUXFileReader inux;
        in.read(reinterpret_cast<char*>(&inux),sizeof(LINUXFileReader));
        if (inux.id == 0x7f && inux.id2 == 0x45 && inux.id3 == 0x4c && inux.id4 == 0x46)
        {
            
            std::cout << "Este es una Archivo Ejecutable de Linux de: \n";
            if (inux.machinetype == 0x02)
            {
                std::cout << "Machine Type: 64 bits\n";
            }
            else if (inux.machinetype == 0x01)
            {
                std::cout << "Machine Type: 32 bits\n";
            }
            return 1;
        }
        else
        {
            return 2;
        }
    }

    private:


};