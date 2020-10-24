/*
	Header file for ArgParser project.

	24/10/2020, Jack Shendrikov

*/

#include <vector>
#include <memory>
#include <string>
#include <map>

using namespace std;

struct Argument {
	Argument() : hasValue(false), parsed(false) {}
	string short_arg;
	string long_arg;
	string description;
	bool hasValue;
	string value;
	bool parsed;
};


class ArgParser {
	vector<unique_ptr<Argument>> args;
	map<string, Argument*> argNames;
	bool parsed = false;
	int flagCounter = 0;
	string execName;
	string description;
	string usage;
	vector<string> textArguments;

public:
	void setArgument(string short_arg, string long_arg, string descr, bool hasVal);
	void setArguments(vector<Argument> args);
	bool parseArguments(int argc, char** argv);
	bool getFlag(string arg_flag, string& arg_value);
	bool exists(string arg_flag);
	bool getTextArgument(uint32_t index, string& value);
	void printHelp();
	void setDescription(string descr) { this->description = descr; }
	void setUsage(string use) { this->usage = use; }
	int flagCount() { return flagCounter; }
	string executableName() { return execName; }
};
