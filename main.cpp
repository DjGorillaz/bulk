#include <iostream>
#include <fstream>
#include <utility>
#include <memory>

#include "bulk.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: bulk count";
        return 0;
    }

    try
    {
        App app(std::atoi(argv[1]));
        app.exporters.emplace_back(std::make_unique<Console>());
        app.exporters.emplace_back(std::make_unique<File>());
        app.start();
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what();
    }

    std::cin.get();
    return 1;
}