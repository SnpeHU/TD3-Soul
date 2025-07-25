#include "InputHandler.h"
#include "Object/Player.h"
#include "Novice.h"

InputHandler::InputHandler()
{

    moveUpCommand = std::make_unique<MoveUpCommand>();
    moveDownCommand = std::make_unique<MoveDownCommand>();
    moveLeftCommand = std::make_unique<MoveLeftCommand>();
    moveRightCommand = std::make_unique<MoveRightCommand>();
    jumpCommand = std::make_unique<JumpCommand>();
    rollCommand = std::make_unique<RollCommand>();
    aimCommand = std::make_unique<AimCommand>();
    stopAimCommand = std::make_unique<StopAimCommand>();

    InitializeDefaultBindings();
}

InputHandler::~InputHandler() = default;

void InputHandler::InitializeDefaultBindings()
{

    keyBindings[DIK_W] = moveUpCommand.get();
    keyBindings[DIK_S] = moveDownCommand.get();
    keyBindings[DIK_A] = moveLeftCommand.get();
    keyBindings[DIK_D] = moveRightCommand.get();
    keyBindings[DIK_SPACE] = jumpCommand.get();
}

void InputHandler::HandleInput(char* keys, char* prekeys, Player* player)
{
	(void)prekeys;
    if (!player || player->GetIsDead()) {
        return;
    }

    player->ResetMovementFlags();

    for (const auto& binding : keyBindings) {
        int key = binding.first;
        ICommand* command = binding.second;

        if (keys[key]) {
            command->Execute(player);
        }
    }

    if (Novice::IsTriggerMouse(1)) {
        rollCommand->Execute(player);
    }

    if (Novice::IsPressMouse(0)) {
        aimCommand->Execute(player);
    } else if (player->GetIsAiming()) {
        stopAimCommand->Execute(player);
    }
}

void InputHandler::BindCommand(int key, std::unique_ptr<ICommand> command)
{
    keyBindings[key] = command.get();
}