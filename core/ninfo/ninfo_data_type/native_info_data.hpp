#ifndef TRYAMP_NATIVEINFO_DATA_HPP
#define TRYAMP_NATIVEINFO_DATA_HPP
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_aicg13_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_aicgdih_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_angl_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_bond_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_contact_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_dihd_line.hpp>
#include<TryAmp/core/ninfo/ninfo_data_type/ninfo_pdns_line.hpp>


namespace Amp {


struct NativeInfo {

public:

	NativeInfo() = default;
	~NativeInfo() = default;

	Ninfo_BondLine bond(const std::size_t& index) const {return native_bond_data[index];}
	Ninfo_BondLine& bond(const std::size_t& index) {return native_bond_data[index];}

	Ninfo_AnglLine angle(const std::size_t& index) const {return native_angle_data[index];}
	Ninfo_AnglLine& angle(const std::size_t& index) {return native_angle_data[index];}

	Ninfo_AICG13Line aicg13(const std::size_t& index) const {return native_aicg13_data[index];}
	Ninfo_AICG13Line& aicg13(const std::size_t& index) {return native_aicg13_data[index];}

	Ninfo_DihdLine dihedral(const std::size_t& index) const {return native_dihedral_data[index];}
	Ninfo_DihdLine& dihedral(const std::size_t& index) {return native_dihedral_data[index];}

	Ninfo_AICGDihLine aicgdih(const std::size_t& index) const {return native_aicgdih_data[index];}
	Ninfo_AICGDihLine& aicgdih(const std::size_t& index) {return native_aicgdih_data[index];}

	Ninfo_ContactLine contact(const std::size_t& index) const {return native_contact_data[index];}
	Ninfo_ContactLine& contact(const std::size_t& index) {return native_contact_data[index];}

	Ninfo_PDNSLine pdns(const std::size_t& index) const {return native_pdns_data[index];}
	Ninfo_PDNSLine& pdns(const std::size_t& index) {return native_pdns_data[index];}

	std::size_t bond_data_size() const {return native_bond_data.size();}
	std::size_t angle_data_size() const {return native_angle_data.size();}
	std::size_t aicg13_data_size() const {return native_aicg13_data.size();}
	std::size_t dihedral_data_size() const {return native_dihedral_data.size();}
	std::size_t aicgdih_data_size() const {return native_aicgdih_data.size();}
	std::size_t contact_data_size() const {return native_contact_data.size();}
	std::size_t pdns_data_size() const {return native_pdns_data.size();}


	void add_BondLine(const Ninfo_BondLine& bond_line) {native_bond_data.push_back(bond_line);}
	void add_AnglLine(const Ninfo_AnglLine& angl_line) {native_angle_data.push_back(angl_line);}
	void add_AICG13Line(const Ninfo_AICG13Line& aicg13_line) {native_aicg13_data.push_back(aicg13_line);}
	void add_DihdLine(const Ninfo_DihdLine& dihd_line) {native_dihedral_data.push_back(dihd_line);}
	void add_AICGDihLine(const Ninfo_AICGDihLine& aicgdih_line) {native_aicgdih_data.push_back(aicgdih_line);}
	void add_ContactLine(const Ninfo_ContactLine& contact_line) {native_contact_data.push_back(contact_line);}
	void add_PDNSLine(const Ninfo_PDNSLine& pdns_line) {native_pdns_data.push_back(pdns_line);}

	template<typename... Args>
	void add_BondLine(const Args&... args) {native_bond_data.push_back(Ninfo_BondLine(args...));}
	template<typename... Args>
	void add_AnglLine(const Args&... args) {native_angle_data.push_back(Ninfo_AnglLine(args...));}
	template<typename... Args>
	void add_AICG13Line(const Args&... args) {native_aicg13_data.push_back(Ninfo_AICG13Line(args...));}
	template<typename... Args>
	void add_DihdLine(const Args&... args) {native_dihedral_data.push_back(Ninfo_DihdLine(args...));}
	template<typename... Args>
	void add_AICGDihLine(const Args&... args) {native_aicgdih_data.push_back(Ninfo_AICGDihLine(args...));}
	template<typename... Args>
	void add_ContactLine(const Args&... args) {native_contact_data.push_back(Ninfo_ContactLine(args...));}
	template<typename... Args>
	void add_PDNSLine(const Args&... args) {native_pdns_data.push_back(Ninfo_PDNSLine(args...));}

private:

	std::vector<Ninfo_BondLine> native_bond_data;
	std::vector<Ninfo_AnglLine> native_angle_data;
	std::vector<Ninfo_AICG13Line> native_aicg13_data;
	std::vector<Ninfo_DihdLine> native_dihedral_data;
	std::vector<Ninfo_AICGDihLine> native_aicgdih_data;
	std::vector<Ninfo_ContactLine> native_contact_data;
	std::vector<Ninfo_PDNSLine> native_pdns_data;

};

}


#endif /* TRYAMP_NATIVEINFO_DATA_HPP */
