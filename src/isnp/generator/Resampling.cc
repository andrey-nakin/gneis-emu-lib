#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Resampling.hh"

namespace isnp {

namespace generator {

Resampling::Resampling() :
		particleGun(MakeGun()), sampleFileName(""), energyColumn("KineticEnergy"), sampleFileLoaded(false) {

}

Resampling::~Resampling() {

}

void Resampling::GeneratePrimaries(G4Event* const anEvent) {

	if (!sampleFileLoaded) {
		LoadSampleFile();
	}

	auto const dataSize = dataFrame->size();

	// set particle energy
	particleGun->SetParticleEnergy(dataFrame->numeric(energyColumn)[CLHEP::RandFlat::shootInt(dataSize)] * MeV);

	// generate particle
	particleGun->GeneratePrimaryVertex(anEvent);

}

void Resampling::SetSampleFileName(const G4String& fn) {
	sampleFileName = fn;
	sampleFileLoaded = false;
}

std::unique_ptr<G4ParticleGun> Resampling::MakeGun() {
	return std::make_unique<G4ParticleGun>();
}

void Resampling::LoadSampleFile() {
	sampleFileLoaded = true;
}

}

}
