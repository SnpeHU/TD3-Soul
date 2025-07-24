#pragma once
#include "ICommand.h"

class Player;

// Movement Commands
class MoveUpCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

class MoveDownCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

class MoveLeftCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

class MoveRightCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

// Action Commands
class JumpCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

class RollCommand : public ICommand
{
public:
public:
    void Execute(Player* player) override;
};

class AimCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};

class StopAimCommand : public ICommand
{
public:
    void Execute(Player* player) override;
};