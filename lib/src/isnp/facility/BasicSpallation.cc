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
#include "isnp/facility/component/BeamPointer.hh"
#include "isnp/detector/Basic.hh"

namespace isnp {

namespace facility {

static G4String const DEFAULT_WORLD_MATERIAL = "G4_Galactic";

static G4double Square(G4double const x) {
	return std::pow(x, 2);
}

BasicSpallation::BasicSpallation() :
		detector(nullptr), messenger(
				std::make_unique < BasicSpallationMessenger > (*this)), worldRadius(
				0.0), xAngle(-2.0 * deg), yAngle(-32.0 * deg), distance(
				1.0 * m), detectorWidth(10 * cm), detectorHeight(10 * cm), detectorLength(
				1.0 * cm), verboseLevel(0), worldMaterial(
				DEFAULT_WORLD_MATERIAL), logicWorld(nullptr) {

	component::SpallationTarget::GetInstance();
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
		auto targetBounds = 250. * mm;
		auto detectorBounds = std::sqrt(
				Square(HalfOf(GetDetectorWidth()))
						+ Square(HalfOf(GetDetectorHeight())));

		worldRadius = 1.0 * mm + std::max(targetBounds, detectorBounds);
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
		auto const spallationTarget =
				component::SpallationTarget::GetInstance();
		spallationTarget->SetRotation(
				spallationTarget->GetRotation()
						+ G4ThreeVector(-GetXAngle(), -GetYAngle(), 0.));
		spallationTarget->Place(logicWorld);

		auto const bp = component::BeamPointer::GetInstance();
		bp->SetRotation(G4ThreeVector());
		bp->SetPosition(G4ThreeVector());

	}

	if (!detector) {
		detector = MakeDefaultDetector();
	}

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
			G4ThreeVector(0, 0, GetDistance() + HalfOf(GetDetectorLength())),
			logicTarget, logicTarget->GetName(), logicWorld, single,
			numOfCopies, checkOverlaps);

	return physWorld;

}

G4double BasicSpallation::GetXAngle() const {
	return xAngle;
}

void BasicSpallation::SetXAngle(G4double const anAngle) {
	xAngle = anAngle;
}

G4double BasicSpallation::GetYAngle() const {
	return yAngle;
}

void BasicSpallation::SetYAngle(G4double const anAngle) {
	yAngle = anAngle;
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

	auto const nistManager = G4NistManager::Instance();
	auto const material = nistManager->FindOrBuildMaterial(aWorldMaterial);

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

G4VSensitiveDetector* BasicSpallation::GetDetector() const {

	return detector;

}

void BasicSpallation::SetDetector(G4VSensitiveDetector* const aDetector) {

	detector = aDetector;

}

G4double BasicSpallation::HalfOf(G4double const v) {

	return 0.5 * v;

}

G4VSensitiveDetector* BasicSpallation::MakeDefaultDetector() {

	return new isnp::detector::Basic;

}

}

}
