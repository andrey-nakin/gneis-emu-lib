#include <cmath>

#include <Randomize.hh>

#include "isnp/util/RandomNumberGenerator.hh"

namespace isnp {

namespace util {

G4double RandomNumberGenerator::locality(G4double const significant,
		unsigned const precision) {

	G4double halfRange;
	auto const log = std::log10(std::fabs(significant));

	if (log >= 0) {
		halfRange = std::pow(10.0, std::floor(log) - precision + 1) / 2;
	} else {
		halfRange = std::pow(10.0, -std::floor(-log) - precision) / 2;
	}

	return CLHEP::RandFlat::shoot(significant - halfRange,
			significant + halfRange);

}

}

}
