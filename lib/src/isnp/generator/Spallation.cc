#include <string>

#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>
#include <G4UnitsTable.hh>

#include "isnp/generator/Spallation.hh"
#include "isnp/generator/SpallationMessenger.hh"
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace generator {

Spallation::Spallation() :
		particleGun(MakeGun()), messenger(
				std::make_unique < SpallationMessenger > (*this)), positionX(0), positionY(
				0), counter(0), verboseLevel(1), mode(Mode::UniformRectangle), uniformRectangle(
				dist::UniformRectangleProps(120 * mm, 50 * mm)), uniformCircle(
				dist::UniformCircleProps(4.0 * cm)), gaussEllipse(
				dist::GaussEllipseProps(200 * mm, 50 * mm)), targetTransformDetected(
				false) {
}

Spallation::~Spallation() {
}

void Spallation::GeneratePrimaries(G4Event* const anEvent) {

	using namespace facility::component;

	if (!targetTransformDetected) {
		targetTransform = DetectTargetTransform();
		targetTransformDetected = true;
	}

	particleGun->SetParticlePosition(GeneratePosition(targetTransform));
	particleGun->SetParticleMomentumDirection(
			GenerateDirection(targetTransform));
	particleGun->GeneratePrimaryVertex(anEvent);
	++counter;

	if (verboseLevel > 1) {
		G4cout << "Spallation: generating #" << counter << " particle\n";
		if (verboseLevel > 2) {
			G4cout << "Spallation position: "
					<< particleGun->GetParticlePosition() << "\n";
			G4cout << "Spallation direction: "
					<< particleGun->GetParticleMomentumDirection() << "\n";
		}
	}

}

G4ThreeVector Spallation::GenerateDirection(
		G4Transform3D const& transform) const {

	G4ThreeVector direction = G4ThreeVector(0., 0., 1.);
	direction.transform(transform.getRotation());
	return direction;

}

const dist::AbstractDistribution& Spallation::ResolveDistribution() const {

	switch (mode) {
	case Mode::UniformCircle:
		return uniformCircle;
		break;

	case Mode::UniformRectangle:
		return uniformRectangle;
		break;

	default:
		return gaussEllipse;
		break;
	}

}

G4ThreeVector Spallation::GeneratePosition(
		G4Transform3D const& transform) const {

	using namespace facility::component;

	G4ThreeVector position = ResolveDistribution().Generate();

	position.setX(position.getX() + positionX);
	position.setY(position.getY() + positionY);
	position.setZ(position.getZ() - 250 * mm);
	position.transform(transform.getRotation());
	position += transform.getTranslation();

	return position;

}

std::unique_ptr<G4ParticleGun> Spallation::MakeGun() {
	auto const particleTable = G4ParticleTable::GetParticleTable();
	auto const particleDefinition = particleTable->FindParticle("proton");
	auto gun = std::make_unique < G4ParticleGun > (particleDefinition);

	gun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	gun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
	gun->SetParticleEnergy(1.0 * GeV);

	return gun;
}

G4Transform3D Spallation::DetectTargetTransform() const {

	auto const position = GetVector(
			"/isnp/facility/component/spTarget/position");
	auto const rotation = GetVector(
			"/isnp/facility/component/spTarget/rotation");

	G4RotationMatrix rotm = G4RotationMatrix();
	rotm.rotateX(rotation.getX());
	rotm.rotateY(rotation.getY());
	rotm.rotateZ(rotation.getZ());
	return G4Transform3D(rotm, position);

}

G4ThreeVector Spallation::GetVector(const char* const cmd) const {

	G4ThreeVector result;
	auto const uiManager = G4UImanager::GetUIpointer();

	G4String const x = uiManager->GetCurrentStringValue(cmd, 1);
	G4String const y = uiManager->GetCurrentStringValue(cmd, 2);
	G4String const z = uiManager->GetCurrentStringValue(cmd, 3);
	G4String const units = uiManager->GetCurrentStringValue(cmd, 4);

	if (!x.isNull() && !y.isNull() && !z.isNull() && !units.isNull()) {
		auto const unitValue = G4UnitDefinition::GetValueOf(units);

		result.setX(std::stof(x) * unitValue);
		result.setY(std::stof(y) * unitValue);
		result.setZ(std::stof(z) * unitValue);
	}

	return result;

}

}

}
