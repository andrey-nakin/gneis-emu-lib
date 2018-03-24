#include <sstream>
#include <gtest/gtest.h>
#include "gneis/util/NameBuilder.hh"

TEST(gneis_util_NameBuilder, Make_pchar_pchar)
{
	const char* const s1 = "first";
	const char* const s2 = "second";
	const G4String res = gneis::util::NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}

TEST(gneis_util_NameBuilder, Make_g4s_pchar)
{
	const G4String s1 = "first";
	const char* const s2 = "second";
	const G4String res = gneis::util::NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}

TEST(gneis_util_NameBuilder, Make_g4s_g4s)
{
	const G4String s1 = "first";
	const G4String s2 = "second";
	const G4String res = gneis::util::NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}
