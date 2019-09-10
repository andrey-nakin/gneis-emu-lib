#include <gtest/gtest.h>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>
#include "isnp/util/Convert.hh"
#include "isnp/facility/component/SpallationTarget.hh"

namespace isnp {

namespace util {

TEST(Convert, StringsToVector) {

	EXPECT_EQ(G4ThreeVector(1., 2., 3.) * deg,
			Convert::StringsToVector("1", "2", "3", "deg"));
	EXPECT_EQ(G4ThreeVector(1., 2., 3.) * m,
			Convert::StringsToVector("1", "2", "3", "m"));

}

TEST(Convert, CommandToVector) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/facility basicSpallation"));

	auto const facility = facility::component::SpallationTarget::GetInstance();
	EXPECT_TRUE(facility != nullptr);

	auto const saved = facility->GetPosition();
	auto const cmd = "/isnp/facility/component/spTarget/position";

	facility->SetPosition(G4ThreeVector(1., 2., 3.) * m);
	EXPECT_EQ(facility->GetPosition(), Convert::CommandToVector(cmd));

	facility->SetPosition(G4ThreeVector(1., 2., 3.) * cm);
	EXPECT_EQ(facility->GetPosition(), Convert::CommandToVector(cmd));

	facility->SetPosition(G4ThreeVector(1., 2., 3.) * mm);
	EXPECT_EQ(facility->GetPosition(), Convert::CommandToVector(cmd));

	facility->SetPosition(saved);

}

}

}
