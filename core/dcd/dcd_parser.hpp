// This class is a parser class for dcd binary file.
//-------------------------------------------------------------------------------
// include guard
#ifndef TRYAMP_DCD_PARSER_HPP
#define TRYAMP_DCD_PARSER_HPP

//-------------------------------------------------------------------------------
// includes

#include<TryAmp/core/base/Parser.hpp>
#include<TryAmp/core/dcd/dcd_data_type/dcd_1stheader.hpp>
#include<TryAmp/core/dcd/dcd_data_type/dcd_2ndheader.hpp>
#include<TryAmp/core/dcd/dcd_data_type/dcd_3rdheader.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdint>
#include<cstring>
#include<array>

//-------------------------------------------------------------------------------
// namespace
namespace Amp {
//-------------------------------------------------------------------------------
// header


class DCDParser : public FileParser {

public :
	DCDParser() : FileParser() {}
	DCDParser(const std::string& input_file_name) : FileParser(input_file_name) {}
	~DCDParser() = default;


protected :

	std::size_t frame_num = 0;
	std::size_t atom_num = 0;

	DCD_1stHeader dcd_header1;
	DCD_2ndHeader dcd_header2;
	DCD_3rdHeader dcd_header3;

	bool is_read_headers = false;


	

	std::array<std::vector<float>, 3> read_xyz() {
		const std::string& x_block = read_block();
		const std::string& y_block = read_block();
		const std::string& z_block = read_block();
		std::array<std::vector<float>, 3> xyz;
		xyz[0] = read_coordinates(x_block);
		xyz[1] = read_coordinates(y_block);
		xyz[2] = read_coordinates(z_block);

		return xyz;
	}


	void read_num_frame_and_atom() {

		open();
		is_read_headers = true;
		const std::string& first_block = read_block();
		dcd_header1 = parse_1st_header(first_block);
		read_frame_num(first_block);

		const std::string& second_block = read_block();
		dcd_header2 = parse_2nd_header(second_block);

		const std::string& third_block = read_block();
		read_atom_num(third_block);
		dcd_header3 = parse_3rd_header();
		std::cout << "frame number = " << frame_num << std::endl;
		std::cout << "atom number = " << atom_num << std::endl;

//		for (const std::string& header : headers) {
//			std::cout << header << std::endl;
//		}

	}


	DCD_1stHeader parse_1st_header(const std::string& block_1) {

		const std::string& signature = {
			read_binary_as<char>(&block_1.at(0)),
			read_binary_as<char>(&block_1.at(1)),
			read_binary_as<char>(&block_1.at(2)),
			read_binary_as<char>(&block_1.at(3))
		};
		const int& nframes = read_binary_as<int>(&block_1.at(4));
		const int& istart = read_binary_as<int>(&block_1.at(8));
		const int& nstep_save = read_binary_as<int>(&block_1.at(12));
		const int& nsteps = read_binary_as<int>(&block_1.at(16));
		const int& nunits = read_binary_as<int>(&block_1.at(20));

		const std::array<int, 4>& zero4 = {
			read_binary_as<int>(&block_1.at(24)),
			read_binary_as<int>(&block_1.at(28)),
			read_binary_as<int>(&block_1.at(32)),
			read_binary_as<int>(&block_1.at(36))
		};

		const float& delta = read_binary_as<float>(&block_1.at(40));
		const std::array<int, 9>& zero9 = {
			read_binary_as<int>(&block_1.at(44)),
			read_binary_as<int>(&block_1.at(48)),
			read_binary_as<int>(&block_1.at(52)),
			read_binary_as<int>(&block_1.at(56)),
			read_binary_as<int>(&block_1.at(60)),
			read_binary_as<int>(&block_1.at(64)),
			read_binary_as<int>(&block_1.at(68)),
			read_binary_as<int>(&block_1.at(72)),
			read_binary_as<int>(&block_1.at(76))
		};

		const int& version = read_binary_as<int>(&block_1.at(80));

		DCD_1stHeader retval(signature, nframes, istart, nstep_save, nsteps, nunits, zero4, delta, zero9, version);
		return retval;
	}


	DCD_2ndHeader parse_2nd_header(const std::string& block_2) {

		const int& nline = read_binary_as<int>(&block_2.at(0));

		std::string s_tempk;
		for (std::size_t idx = 0; idx < 80; ++idx)
			s_tempk += read_binary_as<char>(&block_2.at(164 + idx));

		float tempk = std::stof(s_tempk);

		std::vector<int> unit_size(nline - 3);

		for (int iunit = 0; iunit < (nline - 3); ++iunit) {
			std::string buffer;
			for (std::size_t idx = 0; idx < 80; ++idx) {
				buffer += read_binary_as<char>(&block_2.at(244 + 80 * iunit + idx));
			}
			unit_size[iunit] = std::stoi(buffer);
		}

		DCD_2ndHeader retval(nline, tempk, unit_size);
		return retval;
	}


	DCD_3rdHeader parse_3rd_header() {

		DCD_3rdHeader retval(atom_num);
		return retval;

	}



private:


	template<typename T>
	T read_binary_as(const char *str) {
	    T result;
	    std::memcpy(std::addressof(result), str, sizeof(T));
	    return result;
	}
	
	const std::string read_block() {
		std::int32_t block_size;
		std::vector<char> buffer;
	
		constexpr int int32_size = sizeof(float);
		input_file.read(reinterpret_cast<char*>(&block_size), int32_size);
		buffer.resize(block_size);
		input_file.read(buffer.data(), block_size);
	
		std::int32_t check_block_size;
		input_file.read(reinterpret_cast<char*>(&check_block_size), int32_size);
	
		if (block_size != check_block_size) {
			std::cerr << "Error: Left Block size is not consistent with Right one" << std::endl;
			std::exit(1);
		}
	
//		std::cout << block_size << std::endl;
		const std::string result(buffer.begin(), buffer.end());
	
		return result;
	}
	
	
	
	void read_frame_num(const std::string& first_block) {
		constexpr int frame_num_index = 4;
		frame_num = read_binary_as<int>(&first_block.at(frame_num_index));
	}


	void read_atom_num(const std::string& third_block) {
		constexpr int atom_num_index = 0;
		atom_num = read_binary_as<int>(&third_block.at(atom_num_index));
	}



	const std::vector<float> read_coordinates(const std::string& block) {
		std::vector<float> coordinates(atom_num);
		for (std::size_t i_atom = 0; i_atom < atom_num; ++i_atom) {
			constexpr int float_size = sizeof(float);
			std::size_t pos_of_atom = i_atom * float_size;
			coordinates[i_atom] = read_binary_as<float>(&block.at(pos_of_atom));
		}
		return coordinates;
	}


};

}

#endif /* TRYAMP_DCD_PARSER_HPP */
