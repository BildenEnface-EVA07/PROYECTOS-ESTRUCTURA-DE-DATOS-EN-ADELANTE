using namespace std;
#include <matplotpp/matplotpp.h>
#include "rapidcsv.h"
#include <iostream>
#include "fstream"
#include "CRC.h"
#include <iomanip>
#include <cstdint>
#include <string.h>
#include "AVL.h"
#include <vector>
#include "csvabin.h"

class DataFilter : public MatPlot
{
public:
    std::vector<DatosArchivo> draw;
    std::vector<DatosArchivo> draw2;
    static std::vector<double> newcases;
    static std::vector<double> cum_cases;
    static std::vector<double> new_kills;
    static std::vector<double> cum_kills;

    DataFilter()
    {
    }
    void busqueda_por_pais(std::string pais);

    void busqueda_porRangodeFecha(int mes1, int dia1, int mes2, int dia2);

    void busqueda_por_Fecha_Exacta(std::string fecha);

    //--------------------------------------de menor pa abajo

    void Busqueda_por_CasosNUevos_Mayor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_CasosAcumulados_Mayor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_MuertesNuevas_Mayor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_MuertesAcumuladas_Mayor_a(int size, std::vector<DatosArchivo> draw);

    //--------------------------------------de menor pa abajo

    void Busqueda_por_CasosNUevos_Menor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_CasosAcumulados_Menor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_MuertesNuevas_Menor_a(int size, std::vector<DatosArchivo> draw);

    void Busqueda_por_MuertesAcumuladas_Menor_a(int size, std::vector<DatosArchivo> draw);

    void Llenar_Vectores(std::vector<DatosArchivo> damm);

    void ImprimirCosas(int argc, char **argv);
    void DISPLAY();

private:
};