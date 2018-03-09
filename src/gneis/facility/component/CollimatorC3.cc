#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4SubtractionSolid.hh>
#include <G4Tubs.hh>

#include "gneis/facility/component/CollimatorC3.hh"
#include "gneis/repository/Colours.hh"
#include "gneis/util/NameBuilder.hh"

const G4double gneis::facility::component::CollimatorC3::diameter = 120 * mm;
const G4double gneis::facility::component::CollimatorC3::length = 600 * mm;

G4LogicalVolume* gneis::facility::component::CollimatorC3::AsCylinder(
		G4double const outerRadius) {

	return AsCylinder(GetDefaultName(), outerRadius);
}

G4LogicalVolume* gneis::facility::component::CollimatorC3::AsCylinder(
		const G4String &name, G4double const outerRadius) {

	return MakeLogical(
			MakeCylinder(name, GetLength(), outerRadius, GetDiameter()));
}

G4LogicalVolume* gneis::facility::component::CollimatorC3::Instance(
		G4VSolid* const outer) {

	return Instance(GetDefaultName(), outer);
}

G4LogicalVolume* gneis::facility::component::CollimatorC3::Instance(
		const G4String &name, G4VSolid* const outer) {

	const auto aperture = new G4Tubs(name, 0.0, HalfOf(diameter),
			HalfOf(GetLength()), 0.0 * deg, 360.0 * deg);
	const auto solid = new G4SubtractionSolid(name, outer, aperture);

	return MakeLogical(solid);
}

G4String gneis::facility::component::CollimatorC3::GetDefaultName() {
	return util::NameBuilder::Make("Collimator", "C3");
}

G4double gneis::facility::component::CollimatorC3::GetLength() {
	return length;
}

G4double gneis::facility::component::CollimatorC3::GetHalfLength() {
	return HalfOf(GetLength());
}

G4double gneis::facility::component::CollimatorC3::GetDiameter() {
	return diameter;
}

G4double gneis::facility::component::CollimatorC3::GetHalfDiameter() {
	return HalfOf(GetDiameter());
}

G4LogicalVolume* gneis::facility::component::CollimatorC3::MakeLogical(
		G4VSolid * const solid) {

	const auto nist = G4NistManager::Instance();

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"), solid->GetName());
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Steel()));

	return logic;
}
