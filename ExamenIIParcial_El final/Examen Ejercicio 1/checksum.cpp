#include "checksum.h"
#include <string.h>
#include <iostream>

uint32_t Checksum::compute(const std::string& str)
{
    uint32_t sum = 0;
    for (int i = 0; i < str.length(); i++)
    {
        sum = str.at(4*i) + (str.at(4*i + 1)<< 16);
    }
    if (str.length()%4) sum = str.at(str.length() - 1);
    return sum;
    
}