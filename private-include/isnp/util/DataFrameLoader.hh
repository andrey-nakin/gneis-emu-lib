#ifndef isnp_util_DataFrameLoader_hh
#define isnp_util_DataFrameLoader_hh

#include <iostream>
#include <memory>
#include <set>

#include "isnp/util/DataFrame.hh"

namespace isnp {

namespace util {

/**
 * Loads DataFrame from a stream.
 */
class DataFrameLoader {

public:

	DataFrameLoader(std::set<G4String> const& aNumericColumns, std::set<G4String> const& aCategoryColumns);

	std::unique_ptr<DataFrame> load(std::istream&);

private:

	std::set<G4String> const numericColumns, categoryColumns;

};

}

}

#endif	//	isnp_util_DataFrameLoader_hh
