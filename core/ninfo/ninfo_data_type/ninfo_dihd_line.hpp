#ifndef TRYAMP_NINFO_DIHD_LINE_HPP
#define TRYAMP_NINFO_DIHD_LINE_HPP
#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<tuple>
#include<type_traits>


namespace Amp {

struct Ninfo_DihdLine {

public:

	template<typename... Args>
	Ninfo_DihdLine(const Args&... arguments) {
		static_assert(std::is_same<std::tuple<Args...>, std::tuple<
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		float,
		float,
		float,
		float,
		float,
		std::string>>::value, "usage: Ninfo_DihdLine, 11 x unsigned long long, 5 x float, string");

		const std::tuple<Args...> args_tuple(arguments...);
		serial_number = std::get<0>(args_tuple);
		lhs_unit = std::get<1>(args_tuple);
		rhs_unit = std::get<2>(args_tuple);
		mass_point1 = std::get<3>(args_tuple);
		mass_point2 = std::get<4>(args_tuple);
		mass_point3 = std::get<5>(args_tuple);
		mass_point4 = std::get<6>(args_tuple);
		local_mass_point1 = std::get<7>(args_tuple);
		local_mass_point2 = std::get<8>(args_tuple);
		local_mass_point3 = std::get<9>(args_tuple);
		local_mass_point4 = std::get<10>(args_tuple);
		native_dihedral_size = std::get<11>(args_tuple);
		factor_go = std::get<12>(args_tuple);
		correct_mgo = std::get<13>(args_tuple);
		coefficient_lhs = std::get<14>(args_tuple);
		coefficient_rhs = std::get<15>(args_tuple);
		dihd_type = std::get<16>(args_tuple);
	}

	~Ninfo_DihdLine() = default;

	std::string kind() const {return line_kind;}

	int serial_id() const {return serial_number;}
	int& serial_id() {return serial_number;}

	int unit_num1() const {return lhs_unit;}
	int& unit_num1() {return lhs_unit;}

	int unit_num2() const {return rhs_unit;}
	int& unit_num2() {return rhs_unit;}

	int global_mp1() const {return mass_point1;}
	int& global_mp1() {return mass_point1;}

	int global_mp2() const {return mass_point2;}
	int& global_mp2() {return mass_point2;}

	int global_mp3() const {return mass_point3;}
	int& global_mp3() {return mass_point3;}

	int global_mp4() const {return mass_point4;}
	int& global_mp4() {return mass_point4;}

	int local_mp1() const {return local_mass_point1;}
	int& local_mp1() {return local_mass_point1;}

	int local_mp2() const {return local_mass_point2;}
	int& local_mp2() {return local_mass_point2;}

	int local_mp3() const {return local_mass_point3;}
	int& local_mp3() {return local_mass_point3;}

	int local_mp4() const {return local_mass_point4;}
	int& local_mp4() {return local_mass_point4;}


	float native_dihd() const {return native_dihedral_size;}
	float& native_dihd() {return native_dihedral_size;}

	float factor() const {return factor_go;}
	float& factor() {return factor_go;}

	float mgo() const {return correct_mgo;}
	float& mgo() {return correct_mgo;}

	float coef_lhs() const {return coefficient_lhs;}
	float& coef_lhs() {return coefficient_lhs;}

	float coef_rhs() const {return coefficient_rhs;}
	float& coef_rhs() {return coefficient_rhs;}

	std::string type() const {return dihd_type;}
	std::string& type() {return dihd_type;}



private:

	const std::string line_kind = "dihd";
	int serial_number;
	int lhs_unit;
	int rhs_unit;
	int mass_point1;
	int mass_point2;
	int mass_point3;
	int mass_point4;
	int local_mass_point1;
	int local_mass_point2;
	int local_mass_point3;
	int local_mass_point4;
	float native_dihedral_size;
	float factor_go;
	float correct_mgo;
	float coefficient_lhs;
	float coefficient_rhs;
	std::string dihd_type;

};


}


#endif /* TRYAMP_NINFO_DIHD_LINE_HPP */
