#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Spallation.hh"

isnp::generator::Spallation::Spallation() :
		diameter(4.0 * cm) {

	G4int const n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);

	auto const particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("proton");

	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	particleGun->SetParticlePosition(G4ThreeVector(0, 0, -18.25 * m));
	particleGun->SetParticleEnergy(1.0 * GeV);
}

isnp::generator::Spallation::~Spallation() {
	delete particleGun;
}

void isnp::generator::Spallation::GeneratePrimaries(G4Event* const anEvent) {
	particleGun->SetParticlePosition(GeneratePosition());
	particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector isnp::generator::Spallation::GeneratePosition() const {
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
