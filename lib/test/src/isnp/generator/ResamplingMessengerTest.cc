#include <cmath>

#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Resampling.hh>

namespace isnp {

namespace generator {

TEST(ResamplingMessenger, GetVerboseLevel) {

	auto const uiManager = G4UImanager::GetUIpointer();

	Resampling resampling;

	EXPECT_EQ(1, uiManager->GetCurrentIntValue("/isnp/gun/resampling/verbose"));
	resampling.SetVerboseLevel(0);
	EXPECT_EQ(0, uiManager->GetCurrentIntValue("/isnp/gun/resampling/verbose"));

}

TEST(ResamplingMessenger, SetVerboseLevel) {

	auto const uiManager = G4UImanager::GetUIpointer();

	Resampling resampling;

	EXPECT_EQ(1, resampling.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun/resampling/verbose 2"));
	EXPECT_EQ(2, resampling.GetVerboseLevel());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/gun/resampling/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/gun/resampling/verbose 4"));

}

TEST(ResamplingMessenger, GetFile) {

	auto const uiManager = G4UImanager::GetUIpointer();

	Resampling resampling;

	EXPECT_EQ("",
			uiManager->GetCurrentStringValue("/isnp/gun/resampling/file"));
	resampling.SetSampleFileName("file1.dat");
	EXPECT_EQ("file1.dat",
			uiManager->GetCurrentStringValue("/isnp/gun/resampling/file"));

}

TEST(ResamplingMessenger, SetFile) {

	auto const uiManager = G4UImanager::GetUIpointer();

	Resampling resampling;

	EXPECT_EQ("", resampling.GetSampleFileName());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/resampling/file file1.dat"));
	EXPECT_EQ("file1.dat", resampling.GetSampleFileName());

}

}

}
