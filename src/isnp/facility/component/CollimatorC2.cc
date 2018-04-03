#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>

#include "isnp/facility/component/CollimatorC2.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

const G4double isnp::facility::component::CollimatorC2::width = 210 * mm;
const G4double isnp::facility::component::CollimatorC2::height = 100 * mm;
const G4double isnp::facility::component::CollimatorC2::length = 710 * mm;

G4LogicalVolume* isnp::facility::component::CollimatorC2::AsCylinder(
		G4double const outerRadius) {

	return AsCylinder(GetDefaultName(), outerRadius);
}

G4LogicalVolume* isnp::facility::component::CollimatorC2::AsCylinder(
		const G4String &name, G4double const outerRadius) {

	return Instance(name,
			MakeCylinder(util::NameBuilder::Make(name, "Outer"), GetLength(),
					outerRadius));
}

G4LogicalVolume* isnp::facility::component::CollimatorC2::Instance(
		G4VSolid *outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* isnp::facility::component::CollimatorC2::Instance(
		const G4String &name, G4VSolid *outer) {

	const auto nist = G4NistManager::Instance();

	const auto aperture = new G4Box(util::NameBuilder::Make(name, "Aperture"),
			GetHalfWidth(), GetHalfHeight(), GetHalfLength() + 1.0 * mm);
	const auto solid = new G4SubtractionSolid(
			util::NameBuilder::Make(name, "WithAperture"), outer, aperture);
	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;
}

G4String isnp::facility::component::CollimatorC2::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C2");
}

G4double isnp::facility::component::CollimatorC2::GetWidth() {
	return width;
}

G4double isnp::facility::component::CollimatorC2::GetHalfWidth() {
	return HalfOf(GetWidth());
}

G4double isnp::facility::component::CollimatorC2::GetHeight() {
	return height;
}

G4double isnp::facility::component::CollimatorC2::GetHalfHeight() {
	return HalfOf(GetHeight());
}

G4double isnp::facility::component::CollimatorC2::GetLength() {
	return length;
}

G4double isnp::facility::component::CollimatorC2::GetHalfLength() {
	return HalfOf(GetLength());
}
