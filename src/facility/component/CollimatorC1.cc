#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>

#include "facility/component/CollimatorC1.hh"
#include "repository/Colours.hh"

const G4double gneis::facility::component::CollimatorC1::width = 140 * mm;
const G4double gneis::facility::component::CollimatorC1::height = 180 * mm;
const G4double gneis::facility::component::CollimatorC1::length = 400 * mm;

G4LogicalVolume* gneis::facility::component::CollimatorC1::Instance(
		G4VSolid *outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* gneis::facility::component::CollimatorC1::Instance(
		const G4String &name, G4VSolid *outer) {

	const auto nist = G4NistManager::Instance();

	const auto aperture = new G4Box(name, HalfOf(width), HalfOf(height),
			HalfOf(length));
	const auto solid = new G4SubtractionSolid(name, outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_BRASS"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Brass()));

	return logic;
}

G4String gneis::facility::component::CollimatorC1::GetDefaultName() {
	return "collimator-C1";
}

G4double gneis::facility::component::CollimatorC1::GetLength() {
	return length;
}

G4double gneis::facility::component::CollimatorC1::GetHalfLength() {
	return HalfOf(GetLength());
}
