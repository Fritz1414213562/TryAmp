#ifndef TRYAMP_ANALYSIS_HYDROGEN_BOND_ANALYSIS_HPP
#define TRYAMP_ANALYSIS_HYDROGEN_BOND_ANALYSIS_HPP
#include<TryAmp/core/pdb/pdb.hpp>
#include<TryAmp/core/snapshot.hpp>
#include<TryAmp/analysis/base/analysis_base.hpp>
#include<TryAmp/analysis/hydrogenbond/hydrogen_bond.hpp>
#include<TryAmp/analysis/hydrogenbond/hydrogen_bond_search.hpp>
#include<fstream>
#include<vector>
#include<array>
#include<memory>
#include<utility>


namespace Amp::analysis {

class HydrogenBondAnalysis : public AnalysisBase<HydrogenBondAnalysis> {

public:


// constructors

	HydrogenBondAnalysis()	= default;

	HydrogenBondAnalysis(const std::string& input_topo) : _topo(input_topo) {}


// destructor

	~HydrogenBondAnalysis() = default;


	void load_file(const std::string& input_topo) {
		_topo = input_topo;
	}


//	components of a run method

	bool is_loaded() {
		std::ifstream tmp_file(_topo, std::ios::in);
		const bool retval = tmp_file.is_open();
		tmp_file.close();
		return retval;
	}

	void prepare();
	void calculate();

	std::vector<HydrogenBond> conclude();


//	additional option

//	void add_donor_type(
//		const std::vector<std::string>& additional_keys,
//		const std::vector<HBond_HeavyDonor>& additional_values) {
//		additional_donors = std::make_pair(additional_keys, additional_values);
//		is_donor_added = true;
//	}
//
//	void add_acceptor_type(
//		const std::vector<std::string>& additional_keys,
//		const std::vector<HBond_HeavyAcceptor>& additional_values) {
//		additional_acceptors = std::make_pair(additional_keys, additional_values);
//		is_acceptor_added = true;
//	}
//
//	void change_cutoff(const float& dist, const float& deg) {
//		cutoff_dist = dist;
//		cutoff_deg = deg;
//	}


private:

	std::string _topo;

	bool is_donor_added = false;
	bool is_acceptor_added = false;
	std::vector<std::string> donor_heavy_names;
	std::vector<std::string> donor_hydrogen_names;
	std::vector<std::string> acceptor_names;
	
	float cutoff_dist = 3.0;
	float cutoff_deg = 120.0;



	std::vector<std::vector<PDB_AtomLine>> _atom_info;
	std::vector<HydrogenBond> _hydrogen_bonds;


// about debuging
	bool is_debug_mode = false;
	void set_debug() {is_debug_mode = true;}
};






inline void HydrogenBondAnalysis::prepare() {
	std::unique_ptr<PDBReader> pdb_reader = std::make_unique<PDBReader>(_topo);
	const std::vector<PDB_AtomLine>& pdb_topo = pdb_reader->read();

	// divide atom line
	_atom_info = pdb_reader->divide_residues(pdb_topo);
}





inline void HydrogenBondAnalysis::calculate() {

	const HBond_HeavyDonorDict donor_dict
		= (is_donor_added)
			? HBond_HeavyDonorDict(additional_donors.first, additional_donors.second)
			: HBond_HeavyDonorDict();

	const HBond_HeavyAcceptorDict acceptor_dict
		= (is_acceptor_added)
			? HBond_HeavyAcceptorDict(additional_acceptors.first, additional_acceptors.second)
			: HBond_HeavyAcceptorDict();

	if (is_debug_mode)
		std::cout << "Donor and Acceptor pair is defined." << std::endl;

	std::vector<HBond_Donor> hbond_donor;
	std::vector<HBond_Acceptor> hbond_acceptor;

	for (const std::vector<PDB_AtomLine>& resi_topo : _atom_info) {

		const std::vector<HBond_Donor>& resi_hbond_donor
			= search_hbond_donor(donor_dict, resi_topo);
		const std::vector<HBond_Acceptor>& resi_hbond_acceptor
			= search_acceptor(acceptor_dict, resi_topo);

		for (const HBond_Donor& donor_atoms : resi_hbond_donor)
			hbond_donor.push_back(donor_atoms);
		for (const HBond_Acceptor& acceptor_atom : resi_hbond_acceptor)
			hbond_acceptor.push_back(acceptor_atom);

	}

	_hydrogen_bonds = search_hydrogen_bond(hbond_donor, hbond_acceptor, cutoff_dist, cutoff_deg);

}


inline std::vector<HydrogenBond> HydrogenBondAnalysis::conclude() {

	// deallocate _atom_info

	for (std::size_t i_resi = 0; i_resi < _atom_info.size(); ++i_resi) {
		std::vector<PDB_AtomLine>().swap(_atom_info[i_resi]);
	}
	std::vector<std::vector<PDB_AtomLine>>().swap(_atom_info);

	return _hydrogen_bonds;
}



}


#endif /* TRYAMP_ANALYSIS_HYDROGEN_BOND_ANALYSIS_HPP */
