#ifndef TRYAMP_PARSER_BASE_HPP
#define TRYAMP_PARSER_BASE_HPP
#include<fstream>
#include<vector>
#include<iostream>
#include<string>
#include<type_traits>

namespace Amp {

class FileParser {

public:

	FileParser() = default;
	FileParser(const std::string& inputfile_name) : input_name(inputfile_name) {
		open();
	}

	~FileParser() = default;

	void open(const std::string& inputfile_name) {
		load(inputfile_name);
		open();
	}

	void close() {if (input_file.is_open()) input_file.close();}

	const std::string name() {return input_name;}

protected:

	std::ifstream input_file;

	void open() {
		close();
		input_file.open(input_name);
		if (!input_file.is_open()) {
			std::cerr << "The file, " << input_name << " could not be found." << std::endl;;
			std::exit(1);
		}
	}


	void load(const std::string& file_name) {input_name = file_name;}



private:

//	const char comment_out_char = '*';
//	const char delimiter = ' ';
	std::string input_name;

};

}

#endif /* TRYAMP_PARSER_BASE_HPP */
