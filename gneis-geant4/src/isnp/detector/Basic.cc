#include <fstream>
#include <G4SystemOfUnits.hh>
#include "isnp/detector/Basic.hh"
#include "isnp/util/FileNameBuilder.hh"
#include "isnp/info/Version.hh"
#include "isnp/info/Geant4Version.hh"

isnp::detector::Basic::Basic() :
		G4VSensitiveDetector("detector") {

}

isnp::detector::Basic::Basic(const G4String& name) :
		G4VSensitiveDetector(name) {

}

isnp::detector::Basic::~Basic() {
	flush();
}

G4bool isnp::detector::Basic::ProcessHits(G4Step* const aStep,
		G4TouchableHistory* const /* ROhist */) {

	const auto track = aStep->GetTrack();
	const auto dp = track->GetDynamicParticle();
	Data data;

	auto const particleName = dp->GetParticleDefinition()->GetParticleName();
	auto const findResult = keyMap.find(particleName);
	if (findResult != std::end(keyMap)) {
		data.nameKey = findResult->second;
	} else {
		auto const key = keyMap.size();
		keyMap[particleName] = key;
		nameMap[key] = particleName;
		data.nameKey = key;
	}

	data.totalEnergy = dp->GetTotalEnergy();
	data.kineticEnergy = dp->GetKineticEnergy();
	data.time = dp->GetProperTime();
	data.direction = dp->GetMomentumDirection();
	data.position = aStep->GetPreStepPoint()->GetPosition();
	accum.push_back(data);

	aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	return true;
}

void isnp::detector::Basic::flush() {
	std::ofstream file(isnp::util::FileNameBuilder::Make(GetName(), ".txt"));
	file << "# geant4 " << info::Geant4Version::GetAsString() << " "
			<< info::Geant4Version::GetDateAsString() << " isnp-exp-lib "
			<< info::Version::GetAsString() << " "
			<< info::Version::GetDateAsString() << "\n"
			<< "Type\tTotalEnergy\tKineticEnergy\tTime\tDirectionX\tDirectionY\tDirectionZ\tPositionX\tPositionY\tPositionZ\n";

	std::for_each(std::begin(accum), std::end(accum), [&](auto i) {
		file << nameMap[i.nameKey]

		<< '\t' << i.totalEnergy / MeV << '\t' << i.kineticEnergy / MeV

		<< '\t' << i.time / ns

		<< '\t' << i.direction.getX() << '\t' << i.direction.getY() << '\t'
		<< i.direction.getZ()

		<< '\t' << i.position.getX() / mm << '\t'
		<< i.position.getY() / mm << '\t' << i.position.getZ() / mm

		<< '\n';
	});

	accum.clear();
}

