#ifndef HYDROGEN_BOND_SEARCH_HPP
#define HYDROGEN_BOND_SEARCH_HPP
#include<TryAmp/analysis/hbond/donor_hydrogen_search.hpp>
#include<TryAmp/analysis/hbond/acceptor_search.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<vector>
#include<array>
#include<cmath>


namespace Amp::analysis {


struct HydrogenBond {

	HydrogenBond() = default;
	~HydrogenBond() = default;

	HydrogenBond(
		const HBond_Donor& donor,
		const HBond_Acceptor& acceptor,
		const float& dist,
		const float& deg) :
		_donor_heavy(donor.heavy_atom_line()),
		_donor_hydrogen(donor.hydrogen_atom_line()),
		_acceptor_heavy(acceptor.heavy_atom_line()),
		_dist(dist),
		_angle(deg) {}
	
	PDB_AtomLine donor_heavy() const {return _donor_heavy;}
	PDB_AtomLine donor_hydrogen() const {return _donor_hydrogen;}
	PDB_AtomLine acceptor_heavy() const {return _acceptor_heavy;}

	float length() const {return _dist;}
	float angle() const {return _angle;}

private:

	PDB_AtomLine _donor_heavy;
	PDB_AtomLine _donor_hydrogen;
	PDB_AtomLine _acceptor_heavy;
	float _dist = 0.;
	float _angle = 0.;

};


inline std::vector<HydrogenBond> search_hydrogen_bond(
	const std::vector<HBond_Donor>& donor_set, const std::vector<HBond_Acceptor>& acceptor_set,
	const float& cutoff_length, const float& cutoff_degree) {

	const float& pi = std::acos(-1.0);

	std::vector<HydrogenBond> result;

	for (const HBond_Donor& donor : donor_set) {
		const PDB_AtomLine& donor_heavy = donor.heavy_atom_line();
		const PDB_AtomLine& donor_hydrogen = donor.hydrogen_atom_line();
		const std::array<float, 3>& hydrogen_position = donor_hydrogen.coordinate();

		std::array<float, 3> h2d_vec;
		for (std::size_t idim = 0; idim < 3; ++idim)
			h2d_vec[idim] = donor_heavy.coordinate()[idim] - hydrogen_position[idim];

		float h2d_scalar = 0.;
		for (std::size_t idim = 0; idim < 3; ++idim)
			h2d_scalar += (h2d_vec[idim] * h2d_vec[idim]);
		h2d_scalar = std::sqrt(h2d_scalar);

		for (const HBond_Acceptor& acceptor : acceptor_set) {
			const PDB_AtomLine& acceptor_heavy = acceptor.heavy_atom_line();

			std::array<float, 3> h2a_vec;
			for (std::size_t idim = 0; idim < 3; ++idim)
				h2a_vec[idim] = acceptor_heavy.coordinate()[idim] - hydrogen_position[idim];

			float h2a_scalar = 0.;
			for (std::size_t idim = 0; idim < 3; ++idim)
				h2a_scalar += (h2a_vec[idim] * h2a_vec[idim]);
			h2a_scalar = std::sqrt(h2a_scalar);

			float dha_cos = 0.;
			for (std::size_t idim = 0; idim < 3; ++idim)
				dha_cos += (h2a_vec[idim] * h2d_vec[idim]);
			dha_cos /= (h2d_scalar * h2a_scalar);
			const float& dha_degree = std::acos(dha_cos) * 180.0 / pi;

			if ((h2a_scalar <= cutoff_length) && (dha_degree >= cutoff_degree))
				result.push_back(HydrogenBond(donor, acceptor, h2a_scalar, dha_degree));
		}
	}

	return result;
}

}


#endif // HYDROGEN_BOND_SEARCH_HPP
