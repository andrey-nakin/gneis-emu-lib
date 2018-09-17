#include <gtest/gtest.h>
#include <G4SystemOfUnits.hh>
#include "isnp/util/Box.hh"

namespace isnp {

namespace util {

TEST(Box, Generic)
{

	Box const box(123. * mm, 234. * mm, 345. * mm);

	EXPECT_EQ(123. * mm, box.GetWidth());
	EXPECT_EQ(123. * mm / 2, box.GetHalfWidth());

	EXPECT_EQ(234. * mm, box.GetHeight());
	EXPECT_EQ(234. * mm / 2, box.GetHalfHeight());

	EXPECT_EQ(345. * mm, box.GetLength());
	EXPECT_EQ(345. * mm / 2, box.GetHalfLength());

}

}

}
