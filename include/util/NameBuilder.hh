#ifndef NameBuilder_hh
#define NameBuilder_hh

#include <G4String.hh>

namespace gneis {

namespace util {

/**
 * Construction of composite names.
 */
class NameBuilder final {
public:

	NameBuilder() = delete;

	static G4String Make(const char *parent, const char *child);
	static G4String Make(G4String const &parent, const char *child);
	static G4String Make(G4String const &parent, G4String const &child);

private:

	static G4String GetSeparator();

};

}

}

#endif	//	NameBuilder_hh
