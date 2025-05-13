#ifndef TRYAMP_NINFO_PARSER_HPP
#define TRYAMP_NINFO_PARSER_HPP
#include<TryAmp/core/base/Parser.hpp>
#include<TryAmp/util/split_line.hpp>
#include<TryAmp/core/ninfo/ninfo_read_style/ninfo_read_style.hpp>
#include<TryAmp/core/ninfo/ninfo_read_style/ninfo_column_meaning.hpp>
#include<iostream>
#include<string>
#include<vector>

namespace Amp {

template<Ninfo_ReadStyle STYLE_FLAG>
class NinfoParser : public FileParser {

public:
	NinfoParser() : FileParser() {}
	NinfoParser(const std::string& input_file_name) : FileParser(input_file_name) {}
	~NinfoParser() = default;

protected:
	
	std::vector<std::string> split_Line(const std::string& line) const;

private:

	const char delim = ' ';
	const std::string& empty_line_type = "";
	const std::string& block_name_bond = "bond";
	const std::string& block_name_angl = "angl";
	const std::string& block_name_aicg13 = "aicg13";
	const std::string& block_name_dihd = "dihd";
	const std::string& block_name_aicgdih = "aicgdih";
	const std::string& block_name_contact = "contact";
	const std::string& block_name_pdns = "pdns";


	std::vector<std::string> split_BondLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<BOND_NAME_BEGIN, BOND_NAME_END>(line));
		result.push_back(read_PartialLine<BOND_SER_ID_BEGIN, BOND_SER_ID_END>(line));
		result.push_back(read_PartialLine<BOND_UNIT1_BEGIN, BOND_UNIT1_END>(line));
		result.push_back(read_PartialLine<BOND_UNIT2_BEGIN, BOND_UNIT2_END>(line));
		result.push_back(read_PartialLine<BOND_GLO_MP1_BEGIN, BOND_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<BOND_GLO_MP2_BEGIN, BOND_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<BOND_LOC_MP1_BEGIN, BOND_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<BOND_LOC_MP2_BEGIN, BOND_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<BOND_NAT_LEN_BEGIN, BOND_NAT_LEN_END>(line));
		result.push_back(read_PartialLine<BOND_FACTOR_BEGIN, BOND_FACTOR_END>(line));
		result.push_back(read_PartialLine<BOND_MGO_BEGIN, BOND_MGO_END>(line));
		result.push_back(read_PartialLine<BOND_COEF_BEGIN, BOND_COEF_END>(line));


