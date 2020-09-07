#include <iostream>
#include <fstream>
#include "Yaml.hpp"
#include "Jzon.h"

namespace Json = Jzon;

void printJson(const Json::Node& root)
{
    if (root.isObject())
    {
        std::cout << "{\n";
        for (const auto& n : root)
        {
            std::cout << n.first << " : ";
            printJson(n.second);
            std::cout << '\n';
        }
        std::cout << "}";
    }
    else if (root.isArray())
    {
        bool first = true;
        std::cout << "[ ";
        for (const auto& n : root)
        {
            if (first) first = false;
            else std::cout << ", ";

            printJson(n.second);
        }
        std::cout << " ]";
    }
    else
    {
        std::cout << root.toString();
    }
}

Yaml::Node ConvertirAYaml(const Json::Node& root)
{
    if (root.isObject())
    {
        Yaml::Node objeto;
        for (const auto &n: root)
        {
            objeto[n.first] = ConvertirAYaml(n.second);
        }
        return objeto;

    }
    else if (root.isArray())
    {
        Yaml::Node arreglo;
        for (const auto& n: root)
        {
            arreglo.PushBack()=ConvertirAYaml(n.second);
        }
        return arreglo;
    }
    else
    {
        Yaml::Node objeto;
        objeto = root.toString();
        return objeto;
    }
}

Yaml::Node Convertir(const Json::Node& root)
{
    if (root.isObject())
    {
        Yaml::Node objeto;
        auto it = root.begin();
        while (it != root.end())
        {
            objeto[(*it).first] = Convertir((*it).second);
            it++;
        }
        return objeto;
    }
    else if (root.isArray())
    {
        Yaml::Node arreglo;
        auto it = root.begin();
        while (it != root.end())
        {
            arreglo.PushBack() = Convertir((*it).second);
        }
        return arreglo;
    }
    else
    {
        Yaml::Node nada;
        nada = root.toString();
        return nada;
    }
    
    
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }
    Json::Parser parser;
	
	Json::Node root = parser.parseFile(argv[1]);
    
	if (!root.isValid())
	{
		std::cerr << parser.getError() << '\n';
		return 1;
	}

    Yaml::Node nuevaroot = ConvertirAYaml(root);
    Yaml::Serialize(nuevaroot,argv[2],Yaml::SerializeConfig(2,64,true,false));
    return 0;
}
