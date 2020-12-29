#ifndef TRYAMP_NINFO_AICG13_LINE_HPP
#define TRYAMP_NINFO_AICG13_LINE_HPP
#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<tuple>
#include<type_traits>


namespace Amp {

struct Ninfo_AICG13Line {

public:

	template<typename... Args>
	Ninfo_AICG13Line(const Args&... arguments) {
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
		float,
		float,
		float,
		float,
		float,
		std::string>>::value, "usage: Ninfo_AICG13Line, 9 x unsigned long long, 5 x float, string");

		const std::tuple<Args...> args_tuple(arguments...);
		serial_number = std::get<0>(args_tuple);
		lhs_unit = std::get<1>(args_tuple);
		rhs_unit = std::get<2>(args_tuple);
		lhs_mass_point = std::get<3>(args_tuple);
		mid_mass_point = std::get<4>(args_tuple);
		rhs_mass_point = std::get<5>(args_tuple);
		lhs_local_mp = std::get<6>(args_tuple);
		mid_local_mp = std::get<7>(args_tuple);
		rhs_local_mp = std::get<8>(args_tuple);
		native_aicg13_length = std::get<9>(args_tuple);
		factor_go = std::get<10>(args_tuple);
		correct_mgo = std::get<11>(args_tuple);
		coefficient = std::get<12>(args_tuple);
		width_gauss = std::get<13>(args_tuple);
		aicg13_type = std::get<14>(args_tuple);
	}

	~Ninfo_AICG13Line() = default;

	std::string kind() const {return line_kind;}

	int serial_id() const {return serial_number;}
	int& serial_id() {return serial_number;}

	int unit_num1() const {return lhs_unit;}
	int& unit_num1() {return lhs_unit;}

	int unit_num2() const {return rhs_unit;}
	int& unit_num2() {return rhs_unit;}

	int global_mp1() const {return lhs_mass_point;}
	int& global_mp1() {return lhs_mass_point;}

	int global_mp2() const {return mid_mass_point;}
	int& global_mp2() {return mid_mass_point;}

	int global_mp3() const {return rhs_mass_point;}
	int& global_mp3() {return rhs_mass_point;}

	int local_mp1() const {return lhs_local_mp;}
	int& local_mp1() {return lhs_local_mp;}

	int local_mp2() const {return mid_local_mp;}
	int& local_mp2() {return mid_local_mp;}

	int local_mp3() const {return rhs_local_mp;}
	int& local_mp3() {return rhs_local_mp;}

	float native_aicg13() const {return native_aicg13_length;}
	float& native_aicg13() {return native_aicg13_length;}

	float factor() const {return factor_go;}
	float& factor() {return factor_go;}

	float mgo() const {return correct_mgo;}
	float& mgo() {return correct_mgo;}

	float coef_aicg13() const {return coefficient;}
	float& coef_aicg13() {return coefficient;}

	float coef_width() const {return width_gauss;}
	float& coef_width() {return width_gauss;}

	std::string type() const {return aicg13_type;}
	std::string& type() {return aicg13_type;}



private:

	const std::string line_kind = "aicg13";
	int serial_number;
	int lhs_unit;
	int rhs_unit;
	int lhs_mass_point;
	int mid_mass_point;
	int rhs_mass_point;
	int lhs_local_mp;
	int mid_local_mp;
	int rhs_local_mp;
	float native_aicg13_length;
	float factor_go;
	float correct_mgo;
	float coefficient;
	float width_gauss;
	std::string aicg13_type;

};


}


#endif /* TRYAMP_NINFO_AICG13_LINE_HPP */
