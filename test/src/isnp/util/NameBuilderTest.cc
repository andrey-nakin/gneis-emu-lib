#include <gtest/gtest.h>
#include "isnp/util/NameBuilder.hh"

namespace isnp {

namespace util {

TEST(NameBuilder, Make_pchar_pchar)
{
	const char* const s1 = "first";
	const char* const s2 = "second";
	const G4String res = NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}

TEST(NameBuilder, Make_g4s_pchar)
{
	const G4String s1 = "first";
	const char* const s2 = "second";
	const G4String res = NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}

TEST(NameBuilder, Make_g4s_g4s)
{
	const G4String s1 = "first";
	const G4String s2 = "second";
	const G4String res = NameBuilder::Make(s1, s2);
	EXPECT_EQ("first:second", res);
}

}

}
