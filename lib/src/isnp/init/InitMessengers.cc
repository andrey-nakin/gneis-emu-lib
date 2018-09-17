#include "isnp/init/InitMessengers.hh"
#include "isnp/init/FileNameBuilderMessenger.hh"
#include "isnp/init/PhysListMessenger.hh"
#include "isnp/init/FacilityMessenger.hh"
#include "isnp/init/UserActionMessenger.hh"

namespace isnp {

namespace init {

InitMessengers::InitMessengers(G4RunManager& aRunManager) :
		fileNameBuilderMessenger(new FileNameBuilderMessenger), physListMessenger(
				new PhysListMessenger(aRunManager)), facilityMessenger(
				new FacilityMessenger(aRunManager)), userActionMessenger(
				new UserActionMessenger(aRunManager)) {

}

InitMessengers::~InitMessengers() {

}

}

}
