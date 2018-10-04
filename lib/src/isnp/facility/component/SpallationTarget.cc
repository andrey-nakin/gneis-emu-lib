#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>

#include "isnp/facility/component/SpallationTarget.hh"
#include "isnp/facility/component/SpallationTargetMessenger.hh"
#include "isnp/repository/Colours.hh"
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace facility {

namespace component {

G4Transform3D SpallationTarget::transform;

SpallationTarget::SpallationTarget() :
		util::Box(200.0 * mm, 50.0 * mm, 400.0 * mm), messenger(
				std::make_unique < SpallationTargetMessenger > (*this)), hasCooler(
				true) {
}

G4LogicalVolume* SpallationTarget::Instance() {
	return Instance(util::NameBuilder::Make("Spallation", "Target"));
}

G4LogicalVolume* SpallationTarget::Instance(const G4String &name) {

	const auto nist = G4NistManager::Instance();

	const auto solid = new G4Box(name, GetHalfWidth(), GetHalfHeight(),
			GetHalfLength());

	const auto logic = new G4LogicalVolume(solid,
			nist->FindOrBuildMaterial("G4_Pb"), name);
	logic->SetVisAttributes(G4VisAttributes(repository::Colours::Lead()));

	return logic;
}

void SpallationTarget::Place(G4LogicalVolume* const destination,
		G4Transform3D const& transform) {

	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;

	SetTransform(transform);

	auto const logicSpTarget = Instance();

	new G4PVPlacement(transform, logicSpTarget, logicSpTarget->GetName(),
			destination, single, numOfCopies, checkOverlaps);

}

G4bool SpallationTarget::GetHasCooler() const {

	return hasCooler;

}

void SpallationTarget::SetHasCooler(G4bool const v) {

	hasCooler = v;

}

}

}

}
