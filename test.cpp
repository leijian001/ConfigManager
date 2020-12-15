#include <iostream>
#include <vector>
#include <list>
#include "ConfigManager.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello world" << std::endl;

    int a = 1;
    float b = 2;
    std::string s = "Hello";
    std::array<int, 3> arr = {1, 2, 3};
    std::vector<float> v   = {11, 22, 33};
    std::list<int>     l   = {111, 222, 333};

    ConfigManager manager;
    manager.Register("A", &a, 2);
    manager.Register("B", &b, 3);
    manager.Register("S", &s, "World");
    manager.Register("Arr", &arr);
    manager.Register("V", &v, {2, 3, 4});
    manager.Register("L", &l);

    ConfigManager r;
    int e = 10;
    float f = 12;
    std::string ss = "First";
    std::vector<float> vv = {7, 8, 9};
    r.Register("AA", &e, 11);
    r.Register("BB", &f, 13);
    r.Register("SS", &ss, "Second");
    r.Register("VV", &vv, {17, 18, 19});

    manager.Register("R", r);

    std::cout << manager.dumpJson().dump() << std::endl;

    manager.loadJson(nlohmann::json::parse("{\"A\": 7, \"V\":[7,8,9], \"R\":{\"AA\":111}}"));
    std::cout << manager.dumpJson().dump() << std::endl;

    for(auto &t: v)
    {
        std::cout << t << '\t' ;
    }

    return 0;
}