		return result;
	}


	std::vector<std::string> split_AnglLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<ANGL_NAME_BEGIN, ANGL_NAME_END>(line));
		result.push_back(read_PartialLine<ANGL_SER_ID_BEGIN, ANGL_SER_ID_END>(line));
		result.push_back(read_PartialLine<ANGL_UNIT1_BEGIN, ANGL_UNIT1_END>(line));
		result.push_back(read_PartialLine<ANGL_UNIT2_BEGIN, ANGL_UNIT2_END>(line));
		result.push_back(read_PartialLine<ANGL_GLO_MP1_BEGIN, ANGL_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<ANGL_GLO_MP2_BEGIN, ANGL_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<ANGL_GLO_MP3_BEGIN, ANGL_GLO_MP3_END>(line));
		result.push_back(read_PartialLine<ANGL_LOC_MP1_BEGIN, ANGL_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<ANGL_LOC_MP2_BEGIN, ANGL_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<ANGL_LOC_MP3_BEGIN, ANGL_LOC_MP3_END>(line));
		result.push_back(read_PartialLine<ANGL_NAT_SIZE_BEGIN, ANGL_NAT_SIZE_END>(line));
		result.push_back(read_PartialLine<ANGL_FACTOR_BEGIN, ANGL_FACTOR_END>(line));
		result.push_back(read_PartialLine<ANGL_MGO_BEGIN, ANGL_MGO_END>(line));
		result.push_back(read_PartialLine<ANGL_COEF_BEGIN, ANGL_COEF_END>(line));


		return result;
	}


	std::vector<std::string> split_AICG13Line(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<AICG13_NAME_BEGIN, AICG13_NAME_END>(line));
		result.push_back(read_PartialLine<AICG13_SER_ID_BEGIN, AICG13_SER_ID_END>(line));
		result.push_back(read_PartialLine<AICG13_UNIT1_BEGIN, AICG13_UNIT1_END>(line));
		result.push_back(read_PartialLine<AICG13_UNIT2_BEGIN, AICG13_UNIT2_END>(line));
		result.push_back(read_PartialLine<AICG13_GLO_MP1_BEGIN, AICG13_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<AICG13_GLO_MP2_BEGIN, AICG13_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<AICG13_GLO_MP3_BEGIN, AICG13_GLO_MP3_END>(line));
		result.push_back(read_PartialLine<AICG13_LOC_MP1_BEGIN, AICG13_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<AICG13_LOC_MP2_BEGIN, AICG13_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<AICG13_LOC_MP3_BEGIN, AICG13_LOC_MP3_END>(line));
		result.push_back(read_PartialLine<AICG13_NAT_LEN_BEGIN, AICG13_NAT_LEN_END>(line));
		result.push_back(read_PartialLine<AICG13_FACTOR_BEGIN, AICG13_FACTOR_END>(line));
		result.push_back(read_PartialLine<AICG13_MGO_BEGIN, AICG13_MGO_END>(line));
		result.push_back(read_PartialLine<AICG13_COEF_BEGIN, AICG13_COEF_END>(line));
		result.push_back(read_PartialLine<AICG13_WIDTH_BEGIN, AICG13_WIDTH_END>(line));


		return result;
	}


	std::vector<std::string> split_DihdLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<DIHD_NAME_BEGIN, DIHD_NAME_END>(line));
		result.push_back(read_PartialLine<DIHD_SER_ID_BEGIN, DIHD_SER_ID_END>(line));
		result.push_back(read_PartialLine<DIHD_UNIT1_BEGIN, DIHD_UNIT1_END>(line));
		result.push_back(read_PartialLine<DIHD_UNIT2_BEGIN, DIHD_UNIT2_END>(line));
		result.push_back(read_PartialLine<DIHD_GLO_MP1_BEGIN, DIHD_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<DIHD_GLO_MP2_BEGIN, DIHD_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<DIHD_GLO_MP3_BEGIN, DIHD_GLO_MP3_END>(line));
		result.push_back(read_PartialLine<DIHD_GLO_MP4_BEGIN, DIHD_GLO_MP4_END>(line));
		result.push_back(read_PartialLine<DIHD_LOC_MP1_BEGIN, DIHD_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<DIHD_LOC_MP2_BEGIN, DIHD_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<DIHD_LOC_MP3_BEGIN, DIHD_LOC_MP3_END>(line));
		result.push_back(read_PartialLine<DIHD_LOC_MP4_BEGIN, DIHD_LOC_MP4_END>(line));
		result.push_back(read_PartialLine<DIHD_NAT_SIZE_BEGIN, DIHD_NAT_SIZE_END>(line));
		result.push_back(read_PartialLine<DIHD_FACTOR_BEGIN, DIHD_FACTOR_END>(line));
		result.push_back(read_PartialLine<DIHD_MGO_BEGIN, DIHD_MGO_END>(line));
		result.push_back(read_PartialLine<DIHD_COEF1_BEGIN, DIHD_COEF1_END>(line));
		result.push_back(read_PartialLine<DIHD_COEF2_BEGIN, DIHD_COEF2_END>(line));


		return result;
	}


	std::vector<std::string> split_AICGDihLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<AICGDIH_NAME_BEGIN, AICGDIH_NAME_END>(line));
		result.push_back(read_PartialLine<AICGDIH_SER_ID_BEGIN, AICGDIH_SER_ID_END>(line));
		result.push_back(read_PartialLine<AICGDIH_UNIT1_BEGIN, AICGDIH_UNIT1_END>(line));
		result.push_back(read_PartialLine<AICGDIH_UNIT2_BEGIN, AICGDIH_UNIT2_END>(line));
		result.push_back(read_PartialLine<AICGDIH_GLO_MP1_BEGIN, AICGDIH_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<AICGDIH_GLO_MP2_BEGIN, AICGDIH_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<AICGDIH_GLO_MP3_BEGIN, AICGDIH_GLO_MP3_END>(line));
		result.push_back(read_PartialLine<AICGDIH_GLO_MP4_BEGIN, AICGDIH_GLO_MP4_END>(line));
		result.push_back(read_PartialLine<AICGDIH_LOC_MP1_BEGIN, AICGDIH_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<AICGDIH_LOC_MP2_BEGIN, AICGDIH_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<AICGDIH_LOC_MP3_BEGIN, AICGDIH_LOC_MP3_END>(line));
		result.push_back(read_PartialLine<AICGDIH_LOC_MP4_BEGIN, AICGDIH_LOC_MP4_END>(line));
		result.push_back(read_PartialLine<AICGDIH_NAT_SIZE_BEGIN, AICGDIH_NAT_SIZE_END>(line));
		result.push_back(read_PartialLine<AICGDIH_FACTOR_BEGIN, AICGDIH_FACTOR_END>(line));
		result.push_back(read_PartialLine<AICGDIH_MGO_BEGIN, AICGDIH_MGO_END>(line));
		result.push_back(read_PartialLine<AICGDIH_COEF_BEGIN, AICGDIH_COEF_END>(line));
		result.push_back(read_PartialLine<AICGDIH_WIDTH_BEGIN, AICGDIH_WIDTH_END>(line));


		return result;
	}


	std::vector<std::string> split_ContactLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<CONTACT_NAME_BEGIN, CONTACT_NAME_END>(line));
		result.push_back(read_PartialLine<CONTACT_SER_ID_BEGIN, CONTACT_SER_ID_END>(line));
		result.push_back(read_PartialLine<CONTACT_UNIT1_BEGIN, CONTACT_UNIT1_END>(line));
		result.push_back(read_PartialLine<CONTACT_UNIT2_BEGIN, CONTACT_UNIT2_END>(line));
		result.push_back(read_PartialLine<CONTACT_GLO_MP1_BEGIN, CONTACT_GLO_MP1_END>(line));
		result.push_back(read_PartialLine<CONTACT_GLO_MP2_BEGIN, CONTACT_GLO_MP2_END>(line));
		result.push_back(read_PartialLine<CONTACT_LOC_MP1_BEGIN, CONTACT_LOC_MP1_END>(line));
		result.push_back(read_PartialLine<CONTACT_LOC_MP2_BEGIN, CONTACT_LOC_MP2_END>(line));
		result.push_back(read_PartialLine<CONTACT_NAT_LEN_BEGIN, CONTACT_NAT_LEN_END>(line));
		result.push_back(read_PartialLine<CONTACT_FACTOR_BEGIN, CONTACT_FACTOR_END>(line));
		result.push_back(read_PartialLine<CONTACT_DUMMY_BEGIN, CONTACT_DUMMY_END>(line));
		result.push_back(read_PartialLine<CONTACT_COEF_BEGIN, CONTACT_COEF_END>(line));


		return result;
	}


	std::vector<std::string> split_PDNSLine(const std::string& line) const {
		std::vector<std::string> result;

		result.push_back(read_PartialLine<PDNS_NAME_BEGIN, PDNS_NAME_END>(line));
		result.push_back(read_PartialLine<PDNS_SER_ID_BEGIN, PDNS_SER_ID_END>(line));
		result.push_back(read_PartialLine<PDNS_UNIT_BEGIN, PDNS_UNIT_END>(line));
		result.push_back(read_PartialLine<PDNS_GLO_MP_BEGIN, PDNS_GLO_MP_END>(line));
		result.push_back(read_PartialLine<PDNS_LOC_MP_BEGIN, PDNS_LOC_MP_END>(line));
		result.push_back(read_PartialLine<PDNS_LENGTH_BEGIN, PDNS_LENGTH_END>(line));
		result.push_back(read_PartialLine<PDNS_ANGLE_NC_BEGIN, PDNS_ANGLE_NC_END>(line));
		result.push_back(read_PartialLine<PDNS_ANGLE_SB_BEGIN, PDNS_ANGLE_SB_END>(line));
		result.push_back(read_PartialLine<PDNS_COEF_BEGIN, PDNS_COEF_END>(line));

		return result;
	}



	template<NINFO_COLUMN_MEANINGS begin_index, NINFO_COLUMN_MEANINGS end_index>
	std::string read_PartialLine(const std::string& line) const {
		constexpr std::size_t parse_length = end_index - begin_index + 1;
		return line.substr(begin_index, parse_length);
	}


};


