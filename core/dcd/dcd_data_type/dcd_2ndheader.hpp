#ifndef TRYAMP_DCD_2NDHEADER_HPP
#define TRYAMP_DCD_2NDHEADER_HPP
#include<vector>
#include<string>
#include<tuple>



namespace Amp {


struct DCD_2ndHeader {

public:

	DCD_2ndHeader() = default;

	DCD_2ndHeader(
		const int& input_nline,
		const float& input_temp,
		const std::vector<int>& input_unit_size
	) : _header(input_nline, input_temp, input_unit_size) {

		if (input_nline != (static_cast<int>(input_unit_size.size()) + 3)) {
			std::cerr << "Input line number is not consistent with actual" << std::endl;
			std::exit(1);
		}
	}

	~DCD_2ndHeader() = default;

	int line_number() const {return std::get<0>(_header);}
	int& line_number() {return std::get<0>(_header);}
	float temperature() const {return std::get<1>(_header);}
	float& temperature() {return std::get<1>(_header);}
	std::vector<int> unit_size() const {return std::get<2>(_header);}
	std::vector<int>& unit_size() {return std::get<2>(_header);}



private:

	std::tuple<
		int,
		float,
		std::vector<int>
	> _header;

};


}



#endif /* TRYAMP_DCD_2NDHEADER_HPP */
