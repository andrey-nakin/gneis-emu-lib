#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "isnp/facility/component/CollimatorC4.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

const G4double isnp::facility::component::CollimatorC4::diameter = 120 * mm;
const G4double isnp::facility::component::CollimatorC4::length = 875 * mm;

G4LogicalVolume* isnp::facility::component::CollimatorC4::AsCylinder(
		G4double const outerRadius) {

	return AsCylinder(GetDefaultName(), outerRadius);
}

G4LogicalVolume* isnp::facility::component::CollimatorC4::AsCylinder(
		const G4String &name, G4double const outerRadius) {

	return MakeLogical(
			MakeCylinder(name, GetLength(), outerRadius, GetDiameter()));
}

G4LogicalVolume* isnp::facility::component::CollimatorC4::Instance(
		G4VSolid* const outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* isnp::facility::component::CollimatorC4::Instance(
		const G4String &name, G4VSolid* const outer) {

	const auto aperture = new G4Tubs(name, 0.0, HalfOf(diameter),
			HalfOf(GetLength()), 0.0 * deg, 360.0 * deg);
	const auto solid = new G4SubtractionSolid(name, outer, aperture);

	return MakeLogical(solid);
}

G4String isnp::facility::component::CollimatorC4::GetDefaultName() {
	return util::NameBuilder::Make("c", "4");
}

G4double isnp::facility::component::CollimatorC4::GetLength() {
	return length;
}

G4double isnp::facility::component::CollimatorC4::GetHalfLength() {
	return HalfOf(GetLength());
}

G4double isnp::facility::component::CollimatorC4::GetDiameter() {
	return diameter;
}

G4double isnp::facility::component::CollimatorC4::GetHalfDiameter() {
	return HalfOf(GetDiameter());
}

G4LogicalVolume* isnp::facility::component::CollimatorC4::MakeLogical(
		G4VSolid * const solid) {

	const auto nist = G4NistManager::Instance();

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), solid->GetName());
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;
}
