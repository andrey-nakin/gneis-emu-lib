#ifndef isnp_util_DataFrameLoader_hh
#define isnp_util_DataFrameLoader_hh

#include <iostream>
#include <memory>
#include <set>
#include <exception>

#include "isnp/util/DataFrame.hh"

namespace isnp {

namespace util {

/**
 * Loads DataFrame from a stream.
 */
class DataFrameLoader {

public:

	class LoaderException: public std::exception {

	};

	class NoColumnException: public LoaderException {
	public:

		NoColumnException(G4String const&);

		G4String const& GetColumnName() const {

			return colName;

		}

	private:

		G4String const colName;

	};

	class NoValueException: public LoaderException {
	public:

		NoValueException(G4String const& aColName, unsigned aLineNo);

		G4String const& GetColumnName() const {

			return colName;

		}

		unsigned GetLineNo() const {

			return lineNo;

		}

	private:

		G4String const colName;
		unsigned const lineNo;

	};

	DataFrameLoader(std::set<G4String> const& aFloatColumns,
			std::set<G4String> const& aCategoryColumns);

	DataFrame load(std::istream&) throw (LoaderException);

private:

	std::set<G4String> const floatColumns, categoryColumns;
	char const commentChar, separatorChar;

};

}

}

#endif	//	isnp_util_DataFrameLoader_hh
