#ifndef TRYAMP_HYDROGEN_BOND_ACCEPTOR_SEARCH_HPP
#define TRYAMP_HYDROGEN_BOND_ACCEPTOR_SEARCH_HPP
#include<TryAmp/analysis/hbond/hbond_hgroup_dict.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<array>
#include<utility>

namespace Amp::analysis {

struct HBond_Acceptor {

public:
	HBond_Acceptor() = default;
	~HBond_Acceptor() = default;
	HBond_Acceptor(const PDB_AtomLine& input_atom_line) : _heavy_atom_line(input_atom_line) {}
	
	PDB_AtomLine heavy_atom_line() const {return _heavy_atom_line;}

private:

	PDB_AtomLine _heavy_atom_line;

};


inline std::vector<HBond_Acceptor> search_acceptor(
	const HBond_HeavyAcceptorDict& ha_dict, const std::vector<PDB_AtomLine>& resi_topo) {

	if (resi_topo.size() < 1)
		throw std::logic_error(
		"The residue which have no atom exists.");
	
	const std::string& resi_name = resi_topo[0].residue_name();
	const HBond_HeavyAcceptor& heavy_atom_names = ha_dict.at(resi_name);

	std::vector<HBond_Acceptor> result;

	for (std::size_t i_atom = 0; i_atom < heavy_atom_names.acceptor_atom_num(); ++i_atom) {
		const std::string& heavy_atom_name = heavy_atom_names[i_atom];

		for (const PDB_AtomLine& atom_line : resi_topo) {
			if (heavy_atom_name == atom_line.atom_name()) {
				result.push_back(HBond_Acceptor(atom_line));
			}
		}
	}
	return result;
}


}


#endif // TRYAMP_HYDROGEN_BOND_ACCEPTOR_SEARCH_HPP
