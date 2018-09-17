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
		// 	fix linking error on gcc 7.3
			G4PhysListFactory factory;
		});

}
