#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include "isnp/dist/UniformCircle.hh"

namespace isnp {

namespace dist {

UniformCircle::Props::Props(G4double const aDiameter) :
		diameter(aDiameter) {
}

UniformCircle::UniformCircle(const Props& aProps) :
		props(aProps) {
}

UniformCircle::~UniformCircle() {
}

G4ThreeVector UniformCircle::Generate() const {

	if (props.GetDiameter() < 1.0 * angstrom) {

		return G4ThreeVector(0, 0, 0);

	} else {

		G4double const maxValue = props.GetDiameter() / 2;
		G4double const minValue = -maxValue;
		G4double const maxValue2 = maxValue * maxValue;
		G4double x, y;

		do {
			x = CLHEP::RandFlat::shoot(minValue, maxValue);
			y = CLHEP::RandFlat::shoot(minValue, maxValue);
		} while (x * x + y * y >= maxValue2);

		return G4ThreeVector(x, y, 0);

	}

}

}

}
