#include "datafilter.h"
using namespace std;
#include <matplotpp/matplotpp.h>
#include "CRC.h"

std::vector<double> DataFilter::cum_cases;
std::vector<double> DataFilter::new_kills;
std::vector<double> DataFilter::newcases;
std::vector<double> DataFilter::cum_kills;

void DataFilter::busqueda_por_pais(std::string pais)
{
    std::ifstream in("covid.bin");
    if (!in.is_open())
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    header provish;
    in.read(reinterpret_cast<char *>(&provish), sizeof(header));
    uint32_t crc = CRC::Calculate(reinterpret_cast<char*>(&provish),sizeof(header) - sizeof(uint32_t), CRC::CRC_32());
    if (crc != provish.CRC)
    {
        std::cerr << "Invalid Billy File or This File is Damaged\n";
    }
    while (!in.eof())
    {
        DatosArchivo datos;
        in.read(reinterpret_cast<char *>(&datos), sizeof(DatosArchivo));
        if (pais == datos.country_name)
        {
            draw2.push_back(datos);
        }
    }
}

/*int parseDate(const std::string &input) {
    int month;
    int day;
    int year;
    if (std::sscanf(input.c_str(), "%d-%d-%-", &year, &month, &day) != 3) {
        // handle error
        return 0;
    } else {
        // check values to avoid int overflow if you can be bothered
        return 10000 * year + 100 * month + day;
    }
}*/

void DataFilter::busqueda_porRangodeFecha(int mes1, int dia1, int mes2, int dia2)
{
    std::ifstream in("covid.bin");
    if (!in.is_open())
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    header provish;
    in.read(reinterpret_cast<char *>(&provish), sizeof(header));
    uint32_t crc = CRC::Calculate(reinterpret_cast<char*>(&provish),sizeof(header) - sizeof(uint32_t), CRC::CRC_32());
    if (crc != provish.CRC)
    {
        std::cerr << "Invalid Billy File or This File is Damaged\n";
    }
    int num = 0;
    std::string postemp = "";
    while (!in.eof())
    {
        DatosArchivo datos;
        postemp = "";
        in.read(reinterpret_cast<char *>(&datos), sizeof(DatosArchivo));
        int num = 0;
        int num2 = 0;
        bool mayor = false;
        bool menor = false;
        postemp = datos.date_reported;
        char temp[2] = {datos.date_reported[5], datos.date_reported[6]};
        stringstream s(temp);
        s >> num;
        //num = std::stoi(temp);
        //std::cout <<"temp1: "<< temp << "\n";
        char temp2[2] = {datos.date_reported[8],datos.date_reported[9]};
        stringstream z(temp2);
        z >> num2;
        std::cout << "\nnum:" << num <<"\nnum2:" << num2;
        //num2 = std::stoi(temp2);
        //std::cout <<"temp2: "<< temp2 << "\n";
        if (num > mes1 && num < mes2)
        {
            mayor = true;
            menor = true;
        }
        else if (num == mes1)
        {
            if (num2 >= dia1)
            {
                mayor = true;
            }
        }
        else if (num == mes2)
        {
            if (num2 <= dia2)
            {
                menor = true;
            }
        }

        if (mayor == true && menor == true)
        {
            draw.push_back(datos);
            std::cout << datos.date_reported << "\n";
        }
        
        
    }
}

void DataFilter::busqueda_por_Fecha_Exacta(std::string fecha)
{
    std::ifstream in("covid.bin");
    if (!in.is_open())
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    header provish;
    in.read(reinterpret_cast<char *>(&provish), sizeof(header));
    uint32_t crc = CRC::Calculate(reinterpret_cast<char*>(&provish),sizeof(header) - sizeof(uint32_t), CRC::CRC_32());
    if (crc != provish.CRC)
    {
        std::cerr << "Invalid Billy File or This File is Damaged\n";
    }
    while (!in.eof())
    {
        DatosArchivo datos;
        in.read(reinterpret_cast<char *>(&datos), sizeof(DatosArchivo));
        if (fecha == datos.date_reported)
        {
            draw.push_back(datos);
            std::cout << datos.date_reported << "\n";
        }
        else
        {
        }
    }
}

void DataFilter::Busqueda_por_CasosNUevos_Mayor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_cases > size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].new_cases << "\n";
        }
    }
}

void DataFilter::Busqueda_por_CasosAcumulados_Mayor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].cumalitive_cases > size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].cumalitive_cases << "\n";
        }
    }
}

void DataFilter::Busqueda_por_MuertesNuevas_Mayor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_deaths > size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].new_deaths << "\n";
        }
    }
}

void DataFilter::Busqueda_por_MuertesAcumuladas_Mayor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_deaths > size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].cumulative_deaths << "\n";
        }
    }
}

void DataFilter::Busqueda_por_CasosNUevos_Menor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_cases < size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].new_cases << "\n";
        }
    }
}

void DataFilter::Busqueda_por_CasosAcumulados_Menor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].cumalitive_cases < size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].cumalitive_cases << "\n";
        }
    }
}

void DataFilter::Busqueda_por_MuertesNuevas_Menor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_deaths < size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].new_deaths << "\n";
        }
    }
}

void DataFilter::Busqueda_por_MuertesAcumuladas_Menor_a(int size, std::vector<DatosArchivo> draw)
{
    for (int i = 0; i < draw.size(); i++)
    {
        if (draw[i].new_deaths < size)
        {
            std::cout << draw[i].date_reported << " " << draw[i].country_name
                      << " " << draw[i].cumulative_deaths << "\n";
        }
    }
}

void DataFilter::Llenar_Vectores(std::vector<DatosArchivo> damm)
{

    for (int i = 0; i < damm.size(); i++)
    {
        newcases.push_back(damm[i].new_cases);
        cum_cases.push_back(damm[i].cumalitive_cases);
        new_kills.push_back(damm[i].new_deaths);
        cum_kills.push_back(damm[i].cumulative_deaths);
    }
}

void DataFilter::DISPLAY()
{
    int n = cum_cases.size();
    std::vector<double> x(n);

    for (int i = 0; i < n; i++)
    {
        x[i] = i;
    }

    layer("Cumulative cases", 0);
    subplot(1, 1, 1);
    plot(x, cum_cases);

    layer("new cases", 0);
    subplot(1, 1, 1);
    plot(x, new_kills);

    layer("new deaths", 0);
    subplot(1, 1, 1);
    plot(x, new_kills);

    layer("Cumulative deaths", 0);
    subplot(1, 1, 1);
    plot(x, cum_kills);
}

DataFilter mp;
void Display() { mp.display(); }
void Reshape(int w, int h) { mp.reshape(w, h); }
void Idle(void)
{
    glutPostRedisplay();
    usleep(10000);
}
void Mouse(int button, int state, int x, int y) { mp.mouse(button, state, x, y); }
void Motion(int x, int y) { mp.motion(x, y); }
void Passive(int x, int y) { mp.passivemotion(x, y); }
void Keyboard(unsigned char key, int x, int y) { mp.keyboard(key, x, y); }

void DataFilter::ImprimirCosas(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow(100, 100, 500, 400);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
    glutMotionFunc(Motion);
    glutMouseFunc(Mouse);
    glutPassiveMotionFunc(Passive);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
}