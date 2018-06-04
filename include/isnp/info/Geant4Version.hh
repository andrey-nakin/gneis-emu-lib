#ifndef isnp_info_Geant4Version_hh
#define isnp_info_Geant4Version_hh

#include <vector>
#include <G4String.hh>

namespace isnp {

namespace info {

/**
 * Class provides information about Geant4 version.
 */
class Geant4Version {
public:

	Geant4Version() = delete;

	static const std::vector<int> Get();
	static const G4String GetAsString();
	static bool Matches(int major, int minor = -1, int patch = -1);
	static const G4String GetDateAsString();

private:

};

}

}

#endif	//	isnp_info_Geant4Version_hh
