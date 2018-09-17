#include <sstream>
#include <gtest/gtest.h>
#include "isnp/info/Geant4Version.hh"

namespace isnp {

namespace info {

TEST(Geant4Version, Get)
{

	const std::vector<int> ver = Geant4Version::Get();
	EXPECT_EQ(3, ver.size());
	EXPECT_TRUE(ver[0] >= 10);
	EXPECT_TRUE(ver[1] >= 0);
	EXPECT_TRUE(ver[2] >= 0);

}

TEST(Geant4Version, GetAsString)
{

	const G4String ver = Geant4Version::GetAsString();
	EXPECT_FALSE(ver.isNull());

}

TEST(Geant4Version, Matches)
{

	auto const major = Geant4Version::Get()[0];
	auto const minor = Geant4Version::Get()[1];
	auto const patch = Geant4Version::Get()[2];

	EXPECT_TRUE(
			Geant4Version::Matches(major, minor, patch)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(major, minor)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(major)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(major + 1, minor, patch)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(major, minor + 1, patch)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(major, minor, patch + 1)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(major - 1, minor + 1, patch)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(major - 1, minor, patch + 1)
	);

}

}

}
