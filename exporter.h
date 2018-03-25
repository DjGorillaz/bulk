#pragma once

#include <sstream>
#include <iostream>

class State;

class Exporter
{
public:
    virtual void print(State* state) = 0;
};

class Console: public Exporter
{
public:
    Console(std::ostream& ss_ = std::cout): ss(ss_) { }
    void print(State* state) override;
private:
    std::ostream& ss;
};

class File: public Exporter
{
public:
    void print(State* state) override;
};
