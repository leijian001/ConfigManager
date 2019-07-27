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
    manager.register_item("A", &a, 2);
    manager.register_item("B", &b, 3);
    manager.register_item("S", &s, "World");
    manager.register_item("Arr", &arr);
    manager.register_item("V", &v, {2, 3, 4});
    manager.register_item("L", &l);

    ConfigManager r;
    int e = 10;
    float f = 12;
    std::string ss = "First";
    std::vector<float> vv = {7, 8, 9};
    r.register_item("AA", &e, 11);
    r.register_item("BB", &f, 13);
    r.register_item("SS", &ss, "Second");
    r.register_item("VV", &vv, {17, 18, 19});

    manager.register_item("R", r);

    std::cout << manager.dumpJson().dump() << std::endl;

    manager.loadJson(nlohmann::json::parse("{\"A\": 7, \"V\":[7,8,9], \"R\":{\"AA\":111}}"));
    std::cout << manager.dumpJson().dump() << std::endl;

    for(auto &t: v)
    {
        std::cout << t << '\t' ;
    }

    return 0;
}