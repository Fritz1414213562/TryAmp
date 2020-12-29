#ifndef TRYAMP_NINFO_PDNS_LINE_HPP
#define TRYAMP_NINFO_PDNS_LINE_HPP
#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<tuple>
#include<type_traits>


namespace Amp {

struct Ninfo_PDNSLine {

public:

	template<typename... Args>
	Ninfo_PDNSLine(const Args&... arguments) {
		static_assert(std::is_same<std::tuple<Args...>, std::tuple<
		int,
		int,
		int,
		int,
		float,
		float,
		float,
		float>>::value, "usage: Ninfo_BondLine, 4 x unsigned long long, 4 x float");

		const std::tuple<Args...> args_tuple(arguments...);
		serial_number = std::get<0>(args_tuple);
		unit_number = std::get<1>(args_tuple);
		mass_point = std::get<2>(args_tuple);
		local_mass_point = std::get<3>(args_tuple);
		pdns_contact_length = std::get<4>(args_tuple);
		pdns_angle_NC = std::get<5>(args_tuple);
		pdns_angle_SB = std::get<6>(args_tuple);
		coefficient = std::get<7>(args_tuple);
	}

	~Ninfo_PDNSLine() = default;

	std::string kind() const {return line_kind;}

	int serial_id() const {return serial_number;}
	int& serial_id() {return serial_number;}

	int unit_num() const {return unit_number;}
	int& unit_num() {return unit_number;}

	int global_mp() const {return mass_point;}
	int& global_mp() {return mass_point;}

	int local_mp() const {return local_mass_point;}
	int& local_mp() {return local_mass_point;}

	float pdns_length() const {return pdns_contact_length;}
	float& pdns_length() {return pdns_contact_length;}

	float angle_NC() const {return pdns_angle_NC;}
	float& angle_NC() {return pdns_angle_NC;}

	float angle_SB() const {return pdns_angle_SB;}
	float& angle_SB() {return pdns_angle_SB;}

	float coef() const {return coefficient;}
	float& coef() {return coefficient;}


private:

	const std::string line_kind = "pdns";
	int serial_number;
	int unit_number;
	int mass_point;
	int local_mass_point;
	float pdns_contact_length;
	float pdns_angle_NC;
	float pdns_angle_SB;
	float coefficient;

};


}


#endif /* TRYAMP_NINFO_PDNS_LINE_HPP */
