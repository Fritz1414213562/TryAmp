#ifndef TRYAMP_DCD_1STHEADER_HPP
#define TRYAMP_DCD_1STHEADER_HPP
#include<vector>
#include<string>
#include<tuple>



namespace Amp {


struct DCD_1stHeader {

public:

	DCD_1stHeader() = default;

	DCD_1stHeader(
		const std::string& input_signature,
		const int& input_nframes,
		const int& input_istart,
		const int& input_nstep_save,
		const int& input_nsteps,
		const int& input_nunits,
		const std::array<int, 4>& input_zero4,
		const float& input_delta,
		const std::array<int, 9>& input_zero9,
		const int& input_version
	) : _header(
		input_signature,
		input_nframes,
		input_istart,
		input_nstep_save,
		input_nsteps,
		input_nunits,
		input_zero4,
		input_delta,
		input_zero9,
		input_version
	) {}

	~DCD_1stHeader() = default;


	std::string signature() const {return std::get<0>(_header);}
	std::string& signature() {return std::get<0>(_header);}
	int frame_number() const {return std::get<1>(_header);}
	int& frame_number() {return std::get<1>(_header);}
	int initial_frame() const {return std::get<2>(_header);}
	int& initial_frame() {return std::get<2>(_header);}
	int save_step() const {return std::get<3>(_header);}
	int& save_step() {return std::get<3>(_header);}
	int step_number() const {return std::get<4>(_header);}
	int& step_number() {return std::get<4>(_header);}
	int unit_number() const {return std::get<5>(_header);}
	int& unit_number() {return std::get<5>(_header);}
	std::array<int, 4> zero4() const {return std::get<6>(_header);}
	std::array<int, 4>& zero4() {return std::get<6>(_header);}
	float time_increment() const {return std::get<7>(_header);}
	float& time_increment() {return std::get<7>(_header);}
	std::array<int, 9> zero9() const {return std::get<8>(_header);}
	std::array<int, 9>& zero9() {return std::get<8>(_header);}
	int version() const {return std::get<9>(_header);}
	int& version() {return std::get<9>(_header);}


private:

	std::tuple<
		std::string,
		int,
		int,
		int,
		int,
		int,
		std::array<int, 4>,
		float,
		std::array<int, 9>,
		int
	> _header;

};


}



#endif /* TRYAMP_DCD_1STHEADER_HPP */
