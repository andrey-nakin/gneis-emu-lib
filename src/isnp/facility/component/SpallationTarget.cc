#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>

#include "isnp/facility/component/SpallationTarget.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

const G4double isnp::facility::component::SpallationTarget::width = 200.0 * mm;
const G4double isnp::facility::component::SpallationTarget::height = 50.0 * mm;
const G4double isnp::facility::component::SpallationTarget::length = 400.0 * mm;

G4LogicalVolume* isnp::facility::component::SpallationTarget::Instance() {
	return Instance(util::NameBuilder::Make("Target", "Spallation"));
}

G4LogicalVolume* isnp::facility::component::SpallationTarget::Instance(
		const G4String &name) {

	const auto nist = G4NistManager::Instance();

	const auto solid = new G4Box(name, GetHalfWidth(), GetHalfHeight(),
			GetHalfLength());

	const auto logic = new G4LogicalVolume(solid, nist->FindOrBuildMaterial("G4_Pb"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Lead()));

	return logic;
}

G4double isnp::facility::component::SpallationTarget::GetWidth() {
	return width;
}

G4double isnp::facility::component::SpallationTarget::GetHeight() {
	return height;
}

G4double isnp::facility::component::SpallationTarget::GetLength() {
	return length;
}

G4double isnp::facility::component::SpallationTarget::GetHalfWidth() {
	return HalfOf(GetWidth());
}

G4double isnp::facility::component::SpallationTarget::GetHalfHeight() {
	return HalfOf(GetHeight());
}

G4double isnp::facility::component::SpallationTarget::GetHalfLength() {
	return HalfOf(GetLength());
}
