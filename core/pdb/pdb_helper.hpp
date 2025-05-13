#ifndef TRYAMP_PDB_HELPER_HPP
#define TRYAMP_PDB_HELPER_HPP
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<TryAmp/core/snapshot.hpp>
#include<iostream>
#include<vector>
#include<array>


namespace Amp {


inline Snapshot<float, 3> pdb2snap(const std::vector<Amp::PDB_AtomLine>& pdb_atomlines) {

	Snapshot<float, 3> retval(pdb_atomlines.size());

	for (std::size_t iatom = 0; iatom < pdb_atomlines.size(); ++iatom) {
		const std::array<float, 3>& atom_coord = pdb_atomlines[iatom].coordinate();
		for (int idim = 0; idim < 3; ++idim) {
			retval(idim, iatom) = atom_coord[idim];
		}
	}
	return retval;
}


}

#endif // TRYAMP_PDB_HELPER_HPP
