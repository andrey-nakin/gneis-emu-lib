#ifndef isnp_utl_RandomNumberGenerator_hh
#define isnp_utl_RandomNumberGenerator_hh

#include <G4Types.hh>

namespace isnp {

namespace util {

/**
 * Helper class for random number generation.
 */
class RandomNumberGenerator {

public:

	RandomNumberGenerator() = delete;

	static G4double locality(G4double significant, unsigned precision);

};

}

}

#endif	//	isnp_utl_RandomNumberGenerator_hh
