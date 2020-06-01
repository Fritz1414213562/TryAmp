#ifndef TRYAMP_WRITER_BASE_HPP
#define TRYAMP_WRITER_BASE_HPP
#include<fstream>
#include<vector>
#include<iostream>
#include<string>
#include<type_traits>

namespace Amp {

class FileWriter {

public:

	FileWriter() = default;
	FileWriter(const std::string& outputfile_name) : output_name(outputfile_name) {
		open();
	}

	~FileWriter() = default;

	void open(const std::string& outputfile_name) {
		output_name = outputfile_name;
		open();
	}

	void close() {if (output_file.is_open()) output_file.close();}

	const std::string name() {return output_name;}

protected:

	std::ofstream output_file;

	void open() {
		close();
		output_file.open(output_name);
		if (!output_file.is_open()) {
			std::cerr << "The file, " << output_name << " could not be found." << std::endl;;
			std::exit(1);
		}
	}



private:

//	const char comment_out_char = '*';
//	const char delimiter = ' ';
	std::string output_name;

};

}

#endif /* TRYAMP_WRITER_BASE_HPP */
