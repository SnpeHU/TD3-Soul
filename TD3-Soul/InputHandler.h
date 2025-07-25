#pragma once
#include "ICommand.h"
#include "PlayerCommands.h"
#include <memory>
#include <unordered_map>

class Player;

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void HandleInput(char* keys, char* prekeys, Player* player);
    void BindCommand(int key, std::unique_ptr<ICommand> command);

private:
    // プレーヤー命令集合
    std::unique_ptr<MoveUpCommand> moveUpCommand;
    std::unique_ptr<MoveDownCommand> moveDownCommand;
    std::unique_ptr<MoveLeftCommand> moveLeftCommand;
    std::unique_ptr<MoveRightCommand> moveRightCommand;
    std::unique_ptr<JumpCommand> jumpCommand;
    std::unique_ptr<RollCommand> rollCommand;
    std::unique_ptr<AimCommand> aimCommand;
    std::unique_ptr<StopAimCommand> stopAimCommand;

	// マップでキーとコマンドを保存
    std::unordered_map<int, ICommand*> keyBindings;
    
    void InitializeDefaultBindings();
};