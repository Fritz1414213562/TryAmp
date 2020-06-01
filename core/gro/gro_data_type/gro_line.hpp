#ifndef TRYAMP_DATA_TYPE_LINE_HPP
#define TRYAMP_DATA_TYPE_LINE_HPP
#include<string>
#include<array>


namespace Amp {


struct Gro_Line {

public:


	Gro_Line() = delete;

	~Gro_Line() = default;

	Gro_Line(
		const int& input_resi_id,
		const std::string& input_resi_name,
		const std::string& input_atom_name,
		const int& input_atom_id,
		const std::array<float, 3>& input_coord) :
			_resi_id(input_resi_id),
			_resi_name(input_resi_name),
			_atom_name(input_atom_name),
			_atom_id(input_atom_id),
			_coord(input_coord),
			_velo({0., 0., 0.}) {}
	
	Gro_Line(
		const int& input_resi_id,
		const std::string& input_resi_name,
		const std::string& input_atom_name,
		const int& input_atom_id,
		const std::array<float, 3>& input_coord,
		const std::array<float, 3>& input_velo) :
			_resi_id(input_resi_id),
			_resi_name(input_resi_name),
			_atom_name(input_atom_name),
			_atom_id(input_atom_id),
			_coord(input_coord),
			_velo(input_velo) {}
	

	int resi_id() const {return _resi_id;}
	int& resi_id() {return _resi_id;}
	std::string resi_name() const {return _resi_name;}
	std::string& resi_name() {return _resi_name;}
	std::string atom_name() const {return _atom_name;}
	std::string& atom_name() {return _atom_name;}
	int atom_id() const {return _atom_id;}
	int& atom_id() {return _atom_id;}	
	std::array<float, 3> coordinates() const {return _coord;}
	std::array<float, 3>& coordinates() {return _coord;}
	std::array<float, 3> velocity() const {return _velo;}
	std::array<float, 3>& velocity() {return _velo;}

	
private:

	int _resi_id;
	std::string _resi_name;
	std::string _atom_name;
	int _atom_id;
	std::array<float, 3> _coord;
	std::array<float, 3> _velo;

};

}


#endif /* TRYAMP_DATA_TYPE_LINE_HPP */
