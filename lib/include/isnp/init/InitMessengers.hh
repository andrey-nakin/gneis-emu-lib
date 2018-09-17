#ifndef isnp_init_InitMessengers_hh
#define isnp_init_InitMessengers_hh

#include <memory>

#include <G4RunManager.hh>

namespace isnp {

namespace init {

class FileNameBuilderMessenger;
class PhysListMessenger;
class FacilityMessenger;
class UserActionMessenger;

class InitMessengers {
public:

	InitMessengers(G4RunManager& aRunManager);
	~InitMessengers();

private:

	std::unique_ptr<FileNameBuilderMessenger> const fileNameBuilderMessenger;
	std::unique_ptr<PhysListMessenger> const physListMessenger;
	std::unique_ptr<FacilityMessenger> const facilityMessenger;
	std::unique_ptr<UserActionMessenger> const userActionMessenger;

};

}

}

#endif	//	isnp_init_InitMessenger_hh
