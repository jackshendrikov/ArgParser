/*
	Main test file for ArgParser project.

	24/10/2020, Jack Shendrikov

*/


#include "ArgParser.h"

#include <iostream>


int main(int argc, char** argv) {
	ArgParser argparse;

	argparse.setArgument("h", "help", "See Help.", false);
	argparse.setArgument("v", "version", "Print version information.", false);
	argparse.setArgument("n", "number", "Print number, any number.", true);
	argparse.setArgument("l", "list", "Print list content.", true);
	argparse.setArgument("", "elf", "Elves only come in long (tall) form, there are no short elves.", false);
	argparse.setArgument("d", "", "D is for dwarfs. They are only in short form.", false);
	argparse.setDescription("Test for ArgParser project.");
	argparse.setUsage("./main_test <options>");

	if (!argparse.parseArguments(argc, argv)) {
		cerr << "Couldn't parse arguments..." << endl;
		return 1;
	}

	cout << "Number of flags found: " << argparse.flagCount() << endl;

	if (argparse.exists("help")) {
		argparse.printHelp();
		cout << "Arg: help" << endl;
	}

	if (argparse.exists("version")) {
		cout << "Arg: version" << endl;
	}
	
	if (argparse.exists("elf")) {
		cout << "Arg: elf" << endl;
	}

	if (argparse.exists("d")) {
		cout << "Arg: dwarf" << endl;
	}
	
	string number;
	if (argparse.getFlag("number", number)) {
		cout << "Arg: number " << number << endl;
	}

	string list;
	if (argparse.getFlag("list", list)) {
		cout << "Arg: list " << list << endl;
	}

	string textarg;
	if (argparse.getTextArgument(0, textarg)) {
		cout << "Got text argument: " << textarg << endl;
	}

	return 0;
}

