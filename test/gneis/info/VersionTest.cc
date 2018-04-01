#include <sstream>
#include <gtest/gtest.h>
#include "gneis/info/Version.hh"

TEST(gneis_info_Version, Defines)
{
	EXPECT_TRUE(GNEISEMULIB_VERSION_MAJOR >= 0);
	EXPECT_TRUE(GNEISEMULIB_VERSION_MINOR >= 0);
	EXPECT_TRUE(GNEISEMULIB_VERSION_PATCH >= 0);
}

TEST(gneis_info_Version, Get)
{
	const std::vector<int> ver = gneis::info::Version::Get();
	EXPECT_EQ(3, ver.size());
	EXPECT_EQ(GNEISEMULIB_VERSION_MAJOR, ver[0]);
	EXPECT_EQ(GNEISEMULIB_VERSION_MINOR, ver[1]);
	EXPECT_EQ(GNEISEMULIB_VERSION_PATCH, ver[2]);
}

TEST(gneis_info_Version, GetAsString)
{
	std::stringstream s;
	s
	<< GNEISEMULIB_VERSION_MAJOR
	<< '.'
	<< GNEISEMULIB_VERSION_MINOR
	<< '.'
	<< GNEISEMULIB_VERSION_PATCH;
	const G4String ver = gneis::info::Version::GetAsString();
	EXPECT_EQ(s.str(), ver);
}

TEST(gneis_info_Version, Matches)
{
	EXPECT_TRUE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR, GNEISEMULIB_VERSION_MINOR, GNEISEMULIB_VERSION_PATCH)
	);
	EXPECT_TRUE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR, GNEISEMULIB_VERSION_MINOR)
	);
	EXPECT_TRUE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR)
	);
	EXPECT_FALSE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR + 1, GNEISEMULIB_VERSION_MINOR, GNEISEMULIB_VERSION_PATCH)
	);
	EXPECT_FALSE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR, GNEISEMULIB_VERSION_MINOR + 1, GNEISEMULIB_VERSION_PATCH)
	);
	EXPECT_FALSE(
			gneis::info::Version::Matches(GNEISEMULIB_VERSION_MAJOR, GNEISEMULIB_VERSION_MINOR, GNEISEMULIB_VERSION_PATCH + 1)
	);
}
