#include <G4SystemOfUnits.hh>
#include <G4Tubs.hh>
#include <G4Box.hh>
#include <G4SubtractionSolid.hh>
#include "isnp/facility/component/BoxComponent.hh"

namespace isnp {

namespace facility {

namespace component {

G4double BoxComponent::HalfOf(G4double const v) {
	return 0.5 * v;
}

G4VSolid* BoxComponent::MakeCylinder(G4String const &name, G4double const len,
		G4double const outerRadius) {

	return MakeCylinder(name, len, outerRadius, 0.0);
}

G4VSolid* BoxComponent::MakeCylinder(G4String const &name, G4double const len,
		G4double const outerRadius, G4double const aperture) {

	return new G4Tubs(name, 0.5 * aperture, outerRadius, 0.5 * len, 0.0 * deg,
			360.0 * deg);
}

G4VSolid* BoxComponent::SolidWithAperture(const G4String &name,
		G4VSolid* const outer, util::Box const& aperture) {

	auto const ap = new G4Box(util::NameBuilder::Make(name, "Aperture"),
			aperture.GetHalfWidth(), aperture.GetHalfHeight(),
			aperture.GetHalfLength() + 1.0 * mm);
	auto const solid = new G4SubtractionSolid(
			util::NameBuilder::Make(name, "WithAperture"), outer, ap);

	return solid;

}

}

}

}
