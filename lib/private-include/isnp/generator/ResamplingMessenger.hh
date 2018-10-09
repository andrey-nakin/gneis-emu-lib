#ifndef isnp_generator_ResamplingMessenger_hh
#define isnp_generator_ResamplingMessenger_hh

#include <memory>

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcommand.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "isnp/generator/Resampling.hh"

namespace isnp {

namespace generator {

class ResamplingMessenger: public G4UImessenger {
public:

	ResamplingMessenger(Resampling& generator);
	~ResamplingMessenger() override;

	G4String GetCurrentValue(G4UIcommand*) override;
	void SetNewValue(G4UIcommand*, G4String) override;

private:

	Resampling& generator;
	std::unique_ptr<G4UIdirectory> const directory;
	std::unique_ptr<G4UIcmdWithAnInteger> const verboseCmd;
	std::unique_ptr<G4UIcmdWithAString> const fileCmd;

};

}

}

#endif	//	isnp_generator_ResamplingMessenger_hh
