#ifndef TRYAMP_ANALYSIS_HPP
#define TRYAMP_ANALYSIS_HPP

// interface, base and common
#include<TryAmp/analysis/analysis_interface.hpp>
#include<TryAmp/analysis/base/analysis_base.hpp>
#include<vector>

// method

#include<TryAmp/analysis/hbond/hydrogen_bond_analysis.hpp>


namespace Amp {


// about hydrogen bond

using HydrogenBondAnalysis = AnalysisInterface<analysis::HydrogenBondAnalysis>;
using HBond_HeavyDonorNames = std::vector<analysis::HBond_HeavyDonor>;
using HBond_HeavyAcceptorNames = std::vector<analysis::HBond_HeavyAcceptor>;
using HBond = analysis::HydrogenBond;

}


#endif // TRYAMP_ANALYSIS_HPP
