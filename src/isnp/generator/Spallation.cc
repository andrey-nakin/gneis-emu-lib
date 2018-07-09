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
		xWidth(200 * mm), yWidth(50 * mm) {
}

Spallation::Spallation() :
		particleGun(MakeGun()), messenger(
				std::make_unique < SpallationMessenger > (*this)), positionX(0), positionY(
				0), counter(0), verboseLevel(1), mode(Mode::UniformCircle), uniformRectangle(
				dist::UniformRectangle::Props(120 * mm, 50 * mm)) {
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

	switch (mode) {
	case Mode::UniformCircle:
		position = GeneratePositionUC();
		break;

	case Mode::UniformRectangle:
		position = uniformRectangle.Generate();
		break;

	default:
		position = GeneratePositionGE();
		break;
	}

	position.setX(position.getX() + positionX);
	position.setY(position.getY() + positionY);
	position.setZ(position.getZ() - SpallationTarget::GetHalfLength());
	position.transform(transform.getRotation());
	position += transform.getTranslation();

	return position;

}

G4ThreeVector Spallation::GeneratePositionUC() const {

	if (ucProps.GetDiameter() < 1.0 * angstrom) {

		return G4ThreeVector(0, 0, 0);

	} else {

		G4double const maxValue = ucProps.GetDiameter() / 2;
		G4double const minValue = -maxValue;
		G4double const maxValue2 = maxValue * maxValue;
		G4double x, y;

		do {
			x = CLHEP::RandFlat::shoot(minValue, maxValue);
			y = CLHEP::RandFlat::shoot(minValue, maxValue);
		} while (x * x + y * y >= maxValue2);

		return G4ThreeVector(x, y, 0);

	}

}

G4ThreeVector Spallation::GeneratePositionGE() const {

	// relation between Full Width at High Maximum and sigma parameter of Gauss distribution
	G4double const static FWHM = 1.0 / (2 * std::sqrt(2 * std::log(2)));

	G4double const x = CLHEP::RandGauss::shoot() * geProps.GetXWidth() * FWHM;
	G4double const y = CLHEP::RandGauss::shoot() * geProps.GetYWidth() * FWHM;
	return G4ThreeVector(x, y, 0);

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
