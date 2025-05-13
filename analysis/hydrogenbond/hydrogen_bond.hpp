#ifndef TRYAMP_ANALYSIS_HYDROGEN_BOND_HPP
#define TRYAMP_ANALYSIS_HYDROGEN_BOND_HPP
#include<TryAmp/analysis/hydrogenbond/donor_heavy.hpp>
#include<TryAmp/analysis/hydrogenbond/donor_hydrogen.hpp>
#include<TryAmp/analysis/hydrogenbond/acceptor.hpp>
#include<TryAmp/core/pdb/pdb_data_type/pdb_atom_line.hpp>
#include<vector>
#include<array>
#include<cmath>


namespace Amp::analysis {


struct HydrogenBond {

	HydrogenBond() = default;
	~HydrogenBond() = default;

	HydrogenBond(
		const std::string& input_donor_heavy,
		const std::string& input_donor_hydrogen
		const std::string& input_acceptor,
		const float& dist,
		const float& deg) :
		_donor_heavy   (input_donor_heavy),
		_donor_hydrogen(input_donor_hydrogen),
		_acceptor(input_acceptor),
		_dist(dist),
		_angle(deg) {}
	
	std::string donor_heavy() const {return _donor_heavy;}
	std::string donor_hydrogen() const {return _donor_hydrogen;}
	std::string acceptor() const {return _acceptor;}

	float length() const {return _dist;}
	float angle() const {return _angle;}

private:

	std::string _donor_heavy;
	std::string _donor_hydrogen;
	std::string _acceptor;
	float _dist = 3.;
	float _angle = 120.;

};


}


#endif // TRYAMP_ANALYSIS_HYDROGEN_BOND_HPP
