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
	typedef std::map<G4String, unsigned> PrecisionMap;

	struct DataPack {

		FloatVectorMap floatColumns;
		CategoryVectorMap categoryColumns;
		CategoryNameMap categoryNames;
		PrecisionMap precisions;

	};

public:

	class NoSuchColumnException: public std::exception {

	};

	typedef FloatVector::size_type size_type;

	DataFrame(DataFrame&&);

	size_type Size() const;

	G4String const& CategoryName(const G4String& columnName,
			CategoryId id) const;
	CategoryVector const& CategoryColumn(const G4String& columnName) const;
	FloatVector const& FloatColumn(const G4String& columnName) const;
	unsigned Precision(const G4String& columnName) const;

	G4String const& CategoryValue(const G4String& columnName,
			const size_type i) const {

		return CategoryName(columnName, CategoryColumn(columnName)[i]);

	}

	float FloatValue(const G4String& columnName, const size_type i) const {

		return FloatColumn(columnName)[i];

	}

private:

	friend class DataFrameLoader;

	DataFrame (std::unique_ptr<DataPack>);

	std::unique_ptr<DataPack> data;

};

}

}

#endif	//	isnp_utl_DataFrame_hh
