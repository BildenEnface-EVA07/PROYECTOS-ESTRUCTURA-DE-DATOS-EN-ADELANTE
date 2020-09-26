#ifndef CSVABIN_H
#define CSVABIN_H
#include "rapidcsv.h"
#include <iostream>
#include "fstream"
#include "CRC.h"
#include <iomanip>
#include <cstdint>
#include <string.h>

namespace csv = rapidcsv;

struct header
{
    header()
        : CRC(0)
    {
        std::fill(signature,signature+ 20,0);
        std::fill(nombre,nombre+ 20,0);
        std::fill(date,date+ 20,0);
        std::fill(country_code,country_code +20,0);
        std::fill(country_name,country_name + 20,0);
        std::fill(who_region,who_region + 20,0);
        std::fill(new_cases,new_cases + 20,0);
        std::fill(cumalitive_cases,cumalitive_cases + 20,0);
        std::fill(new_deaths,new_deaths + 20,0);
        std::fill(cumulative_deaths,cumulative_deaths + 20,0);
    }
    void set_signature(const std::string sig)
    {
        std::copy(sig.begin(), sig.end(), signature);
    }
    void set_nombre(const std::string nambre)
    {
        std::copy(nambre.begin(), nambre.end(), nombre);
    }
    void set_date_reported(const std::string fecha)
    {
        std::copy(fecha.begin(), fecha.end(), date);
    }

    void set_country_code(const std::string code)
    {
        std::copy(code.begin(), code.end(), country_code);
    }

    void set_country_name(const std::string name)
    {
        std::copy(name.begin(), name.end(), country_name);
    }

    void set_who_region(const std::string region)
    {
        std::copy(region.begin(), region.end(), who_region);
    }
    void set_newcases(const std::string casos)
    {
        std::copy(casos.begin(), casos.end(), new_cases);
    }
    void set_cumulative_cases(const std::string casosc)
    {
        std::copy(casosc.begin(), casosc.end(), cumalitive_cases);
    }
    void set_new_deaths(const std::string muertes)
    {
        std::copy(muertes.begin(), muertes.end(), new_deaths);
    }
    void set_cumulative_deaths(const std::string muertesc)
    {
        std::copy(muertesc.begin(), muertesc.end(), cumulative_deaths);
    }
    char signature[20];
    char nombre[20];
    char date[20];
    char country_code[20];
    char country_name[20];
    char who_region[20];
    char new_cases[20];
    char cumalitive_cases[20];
    char new_deaths[20];
    char cumulative_deaths[20];
    uint32_t CRC;
} __attribute((packed));

struct DatosArchivo
{
    DatosArchivo()
        : new_cases(0), cumalitive_cases(0), new_deaths(0), cumulative_deaths(0)
    {
        std::fill(date_reported, date_reported + 20, 0);
        std::fill(country_code, country_code + 10, 0);
        std::fill(country_name, country_name + 64, 0);
        std::fill(who_region, who_region + 10, 0);
    }
    void set_date_reported(const std::string fecha)
    {
        std::copy(fecha.begin(), fecha.end(), date_reported);
    }

    void set_country_code(const std::string code)
    {
        std::copy(code.begin(), code.end(), country_code);
    }

    void set_country_name(const std::string name)
    {
        std::copy(name.begin(), name.end(), country_name);
    }

    void set_who_region(const std::string region)
    {
        std::copy(region.begin(), region.end(), who_region);
    }
    char date_reported[20];
    char country_code[10];
    char country_name[64];
    char who_region[10];
    int new_cases;
    int cumalitive_cases;
    int new_deaths;
    int cumulative_deaths;
} __attribute((packed));

