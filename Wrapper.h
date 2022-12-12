#pragma once
#include <vector>
#include <exception>
#include <map>
#include <functional>
#include <string>

template<typename Obj, typename ...Args>
using method = int(Obj::*)(Args...);

class Wrapper
{
public:
	Wrapper() = delete;
	~Wrapper() = default;

	Wrapper(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;
	Wrapper& operator =(Wrapper const&) = delete;
	Wrapper& operator =(Wrapper&&) = default;

	template<typename Subj, typename... arg>
	Wrapper(Subj* subj, method<Subj, arg...> func, const std::vector < std::pair<std::string, int>>& args) {
		if (subj == nullptr || func == nullptr || args.size() != sizeof...(arg)) {
			throw std::exception("Wrapper exception: invalid argument");
		}
		caller = [this, &subj, func](const std::vector<int>& argFunc) {
			return executeFunc(subj, func, argFunc, std::make_index_sequence<sizeof...(arg)>{});
		};
	}
	int execute(const std::map<std::string, int>& argMap);
private:
	bool isExist(std::string name) {
		for (auto& n : nameArg) {
			if (n.compare(name) == 0)
				return true;
		}
		return false;
	}
	template<typename Subj, typename FuncName, int... Ind>
	int executeFunc(Subj* subj, FuncName funcName, const std::vector<int>& args, const std::index_sequence<Ind...>&) {
		return ((subj->*funcName)(args[Ind]...));
	}
	std::function<int(std::vector<int>&)> caller;
	std::vector<std::string> nameArg;
};