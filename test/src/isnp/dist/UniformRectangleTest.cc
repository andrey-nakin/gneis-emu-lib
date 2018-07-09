#include <cmath>
#include <G4SystemOfUnits.hh>
#include <gtest/gtest.h>

#include "isnp/dist/UniformRectangle.hh"
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace dist {

TEST(UniformRectangle, GetXWidth)
{

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());

}

TEST(UniformRectangle, SetXWidth)
{

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

	generator.GetProps().SetXWidth(200 * mm);
	EXPECT_EQ(200 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(100 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

	generator.GetProps().SetXHalfWidth(140 * mm);
	EXPECT_EQ(280 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(140 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

}

TEST(UniformRectangle, GetYWidth)
{

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

}

TEST(UniformRectangle, SetYWidth)
{

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

	generator.GetProps().SetYWidth(100 * mm);
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(100 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYHalfWidth());

	generator.GetProps().SetYHalfWidth(140 * mm);
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(280 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(140 * mm, generator.GetProps().GetYHalfWidth());

}

TEST(UniformRectangle, Generate)
{

	using namespace isnp::testutil;

	UniformRectangle generator(UniformRectangle::Props(120 * mm, 50 * mm));

	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(60 * mm, generator.GetProps().GetXHalfWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());
	EXPECT_EQ(25 * mm, generator.GetProps().GetYHalfWidth());

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
