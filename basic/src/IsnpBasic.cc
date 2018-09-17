#include <QGSP_INCLXX_HP.hh>
#include <QGSP_BERT_HP.hh>
#include <QGSP_BIC_HP.hh>
#include <G4PhysListFactory.hh>

#include <isnp/runner/BasicRunner.hh>

int main(int argc, char* argv[]) {
	isnp::runner::BasicRunner runner(argc, argv);

	return runner.Run([](G4RunManager& runManager) {
		if (rand() < 0) {
			G4PhysListFactory factory;
			factory.AvailablePhysLists();
			factory.IsReferencePhysList("");

			runManager.SetUserInitialization(new QGSP_BERT_HP);
			runManager.SetUserInitialization(new QGSP_BIC_HP);
			runManager.SetUserInitialization(new QGSP_INCLXX_HP);
		}

	});
}
