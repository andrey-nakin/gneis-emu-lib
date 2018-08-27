#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include "isnp/dist/UniformRectangle.hh"

namespace isnp {

namespace dist {

UniformRectangle::Props::Props(G4double const aXWidth, G4double const aYWidth) :
		xWidth(aXWidth), yWidth(aYWidth), xHalfWidth(aXWidth / 2), yHalfWidth(
				aYWidth / 2) {
}

UniformRectangle::UniformRectangle(const Props& aProps) :
		props(aProps) {
}

G4ThreeVector UniformRectangle::Generate() const {

	G4double const x =
			props.GetXWidth() < 1.0 * angstrom ?
					0.0 :
					CLHEP::RandFlat::shoot(-props.GetXHalfWidth(),
							props.GetXHalfWidth());
	G4double const y =
			props.GetYWidth() < 1.0 * angstrom ?
					0.0 :
					CLHEP::RandFlat::shoot(-props.GetYHalfWidth(),
							props.GetYHalfWidth());

	return G4ThreeVector(x, y, 0);

}

}

}
