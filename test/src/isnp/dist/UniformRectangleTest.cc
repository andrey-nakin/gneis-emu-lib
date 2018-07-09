#include <cmath>
#include <G4SystemOfUnits.hh>
#include <gtest/gtest.h>

#include "isnp/dist/UniformRectangle.hh"
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace dist {

TEST(Spallation, Generate)
{

	using namespace isnp::testutil;

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));
	Stat x, y, z, r;

	for (int i = 0; i < 1000000; i++) {
		auto const pos = generator.Generate();
		x += pos.getX();
		y += pos.getY();
		z += pos.getZ();
	}

	EXPECT_TRUE(x.Is(0.0 * mm));
	EXPECT_NEAR(-60 * mm, x.GetMin(), 0.001 * mm);
	EXPECT_NEAR(60 * mm, x.GetMax(), 0.001 * mm);
	EXPECT_NEAR(120 * mm / std::sqrt(12), x.GetStd(), 0.1 * mm);

	EXPECT_TRUE(y.Is(0.0 * mm));
	EXPECT_NEAR(-25 * mm, y.GetMin(), 0.001 * mm);
	EXPECT_NEAR(25 * mm, y.GetMax(), 0.001 * mm);
	EXPECT_NEAR(50.0 * mm / std::sqrt(12), y.GetStd(), 0.1 * mm);

	EXPECT_TRUE(z.Is(0.0 * mm));
	EXPECT_NEAR(0 * mm, z.GetMin(), 0 * mm);
	EXPECT_NEAR(0 * mm, z.GetMax(), 0 * mm);
	EXPECT_NEAR(0 * mm, z.GetStd(), 0 * mm);

}

}

}
