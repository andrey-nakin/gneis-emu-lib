#include <fstream>
#include <G4SystemOfUnits.hh>
#include "gneis/detector/BasicNeutrons.hh"

gneis::detector::BasicNeutrons::BasicNeutrons() :
		G4VSensitiveDetector("BasicNeutrons") {

}

gneis::detector::BasicNeutrons::BasicNeutrons(const G4String& name) :
		G4VSensitiveDetector(name) {

}

gneis::detector::BasicNeutrons::~BasicNeutrons() {
	flush();
}

G4bool gneis::detector::BasicNeutrons::ProcessHits(G4Step* const aStep,
		G4TouchableHistory* const /* ROhist */) {

	const auto dp = aStep->GetTrack()->GetDynamicParticle();

	G4cout << "detector " << GetName()
			<< "\t" << dp->GetParticleDefinition()->GetParticleName()
			<< "\t" << dp->GetTotalEnergy() / MeV
			<< '\n';

	if (dp->GetParticleDefinition()->GetParticleName() == "neutron") {
		energies.push_back(dp->GetKineticEnergy());
		momenta.push_back(dp->GetMomentum());
	}

	aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	return true;
}

void gneis::detector::BasicNeutrons::flush() {
	G4String fileName = GetName() + ".txt";
	std::ofstream file(fileName);
	file << "# Energy (MeV)\tMomentum X\tMomentum Y\tMomentum Z\n";

	auto ei = energies.begin(), last = energies.end();
	auto mi = momenta.begin();

	for (; ei != last; ++ei, ++mi) {
		file << *ei / MeV << '\t' << mi->getX() << '\t' << mi->getY() << '\t'
				<< mi->getZ() << '\n';
	}
}

