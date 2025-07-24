#pragma once

class Player;

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void Execute(Player* player) = 0;
};

// Forward declarations for concrete commands
class MoveUpCommand;
class MoveDownCommand;
class MoveLeftCommand;
class MoveRightCommand;
class JumpCommand;
class RollCommand;
class AimCommand;
class StopAimCommand;

