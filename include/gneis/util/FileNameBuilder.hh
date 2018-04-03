#ifndef gneis_util_FileNameBuilder_hh
#define gneis_util_FileNameBuilder_hh

#include <G4String.hh>

namespace gneis {

namespace util {

/**
 * Construction of disk file names.
 */
class FileNameBuilder final {
public:

	FileNameBuilder() = delete;

	static G4String Make(char const* base, char const* suffix = nullptr);
	static G4String Make(G4String const& base, char const* suffix = nullptr);
	static void SetCommonSuffix(G4String const& s);

private:

	static G4String commonSuffix;

};

}

}

#endif	//	gneis_util_FileNameBuilder_hh
