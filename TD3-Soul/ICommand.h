#pragma once
class ICommand
{
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
};

