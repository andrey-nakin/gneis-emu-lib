#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>

#include "isnp/facility/component/CollimatorC1.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

const G4double isnp::facility::component::CollimatorC1::width = 140 * mm;
const G4double isnp::facility::component::CollimatorC1::height = 180 * mm;
const G4double isnp::facility::component::CollimatorC1::length = 400 * mm;

G4LogicalVolume* isnp::facility::component::CollimatorC1::AsCylinder(
		G4double const outerRadius) {

	return AsCylinder(GetDefaultName(), outerRadius);
}

G4LogicalVolume* isnp::facility::component::CollimatorC1::AsCylinder(
		const G4String &name, G4double const outerRadius) {

	return Instance(name,
			MakeCylinder(util::NameBuilder::Make(name, "Outer"), GetLength(),
					outerRadius));
}

G4LogicalVolume* isnp::facility::component::CollimatorC1::Instance(
		G4VSolid *outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* isnp::facility::component::CollimatorC1::Instance(
		const G4String &name, G4VSolid *outer) {

	const auto nist = G4NistManager::Instance();

	const auto aperture = new G4Box(util::NameBuilder::Make(name, "Aperture"),
			GetHalfWidth(), GetHalfHeight(), GetHalfLength() + 1 * mm);
	const auto solid = new G4SubtractionSolid(
			util::NameBuilder::Make(name, "WithAperture"), outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_BRASS"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Brass()));

	return logic;
}

G4String isnp::facility::component::CollimatorC1::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C1");
}

G4double isnp::facility::component::CollimatorC1::GetWidth() {
	return width;
}

G4double isnp::facility::component::CollimatorC1::GetHalfWidth() {
	return HalfOf(GetWidth());
}

G4double isnp::facility::component::CollimatorC1::GetHeight() {
	return height;
}

G4double isnp::facility::component::CollimatorC1::GetHalfHeight() {
	return HalfOf(GetHeight());
}

G4double isnp::facility::component::CollimatorC1::GetLength() {
	return length;
}

G4double isnp::facility::component::CollimatorC1::GetHalfLength() {
	return HalfOf(GetLength());
}
