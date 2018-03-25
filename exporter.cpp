#include <fstream>

#include "exporter.h"
#include "bulk.h"

void Console::print(State* state)
{
    std::string d = " ";
    ss << "bulk:";
    for(auto c: state->commands)
    {
        ss << d << c;
        d = ", ";
    }  
    ss << std::endl;
}

void File::print(State* state)
{
    std::string fileName = "bulk" + std::to_string(state->timeOfCreation) + ".log";
    std::ofstream outputFile;
    outputFile.open(fileName);
    Console cons(outputFile);
    cons.print(state);
    outputFile.close();
}