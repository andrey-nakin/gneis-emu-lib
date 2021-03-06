#include <cmath>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include "isnp/dist/GaussEllipse.hh"

namespace isnp {

namespace dist {

// relation between Full Width at High Maximum and sigma parameter of Gauss distribution
G4double const static FWHM = 1.0 / (2 * std::sqrt(2 * std::log(2)));

G4ThreeVector GaussEllipse::Generate() const {

	G4double const x = CLHEP::RandGauss::shoot() * GetProps().GetXWidth()
			* FWHM;
	G4double const y = CLHEP::RandGauss::shoot() * GetProps().GetYWidth()
			* FWHM;
	return G4ThreeVector(x, y, 0);

}

}

}
