#include <iostream>
#include "libraries/enigma.h" // eng namespace

using namespace eng; // Enigma stuff namespace

// constants:
const std::string DISKS_PATH = "disks/";
const std::string REFLECTORS_PATH = "reflectors/";
const std::string SETTINGS_PATH = "settings.txt";
const std::string HELP_FILE_NAME = "help.info";
const std::string VERSION_FILE_NAME = "version.info";
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// structures / classes:



// functions:

void load_settings(Enigma* enigma, std::string settings_path)
{
	std::fstream settings_file;
	int connections[STD_ALPHA_LEN];
	std::string file_name;
	
	settings_file.open(settings_path, std::ios::in);

	for (int i = 0; i < STANDARD_DISKS_AMOUNT; i++)
	{
		do {
			settings_file >> file_name;
		} while (file_name[0] == '#');
		
		file_name = DISKS_PATH + file_name + ".rtr";
		enigma->load_connections(file_name, connections);
		enigma->add_disk(connections);
	}

	do {
		settings_file >> file_name;
	} while (file_name[0] == '#');

	file_name = REFLECTORS_PATH + file_name + ".rtr";
	enigma->load_connections(file_name, connections);
	enigma->set_reflector(connections);
	
	settings_file.close();
}

void cmd(int argc, char** argv, Enigma* enigma)
{
	std::vector<std::string> arguments = hq::cmd::separate_args(argc, argv);
	std::string argument;
	
	for (int i = 0; i < arguments.size(); i++)
	{
		argument = arguments[i];

		if (argument == "-h" || argument == "--help")
		{
			std::cout << hq::read_file(HELP_FILE_NAME);
		}
		else if (argument == "-v" || argument == "--version")
		{
			std::cout << hq::read_file(VERSION_FILE_NAME);
		}
		else if (i < arguments.size() - 1) // if it's not last provided input/parameter
		{
			if (argument == "-f" || argument == "--file")
			{
				i++; // we now gonna read value of the parameter
				std::string input_text = hq::read_file(arguments[i]);
				std::cout << enigma->encrypt_message(input_text);
			}
			else if (argument == "-t" || argument == "--text")
			{
				i++; // we now gonna read value of the parameter
				std::string input_text = arguments[i];
				std::cout << enigma->encrypt_message(input_text);
			}
		}
		else if (argument == "-s" || argument == "--setings")
		{
			
		}
		else
		{
			std::cout << "#Incorrect command use!";
		}
	}
}

int main(int argc, char** argv)
{
	// machine declaration:
	Enigma enigma(ALPHABET);
	
	load_settings(&enigma, SETTINGS_PATH);
	cmd(argc, argv, &enigma);
	
	return 0;
}