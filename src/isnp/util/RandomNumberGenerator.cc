#include <Randomize.hh>

#include "isnp/util/RandomNumberGenerator.hh"

namespace isnp {

namespace util {

G4double RandomNumberGenerator::locality(G4double const significant, unsigned const precision) {
	return CLHEP::RandFlat::shoot(significant - 0.000005, significant + 0.000005);
}

}

}
