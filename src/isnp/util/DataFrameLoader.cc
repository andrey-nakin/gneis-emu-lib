#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace util {

DataFrameLoader::DataFrameLoader(std::set<G4String> const& aNumericColumns,
		std::set<G4String> const& aCategoryColumns) :
		numericColumns(aNumericColumns), categoryColumns(aCategoryColumns) {

}

std::unique_ptr<DataFrame> DataFrameLoader::load(std::istream& is) {

	// @TODO

}

}

}
