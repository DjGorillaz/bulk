#pragma once

#include <iostream>
#include <istream>
#include <memory>
#include <list>
#include <chrono>

#include "exporter.h"

class State;

class App
{
public:
    App(std::size_t size_, std::istream& in = std::cin);
    void start();
    void setCurrent(std::unique_ptr<State>&& state);
    std::list<std::unique_ptr<Exporter>> exporters;
private:
    std::istream& inStream;
    std::size_t size;
    std::unique_ptr<State> currState;
};

class State
{
    friend class Console;
    friend class File;
public:
    State(std::size_t size_): size(size_) { }
    ~State() = default;
    virtual void readString(App*, std::string&) = 0;
    virtual void print(App* app);
    virtual void printLast(App* app);
protected:
    std::size_t size = 0;
    std::size_t currSize = 0;
    std::list<std::string> commands;
    std::size_t timeOfCreation;
};

class StaticBulk: public State
{
public:
    StaticBulk(std::size_t& size_): State(size_) { }
    void readString(App* app, std::string& cmd) override;
};

class DynamicBulk: public State
{
public:
    DynamicBulk(std::size_t& size_): State(size_) { }
    void readString(App* app, std::string& cmd) override;
    void printLast(App*) override { /*empty*/ }
private:
    unsigned int lvl = 1;
};
