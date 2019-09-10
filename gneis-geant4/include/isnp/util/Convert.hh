#ifndef isnp_util_Convert_hh
#define	isnp_util_Convert_hh

#include <G4String.hh>
#include <G4ThreeVector.hh>
#include <G4Transform3D.hh>

namespace isnp {

namespace util {

class Convert {
public:

	static G4ThreeVector StringsToVector(G4String const &x, G4String const &y,
			G4String const &z, G4String const &units);

	static G4ThreeVector CommandToVector(const char* cmd);

	static G4Transform3D VectorsToTransform(G4ThreeVector rotation,
			G4ThreeVector translation);

private:

	Convert();

};

}

}

#endif	//	isnp_util_Convert_hh
