#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>

#include "gneis/facility/component/CollimatorC2.hh"
#include "gneis/repository/Colours.hh"
#include "gneis/util/NameBuilder.hh"

const G4double gneis::facility::component::CollimatorC2::width = 210 * mm;
const G4double gneis::facility::component::CollimatorC2::height = 100 * mm;
const G4double gneis::facility::component::CollimatorC2::length = 710 * mm;

G4LogicalVolume* gneis::facility::component::CollimatorC2::Instance(
		G4VSolid *outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* gneis::facility::component::CollimatorC2::Instance(
		const G4String &name, G4VSolid *outer) {

	const auto nist = G4NistManager::Instance();

	const auto aperture = new G4Box(name, HalfOf(width), HalfOf(height),
			HalfOf(length));
	const auto solid = new G4SubtractionSolid(name, outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;
}

G4String gneis::facility::component::CollimatorC2::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C2");
}

G4double gneis::facility::component::CollimatorC2::GetLength() {
	return length;
}

G4double gneis::facility::component::CollimatorC2::GetHalfLength() {
	return HalfOf(GetLength());
}
