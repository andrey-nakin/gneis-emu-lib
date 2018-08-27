#include <cmath>
#include <G4SystemOfUnits.hh>
#include <gtest/gtest.h>

#include "isnp/dist/UniformCircle.hh"
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace dist {

TEST(UniformCircle, GetDiameter)
{

	UniformCircle generator(UniformCircleProps(120 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetDiameter());

}

TEST(UniformCircle, SetDiameter)
{

	UniformCircle generator(UniformCircleProps(120 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetDiameter());

	generator.GetProps().SetDiameter(200 * mm);
	EXPECT_EQ(200 * mm, generator.GetProps().GetDiameter());

}

TEST(UniformCircle, Generate)
{

	using namespace isnp::testutil;

	UniformCircle generator(UniformCircleProps(40 * mm));
	Stat x, y, z, r;

	for (int i = 0; i < 1000000; i++) {
		auto const pos = generator.Generate();
		x += pos.getX();
		y += pos.getY();
		z += pos.getZ();
		r += std::sqrt(pos.getX() * pos.getX() + pos.getY() * pos.getY());
	}

	EXPECT_TRUE(x.Is(0.0 * cm));
	EXPECT_NEAR(-2 * cm, x.GetMin(), 0.001 * cm);
	EXPECT_NEAR(2 * cm, x.GetMax(), 0.001 * cm);
	EXPECT_NEAR(1.0 * cm, x.GetStd(), 0.001 * cm);

	EXPECT_TRUE(y.Is(0.0 * cm));
	EXPECT_NEAR(-2 * cm, y.GetMin(), 0.001 * cm);
	EXPECT_NEAR(2 * cm, y.GetMax(), 0.001 * cm);
	EXPECT_NEAR(1.0 * cm, y.GetStd(), 0.001 * cm);

	EXPECT_DOUBLE_EQ(0.0 * mm, z.GetMean());

	EXPECT_NEAR(2 * cm, r.GetMax(), 0.01 * cm);
	EXPECT_NEAR(0.47 * cm, r.GetStd(), 0.01 * cm);

}

TEST(UniformCircle, ZeroDiameter)
{

	UniformCircle generator(UniformCircleProps(0 * mm));

	auto const pos = generator.Generate();
	EXPECT_DOUBLE_EQ(0.0, pos.getX());
	EXPECT_DOUBLE_EQ(0.0, pos.getY());

}

}

}
