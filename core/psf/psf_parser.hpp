#ifndef TRYAMP_PSF_PARSER_HPP
#define TRYAMP_PSF_PARSER_HPP
#include<TryAmp/core/base/Parser.hpp>
#include<fstream>
#include<iostream>
#include<array>
#include<vector>


namespace Amp {

class PSFParser : public FileParser {

public:
	PSFParser() : FileParser() {}
	PSFParser(const std::string& filename) : FileParser(filename) {}
	~PSFParser() = default;


protected:


	const std::size_t read_BlockNum(const std::string& line) {
		const std::string& buffer = readline_rangeof<BLOCK_NUMBER_BEGIN, BLOCK_NUMBER_END>(line);
		return std::stoi(buffer);
	}


	const std::string read_BlockKind(const std::string& line) {
		return readline_rangeof<BLOCK_KIND_BEGIN, BLOCK_KIND_END>(line); 
	}


	const int read_AtomID(const std::string& line) {
		const std::string& buffer = readline_rangeof<ATOM_ID_BEGIN, ATOM_ID_END>(line);
		return std::stoi(buffer);
	}


	const std::string read_SegmentName(const std::string& line) {
		return readline_rangeof<SEGMENT_NAME_BEGIN, SEGMENT_NAME_END>(line);
	}


	const int read_ResidueID(const std::string& line) {
		const std::string& buffer = readline_rangeof<RESIDUE_ID_BEGIN, RESIDUE_ID_END>(line);
		return std::stoi(buffer);
	}


	const std::string read_ResidueName(const std::string& line) {
		return readline_rangeof<RESIDUE_NAME_BEGIN, RESIDUE_NAME_END>(line);
	}


	const std::string read_AtomName(const std::string& line) {
		return readline_rangeof<ATOM_NAME_BEGIN, ATOM_NAME_END>(line);
	}


	const std::string read_AtomType(const std::string& line) {
		return readline_rangeof<ATOM_TYPE_BEGIN, ATOM_TYPE_END>(line);
	}


	const float read_Charge(const std::string& line) {
		const std::string& buffer = readline_rangeof<CHARGE_BEGIN, CHARGE_END>(line);
		return std::stof(buffer);
	}


	const float read_Mass(const std::string& line) {
		const std::string& buffer = readline_rangeof<MASS_BEGIN, MASS_END>(line);
		return std::stof(buffer);
	}


	const int read_UnusedZero(const std::string& line) {
		const std::string& buffer = readline_rangeof<UNUSED_ZERO_BEGIN, UNUSED_ZERO_END>(line);
		return std::stoi(buffer);
	}


	const std::vector<std::array<int, 2>> read_BondLine(const std::string& line) {
		const std::vector<std::array<int, 2>>& result = read_AtomOrder<2>(line);
		return result;
	}



private:
	

	enum COLUMN_MEANINGS {
		// header
		BLOCK_NUMBER_BEGIN = 1,
		BLOCK_NUMBER_END = 8,
		BLOCK_KIND_BEGIN = 10,
		BLOCK_KIND_END = 15,

		// contents in ATOM block
		ATOM_ID_BEGIN = 1,
		ATOM_ID_END = 8,
		SEGMENT_NAME_BEGIN = 11,
		SEGMENT_NAME_END = 13,
		RESIDUE_ID_BEGIN = 15,
		RESIDUE_ID_END = 18,
		RESIDUE_NAME_BEGIN = 21,
		RESIDUE_NAME_END = 23,
		ATOM_NAME_BEGIN = 25,
		ATOM_NAME_END = 28,
		ATOM_TYPE_BEGIN = 30,
		ATOM_TYPE_END = 33,
		CHARGE_BEGIN = 36,
		CHARGE_END = 44,
		MASS_BEGIN = 51,
		MASS_END = 58,
		UNUSED_ZERO_BEGIN = 70,
		UNUSED_ZERO_END = 70,

		// order block
		ORDER_COLUMN_SIZE = 8,

	};

	template<COLUMN_MEANINGS start, COLUMN_MEANINGS end>
	const std::string readline_rangeof(const std::string& line) {
		const int& line_length = end - (start - 1);
		const std::string& res = line.substr(start - 1, line_length);
		return res;
	}

	template<std::size_t pair_size>
	const std::vector<std::array<int, pair_size>> read_AtomOrder(const std::string& line) {
		constexpr std::size_t COLUMN_SIZE = static_cast<int>(ORDER_COLUMN_SIZE);
		constexpr std::size_t INTERVAL_SIZE = pair_size * COLUMN_SIZE;

		std::vector<std::array<int, pair_size>> result;
		const std::size_t& line_length = COLUMN_SIZE * (line.size() / COLUMN_SIZE);

		for (std::size_t pos_of_id = 0; pos_of_id < line_length; pos_of_id += INTERVAL_SIZE) {
			std::array<int, pair_size> pair_set;
			for (std::size_t i_pair = 0; i_pair < pair_size; ++i_pair) {
				const int& atom_id = std::stoi(line.substr(pos_of_id + i_pair * COLUMN_SIZE, COLUMN_SIZE));
				pair_set[i_pair] = atom_id;
			}
			result.push_back(pair_set);
		}

		return result;
	}



};
}

#endif /* TRYAMP_PSF_PARSER_HPP */