class csvabin
{
public:
    void LeerDocumento(char *argv[])
    {
        std::ifstream in(argv[1]);
        if (!in.is_open())
        {
            std::cerr << "Cannot open file: " << argv << "\n";
        }
        csv::Document doc(in);
        header newheader;
        std::ofstream out(argv[2]);
            if (!out.is_open())
            {
                std::cerr << "Cannot open file\n";
            }

        newheader.set_signature("ABIL");
        newheader.set_nombre("covid-Information");
        newheader.set_date_reported("Date_reported");
        newheader.set_country_code("Country_code");
        newheader.set_country_name("Country");
        newheader.set_who_region("WHO_region");
        newheader.set_newcases("New_cases");
        newheader.set_cumulative_cases("Cumulative_cases");
        newheader.set_new_deaths("New_deaths");
        newheader.set_cumulative_deaths("Cumulative_deaths");
        newheader.CRC = CRC::Calculate(reinterpret_cast<char*>(&newheader),sizeof(header) - sizeof(uint32_t), CRC::CRC_32());
        out.write(reinterpret_cast<char*>(&newheader),sizeof(header));
        for (int i = 1; i < doc.GetRowCount(); i++)
        {
            DatosArchivo nuevo;
            for (int n = 0; n < doc.GetColumnCount(); n++)
            {
                if (doc.GetColumnName(n) == "Date_reported")
                {
                    nuevo.set_date_reported(doc.GetCell<std::string>(n,i));
                }
                else if (doc.GetColumnName(n) == " Country_code")
                {
                    nuevo.set_country_code(doc.GetCell<std::string>(n,i));
                }
                else if (doc.GetColumnName(n) == " Country")
                {
                    nuevo.set_country_name(doc.GetCell<std::string>(n,i));
                }
                else if (doc.GetColumnName(n) == " WHO_region")
                {
                    nuevo.set_who_region(doc.GetCell<std::string>(n,i));
                }
                else if (doc.GetColumnName(n) == " New_cases")
                {
                    nuevo.new_cases = doc.GetCell<int>(n,i);
                }
                else if (doc.GetColumnName(n) == " Cumulative_cases")
                {
                    nuevo.cumalitive_cases = doc.GetCell<int>(n,i);
                }
                else if (doc.GetColumnName(n) == " New_deaths")
                {
                    nuevo.new_deaths = doc.GetCell<int>(n,i);
                }
                else if (doc.GetColumnName(n) == " Cumulative_deaths")
                {
                    nuevo.cumulative_deaths = doc.GetCell<int>(n,i);
                }
            }
            out.write(reinterpret_cast<char*>(&nuevo),sizeof(DatosArchivo));
        }
        in.close();
    }

    void printFile(char *argv[])
{
    std::ifstream iin(argv[2]);
    header pop;

    iin.read(reinterpret_cast<char*>(&pop),sizeof(header));

    uint32_t crc= CRC::Calculate(reinterpret_cast<char *>(&pop),sizeof(header) - sizeof(uint32_t),CRC::CRC_32());

    std::cout<< crc <<"   /"<<pop.CRC<<"\n";
    if(crc!=pop.CRC)
    {
        std::cerr<<"Bad header, Wrong CRC\n";
        return;
    }
   
    std::cout<<pop.date<< "\t\t"<<pop.country_code<<"\t\t"<<pop.country_name<<"\t\t"<<pop.who_region<<"\t\t"<<pop.new_cases<<"\t\t"<<pop.cumalitive_cases<<"\t\t"<<pop.new_deaths<<"\t\t"<<pop.cumulative_deaths<<"\n\n";


    DatosArchivo dat;
    
    while(!iin.eof())
    {
        iin.read(reinterpret_cast<char*>(&dat),sizeof(DatosArchivo));
        std::cout<<dat.date_reported<<"\t\t\t\t"<<dat.country_code<<"\t\t\t\t"<<dat.country_name<<"\t\t\t\t"<<dat.who_region<<"\t\t\t\t"<<dat.new_cases<<"\t\t\t\t"<<dat.cumalitive_cases<<"\t\t\t\t"<<dat.new_deaths<<"\t\t\t\t"<<dat.cumulative_deaths<<"\n";
    }
}

private:
};
#endif