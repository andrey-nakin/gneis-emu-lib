#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>

#include "facility/component/SpallationTarget.hh"

const G4double gneis::facility::component::SpallationTarget::width = 200.0 * mm;
const G4double gneis::facility::component::SpallationTarget::height = 50.0 * mm;
const G4double gneis::facility::component::SpallationTarget::length = 400.0 * mm;

G4LogicalVolume* gneis::facility::component::SpallationTarget::Instance() {
	return Instance("lead-target");
}

G4LogicalVolume* gneis::facility::component::SpallationTarget::Instance(
		const G4String &name) {

	const auto nist = G4NistManager::Instance();

	const auto solid = new G4Box(name, GetHalfWidth(), GetHalfHeight(),
			GetHalfLength());

	const auto logic = new G4LogicalVolume(solid, nist->FindOrBuildMaterial("G4_Pb"), name);
	logic->SetVisAttributes(G4VisAttributes(G4Colour(0.8, 0.8, 0.8)));

	return logic;
}

G4double gneis::facility::component::SpallationTarget::GetWidth() {
	return width;
}

G4double gneis::facility::component::SpallationTarget::GetHeight() {
	return height;
}

G4double gneis::facility::component::SpallationTarget::GetLength() {
	return length;
}

G4double gneis::facility::component::SpallationTarget::GetHalfWidth() {
	return HalfOf(GetWidth());
}

G4double gneis::facility::component::SpallationTarget::GetHalfHeight() {
	return HalfOf(GetHeight());
}

G4double gneis::facility::component::SpallationTarget::GetHalfLength() {
	return HalfOf(GetLength());
}

G4double gneis::facility::component::SpallationTarget::HalfOf(G4double const v) {
	return 0.5 * v;
}
