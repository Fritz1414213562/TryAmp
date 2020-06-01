#ifndef TRYAMP_PSF_CHAIN_RANGE_HPP
#define TRYAMP_PSF_CHAIN_RANGE_HPP
#include<array>
#include<initializer_list>


namespace Amp {


struct PSF_ChainRange {

public:
	PSF_ChainRange() = default;
	PSF_ChainRange(const std::size_t& lhs, const std::size_t& rhs) : chain_range{lhs, rhs} {}
	~PSF_ChainRange() = default;

	std::size_t begin_index() const {return chain_range[0];}
	std::size_t& begin_index() {return chain_range[0];}
	std::size_t end_index() const {return chain_range[1];}
	std::size_t& end_index() {return chain_range[1];}

	std::size_t size() const {return chain_range[1] - chain_range[0] + 1;}

private:
	std::array<std::size_t, 2> chain_range;

};


}


#endif /* TRYAMP_PSF_CHAIN_RANGE_HPP */
