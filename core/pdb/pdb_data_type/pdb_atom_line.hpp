#ifndef TRYAMP_PDB_ATOM_LINE_HPP
#define TRYAMP_PDB_ATOM_LINE_HPP
#include<vector>


namespace Amp {


struct PDB_AtomLine {


public:

	PDB_AtomLine() = default;
	PDB_AtomLine(
		const int& input_atom_serial_num,
		const std::string& input_atom_name,
		const char& input_alt_loc,
		const std::string& input_residue_name,
		const char& input_chain_id,
		const int& input_residue_seq_num,
		const char& input_insert_code,
		const std::array<float, 3>& input_coord,
		const float& input_occupancy,
		const float& input_temp,
		const std::string& input_element,
		const float& input_charge) : 
			_atom_serial_id(input_atom_serial_num),
			_atom_name(input_atom_name),
			_alt_loc(input_alt_loc),
			_residue_name(input_residue_name),
			_chain_id(input_chain_id),
			_residue_seq_id(input_residue_seq_num),
			_insertion_code(input_insert_code),
			_coord(input_coord),
			_occupancy(input_occupancy),
			_temp(input_temp),
			_element(input_element),
			_atom_charge(input_charge) {}
		

	int atom_id() const {return _atom_serial_id;}
	int& atom_id() {return _atom_serial_id;}
	std::string atom_name() const {return _atom_name;}
	std::string& atom_name() {return _atom_name;}
	char alt_loc() const {return _alt_loc;}
	char& alt_loc() {return _alt_loc;}
	std::string residue_name() const {return _residue_name;}
	std::string& residue_name() {return _residue_name;}
	char chain_id() const {return _chain_id;}
	char& chain_id() {return _chain_id;}
	int residue_seq_id() const {return _residue_seq_id;}
	int& residue_seq_id() {return _residue_seq_id;}
	char insert_code() const {return _insertion_code;}
	char& insert_code() {return _insertion_code;}
	std::array<float, 3> coordinate() const {return _coord;}
	std::array<float, 3>& coordinate() {return _coord;}
	float occupancy() const {return _occupancy;}
	float& occupancy() {return _occupancy;}
	float temperature() const {return _temp;}
	float& temperature() {return _temp;}
	std::string element() const {return _element;}
	std::string& element() {return _element;}
	float charge() const {return _atom_charge;}
	float& charge() {return _atom_charge;}



private:

	int _atom_serial_id;
	std::string _atom_name;
	char _alt_loc;
	std::string _residue_name;
	char _chain_id;
	int _residue_seq_id;
	char _insertion_code;
	std::array<float, 3> _coord;
	float _occupancy;
	float _temp;
	std::string _element;
	float _atom_charge;


};


}



#endif /* TRYAMP_PDB_ATOM_LINE_HPP */
