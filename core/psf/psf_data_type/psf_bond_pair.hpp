#ifndef TRYAMP_PSF_BOND_PAIR_HPP
#define TRYAMP_PSF_BOND_PAIR_HPP


namespace Amp {

struct PSF_BondPair {

public:

	PSF_BondPair(const std::size_t& input_lhs, const std::size_t& input_rhs) :
	pair_lhs(input_lhs),
	pair_rhs(input_rhs) {}

	~PSF_BondPair() = default;

	std::size_t lhs() const {return pair_lhs;}
	std::size_t& lhs() {return pair_lhs;}
	std::size_t rhs() const {return pair_rhs;}
	std::size_t& rhs() {return pair_rhs;}

//	PSF_BondPair operator=(const PSF_BondPair& input_bond_pair) const {
//		return PSF_BondPair(input_bond_pair.lhs(), input_bond_pair.rhs());
//	}

private:
	std::size_t pair_lhs;
	std::size_t pair_rhs;

};

}


#endif /* TRYAMP_PSF_BOND_PAIR_HPP */
