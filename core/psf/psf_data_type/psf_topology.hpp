#ifndef TRYAMP_PSF_TOPOLOGY_HPP
#define TRYAMP_PSF_TOPOLOGY_HPP
#include<TryAmp/core/psf/psf_data_type/psf_atom_line.hpp>
#include<TryAmp/core/psf/psf_data_type/psf_bond_pair.hpp>
#include<TryAmp/core/psf/psf_data_type/psf_chain_range.hpp>
#include<vector>
#include<array>


namespace Amp {

struct PSF_Topology {

public:
	PSF_Topology() = default;
	~PSF_Topology() = default;

	void add_AtomLines(const PSF_AtomLine& atom_line) {
		atom_lines.push_back(atom_line);
	}

	void add_BondPairs(const PSF_BondPair& bond_pair) {
		bond_pairs.push_back(bond_pair);
	}

	std::size_t atom_size() const {return atom_lines.size();}
	std::size_t bond_pair_size() const {return bond_pairs.size();}


	std::vector<PSF_ChainRange> chains() const {

		if (bond_pairs.empty() || bond_pairs.size() < 1) {
			std::cerr << "Error: You don't read !NBOND block" << std::endl;
			std::exit(1);
		}

		std::vector<PSF_ChainRange> chain_range_set;

		PSF_ChainRange chain_range = {std::min(bond_pairs[0].lhs(), bond_pairs[0].rhs()) - 1, 0};
		PSF_BondPair previous_bond_pair = bond_pairs[0];
		const std::size_t& bond_num = bond_pairs.size();

		for (std::size_t index = 1; index < bond_num; ++index) {
			if ((bond_pairs[index].lhs() == previous_bond_pair.lhs()) ||
				(bond_pairs[index].lhs() == previous_bond_pair.rhs()) ||
				(bond_pairs[index].rhs() == previous_bond_pair.lhs()) ||
				(bond_pairs[index].rhs() == previous_bond_pair.rhs())) {
				previous_bond_pair = bond_pairs[index];
			//	std::cout << previous_bond_pair.lhs() << std::endl;
			//	std::cout << previous_bond_pair.rhs() << std::endl;
				continue;
			}
			else {
				chain_range.end_index() = std::max(previous_bond_pair.lhs(), previous_bond_pair.rhs()) - 1;
				chain_range_set.push_back(chain_range);
				chain_range.begin_index() = std::min(bond_pairs[index].lhs(), bond_pairs[index].rhs()) - 1;
				previous_bond_pair = bond_pairs[index];
				continue;
			}
		}

		chain_range.end_index() = std::max(previous_bond_pair.lhs(), previous_bond_pair.rhs()) - 1;
		chain_range_set.push_back(chain_range);

		return chain_range_set;
	}



	PSF_AtomLine atom(const std::size_t& index) const {return atom_lines[index];}
	PSF_AtomLine& atom(const std::size_t& index) {return atom_lines[index];}
	PSF_BondPair bond(const std::size_t& index) const {return bond_pairs[index];}
	PSF_BondPair& bond(const std::size_t& index) {return bond_pairs[index];}

private:
	
	std::vector<PSF_AtomLine> atom_lines;
	std::vector<PSF_BondPair> bond_pairs;

};

}


#endif /* TRYAMP_PSF_TOPOLOGY_HPP */
