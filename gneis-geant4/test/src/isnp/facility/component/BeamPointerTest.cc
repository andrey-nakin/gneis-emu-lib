#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include "isnp/facility/component/BeamPointer.hh"

namespace isnp {

namespace facility {

namespace component {

TEST(BeamPointer, GetRotation) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	auto const facility = BeamPointer::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	EXPECT_EQ(G4ThreeVector(), facility->GetRotation());

}

TEST(BeamPointer, GetPosition) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	auto const facility = BeamPointer::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	EXPECT_EQ(G4ThreeVector(), facility->GetPosition());

}

}

}

}
