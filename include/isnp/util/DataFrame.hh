#ifndef isnp_utl_DataFrame_hh
#define isnp_utl_DataFrame_hh

#include <vector>
#include <map>
#include <exception>

#include <G4Types.hh>
#include <G4String.hh>

namespace isnp {

namespace util {

/**
 * Class holds one or several data vectors, with either numeric or categorized values.
 * All vectors have equal size.
 */
class DataFrame {

	typedef std::vector<G4double> DoubleVector;
	typedef std::map<G4String, DoubleVector> DoubleVectorMap;

public:

	class NoDataException : public std::exception {

	};

	typedef DoubleVector::size_type size_type;

	unsigned GetPrecision() const {

		return precision;

	}

	size_type size() const;

	const DoubleVector& numeric(const G4String& columnName) const;

private:

	unsigned precision;
	DoubleVectorMap numericData;

};

}

}

#endif	//	isnp_utl_DataFrame_hh
