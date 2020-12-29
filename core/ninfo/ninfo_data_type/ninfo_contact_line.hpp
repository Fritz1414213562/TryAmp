#ifndef TRYAMP_NINFO_CONTACT__LINE_HPP
#define TRYAMP_NINFO_CONTACT_LINE_HPP
#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<tuple>
#include<type_traits>


namespace Amp {

struct Ninfo_ContactLine {

public:

	template<typename... Args>
	Ninfo_ContactLine(const Args&... arguments) {
		static_assert(std::is_same<std::tuple<Args...>, std::tuple<
		int,
		int,
		int,
		int,
		int,
		int,
		int,
		float,
		float,
		int,
		float,
		std::string>>::value, "usage: Ninfo_ContactLine, 7 x unsigned long long, 2 x float, unsigned long long, float, string");

		const std::tuple<Args...> args_tuple(arguments...);
		serial_number = std::get<0>(args_tuple);
		lhs_unit = std::get<1>(args_tuple);
		rhs_unit = std::get<2>(args_tuple);
		lhs_mass_point = std::get<3>(args_tuple);
		rhs_mass_point = std::get<4>(args_tuple);
		lhs_local_mp = std::get<5>(args_tuple);
		rhs_local_mp = std::get<6>(args_tuple);
		native_length = std::get<7>(args_tuple);
		factor_go = std::get<8>(args_tuple);
		dummy_number = std::get<9>(args_tuple);
		coefficient = std::get<10>(args_tuple);
		contact_type = std::get<11>(args_tuple);
	}

	~Ninfo_ContactLine() = default;

	std::string kind() const {return line_kind;}

	int serial_id() const {return serial_number;}
	int& serial_id() {return serial_number;}

	int unit_num1() const {return lhs_unit;}
	int& unit_num1() {return lhs_unit;}

	int unit_num2() const {return rhs_unit;}
	int& unit_num2() {return rhs_unit;}

	int global_mp1() const {return lhs_mass_point;}
	int& global_mp1() {return lhs_mass_point;}

	int global_mp2() const {return rhs_mass_point;}
	int& global_mp2() {return rhs_mass_point;}

	int local_mp1() const {return lhs_local_mp;}
	int& local_mp1() {return lhs_local_mp;}

	int local_mp2() const {return rhs_local_mp;}
	int& local_mp2() {return rhs_local_mp;}

	float native_contact_length() const {return native_length;}
	float& native_contact_length() {return native_length;}

	float factor() const {return factor_go;}
	float& factor() {return factor_go;}

	int dummy() const {return dummy_number;}
	int& dummy() {return dummy_number;}

	float coef() const {return coefficient;}
	float& coef() {return coefficient;}

	std::string type() const {return contact_type;}
	std::string& type() {return contact_type;}



private:

	const std::string line_kind = "contact";
	int serial_number;
	int lhs_unit;
	int rhs_unit;
	int lhs_mass_point;
	int rhs_mass_point;
	int lhs_local_mp;
	int rhs_local_mp;
	float native_length;
	float factor_go;
	int dummy_number;
	float coefficient;
	std::string contact_type;

};


}


#endif /* TRYAMP_NINFO_CONTACT_LINE_HPP */
