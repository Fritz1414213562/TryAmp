#ifndef TRYAMP_DCD_3RDHEADER_HPP
#define TRYAMP_DCD_3RDHEADER_HPP
#include<vector>
#include<string>
#include<tuple>



namespace Amp {


struct DCD_3rdHeader {

public:

	DCD_3rdHeader() = default;

	DCD_3rdHeader(const int& input_atom_number) : _header(input_atom_number) {}

	~DCD_3rdHeader() = default;

	int atom_number() const {return _header;}
	int& atom_number() {return _header;}



private:

	int _header;

};


}



#endif /* TRYAMP_DCD_3RDHEADER_HPP */
