#include "rapidcsv.h"
#include <iostream>
#include "fstream"
#include "csvabin.h"
#include "datafilter.h"

namespace csv = rapidcsv;



int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 2;
    }
    csvabin convertidor;
    DataFilter filtrador;
    int menu = 0;
    std::string namearchivo = "";
    int year = 0;
    int mes = 0;
    int dia = 0;
    int year2 = 0;
    int mes2 = 0;
    int dia2 = 0;
    std::string fechac = "";
    char fecha[20];
    bool yaconvertido = false;
    int menufecha = 0;
    int menupais = 0;
    int menuexacto = 0;
    int casos = 0;
    int size = 0;
    //convertidor.printFile(argv);
    do
    {
        std::cout << "Menu de Acciones\n1.Busqueda por fecha\n2.Busqueda por Pais\n3.Busqueda por Fecha Exacta";
        std::cout << "\n4.Convertir A Binario\n5.Salir\nIngrese el numero de su opcion:";
        std::cin >> menu;
        switch (menu)
        {
        case 1:
            std::cout << "Ingrese la fecha: \nIngresa el años: \n";
            std::cin >> year;
            std::cout << "Ingrese el mes: ";
            std::cin >> mes;
            std::cout << "Ingrese el dia: ";
            std::cin >> dia;
            std::cout << "Ingrese el año: ";
            std::cin >> year2;
            std::cout << "Ingrese el mes de la segunda fecha: ";
            std::cin >> mes2;
            std::cout << "Ingrese el dia de la segunda fecha: ";
            std::cin >> dia2;
            //fechac = year + "-" + mes + "-" + dia;
            //std::copy(fechac.begin(), fechac.end(), fecha);
            //filtrador.busqueda_por_Fecha_Exacta(fechac);
            filtrador.busqueda_porRangodeFecha(mes, dia, mes2, dia2);
            std::cout << "\nQue campos desea ver: \n1.Casos nuevos\n2.Casos Acumulado";
            std::cout << "\n3.Muertes nuevas\n4.Muertes Acumulados\n5.Graficar Todo\nIngrese su opcion: ";
            std::cin >> menufecha;
            switch (menufecha)
            {
            case 1:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Menor_a(size, filtrador.draw);
                }
                break;

            case 2:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Menor_a(size, filtrador.draw);
                }

                break;

            case 3:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Menor_a(size, filtrador.draw);
                }

                break;

            case 4:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Menor_a(size, filtrador.draw);
                }

                break;

            case 5:
                filtrador.Llenar_Vectores(filtrador.draw);
                filtrador.ImprimirCosas(argc,argv);
                break;
                
            }
            break;
        case 2:
            std::cout << "Escriba el nombre del pais: ";
            std::cin >> namearchivo;
            filtrador.busqueda_por_pais(namearchivo);
            std::cout << "\nQue campos desea ver: \n1.Casos nuevos\n2.Casos Acumulado";
            std::cout << "\n3.Muertes nuevas\n4.Muertes Acumulados\n5.Graficar Todo\nIngrese su opcion: ";
            std::cin >> menupais;
            switch (menupais)
            {
            case 1:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Mayor_a(size, filtrador.draw2);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Menor_a(size, filtrador.draw2);
                }

                break;

            case 2:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Mayor_a(size, filtrador.draw2);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Menor_a(size, filtrador.draw2);
                }

                break;

            case 3:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Mayor_a(size, filtrador.draw2);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Menor_a(size, filtrador.draw2);
                }

                break;

            case 4:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Mayor_a(size, filtrador.draw2);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Menor_a(size, filtrador.draw2);
                }

                break;

            case 5:
                filtrador.Llenar_Vectores(filtrador.draw2);
                filtrador.ImprimirCosas(argc,argv);
                break;
            }
            break;

        case 4:
            //std::cout << "Escriba el nombre del archivo: ";
            //std::cin >> namearchivo;
            convertidor.LeerDocumento(argv);
            std::cout << "\nSe ha convertido a .bin Correctamente";
            break;

        case 3:
            std::cout << "\nIngrese la fecha: \nIngrese el año: ";
            std::cin >> year;
            std::cout << "Ingrese el mes: ";
            std::cin >> mes;
            std::cout << "Ingrese el dia: ";
            std::cin >> dia;
            fechac = std::to_string(year) + "-0" + std::to_string(mes) + "-" + std::to_string(dia);
            std::cout << "Fecha Ingresada: " << fechac << "\n";
            filtrador.busqueda_por_Fecha_Exacta(fechac);
            std::cout << "\nQue campos desea ver: \n1.Casos nuevos\n2.Casos Acumulado";
            std::cout << "\n3.Muertes nuevas\n4.Muertes Acumulados\n5.Graficar Todo\nIngrese su opcion: ";
            std::cin >> menuexacto;
            switch (menuexacto)
            {
            case 1:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosNUevos_Menor_a(size, filtrador.draw);
                }
                break;

            case 2:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_CasosAcumulados_Menor_a(size, filtrador.draw);
                }

                break;

            case 3:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesNuevas_Menor_a(size, filtrador.draw);
                }

                break;

            case 4:
                std::cout << "\n1.Busquedas mayor a...\n2.Busquedas menor a...\nINgrese la opcion: ";
                casos = 0;
                size = 0;
                std::cin >> casos;
                if (casos == 1)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Mayor_a(size, filtrador.draw);
                }
                else if (casos == 2)
                {
                    std::cout << "\nIngrese el tamaño: ";
                    std::cin >> size;
                    filtrador.Busqueda_por_MuertesAcumuladas_Menor_a(size, filtrador.draw);
                }

                break;

            case 5:
                filtrador.Llenar_Vectores(filtrador.draw);
                filtrador.ImprimirCosas(argc,argv);
                break;
                
            }
            break;
        }
    } while (menu != 5);

    in.close();
    //filtrador.ImprimirCosas(argc,argv);
    return 0;
}