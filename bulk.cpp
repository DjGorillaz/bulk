#include "bulk.h"

App::App(std::size_t size_, std::istream& in):
        size(size_), 
        inStream(in),
        currState(std::make_unique<StaticBulk>(size))
    {    }

void App::start()
{
    std::string cmd;
    while (std::getline(inStream, cmd))
    {
        currState->readString(this, cmd);
    }
    currState->printLast(this);
}

void App::setCurrent(std::unique_ptr<State>&& state)
{
    currState = std::move(state);
}

void State::print(App* app)
{
    if (currSize == 0) return;
    for (auto& e: app->exporters)
        e->print(this);
}

void State::printLast(App* app) 
{
    print(app);
}

void StaticBulk::readString(App* app, std::string& cmd)
{
    if (cmd == "{")
    {
        print(app);
        app->setCurrent(std::make_unique<DynamicBulk>(size));
    }
    else //other symbols
    {
        //Remember time of first command
        if (commands.empty())
            timeOfCreation = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        commands.emplace_back(std::move(cmd));
        ++currSize;

        //if N commands is added
        if (currSize == size)
        {
            print(app);
            commands.clear();
            currSize = 0;
        }
    }
}

void DynamicBulk::readString(App* app, std::string& cmd)
{
    if (cmd == "{")
        ++lvl;
    else if (cmd == "}")
        --lvl;
    else //other symbols
    {
        //Remember time of first command
        if (commands.empty())
            timeOfCreation = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        commands.emplace_back(std::move(cmd));
        ++currSize;
        return;
    }

    //Closing bracket
    if (lvl == 0)
    {
        print(app);
        app->setCurrent(std::make_unique<StaticBulk>(size));
    }
}