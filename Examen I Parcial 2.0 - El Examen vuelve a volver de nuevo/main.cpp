#include <iostream>
#include <fstream>
#include <vector>
#include "zip.h"
#include "time.h"

int main(int argc, char *argv[])
{
    time_t tiempo;

    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <input file 1>  <input file 2>  <input file 3>  <zip file>\n";
        return 1;
    }
    // argv[1] -> input file
    // argv[2] -> input file
    // argv[3] -> input file

    // argv[4] -> output zip file
    std::ifstream in(argv[1]);
    std::ifstream in2(argv[2]);
    std::ifstream in3(argv[3]);
    if (!in.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 2;
    }
    if (!in2.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 2;
    }
    if (!in3.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 2;
    }
    
    std::string texto = "";
    while (!in.eof())
    {
        std::string linea = "";
        getline(in,linea);
        texto = texto + linea;
    }

    std::string texto2 = "";
    while (!in2.eof())
    {
        std::string linea2 = "";
        getline(in2,linea2);
        texto2= texto2 + linea2;
    }
    /*<uint8_t> vecto(in2.tellg());
    in2.seekg(0,std::ios::beg);
    in.read(reinterpret_cast<char *>(vecto.data()),vecto.size());*/

    std::string texto3 = "";
    while (!in3.eof())
    {
        std::string linea3 = "";
        getline(in3,linea3);
        texto3 = texto3 + linea3;
    }




    LocalFileHeader archivo1;
    LocalFileHeader archivo2;
    LocalFileHeader archivo3;

    //header archivo 1
    archivo1.signature = 0x04034b50;
    archivo1.version = 0x14;
    archivo1.flags = 0;
    archivo1.comp_method = 0;
    archivo1.crc32 = 0;
    archivo1.mtime = zip::makeTime(4,30,15);
    archivo1.mdate = zip::makeDate(20,8,2020);
    in.seekg(0,std::ios::end);
    std::cout <<"Tamaño del archivo:" << in.tellg();
    archivo1.orig_file_size = in.tellg();
    archivo1.comp_file_size = in.tellg();
    std::string name =(std::string)argv[1];
    archivo1.name_len = name.length();
    archivo1.extra_len = 0;
    

    //heADER archivo 2
    archivo2.signature = 0x04034b50;
    archivo2.version = 0x14;
    archivo2.flags = 0;
    archivo2.comp_method = 0;
    archivo2.crc32 = 0;
    archivo2.mtime = zip::makeTime(4,30,15);
    archivo2.mdate = zip::makeDate(20,8,2020);
    in2.seekg(0,std::ios::end);
    std::cout <<"\nTamaño del archivo:" << in2.tellg();
    archivo2.orig_file_size = in2.tellg();
    archivo2.comp_file_size = in2.tellg();
    std::string name2 =(std::string)argv[2];
    archivo2.name_len = name2.length();
    archivo2.extra_len = 0;


    //header archivo 3
    archivo3.signature = 0x04034b50;
    archivo3.version = 0x14;
    archivo3.flags = 0;
    archivo3.comp_method = 0;
    archivo3.crc32 = 0;
    archivo3.mtime = zip::makeTime(4,30,15);
    archivo3.mdate = zip::makeDate(20,8,2020);
    in3.seekg(0,std::ios::end);
    std::cout <<"\nTamaño del archivo:" << in3.tellg();
    archivo3.orig_file_size = in3.tellg();
    archivo3.comp_file_size = in3.tellg();
    std::string name3 =(std::string)argv[3];
    archivo3.name_len = name3.length();
    archivo3.extra_len = 0;


    CentralDirectoryFileHeader cd1;
    CentralDirectoryFileHeader cd2;
    CentralDirectoryFileHeader cd3;

    // cd archivo 1
    cd1.signature = 0x02014b50;
    cd1.version_made = 0x14;
    cd1.version_extract = 0x14;
    cd1.flags = 0;
    cd1.comp_method=0;
    cd1.mtime = zip::makeTime(4,30,15);
    cd1.mdate = zip::makeDate(20,8,2020);
    cd1.crc32 = 0;
    cd1.orig_file_size = in.tellg();
    cd1.comp_file_size = in.tellg();
    cd1.name_len = name.length();
    cd1.extra_len = 0;
    cd1.file_comment_len = 0;
    cd1.disk_number = 0;
    cd1.file_attrs1 = 0;
    cd1.file_attrs2 = 0;
    cd1.file_offset = 0;

    //cd archivo 2

    cd2.signature = 0x02014b50;
    cd2.version_made = 0x14;
    cd2.version_extract = 0x14;
    cd2.flags = 0;
    cd2.comp_method=0;
    cd2.mtime = zip::makeTime(4,30,15);
    cd2.mdate = zip::makeDate(20,8,2020);
    cd2.crc32 = 0;
    cd2.orig_file_size = in2.tellg();
    cd2.comp_file_size = in2.tellg();
    cd2.name_len = name2.length();
    cd2.extra_len = 0;
    cd2.file_comment_len = 0;
    cd2.disk_number = 0;
    cd2.file_attrs1 = 0;
    cd2.file_attrs2 = 0;
    cd2.file_offset = 0;

    // cd Archivo3
    cd3.signature = 0x02014b50;
    cd3.version_made = 0x14;
    cd3.version_extract = 0x14;
    cd3.flags = 0;
    cd3.comp_method=0;
    cd3.mtime = zip::makeTime(4,30,15);
    cd3.mdate = zip::makeDate(20,8,2020);
    cd3.crc32 = 0;
    cd3.orig_file_size = in3.tellg();
    cd3.comp_file_size = in3.tellg();
    cd3.name_len = name3.length();
    cd3.extra_len = 0;
    cd3.file_comment_len = 0;
    cd3.disk_number = 0;
    cd3.file_attrs1 = 0;
    cd3.file_attrs2 = 0;
    cd3.file_offset = 0;

    std::ofstream out(argv[4]);
    if (!out.is_open())
    {
        std::cerr << "Cannot open file: " << argv[4] << "\n";
        return 2;
    }
    
    out.write(reinterpret_cast<char*>(&archivo1),sizeof(LocalFileHeader));
    out.write(argv[1], name.length());
    out.write((char *)&texto, sizeof(std::string));
    out.write(reinterpret_cast<char*>(&archivo2),sizeof(LocalFileHeader));
    out.write(argv[2], name2.length());
    out.write((char *)&texto2, sizeof(std::string));
    out.write(reinterpret_cast<char*>(&archivo3),sizeof(LocalFileHeader));
    out.write(argv[3], name3.length());
    out.write((char *)&texto3, sizeof(std::string));
    int offset_cd = out.tellp();
    out.write(reinterpret_cast<char*>(&cd1),sizeof(CentralDirectoryFileHeader));
    out.write(argv[1], name.length());
    out.write(reinterpret_cast<char*>(&cd2),sizeof(CentralDirectoryFileHeader));
    out.write(argv[2], name2.length());
    out.write(reinterpret_cast<char*>(&cd3),sizeof(CentralDirectoryFileHeader));
    out.write(argv[3], name3.length());

    EndOfCentralDirectory ending;
    ending.signature = 0x06054b50;
    ending.disk_number = 0;
    ending.disk_start = 0;
    ending.cd_records1 = 3;
    ending.cd_records2 = 3;
    ending.size_of_cd = (sizeof(CentralDirectoryFileHeader)*3) + name.length() + name2.length() + name3.length();
    ending.offset_of_cd = offset_cd;
    ending.comment_length = 0;
    out.write(reinterpret_cast<char*>(&ending),sizeof(EndOfCentralDirectory));

}
