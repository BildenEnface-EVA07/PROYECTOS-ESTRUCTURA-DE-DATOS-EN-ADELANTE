#include <iostream>
#include "imagenes.h"
#include "compresos.h"
#include "ejecutables.h"

int main(int argc,char *argv[])
{
    int x = 0;
    int y = 0;
    imagenes images;
    compresos compi;
    ejecutables eje;
    if (images.EvaluationsBMP(argv[1]) != 2)
    {

    }
    else if (images.EvaluationsPNG(argv[1],&x,&y) == 1)
    {
        std::cout <<"Width: " << x << "\nHeigth: " << y << "\n";
    }
    else if (images.EvaluationsJPEG(argv[1],&x,&y) == 1)
    {
        std::cout <<"Width: " << x << "\nHeigth: " << y << "\n";
    }
    else if (images.EvaluationsGIF(argv[1]) !=2)
    {

    }
    else if (images.EvaluationsTIF(argv[1]) != 2)
    {

    }
    else if (images.EvaluationsSVG(argv[1]) != 2)
    {

    }
    else if (compi.EvaluationsZIP(argv[1]) != 2)
    {

    }
    else if (compi.EvaluationsRAR(argv[1]) != 2)
    {

    }
    else if (compi.EvaluationsGZ(argv[1]) != 2)
    {
        /* code */
    }
    else if (compi.EvaluationBZ2(argv[1]) != 2)
    {
        /* code */
    }
    else if (compi.EvaluationsXZ(argv[1]) != 2)
    {
        /* code */
    }
    else if (eje.EvaluationsWindows(argv[1]) != 2)
    {
        /* code */
    }
    else if (eje.EvaluationsLinux(argv[1]) != 2)
    {
        /* code */
    }
    else
    {
        std::cout << "Tipo de archivo no soportado\n";
    }
    
    
    
    

    return 1;
}