template<>
inline std::vector<std::string> NinfoParser<NINFO_SPC_SPL>::split_Line(const std::string& line) const {
	return Amp::strmanage::split_String(line, delim);
//	return Amp::strmanage::split_String(line, ' ');
}


template<>
inline std::vector<std::string> NinfoParser<NINFO_COL_SPL>::split_Line(const std::string& line) const {
	std::vector<std::string> result;
	if (read_PartialLine<BOND_NAME_BEGIN, BOND_NAME_END>(line) == block_name_bond) {
		result = split_BondLine(line);
	}
	else if (read_PartialLine<ANGL_NAME_BEGIN, ANGL_NAME_END>(line) == block_name_angl) {
		result = split_AnglLine(line);
	}
	else if (read_PartialLine<AICG13_NAME_BEGIN, AICG13_NAME_END>(line) == block_name_aicg13) {
		result = split_AICG13Line(line);
	}
	else if (read_PartialLine<DIHD_NAME_BEGIN, DIHD_NAME_END>(line) == block_name_dihd) {
		result = split_DihdLine(line);
	}
	else if (read_PartialLine<AICGDIH_NAME_BEGIN, AICGDIH_NAME_END>(line) == block_name_aicgdih) {
		result = split_AICGDihLine(line);
	}
	else if (read_PartialLine<CONTACT_NAME_BEGIN, CONTACT_NAME_END>(line) == block_name_contact) {
		result = split_ContactLine(line);
	}
	else if (read_PartialLine<PDNS_NAME_BEGIN, PDNS_NAME_END>(line) == block_name_pdns) {
		result = split_PDNSLine(line);
	}
	else {
		std::cerr << "Strange string exists.: ==> " << line << std::endl;
		std::exit(1);
	}
//	else {}

	return result;
}



}

#endif /* TRYAMP_NINFO_PARSER_HPP */
