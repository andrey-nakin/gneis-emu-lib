#include <G4SystemOfUnits.hh>
#include <G4Tubs.hh>
#include "isnp/facility/component/BoxComponent.hh"

G4double isnp::facility::component::BoxComponent::HalfOf(G4double const v) {
	return 0.5 * v;
}

G4VSolid* isnp::facility::component::BoxComponent::MakeCylinder(
		G4String const &name, G4double const len, G4double const outerRadius) {

	return MakeCylinder(name, len, outerRadius, 0.0);
}

G4VSolid* isnp::facility::component::BoxComponent::MakeCylinder(
		G4String const &name, G4double const len, G4double const outerRadius,
		G4double const aperture) {

	return new G4Tubs(name, 0.5 * aperture, outerRadius, 0.5 * len, 0.0 * deg,
			360.0 * deg);
}
