#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Spallation.hh"
#include "isnp/generator/SpallationMessenger.hh"
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace generator {

Spallation::UniformCircleProps::UniformCircleProps() :
		diameter(4.0 * cm) {
}

Spallation::GaussianEllipseProps::GaussianEllipseProps() :
		xWidth(50 * mm), yWidth(200 * mm) {
}

Spallation::Spallation() :
		particleGun(MakeGun()), messenger(
				std::make_unique < SpallationMessenger > (*this)), positionX(0), positionY(
				0), counter(0), verboseLevel(1), mode(Mode::UniformCircle) {
}

Spallation::~Spallation() {
}

void Spallation::GeneratePrimaries(G4Event* const anEvent) {

	using namespace facility::component;
	G4Transform3D const transform = SpallationTarget::GetTransform();

	particleGun->SetParticlePosition(GeneratePosition(transform));
	particleGun->SetParticleMomentumDirection(GenerateDirection(transform));
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

G4ThreeVector Spallation::GeneratePosition(
		G4Transform3D const& transform) const {

	using namespace facility::component;

	G4ThreeVector position;

	if (ucProps.GetDiameter() < 1.0 * angstrom) {

		position = G4ThreeVector(positionX, positionY,
				-SpallationTarget::GetHalfLength());

	} else {

		G4double const maxValue = ucProps.GetDiameter() / 2;
		G4double const minValue = -maxValue;
		G4double const maxValue2 = maxValue * maxValue;
		G4double x, y;

		do {
			x = CLHEP::RandFlat::shoot(minValue, maxValue);
			y = CLHEP::RandFlat::shoot(minValue, maxValue);
		} while (x * x + y * y >= maxValue2);

		position = G4ThreeVector(x + positionX, y + positionY,
				-SpallationTarget::GetHalfLength());

	}

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

}

}
