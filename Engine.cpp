#include "Engine.h"

void Engine::regCommand(Wrapper* wrap, const std::string& nameCom) {
	if (wrap == nullptr) {
		throw std::exception("Engine exception: Command not exist");
	}
	if (funcs[nameCom] != nullptr) {
		throw std::exception("Engine exception: This command already exist");
	}
	funcs[nameCom] = wrap;
}
int Engine::executeCom(const std::string& nameCom, const std::map<std::string, int>& arg) {
	auto comm = funcs[nameCom];
	if (comm == nullptr) {
		throw std::exception("Engine exception: This command is not registred");
	}
	return comm->execute(arg);
}