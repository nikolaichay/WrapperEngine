#pragma once
#include "Wrapper.h"

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	Engine(Engine const&) = delete;
	Engine(Engine&&) = default;

	Engine& operator =(Engine const&) = delete;
	Engine& operator =(Engine&&) = default;

	void regCommand(Wrapper* wrap, const std::string& nameCom);
	int executeCom(const std::string& nameCom, const std::map<std::string, int>& arg);

private:
	std::map<std::string, Wrapper*> funcs;
};