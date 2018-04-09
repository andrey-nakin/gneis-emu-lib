#include <fstream>
#include <G4SystemOfUnits.hh>
#include "isnp/detector/Basic.hh"
#include "isnp/util/FileNameBuilder.hh"

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

	auto const particleName = dp->GetParticleDefinition()->GetParticleName();
	auto const findResult = keyMap.find(particleName);
	if (findResult != std::end(keyMap)) {
		names.push_back(findResult->second);
	} else {
		auto const key = names.size();
		keyMap[particleName] = key;
		nameMap[key] = particleName;
		names.push_back(key);
	}

	energies.push_back(dp->GetTotalEnergy());
	kineticEnergies.push_back(dp->GetKineticEnergy());
	momenta.push_back(dp->GetMomentumDirection());
	positions.push_back(aStep->GetPreStepPoint()->GetPosition());

	aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	return true;
}

void isnp::detector::Basic::flush() {
	std::ofstream file(isnp::util::FileNameBuilder::Make(GetName(), ".txt"));
	file
			<< "Type\tTotalEnergy\tKineticEnergy\tDirectionX\tDirectionY\tDirectionZ\tPositionX\tPositionY\tPositionZ\n";

	auto ei = std::begin(energies), last = std::end(energies);
	auto ki = std::begin(kineticEnergies);
	auto mi = std::begin(momenta);
	auto ni = std::begin(names);
	auto pi = std::begin(positions);

	for (; ei != last; ++ei, ++ki, ++mi, ++ni, ++pi) {
		file << nameMap[*ni]

		<< '\t' << *ei / MeV << '\t' << *ki / MeV

		<< '\t' << mi->getX() << '\t' << mi->getY() << '\t' << mi->getZ()

		<< '\t' << pi->getX() / mm << '\t' << pi->getY() / mm << '\t'
				<< pi->getZ() / mm

				<< '\n';
	}
}

