#ifndef TRYAMP_GRO_READER_HPP
#define TRYAMP_GRO_READER_HPP
#include<Amp/core/gro/gro_parser.hpp>
#include<Amp/core/gro/gro_data_type/gro_line.hpp>
#include<iostream>
#include<string>
#include<array>


namespace Amp {


class GROReader : public GROParser {


public:

	GROReader() : GROParser() {}
	GROReader(const std::string& input_filename) : GROParser(input_filename) {}
	~GROReader() = default;




	void read();
	void read(const std::string& filename);




	int atom_num() const {return _atom_num;}
	std::string title() const {return _title;}
	std::vector<Gro_Line> structure() const {return _structure;}
	std::array<float, 9> box_vector() const {return _box_vector;}

private:

	constexpr std::size_t LINE_SIZE_WO_VELO = 44;

	int _atom_num = 0;
	std::string _title;
	std::array<float, 9> _box_vector;

	std::vector<Gro_Line> _structure;

};




void GROReader::read() {
	if (!input_file.is_open())
		throw std::runtime_error(
			"FileOpenError: The input file cannot be opened.");
	
	if (!_structure.empty()) _structure.clear();
	
	std::getline(input_file, _title);
	if (_title.empty()) std::cout << "No Title" << std::endl;
	else std::cout << "Title: " <<  _title << std::endl;

	std::string buffer;
	std::getline(input_file, buffer);
	_atom_num = std::stoi(buffer);
	buffer.clear();

	for (int i_atom = 0; i_atom < _atom_num; ++i_atom) {
		std::getline(input_file, buffer);
		if (buffer.size() > LINE_SIZE_WO_VELO) {
			const int& buffer_resi_id = read_ResiNum(buffer);
			const std::string& buffer_resi_name = read_ResiName(buffer);
			const std::string& buffer_atom_name = read_AtomName(buffer);
			const int& buffer_atom_id = read_AtomNum(buffer);
			const std::array<float, 3>& buffer_coord = read_Coordinates(buffer);
			const std::array<float, 3>& buffer_velo = read_Velocity(buffer);
			const Gro_Line& atom_line(
				buffer_resi_id,
				buffer_resi_name,
				buffer_atom_name,
				buffer_atom_id,
				buffer_coord,
				buffer_velo
			);
			_structure.push_back(atom_line);
		}
		else {
		}

	}

}


}


#endif /* TRYAMP_GRO_READER_HPP */
