#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>

#include "gneis/generator/Spallation.hh"

gneis::generator::Spallation::Spallation() {
	G4int const n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);

	auto const particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("proton");

	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	particleGun->SetParticlePosition(G4ThreeVector(0, 0, -18.25 * m));
	particleGun->SetParticleEnergy(1.0 * GeV);
}

gneis::generator::Spallation::~Spallation() {
	delete particleGun;
}

void gneis::generator::Spallation::GeneratePrimaries(G4Event* anEvent) {
	particleGun->GeneratePrimaryVertex(anEvent);
}
