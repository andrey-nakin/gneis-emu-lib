#include <fstream>
#include <G4SystemOfUnits.hh>
#include "isnp/detector/BasicNeutrons.hh"
#include "isnp/util/FileNameBuilder.hh"

isnp::detector::BasicNeutrons::BasicNeutrons() :
		G4VSensitiveDetector("neutron-detector") {

}

isnp::detector::BasicNeutrons::BasicNeutrons(const G4String& name) :
		G4VSensitiveDetector(name) {

}

isnp::detector::BasicNeutrons::~BasicNeutrons() {
	flush();
}

G4bool isnp::detector::BasicNeutrons::ProcessHits(G4Step* const aStep,
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

void isnp::detector::BasicNeutrons::flush() {
	std::ofstream file(isnp::util::FileNameBuilder::Make(GetName(), ".txt"));
	file << "# Energy (MeV)\tMomentum X\tMomentum Y\tMomentum Z\n";

	auto ei = energies.begin(), last = energies.end();
	auto mi = momenta.begin();

	for (; ei != last; ++ei, ++mi) {
		file << *ei / MeV << '\t' << mi->getX() << '\t' << mi->getY() << '\t'
				<< mi->getZ() << '\n';
	}
}

