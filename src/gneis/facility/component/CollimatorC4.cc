#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "gneis/facility/component/CollimatorC4.hh"
#include "gneis/repository/Colours.hh"
#include "gneis/util/NameBuilder.hh"

const G4double gneis::facility::component::CollimatorC4::diameter = 120 * mm;
const G4double gneis::facility::component::CollimatorC4::length = 875 * mm;

G4LogicalVolume* gneis::facility::component::CollimatorC4::Instance(
		G4VSolid* const outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* gneis::facility::component::CollimatorC4::Instance(
		const G4String &name, G4VSolid* const outer) {

	const auto nist = G4NistManager::Instance();

	const auto aperture = new G4Tubs(name, 0.0, HalfOf(diameter),
			HalfOf(GetLength()), 0.0 * deg, 360.0 * deg);
	const auto solid = new G4SubtractionSolid(name, outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_BRASS"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Brass()));

	return logic;
}

G4String gneis::facility::component::CollimatorC4::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C4");
}

G4double gneis::facility::component::CollimatorC4::GetLength() {
	return length;
}

G4double gneis::facility::component::CollimatorC4::GetHalfLength() {
	return HalfOf(GetLength());
}
