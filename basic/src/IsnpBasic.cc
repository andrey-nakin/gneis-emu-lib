#include <QGSP_INCLXX_HP.hh>
#include <QGSP_BERT_HP.hh>
#include <QGSP_BIC_HP.hh>
#include <G4PhysListFactory.hh>

#include <isnp/runner/BasicRunner.hh>
#include <isnp/info/Version.hh>

int main(int argc, char* argv[]) {

	G4cout << G4endl
			<< "*************************************************************"
			<< G4endl << "IsnpBasic, IsnpEmuLib version "
			<< isnp::info::Version::GetAsString() << " as of "
			<< isnp::info::Version::GetDateAsString() << G4endl
			<< "Copyright Andrey Nakin <andrey.nakin@ter-net.com" << G4endl
			<< "*************************************************************"
			<< G4endl << G4endl;

	isnp::runner::BasicRunner runner(argc, argv);

	return runner.Run([](G4RunManager& /* runManager */) {
		if (rand() < 0) {

			G4PhysListFactory factory;
//			factory.AvailablePhysLists();
//			factory.IsReferencePhysList("");

//			runManager.SetUserInitialization(new QGSP_BERT_HP);
//			runManager.SetUserInitialization(new QGSP_BIC_HP);
//			runManager.SetUserInitialization(new QGSP_INCLXX_HP);
		}

	});

}
