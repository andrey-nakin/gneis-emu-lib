#include <gtest/gtest.h>
#include <G4UImanager.hh>
#include "isnp/util/FileNameBuilder.hh"

namespace isnp {

namespace util {

TEST(FileNameBuilderMessenger, GetSuffix)
{

	auto const uiManager = G4UImanager::GetUIpointer();

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/fileName/suffix 123"));
	EXPECT_EQ(G4String("123"), isnp::util::FileNameBuilder::GetCommonSuffix());

	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/fileName/suffix abc"));
	EXPECT_EQ(G4String("abc"), isnp::util::FileNameBuilder::GetCommonSuffix());

}

}

}
