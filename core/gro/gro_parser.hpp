#ifndef TRYAMP_GRO_PARSER_HPP
#define TRYAMP_GRO_PARSER_HPP
#include<Amp/core/base/Parser.hpp>
#include<array>
#include<string>
#include<iostream>


namespace Amp {

class GROParser : public FileParser {


public:

	GROParser() : FileParser() {}
	GROParser(const std::string& input_filename) : FileParser(input_filename) {}
	~GROParser() = default;

protected:


	int read_ResiNum(const std::string& line) const;
	std::string read_ResiName(const std::string& line) const;
	std::string read_AtomName(const std::string& line) const;
	int read_AtomNum(const std::string& line) const;
	std::array<float, 3>& read_Coordinates(const std::string& line) const;
	std::array<float, 3>& read_Velocity(const std::string& line) const;


private:

	enum Column_Numbers {

		RESI_NUM_BEGIN = 1,
		RESI_NUM_END = 5,
		RESI_NAME_BEGIN = 6,
		RESI_NAME_END = 10,
		ATOM_NAME_BEGIN = 11,
		ATOM_NAME_END = 15,
		ATOM_NUM_BEGIN = 16,
		ATOM_NUM_END = 20,
		COORD_X_BEGIN = 21,
		COORD_X_END = 28,
		COORD_Y_BEGIN = 29,
		COORD_Y_END = 36,
		COORD_Z_BEGIN = 37,
		COORD_Z_END = 44,
		VELO_X_BEGIN = 45,
		VELO_X_END = 52,
		VELO_Y_BEGIN = 53,
		VELO_Y_END = 60,
		VELO_Z_BEGIN = 61,
		VELO_Z_END = 68,

	};

	template<Column_Numbers Begin, Column_Numbers End>
	std::string readline_range_of(const std::string& line) const {
		static_assert((Begin <= End && (Begin > 0)),
			"ReadLine Range is not valid. Begin <= 0 or Begin > End");
		constexpr int line_length = End - (Begin - 1);
		constexpr int begin_index = Begin - 1;
		const std::string& retval = line.substr(begin_index, line_length);
		return retval;
	}

};


int GROParser::read_ResiNum(const std::string& line) const {
	const std::string& buffer = readline_range_of<RESI_NUM_BEGIN, RESI_NUM_END>(line);
	return std::stoi(buffer);
}


std::string GROParser::read_ResiName(const std::string& line) const {
	return readline_range_of<RESI_NAME_BEGIN, RESI_NAME_END>(line);
}


std::string GROParser::read_AtomName(const std::string& line) const {
	return readline_range_of<ATOM_NAME_BEGIN, ATOM_NAME_END>(line);
}


int GROParser::read_AtomNum(const std::string& line) const {
	const std::string& buffer = readline_range_of<ATOM_NUM_BEGIN, ATOM_NUM_END>(line);
	return std::stoi(buffer);
}


std::array<float, 3> GROParser::read_Coordinates(const std::string& line) const {
	if (line.size() < COORD_Z_END)
		throw std::runtime_error(
			"Line size is smaller than 44.
			The gro file format is broken, or you access an invalid line on the file.
			Check line: '" + line + "'.");
	
	const std::string& buffer_codx = readline_range_of<COORD_X_BEGIN, COORD_X_END>(line);
	const std::string& buffer_cody = readline_range_of<COORD_Y_BEGIN, COORD_Y_END>(line);
	const std::string& buffer_codz = readline_range_of<COORD_Z_BEGIN, COORD_Z_END>(line);
	const std::array<float, 3>& retval = {
		std::stof(buffer_codx),
		std::stof(buffer_cody),
		std::stof(buffer_codz)
	};
	return retval;
}


std::array<float, 3> GROParser::read_Velocity(const std::string& line) const {
	if (line.size() < VELO_Z_END)
		throw std::runtime_error(
			"Line size is smaller than 68.
			The gro file format is broken, or you access an invalid line on the file.
			Check line: '" + line + "'.");
	
	const std::string& buffer_velox = readline_range_of<VELO_X_BEGIN, VELO_X_END>(line);
	const std::string& buffer_veloy = readline_range_of<VELO_Y_BEGIN, VELO_Y_END>(line);
	const std::string& buffer_veloz = readline_range_of<VELO_Z_BEGIN, VELO_Z_END>(line);
	const std::array<float, 3>& retval = {
		std::stof(buffer_velox),
		std::stof(buffer_veloy),
		std::stof(buffer_veloz)
	};
	return retval;
}


#endif /* TRYAMP_GRO_PARSER_HPP */
