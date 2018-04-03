#include <fstream>
#include <G4SystemOfUnits.hh>
#include "gneis/detector/Basic.hh"
#include "gneis/util/FileNameBuilder.hh"

gneis::detector::Basic::Basic() :
		G4VSensitiveDetector("detector") {

}

gneis::detector::Basic::Basic(const G4String& name) :
		G4VSensitiveDetector(name) {

}

gneis::detector::Basic::~Basic() {
	flush();
}

G4bool gneis::detector::Basic::ProcessHits(G4Step* const aStep,
		G4TouchableHistory* const /* ROhist */) {

	const auto dp = aStep->GetTrack()->GetDynamicParticle();

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
	momenta.push_back(dp->GetMomentum());

	aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	return true;
}

void gneis::detector::Basic::flush() {
	std::ofstream file(gneis::util::FileNameBuilder::Make(GetName(), ".txt"));
	file << "# Type\tEnergy (MeV)\tMomentum X\tMomentum Y\tMomentum Z\n";

	auto ei = std::begin(energies), last = std::end(energies);
	auto mi = std::begin(momenta);
	auto ni = std::begin(names);

	for (; ei != last; ++ei, ++mi, ++ni) {
		file << nameMap[*ni] << '\t' << *ei / MeV << '\t' << mi->getX() << '\t'
				<< mi->getY() << '\t' << mi->getZ() << '\n';
	}
}

