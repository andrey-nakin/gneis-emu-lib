#include <cmath>

#include <G4SystemOfUnits.hh>
#include <G4Tubs.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4Threading.hh"

#include "isnp/facility/BasicSpallation.hh"
#include "isnp/facility/BasicSpallationMessenger.hh"
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace facility {

static G4String const DEFAULT_WORLD_MATERIAL = "G4_Galactic";

static G4double Square(G4double const x) {
	return std::pow(x, 2);
}

BasicSpallation::BasicSpallation(G4VSensitiveDetector* const aDetector) :
		detector(aDetector), messenger(
				std::make_unique < BasicSpallationMessenger > (*this)), worldRadius(
				0.0), horizontalAngle(30.0 * deg), verticalAngle(0.0 * deg), distance(
				1.0 * m), detectorWidth(10 * cm), detectorHeight(10 * cm), detectorLength(
				1.0 * cm), verboseLevel(0), worldMaterial(
				DEFAULT_WORLD_MATERIAL), logicWorld(nullptr) {

}

BasicSpallation::~BasicSpallation() {

}

G4VPhysicalVolume* BasicSpallation::Construct() {

	using namespace component;

	// Get nist material manager
	auto const nist = G4NistManager::Instance();

	// Option to switch on/off checking of volumes overlaps
	G4RotationMatrix* const noRotation = nullptr;
	G4bool const single = false;
	G4int const numOfCopies = 0;
	G4bool const checkOverlaps = true;

	if (worldRadius < 1 * mm) {
		// auto-calculate
		worldRadius = 1.0 * mm
				+ std::sqrt(
						Square(SpallationTarget::GetHalfWidth())
								+ Square(SpallationTarget::GetHalfHeight())
								+ Square(SpallationTarget::GetHalfLength()));
	}

	if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
		G4cout << "BasicSpallation: create world as a cylinder of "
				<< worldRadius / mm << " mm radius.\n";
	}

	G4String const nameWorld = "World";
	auto const solidWorld = new G4Tubs(nameWorld, 0.0, worldRadius,
			GetDistance() + GetDetectorLength(), 0.0 * deg, 360.0 * deg);
	logicWorld = new G4LogicalVolume(solidWorld,
			nist->FindOrBuildMaterial(worldMaterial), nameWorld);
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

	auto const physWorld = new G4PVPlacement(noRotation, G4ThreeVector(),
			logicWorld, nameWorld, nullptr, single, numOfCopies, checkOverlaps);

	{
		// Neutron source
		auto const logicSpTarget = SpallationTarget::Instance();
		G4RotationMatrix rotm = G4RotationMatrix();
		rotm.rotateY(GetHorizontalAngle());
		rotm.rotateX(GetVerticalAngle());
		G4Transform3D const transform = G4Transform3D(rotm,
				G4ThreeVector(0, 0, 0));
		component::SpallationTarget::SetTransform(transform);
		new G4PVPlacement(transform, logicSpTarget, logicSpTarget->GetName(),
				logicWorld, single, numOfCopies, checkOverlaps);
	}

	if (detector) {
		if (verboseLevel >= 1 && G4Threading::IsMasterThread()) {
			G4cout << "BasicSpallation: creating detector, width="
					<< GetDetectorWidth() / mm << " mm, height="
					<< GetDetectorHeight() / mm << " mm, length="
					<< GetDetectorLength() / mm << " mm" << "\n";
		}

		// Target
		G4String const name = "Target";
		const auto solidTarget = new G4Box(name, HalfOf(GetDetectorWidth()),
				HalfOf(GetDetectorHeight()), HalfOf(GetDetectorLength()));
		const auto logicTarget = new G4LogicalVolume(solidTarget,
				nist->FindOrBuildMaterial("G4_Galactic"), name);
		logicTarget->SetVisAttributes(G4VisAttributes(G4Colour::Red()));

		const auto sdMan = G4SDManager::GetSDMpointer();
		sdMan->AddNewDetector(detector);
		logicTarget->SetSensitiveDetector(detector);

		new G4PVPlacement(noRotation,
				G4ThreeVector(0, 0,
						GetDistance() + HalfOf(GetDetectorLength())),
				logicTarget, logicTarget->GetName(), logicWorld, single,
				numOfCopies, checkOverlaps);
	}

	return physWorld;

}

G4double BasicSpallation::GetHorizontalAngle() const {
	return horizontalAngle;
}

void BasicSpallation::SetHorizontalAngle(G4double const anAngle) {
	horizontalAngle = anAngle;
}

G4double BasicSpallation::GetVerticalAngle() const {
	return verticalAngle;
}

void BasicSpallation::SetVerticalAngle(G4double const anAngle) {
	verticalAngle = anAngle;
}

G4double BasicSpallation::GetDistance() const {
	return distance;
}

void BasicSpallation::SetDistance(G4double const aDistance) {
	distance = aDistance;
}

G4double BasicSpallation::GetDetectorWidth() const {
	return detectorWidth;
}

void BasicSpallation::SetDetectorWidth(G4double const aWidth) {
	detectorWidth = aWidth;
}

G4double BasicSpallation::GetDetectorHeight() const {
	return detectorHeight;
}

void BasicSpallation::SetDetectorHeight(G4double const aHeight) {
	detectorHeight = aHeight;
}

G4double BasicSpallation::GetDetectorLength() const {
	return detectorLength;
}

void BasicSpallation::SetDetectorLength(G4double const aLength) {
	detectorLength = aLength;
}

G4int BasicSpallation::GetVerboseLevel() const {
	return verboseLevel;
}

void BasicSpallation::SetVerboseLevel(G4int aVerboseLevel) {
	verboseLevel = aVerboseLevel;
}

void BasicSpallation::SetWorldMaterial(const G4String& aWorldMaterial) {

	auto nistManager = G4NistManager::Instance();
	auto material = nistManager->FindOrBuildMaterial(aWorldMaterial);

	if (material) {
		if (verboseLevel > 1) {
			G4cout << "BasicSpallation: set material " << aWorldMaterial
					<< "\n";
		}

		this->worldMaterial = aWorldMaterial;
		if (logicWorld) {
			logicWorld->SetMaterial(material);
		}
	} else {
		G4cerr << "BasicSpallation: unknown material " << aWorldMaterial
				<< "\n";
	}

}

G4double BasicSpallation::HalfOf(G4double const v) {

	return 0.5 * v;

}

}

}
