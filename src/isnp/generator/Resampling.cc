#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Resampling.hh"
#include "isnp/util/RandomNumberGenerator.hh"

namespace isnp {

namespace generator {

Resampling::Resampling() :
		particleGun(MakeGun()), sampleFileName(""), energyColumn(
				"KineticEnergy"), sampleFileLoaded(false) {

}

Resampling::~Resampling() {

}

void Resampling::GeneratePrimaries(G4Event* const anEvent) {

	if (!sampleFileLoaded) {
		LoadSampleFile();
	}

	// set particle properties
	particleGun->SetParticleEnergy(ShootNumber(energyColumn) * MeV);
	// @TODO

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

G4double Resampling::ShootNumber(const G4String& column) const {

	auto const dataSize = dataFrame->size();
	auto const rowNo = CLHEP::RandFlat::shootInt(dataSize);
	auto const v = dataFrame->numeric(column)[rowNo];

	if (dataFrame->GetPrecision() > 0) {
		return util::RandomNumberGenerator::locality(v, dataFrame->GetPrecision());
	} else {
		return v;
	}

}

}

}
