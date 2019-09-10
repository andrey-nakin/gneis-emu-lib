#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include "isnp/dist/UniformRectangle.hh"

namespace isnp {

namespace dist {

G4ThreeVector UniformRectangle::Generate() const {

	G4double const x =
			GetProps().GetXWidth() < 1.0 * angstrom ?
					0.0 :
					CLHEP::RandFlat::shoot(-GetProps().GetXHalfWidth(),
							GetProps().GetXHalfWidth());
	G4double const y =
			GetProps().GetYWidth() < 1.0 * angstrom ?
					0.0 :
					CLHEP::RandFlat::shoot(-GetProps().GetYHalfWidth(),
							GetProps().GetYHalfWidth());

	return G4ThreeVector(x, y, 0);

}

}

}
