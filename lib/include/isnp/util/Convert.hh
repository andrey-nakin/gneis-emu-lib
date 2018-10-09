#ifndef isnp_util_Convert_hh
#define	isnp_util_Convert_hh

#include <G4String.hh>
#include <G4ThreeVector.hh>

namespace isnp {

namespace util {

class Convert {
public:

	static G4ThreeVector StringsToVector(G4String const &x, G4String const &y,
			G4String const &z, G4String const &units);

	static G4ThreeVector CommandToVector(const char* cmd);

private:

	Convert();

};

}

}

#endif	//	isnp_util_Convert_hh
