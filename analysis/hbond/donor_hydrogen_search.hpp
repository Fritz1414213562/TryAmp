#ifndef TRYAMP_HYDROGEN_BOND_DONOR_HYDROGEN_SEARCH_HPP
#define TRYAMP_HYDROGEN_BOND_DONOR_HYDROGEN_SEARCH_HPP
#include<TryAmp/analysis/hbond/hbond_hgroup_dict.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<array>
#include<utility>

namespace Amp::analysis {


struct HBond_Donor {

public:
	HBond_Donor() = default;
	~HBond_Donor() = default;
	HBond_Donor(const PDB_AtomLine& input_heavy_atom, const PDB_AtomLine& input_hydrogen_atom) :
		_heavy_atom_line(input_heavy_atom),
		_hydrogen_atom_line(input_hydrogen_atom) {}


	PDB_AtomLine heavy_atom_line() const {return _heavy_atom_line;}
	PDB_AtomLine hydrogen_atom_line() const {return _hydrogen_atom_line;}

private:

	PDB_AtomLine _heavy_atom_line;
	PDB_AtomLine _hydrogen_atom_line;

};



inline std::vector<HBond_Donor> search_hbond_donor(
	const HBond_HeavyDonorDict& hd_dict, const std::vector<PDB_AtomLine>& resi_topo) {

	if (resi_topo.size() < 1)
		throw std::logic_error(
		"The residue which have no atom exists.");
	
	const std::string& resi_name = resi_topo[0].residue_name();
//	std::cout << resi_name << std::endl;
	const HBond_HeavyDonor& heavy_atom_names = hd_dict.at(resi_name);

	std::vector<HBond_Donor> result;

	for (std::size_t i_atom = 0; i_atom < heavy_atom_names.donor_atom_num(); ++i_atom) {
		const std::string& heavy_atom_name = heavy_atom_names[i_atom];
		const std::string& hydrogen_name = {'H', heavy_atom_name[2], heavy_atom_name[3]};
		// search the position of donor heavy atom
		PDB_AtomLine heavy_atom;
		bool exists_donor = false;

		for (const PDB_AtomLine& atom_line : resi_topo) {
			if (heavy_atom_name == atom_line.atom_name()) {
				heavy_atom = atom_line;
				exists_donor = true;
				break;
			}
		}
		if (not exists_donor) continue;

		for (const PDB_AtomLine& atom_line : resi_topo) {
			const std::string& atom_kind = atom_line.atom_name().substr(1, 3);
			if (atom_kind == hydrogen_name) {
				result.push_back(HBond_Donor(heavy_atom, atom_line));
			}
		}
	}

	return result;
}


}


#endif // TRYAMP_HYDROGEN_BOND_DONOR_HYDROGEN_SEARCH_HPP
