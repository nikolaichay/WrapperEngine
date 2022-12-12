#include <iostream>
#include "Engine.h"
#include "Subject.h"
using namespace std;
int main()
{
	Subject sub;
	Wrapper wrap1(&sub, &Subject::F1, { {"arg1", 0},{"arg2", 0} });
	Wrapper wrap2(&sub, &Subject::F2, { {"arg1", 0} });
	Wrapper wrap3(&sub, &Subject::F3, { {"arg1", 0},{"arg2", 0},{"arg3", 0},{"arg4", 0} });
	try {
		Subject* nullsub = nullptr;
		Wrapper exc_wrapper_nullsubj(nullsub, &Subject::F3, { { "arg1",0 }, { "arg2", 0 }, { "arg3", 0 },{"arg4", 0} });
	}
	catch (exception& exc) {
		cout << exc.what() << endl;
	}
	try {
		Subject subj;
		Wrapper exc_wrapper_arg_count(&subj, &Subject::F2, { { "arg1",0 }, { "arg2", 0 }, { "arg3", 0 } });
	}
	catch (exception& exc) {
		cout << exc.what() << endl;
	}
	try {
		Engine engine;
		Wrapper* wrapper_null_command = nullptr;
		engine.regCommand(wrapper_null_command, "wrapper_nullptr_command");
	}
	catch (exception& exc) {
		cout << exc.what() << endl;
	}
	try {
		Engine engine;
		engine.regCommand(&wrap1, "Com1");
		engine.regCommand(&wrap1, "Com1");
	}
	catch (exception& exc) {
		cout << exc.what() << endl;
	}
	try {
		Engine engine;
		engine.executeCom("unknown_command", { {"arg1",0 } });
	}
	catch (exception& exc) {
		cout << exc.what() << endl;
	}
	Engine eng;
	eng.regCommand(&wrap1, "Com1");
	eng.regCommand(&wrap2, "Com2");
	eng.regCommand(&wrap3, "Com3");
	cout << eng.executeCom("Com1", { {"arg1", 3},{"arg2", 4} }) << " " << eng.executeCom("Com2", { {"arg1", 2} }) << " " <<
		eng.executeCom("Com3", { {"arg1", 3},{"arg2", 4}, {"arg3", 3},{"arg4", 4} }) << endl;
	return 0;
}
