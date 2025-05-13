#ifndef TRYAMP_NINFO_READER_HPP
#define TRYAMP_NINFO_READER_HPP
#include<TryAmp/core/ninfo/ninfo_parser.hpp>
#include<TryAmp/core/ninfo/ninfo_read_style/ninfo_read_style.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/native_info_data.hpp>
#include<iostream>
#include<string>
#include<array>
#include<vector>

namespace Amp {


template<Ninfo_ReadStyle STYLE_FLAG>
class NinfoReader : public NinfoParser<STYLE_FLAG> {

public:
	NinfoReader() : NinfoParser<STYLE_FLAG>() {}
	NinfoReader(const std::string& input_file_name) : NinfoParser<STYLE_FLAG>(input_file_name) {}
	~NinfoReader() = default;


	NativeInfo read_NativeInfo() {

		this->open();

		NativeInfo result;

		std::string buffer;
		while (std::getline(this->input_file, buffer)) {

			if (buffer.size() < 4 || buffer.substr(0, 4) == ">>>>" || buffer.substr(0, 4) == "<<<<")
				continue;

			const std::vector<std::string>& words = this->split_Line(buffer);
			if (words.empty()) continue;
			else if (words[0] == "bond") {
				result.add_BondLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stof(words[8]), std::stof(words[9]),
				std::stof(words[10]), std::stof(words[11]));
			}
			else if (words[0] == "angl") {
				result.add_AnglLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stoi(words[8]), std::stoi(words[9]),
				std::stof(words[10]), std::stof(words[11]), std::stof(words[12]),
				std::stof(words[13]));
			}
			else if (words[0] == "angl") {
				result.add_AnglLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stoi(words[8]), std::stoi(words[9]),
				std::stof(words[10]), std::stof(words[11]), std::stof(words[12]),
				std::stof(words[13]));
			}
			else if (words[0] == "aicg13") {
				result.add_AICG13Line(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stoi(words[8]), std::stoi(words[9]),
				std::stof(words[10]), std::stof(words[11]), std::stof(words[12]),
				std::stof(words[13]), std::stof(words[14]));
			}
			else if (words[0] == "dihd") {
				result.add_DihdLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stoi(words[8]), std::stoi(words[9]),
				std::stoi(words[10]), std::stoi(words[11]), std::stof(words[12]),
				std::stof(words[13]), std::stof(words[14]), std::stof(words[15]),
				std::stof(words[16]));
			}
			else if (words[0] == "aicgdih") {
				result.add_AICGDihLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stoi(words[8]), std::stoi(words[9]),
				std::stoi(words[10]), std::stoi(words[11]), std::stof(words[12]),
				std::stof(words[13]), std::stof(words[14]), std::stof(words[15]),
				std::stof(words[16]));
			}
			else if (words[0] == "contact") {
				result.add_ContactLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stoi(words[5]), std::stoi(words[6]),
				std::stoi(words[7]), std::stof(words[8]), std::stof(words[9]),
				std::stoi(words[10]), std::stof(words[11]));

			}
			else if (words[0] == "pdns") {
				result.add_PDNSLine(
				std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]),
				std::stoi(words[4]), std::stof(words[5]), std::stof(words[6]),
				std::stof(words[7]), std::stof(words[8]));
			}
			else if (words[0] == "**") continue;
			else {
				std::cerr << "Error: Strange line: ==> " << buffer << std::endl;
				std::cerr << "Error: Strange block name: ==> " << words[0] << std::endl;
				std::exit(1);
			}
		}

		return result;
	}

};


}

#endif /* TRYAMP_NINFO_READER_HPP */
