// analysis_interface
// vim: tabstop=4 shiftwidth=4 softtabstop=4 
// =====================================================================================
// =====================================================================================

#ifndef TRYAMP_ANALYSIS_INTERFACE_HPP
#define TRYAMP_ANALYSIS_INTERFACE_HPP
#include<TryAmp/analysis/base/analysis_base.hpp>
#include<TryAmp/core/dcd/dcd.hpp>
#include<TryAmp/core/psf/psf.hpp>
#include<memory>
#include<string>
#include<iostream>
#include<vector>


namespace Amp {


template<typename T, bool isExtended = std::is_base_of<analysis::AnalysisBase<T>, T>::value>
class AnalysisInterface {
	static_assert(isExtended, "AnalysisBase Class is not extended.");
	/* assertion
		Analysis Method should extend AnalysisBase Class.
	*/
};


template<typename T>
class AnalysisInterface<T, true> {

public:


//	constructor
	template<typename... Args>
	AnalysisInterface(const Args&... arguments) {
		_object = std::make_unique<T>(arguments...);
	}
//	destructor
	~AnalysisInterface() = default;






// =======================================================================================

/*
	User-defined AnalysisMethod Class must have a run method and load_file method.
*/

//	call user-defined run analysis
	template<typename... Args>
	auto run(const Args&... arguments) {return _object->run(arguments...);}


//	default run analysis
/*	If you use default run, you have to define on a Method Class such methods as
		is_loaded(void) -> bool,
		prepare(void) -> void,
		calculate(void) -> void,
		conclude(void) -> void
*/
	auto run() {
		if (not _object->is_loaded())
			throw std::logic_error(
			"RunMethodLogicError: You must load some files before calling run methods.");

		if (is_debug_mode) std::cout << "Reading data" << std::endl;
		// read file and store data on AnalysisMethod Class
		_object->prepare();
		if (is_debug_mode) std::cout << "Calculation" << std::endl;
		// analysis and calculation
		_object->calculate();
		if (is_debug_mode) std::cout << "Conclusion" << std::endl;
		// conclusion and return
		return _object->conclude();
	}



/*
	file loading method
*/


	template<typename... Args>
	auto load_file(const Args&... filenames)
	-> decltype(std::initializer_list<std::string>{filenames...}, std::declval<void>()) {
		return _object->load_file(filenames...);
	}


	void set_debug() {
		is_debug_mode = true;
		_object->set_debug();
	}


private:
	std::unique_ptr<T> _object;

	bool is_debug_mode = false;

};


}


#endif // TRYAMP_ANALYSIS_INTERFACE_HPP
