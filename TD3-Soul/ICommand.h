#pragma once

class Player;

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void Execute(Player* player) = 0;
};


