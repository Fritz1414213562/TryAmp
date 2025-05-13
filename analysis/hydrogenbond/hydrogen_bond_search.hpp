#ifndef TRYAMP_ANALYSIS_HYDROGEN_BOND_SEARCH_HPP
#define TRYAMP_ANALYSIS_HYDROGEN_BOND_SEARCH_HPP
#include<TryAmp/analysis/hydrogenbond/donor_hydrogen.hpp>
#include<TryAmp/analysis/hydrogenbond/donor_heavy.hpp>
#include<TryAmp/analysis/hydrogenbond/acceptor.hpp>
#include<TryAmp/analysis/hydrogenbond/hydrogen_bond.hpp>
#include<vector>
#include<array>
#include<cmath>


namespace Amp::analysis {


inline std::vector<HydrogenBond> search_hydrogen_bond(
	const std::vector<std::string>& donor_heavy_set, const std::vector<std::string>& acceptor_set,
	const std::vector<std::string>& donor_hydrogen_set,
	const float& cutoff_length, const float& cutoff_degree) {

	const float& pi = std::acos(-1.0);

	std::vector<HydrogenBond> result;

	for (const std::string& donor_heavy : donor_heavy_set) {
		const std::vector<std::string>& hydrogen_atoms = donor_hydrogen_dict[donor];

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


#endif // TRYAMP_ANALYSIS_HYDROGEN_BOND_SEARCH_HPP
