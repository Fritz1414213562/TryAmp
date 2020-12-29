#ifndef TRYAMP_HYDROGEN_BOND_HEAVYGROUP_HPP
#define TRYAMP_HYDROGEN_BOND_HEAVYGROUP_HPP
#include<string>

namespace Amp::analysis {

struct HBond_HeavyDonor {


	template<typename... Args>
	HBond_HeavyDonor(const Args&... arguments) : _atoms{" N  ", arguments...} {}
	HBond_HeavyDonor(const std::vector<std::string>& input_atoms) : _atoms(input_atoms) {}
//	HBond_HeavyDonor(const std::vector<std::string>& input_atoms) : _atoms{" N  "} {
//		_atoms.insert(_atoms.end(), input_atoms.begin(), input_atoms.end());
//	}
	~HBond_HeavyDonor() = default;

	std::string operator[](const std::size_t& idx) const {return _atoms[idx];}
	std::string at(const std::size_t& idx) const {return _atoms.at(idx);}
	std::size_t donor_atom_num() const {return _atoms.size();}

private:

	std::vector<std::string> _atoms;
};


struct HBond_HeavyAcceptor {

	template<typename... Args>
	HBond_HeavyAcceptor(const Args&... arguments) : _atoms{" O  ", " OC1", " OC2", arguments...} {}
	HBond_HeavyAcceptor(const std::vector<std::string>& input_atoms) : _atoms(input_atoms) {}
//	HBond_HeavyAcceptor(const std::vector<std::string>& input_atoms) : _atoms{" O  ", " OC1" ," OC2"}
//	{
//		_atoms.insert(_atoms.end(), input_atoms.begin(), input_atoms.end());
//	}
	~HBond_HeavyAcceptor() = default;

	std::string operator[](const std::size_t& idx) const {return _atoms[idx];}
	std::string at(const std::size_t& idx) const {return _atoms.at(idx);}
	std::size_t acceptor_atom_num() const {return _atoms.size();}

private:
	std::vector<std::string> _atoms;

};


}

#endif // TRYAMP_HYDROGEN_BOND_HEAVYGROUP_HPP
