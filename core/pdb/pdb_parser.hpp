#ifndef TRYAMP_PDB_PARSER_HPP
#define TRYAMP_PDB_PARSER_HPP
#include<TryAmp/core/base/Parser.hpp>
#include<array>
#include<string>
#include<iostream>



namespace Amp {


class PDBParser : public FileParser {

public:

	PDBParser() : FileParser() {}
	PDBParser(const std::string& input_filename) : FileParser(input_filename) {}
	~PDBParser() = default;



protected:

	std::string read_RecordName(const std::string& line) const;

	int read_SerialNum(const std::string& line) const;
	std::string read_AtomName(const std::string& line) const;
	char read_AltLoc(const std::string& line) const;
	std::string read_ResidueName(const std::string& line) const;
	char read_ChainID(const std::string& line) const;
	int read_ResiSeqNum(const std::string& line) const;
	char read_InsertCode(const std::string& line) const;
	std::array<float, 3> read_Coordinate(const std::string& line) const;
	float read_Occupancy(const std::string& line) const;
	float read_TemperatureFactor(const std::string& line) const;
	std::string read_Element(const std::string& line) const;
	float read_Charge(const std::string& line) const;


private:

	enum Column_numbers {
	
	RECORD_NAME_BEGIN = 1,
	RECORD_NAME_TER_END = 3,
	RECORD_NAME_END = 6,
	SERIAL_NUM_BEGIN = 7,
	SERIAL_NUM_END = 11,
	ATOM_NAME_BEGIN = 13,
	ATOM_NAME_END = 16,
	ALTLOC = 17,
	RESIDUE_NAME_BEGIN = 18,
	RESIDUE_NAME_END = 20,
	CHAIN_ID = 22,
	RESIDUE_SEQ_NUM_BEGIN = 23,
	RESIDUE_SEQ_NUM_END = 26,
	INSERT_CORD = 27,
	CORD_X_BEGIN = 31,
	CORD_X_END = 38,
	CORD_Y_BEGIN = 39,
	CORD_Y_END = 46,
	CORD_Z_BEGIN = 47,
	CORD_Z_END = 54,
	OCCUPANCY_BEGIN = 55,
	OCCUPANCY_END = 60,
	TEMP_FACTOR_BEGIN = 61,
	TEMP_FACTOR_END = 66,
	ELEMENT_BEGIN = 77,
	ELEMENT_END = 78,
	CHARGE_BEGIN = 79,
	CHARGE_END = 80,
	};


	template<Column_numbers Begin, Column_numbers End>
	std::string readline_range_of(const std::string& line) const {
		static_assert((Begin <= End && (Begin > 0)),
			"ReadLine Range is not valid. Begin > End or Begin <= 0");
		constexpr int line_length = End - (Begin - 1);
		constexpr int begin_index = Begin - 1;
		const std::string& retval = line.substr(begin_index, line_length);
		return retval;
	}


};









std::string PDBParser::read_RecordName(const std::string& line) const {
	const std::string& buffer = readline_range_of<RECORD_NAME_BEGIN, RECORD_NAME_TER_END>(line);
	std::string retval;
	if (buffer == "TER") retval = "TER";
	else retval = readline_range_of<RECORD_NAME_BEGIN, RECORD_NAME_END>(line);

	return retval;
}


int PDBParser::read_SerialNum(const std::string& line) const {
	const std::string& buffer = readline_range_of<SERIAL_NUM_BEGIN, SERIAL_NUM_END>(line);
	const int& retval = std::stoi(buffer);
	return retval;
}


std::string PDBParser::read_AtomName(const std::string& line) const {
	return readline_range_of<ATOM_NAME_BEGIN, ATOM_NAME_END>(line);
}


char PDBParser::read_AltLoc(const std::string& line) const {
	const std::string& buffer = readline_range_of<ALTLOC, ALTLOC>(line);
	const char retval = *buffer.c_str();
	return retval;
}


std::string PDBParser::read_ResidueName(const std::string& line) const {
	return readline_range_of<RESIDUE_NAME_BEGIN, RESIDUE_NAME_END>(line);
}


char PDBParser::read_ChainID(const std::string& line) const {
	const std::string& buffer = readline_range_of<CHAIN_ID, CHAIN_ID>(line);
	const char retval = *buffer.c_str();
	return retval;
}


int PDBParser::read_ResiSeqNum(const std::string& line) const {
	const std::string& buffer = readline_range_of<RESIDUE_SEQ_NUM_BEGIN, RESIDUE_SEQ_NUM_END>(line);
	const int& retval = std::stoi(buffer);
	return retval;
}


char PDBParser::read_InsertCode(const std::string& line) const {
	const std::string& buffer = readline_range_of<INSERT_CORD, INSERT_CORD>(line);
	const char retval = *buffer.c_str();
	return retval;
}


std::array<float, 3> PDBParser::read_Coordinate(const std::string& line) const {
	const std::string& buffer_codx = readline_range_of<CORD_X_BEGIN, CORD_X_END>(line);
	const std::string& buffer_cody = readline_range_of<CORD_Y_BEGIN, CORD_Y_END>(line);
	const std::string& buffer_codz = readline_range_of<CORD_Z_BEGIN, CORD_Z_END>(line);
	const std::array<float, 3>& retval{
		std::stof(buffer_codx),
		std::stof(buffer_cody),
		std::stof(buffer_codz)
	};
	return retval;
}


float PDBParser::read_Occupancy(const std::string& line) const {
	const std::string& buffer = readline_range_of<OCCUPANCY_BEGIN, OCCUPANCY_END>(line);
	const float& retval = std::stof(buffer);
	return retval;
}


float PDBParser::read_TemperatureFactor(const std::string& line) const {
	const std::string& buffer = readline_range_of<TEMP_FACTOR_BEGIN, TEMP_FACTOR_END>(line);
	const float& retval = std::stof(buffer);
	return retval;
}


std::string PDBParser::read_Element(const std::string& line) const {
	return readline_range_of<ELEMENT_BEGIN, ELEMENT_END>(line);
}


float PDBParser::read_Charge(const std::string& line) const {
	const std::string& buffer = readline_range_of<CHARGE_BEGIN, CHARGE_END>(line);
	const float& retval = (buffer == "  ") ? 0. : std::stof(buffer);
	return retval;
}


}

#endif /* TRYAMP_PDB_PARSER_HPP */
