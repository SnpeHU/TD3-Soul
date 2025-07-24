#include "PlayerCommands.h"
#include "Object/Player.h"

void MoveUpCommand::Execute(Player* player)
{
    if (player) {
        player->SetMoveUp(true);
    }
}

void MoveDownCommand::Execute(Player* player)
{
    if (player) {
        player->SetMoveDown(true);
    }
}

void MoveLeftCommand::Execute(Player* player)
{
    if (player) {
        player->SetMoveLeft(true);
    }
}

void MoveRightCommand::Execute(Player* player)
{
    if (player) {
        player->SetMoveRight(true);
    }
}

void JumpCommand::Execute(Player* player)
{
    if (player) {
        player->SetJump(true);
    }
}

void RollCommand::Execute(Player* player)
{
    if (player) {
        player->SetRoll(true);
    }
}

void AimCommand::Execute(Player* player)
{
    if (player) {
        player->SetAim(true);
    }
}

void StopAimCommand::Execute(Player* player)
{
    if (player) {
        player->SetAim(false);
    }
}