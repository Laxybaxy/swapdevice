#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "json.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    nlohmann::json j;

    //  Read from cfg
    std::ifstream i("config.json");
    if (i) {
        i >> j;
    }
    else { //if no cfg makes default
        printf("unable to read config.json");
        j["list"] = { "speakers","headset" };
        j["current"] = "speakers";
    }

    int newcurrent = NULL;

    for (int i = 0; i < j["list"].size(); i++)
    {
        if (j["list"].at(i) == j["current"])
        {
            newcurrent = i + 1;
            if (newcurrent >= j["list"].size())
            {
                newcurrent = 0;
            }
        }
    }
    j["current"] = j["list"].at(newcurrent);

    //  Write to cfg
    std::ofstream o("config.json");
    o << std::setw(4) << j << std::endl;
    
    //  set defaultdevice
    string a = j["current"];
    string b = a + ".bat";
    //std::cout << b.c_str() << std::endl;
    system(b.c_str());
}