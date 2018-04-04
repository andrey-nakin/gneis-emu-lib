#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Spallation.hh"
#include "isnp/generator/SpallationMessenger.hh"

namespace isnp {

namespace generator {

Spallation::Spallation() :
		particleGun(MakeGun()), messenger(
				std::make_unique < SpallationMessenger > (*this)), diameter(
				4.0 * cm) {
}

Spallation::~Spallation() {
}

void Spallation::GeneratePrimaries(G4Event* const anEvent) {
	particleGun->SetParticlePosition(GeneratePosition());
	particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector Spallation::GeneratePosition() const {
	if (diameter < 1.0 * angstrom) {
		return G4ThreeVector(0.0, 0.0, -18.25 * m);
	}

	G4double const maxValue = diameter / 2;
	G4double const minValue = -maxValue;
	G4double const maxValue2 = maxValue * maxValue;
	G4double x, y;

	do {
		x = CLHEP::RandFlat::shoot(minValue, maxValue);
		y = CLHEP::RandFlat::shoot(minValue, maxValue);
	} while (x * x + y * y >= maxValue2);

	return G4ThreeVector(x, y, -18.25 * m);
}

std::unique_ptr<G4ParticleGun> Spallation::MakeGun() {
	auto const particleTable = G4ParticleTable::GetParticleTable();
	auto const particleDefinition = particleTable->FindParticle("proton");
	auto gun = std::make_unique < G4ParticleGun > (particleDefinition);

	gun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	gun->SetParticlePosition(G4ThreeVector(0, 0, -18.25 * m));
	gun->SetParticleEnergy(1.0 * GeV);

	return gun;
}

}

}
