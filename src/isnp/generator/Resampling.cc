#include <fstream>

#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "isnp/generator/Resampling.hh"
#include "isnp/util/RandomNumberGenerator.hh"
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace generator {

Resampling::Resampling() :
		particleGun(MakeGun()), sampleFileName(""), energyColumn(
				"KineticEnergy"), directionXColumn("DirectionX"), directionYColumn(
				"DirectionY"), directionZColumn("DirectionZ"), positionXColumn(
				"PositionX"), positionYColumn("PositionY"), positionZColumn(
				"PositionZ"), typeColumn("Type"), sampleFileLoaded(false), counter(
				0), verboseLevel(1) {

}

Resampling::~Resampling() {

}

void Resampling::GeneratePrimaries(G4Event* const anEvent) {

	if (!sampleFileLoaded) {
		LoadSampleFile();
	}

	// set particle properties
	particleGun->SetParticleEnergy(ShootNumber(energyColumn) * MeV);
	particleGun->SetParticleMomentumDirection(
			ShootVector(directionXColumn, directionYColumn, directionZColumn));
	particleGun->SetParticlePosition(
			CalculatePosition(
					ShootVector(directionXColumn, directionYColumn,
							directionZColumn),
					ShootVector(positionXColumn, positionYColumn,
							positionZColumn) * mm));

	// generate particle
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

void Resampling::SetSampleFileName(const G4String& fn) {

	sampleFileName = fn;
	sampleFileLoaded = false;

}

std::unique_ptr<G4ParticleGun> Resampling::MakeGun() {

	return std::make_unique<G4ParticleGun>();

}

G4ThreeVector Resampling::CalculatePosition(const G4ThreeVector& direction,
		const G4ThreeVector& targetPos) {

	return G4ThreeVector(
			targetPos.getX()
					- targetPos.getZ() * direction.getX() / direction.getZ(),
			targetPos.getY()
					- targetPos.getZ() * direction.getY() / direction.getZ(),
			0.0);

}

void Resampling::LoadSampleFile() {

	if (verboseLevel > 0) {
		G4cout << "Resampling: loading sample from file " << sampleFileName
				<< "\n";
	}

	if (sampleFileName.isNull()) {
		throw NoFileException();
	}

	std::ifstream f(sampleFileName);
	if (!f) {
		throw NoFileException();
	}

	std::set<G4String> numericColumns, categoryColumns;
	numericColumns.insert(energyColumn);
	numericColumns.insert(directionXColumn);
	numericColumns.insert(directionYColumn);
	numericColumns.insert(directionZColumn);
	numericColumns.insert(positionXColumn);
	numericColumns.insert(positionYColumn);
	numericColumns.insert(positionZColumn);
	categoryColumns.insert(typeColumn);
	util::DataFrameLoader loader(numericColumns, categoryColumns);

	dataFrame = loader.load(f);

	if (verboseLevel > 0) {
		G4cout << "Resampling: " << dataFrame->size()
				<< " records is loaded from file " << sampleFileName << "\n";
	}

	if (dataFrame->size() == 0) {
		throw EmptySampleException();
	}

	sampleFileLoaded = true;

}

G4double Resampling::ShootNumber(const G4String& column) const {

	auto const dataSize = dataFrame->size();
	auto const rowNo = CLHEP::RandFlat::shootInt(dataSize);
	auto const v = dataFrame->numeric(column)[rowNo];

	if (dataFrame->GetPrecision() > 0) {
		return util::RandomNumberGenerator::locality(v,
				dataFrame->GetPrecision());
	} else {
		return v;
	}

}

G4ThreeVector Resampling::ShootVector(const G4String& columnX,
		const G4String& columnY, const G4String& columnZ) const {

	return G4ThreeVector(ShootNumber(columnX), ShootNumber(columnY),
			ShootNumber(columnZ));

}

}

}
