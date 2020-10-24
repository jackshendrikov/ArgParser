/*
	Base file for ArgParser project.

	24/10/2020, Jack Shendrikov

*/


#include "ArgParser.h"
#include <iostream>


// --- SET ARGUMENT ---
void ArgParser::setArgument(string short_arg, string long_arg, string descr, bool hasVal) {
	unique_ptr<Argument> arg(new Argument);
	arg->short_arg = short_arg;
	arg->long_arg = long_arg;
	arg->description = descr;
	arg->hasValue = hasVal;
	args.push_back(move(arg));

	// Set up links.
	if (!short_arg.empty()) { argNames.insert(pair<string, Argument*>(short_arg, args.back().get())); }
	if (!long_arg.empty()) { argNames.insert(pair<string, Argument*>(long_arg, args.back().get())); }
}


// --- SET ARGUMENTS ---
void ArgParser::setArguments(vector<Argument> args) {
	for (Argument a : args) {
		setArgument(a.short_arg, a.long_arg, a.description, a.hasValue);
	}
}


// --- PARSE ARGUMENTS ---
bool ArgParser::parseArguments(int argc, char** argv) {
	// First argument is the name of the executable file.
	execName = string(argv[0]);
	bool expectValue = false;
	map<string, Argument*>::const_iterator flag_it;
	for (int i = 1; i < argc; ++i) {
		// Each flag will begin with a '-' character. Multiple flags may be 
		// joined together in the same string if the flag type is in a short form.
		string entry(argv[i]);

		if (expectValue) {
			// Copy value.
			flag_it->second->value = entry;
			expectValue = false;
		}
		else if (entry.compare(0, 1, "-") == 0) {
			if (textArguments.size() > 0) {
				cerr << "Flags not allowed after text arguments." << endl;
			}

			// Parse flag.
			// Check for the long form.
			if (entry.compare(0, 2, "--") == 0) {
				// Long form of flag.
				entry.erase(0, 2); // Erase the double dash.

				flag_it = argNames.find(entry);
				if (flag_it == argNames.end()) {
					// Flag wasn't found.
					cerr << "Long flag " << entry << " wasn't found." << endl;
					return false;
				}

				// Mark as found.
				flag_it->second->parsed = true;
				++flagCounter;

				if (flag_it->second->hasValue) {
					expectValue = true; // Next argument has to be a value string.
				}
			}
			else {
				// Parse short form flag. Parsing them all sequentially. 
				// Only the last one is permitted to to have an additional value following it.
				entry.erase(0, 1); // Erase the dash.				
				for (int i = 0; i < entry.length(); ++i) {
					string k(&(entry[i]), 1);
					flag_it = argNames.find(k);
					if (flag_it == argNames.end()) {
						// Flag wasn't found.
						cerr << "Short flag " << k << " wasn't found." << endl;
						return false;
					}

					// Mark as found.
					flag_it->second->parsed = true;
					++flagCounter;

					if (flag_it->second->hasValue) {
						if (i != (entry.length() - 1)) {
							// The flag is not at the end, so it can't have value.
							cerr << "Flag " << k << " needs to be followed by a value string." << endl;
							return false;
						}
						else {
							expectValue = true; // Next argument has to be a value string.
						}
					}
				}
			}
		}
		else {
			// Add to text argument vector.
			textArguments.push_back(entry);
		}
	}

	parsed = true;

	return true;
}


// --- GET FLAG ---
bool ArgParser::getFlag(string arg_flag, string& arg_value) {
	if (!parsed) { return false; }

	map<string, Argument*>::const_iterator it = argNames.find(arg_flag);
	if (it == argNames.end()) { return false; }
	if (!it->second->parsed) { return false; }

	if (it->second->hasValue) { arg_value = it->second->value; }

	return true;
}


// --- EXISTS ---
// Returns whether the flag was found.
bool ArgParser::exists(string arg_flag) {
	if (!parsed) { return false; }

	map<string, Argument*>::const_iterator it = argNames.find(arg_flag);
	if (it == argNames.end()) { return false; }
	if (!it->second->parsed) { return false; }

	return true;
}


// --- GET TEXT ARGUMENT ---
// Updates the value parameter with the text argument if found.
bool ArgParser::getTextArgument(uint32_t index, string& value) {
	if (index < textArguments.size()) { value = textArguments.at(index); return true; }

	return false;
}


// --- PRINT HELP ---
void ArgParser::printHelp() {
	cout << endl << description << endl;
	cout << endl << "Usage:" << endl;
	cout << "\t" << usage << endl;
	cout << endl;
	cout << "Options: " << endl;

	// Determine whitespace needed between long_arg and description.
	int count = 1;
	vector<unique_ptr<Argument> >::const_iterator it;
	for (it = args.cbegin(); it != args.cend(); ++it) {
		if ((*it)->long_arg.size() > count) { count = (*it)->long_arg.size(); }
	}

	count += 3; // Number of actual spaces between the longest long_arg and description.

	// Print out the options.
	for (it = args.cbegin(); it != args.cend(); ++it) {
		if ((*it)->short_arg.empty()) {
			cout << "    --" << (*it)->long_arg;
		}
		else if ((*it)->long_arg.empty()) {
			cout << "-" + (*it)->short_arg + "    ";
		}
		else {
			cout << "-" + (*it)->short_arg + ", " << "--" << (*it)->long_arg;
		}
		cout << string(count - (*it)->long_arg.size(), ' ') << (*it)->description << endl;
	}
	cout << '\n' << endl;
}
