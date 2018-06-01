#include "isnp/util/DataFrame.hh"

namespace isnp {

namespace util {

DataFrame::size_type DataFrame::size() const {

	return numericData.empty() ? 0 : numericData.cbegin()->second.size();

}

const DataFrame::DoubleVector& DataFrame::numeric(
		const G4String& columnName) const {

	auto const it = numericData.find(columnName);
	if (it == numericData.cend()) {
		throw NoSuchColumnException();
	}

	return it->second;

}

}

}
