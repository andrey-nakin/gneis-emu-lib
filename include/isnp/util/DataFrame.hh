#ifndef isnp_utl_DataFrame_hh
#define isnp_utl_DataFrame_hh

#include <vector>
#include <map>
#include <exception>
#include <cstdint>
#include <memory>

#include <G4Types.hh>
#include <G4String.hh>

namespace isnp {

namespace util {

class DataFrameLoader;

/**
 * Class holds one or several data vectors, with either numeric or categorized values.
 * All vectors have equal size.
 */
class DataFrame {

public:

	typedef uint8_t CategoryId;

private:

	typedef std::vector<CategoryId> CategoryVector;
	typedef std::vector<G4float> FloatVector;
	typedef std::map<G4String, CategoryVector> CategoryVectorMap;
	typedef std::map<CategoryId, G4String> CategoryMap;
	typedef std::map<G4String, CategoryMap> CategoryNameMap;
	typedef std::map<G4String, FloatVector> FloatVectorMap;

	struct DataPack {

		unsigned precision;
		FloatVectorMap floatColumns;
		CategoryVectorMap categoryColumns;
		CategoryNameMap categoryNames;

	};

public:

	class NoSuchColumnException: public std::exception {

	};

	typedef FloatVector::size_type size_type;

	DataFrame(DataFrame&&);

	unsigned GetPrecision() const {

		return data->precision;

	}

	size_type size() const;

	G4String const& categoryName(const G4String& columnName,
			CategoryId id) const throw (NoSuchColumnException);
	CategoryVector const& categoryColumn(const G4String& columnName) const
			throw (NoSuchColumnException);
	FloatVector const& floatColumn(const G4String& columnName) const
			throw (NoSuchColumnException);

private:

	friend class DataFrameLoader;

	DataFrame (std::unique_ptr<DataPack>);

	std::unique_ptr<DataPack> data;

};

}

}

#endif	//	isnp_utl_DataFrame_hh
