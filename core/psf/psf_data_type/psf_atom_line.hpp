#ifndef TRYAMP_PSF_ATOM_LINE_HPP
#define TRYAMP_PSF_ATOM_LINE_HPP
#include<vector>


namespace Amp {

struct PSF_AtomLine {

public:
	PSF_AtomLine(const int& atom_id, const std::string& segment_name, const int& residue_id, const std::string& residue_name, const std::string& atom_name, const std::string& atom_type, const float& charge, const float& mass, const int& unused_zero) :
	psf_atom_id(atom_id),
	psf_segment_name(segment_name),
	psf_residue_id(residue_id),
	psf_residue_name(residue_name),
	psf_atom_name(atom_name),
	psf_atom_type(atom_type),
	psf_charge(charge),
	psf_mass(mass),
	psf_unused_zero(unused_zero) {}

	~PSF_AtomLine() = default;


	// access
	int atom_id() const {return psf_atom_id;}
	std::string segment_name() const {return psf_segment_name;}
	int residue_id() const {return psf_residue_id;}
	std::string residue_name() const {return psf_residue_name;}
	std::string atom_name() const {return psf_atom_name;}
	std::string atom_type() const {return psf_atom_type;}
	float charge() const {return psf_charge;}
	float mass() const {return psf_mass;}
	int unuzed_zero() const {return psf_unused_zero;}


private:

	const int psf_atom_id;
	const std::string psf_segment_name;
	const int psf_residue_id;
	const std::string psf_residue_name;
	const std::string psf_atom_name;
	const std::string psf_atom_type;
	const float psf_charge;
	const float psf_mass;
	const int psf_unused_zero;
	

};

}


#endif /* TRYAMP_PSF_ATOM_LINE_HPP */
