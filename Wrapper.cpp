#include "Wrapper.h"
using namespace std;
int Wrapper::execute(const std::map<std::string, int>& argMap) {
	std::vector<int> argsVec;
	for (auto& arg : argMap) {
		if (Wrapper::isExist(arg.first)) {
			throw std::exception("Wrapper exception: This command is not init");
		}
		argsVec.push_back(arg.second);
	}
	return caller(argsVec);
}
