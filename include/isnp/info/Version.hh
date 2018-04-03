#ifndef isnp_info_Version_hh
#define isnp_info_Version_hh

#include <vector>
#include <G4String.hh>

namespace isnp {

namespace info {

/**
 * Class provides information about library's version.
 */
class Version {
public:

	Version() = delete;

	static const std::vector<int> Get();
	static const G4String GetAsString();
	static bool Matches(int major, int minor = -1, int patch = -1);

private:

};

}

}

#endif	//	isnp_info_Version_hh
