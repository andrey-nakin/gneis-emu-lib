#include <sstream>
#include <gtest/gtest.h>
#include "isnp/info/Geant4Version.hh"

namespace isnp {

namespace info {

TEST(Geant4Version, Get)
{
	const std::vector<int> ver = Geant4Version::Get();
	EXPECT_EQ(3, ver.size());
	EXPECT_EQ(10, ver[0]);
	EXPECT_EQ(4, ver[1]);
	EXPECT_EQ(0, ver[2]);
}

TEST(Geant4Version, GetAsString)
{
	const G4String ver = Geant4Version::GetAsString();
	EXPECT_EQ("10.4.0", ver);
}

TEST(Geant4Version, Matches)
{
	EXPECT_TRUE(
			Geant4Version::Matches(10, 4, 0)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(10, 4)
	);
	EXPECT_TRUE(
			Geant4Version::Matches(10)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(10 + 1, 4, 0)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(10, 4 + 1, 0)
	);
	EXPECT_FALSE(
			Geant4Version::Matches(10, 4, 0 + 1)
	);
}

}

}
