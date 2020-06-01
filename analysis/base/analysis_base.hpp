// analysis_base
// vim: tabstop=4 shiftwidth=4 softtabstop=4 
// ===========================================================================================


// ===========================================================================================

#ifndef TRYAMP_ANALYSIS_BASE_HPP
#define TRYAMP_ANALYSIS_BASE_HPP
#include<iostream>
#include<string>


namespace Amp::analysis {


template<typename T>
class AnalysisBase {


public:

	AnalysisBase() = default;
	~AnalysisBase() = default;
//	AnalysisBase(const std::string& input_traj, const std::string& input_topo);

/* run analysis
	When a run method has no argument, it becomes the default run method on Interface Class.
	On the other hand, run methods which have some arguments become user-defined method
	on Analysis Method Class (Template Parameter T of AnalysisBase Class).
*/

	template<typename... Args>
	auto run(const Args&... arguments) {
		return static_cast<T&>(this)->run(arguments...);
	}

// ================================================================================ 


/* file loading method
*/

	template<typename... Args>
	auto load_file(const Args&... filenames)
	-> decltype(std::initializer_list<std::string>{filenames...}, std::declval<void>()) {
		return static_cast<T&>(this)->load_file(filenames...);
	}

// member methods for default run method, run(void);

	bool is_loaded();

//	template<typename... Args>
	void prepare();

//	template<typename... Args>
	void calculate();

//	template<typename... Args>
//	void conclude();

//private:

//	void load_traj(const std::string& input_traj);
//	void load_topo(const std::string& input_topo);
//	void load_para(const std::string& input_para);
};

}


#endif /* TRYAMP_ANALYSIS_BASE_HPP */
