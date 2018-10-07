#include <fstream>

#include <G4SystemOfUnits.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <Randomize.hh>

#include "isnp/generator/Resampling.hh"
#include "isnp/generator/ResamplingMessenger.hh"
#include "isnp/util/RandomNumberGenerator.hh"
#include "isnp/util/DataFrameLoader.hh"

namespace isnp {

namespace generator {

Resampling::Resampling() :
		messenger(std::make_unique < ResamplingMessenger > (*this)), particleGun(
				MakeGun()), sampleFileName(""), energyColumn("KineticEnergy"), directionXColumn(
				"DirectionX"), directionYColumn("DirectionY"), directionZColumn(
				"DirectionZ"), positionXColumn("PositionX"), positionYColumn(
				"PositionY"), positionZColumn("PositionZ"), typeColumn("Type"), sampleFileLoaded(
				false), counter(0), verboseLevel(1) {

}

Resampling::~Resampling() {

}

void Resampling::GeneratePrimaries(G4Event* const anEvent) {

	if (!sampleFileLoaded) {
		LoadSampleFile();
	}

	// set particle properties
	auto const particleTable = G4ParticleTable::GetParticleTable();
	auto const dataSize = dataFrame->Size();

	auto const energyRowNo = CLHEP::RandFlat::shootInt(dataSize);
	particleGun->SetParticleDefinition(
			particleTable->FindParticle(
					dataFrame->CategoryValue(typeColumn, energyRowNo)));
	particleGun->SetParticleEnergy(
			ShootNumber(energyColumn, energyRowNo) * MeV);
	particleGun->SetParticlePosition(
			CalculatePosition(
					ShootVector(directionXColumn, directionYColumn,
							directionZColumn, energyRowNo),
					ShootVector(positionXColumn, positionYColumn,
							positionZColumn, energyRowNo) * mm));

	auto const directionRowNo = CLHEP::RandFlat::shootInt(dataSize);
	particleGun->SetParticleMomentumDirection(
			ShootVector(directionXColumn, directionYColumn, directionZColumn,
					directionRowNo));

	// generate particle
	particleGun->GeneratePrimaryVertex(anEvent);

	++counter;

	if (verboseLevel > 1) {
		G4cout << "Resampling: generating #" << counter << " particle"
				<< G4endl;

		if (verboseLevel > 2) {
			G4cout << "Resampling: enerty row=" << energyRowNo << ", energy="
					<< particleGun->GetParticleEnergy() / MeV
					<< " MeV, position="
					<< particleGun->GetParticlePosition() / mm
					<< " mm, direction row=" << directionRowNo << ", direction="
					<< particleGun->GetParticleMomentumDirection() << G4endl;
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

void Resampling::Load(std::istream& f) {

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

	dataFrame = std::make_unique < util::DataFrame > (loader.load(f));

	if (verboseLevel > 0) {
		G4cout << "Resampling: " << dataFrame->Size()
				<< " records is loaded from file " << sampleFileName << "\n";
	}

	if (dataFrame->Size() == 0) {
		throw EmptySampleException();
	}

	sampleFileLoaded = true;

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

	Load(f);

}

G4double Resampling::ShootNumber(G4String const& column,
		util::DataFrame::size_type const rowNo) const {

	auto const v = dataFrame->FloatValue(column, rowNo);
	auto const precision = dataFrame->Precision(column);

	if (precision > 0) {
		return util::RandomNumberGenerator::locality(v, precision);
	} else {
		return v;
	}

}

G4ThreeVector Resampling::ShootVector(G4String const & columnX,
		G4String const& columnY, G4String const & columnZ,
		util::DataFrame::size_type const rowNo) const {

	return G4ThreeVector(ShootNumber(columnX, rowNo),
			ShootNumber(columnY, rowNo), ShootNumber(columnZ, rowNo));

}

}

}
