#include <cmath>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Spallation.hh>
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace generator {

TEST(Spallation, Diameter)
{

	Spallation spallation;

	EXPECT_DOUBLE_EQ(40 * mm, spallation.GetDiameter());

	spallation.SetDiameter(50 * mm);
	EXPECT_DOUBLE_EQ(50 * mm, spallation.GetDiameter());

}

TEST(Spallation, GeneratePosition)
{

	using namespace isnp::testutil;

	Spallation spallation;
	Stat x, y, r;

	for (int i = 0; i < 1000000; i++) {
		auto const pos = spallation.GeneratePosition();
		x += pos.getX();
		y += pos.getY();
		r += std::sqrt(pos.getX() * pos.getX() + pos.getY() * pos.getY());
	}

	EXPECT_TRUE(x.Is(0.0 * cm));
	EXPECT_TRUE(x.GetMin() > -2 * cm);
	EXPECT_TRUE(x.GetMax() < 2 * cm);
	EXPECT_TRUE(x.GetStd() > 0.99 * cm);

	EXPECT_TRUE(y.Is(0.0 * cm));
	EXPECT_TRUE(y.GetMin() > -2 * cm);
	EXPECT_TRUE(y.GetMax() < 2 * cm);
	EXPECT_TRUE(y.GetStd() > 0.99 * cm);

	EXPECT_TRUE(r.GetMax() < 2 * cm);
	EXPECT_TRUE(r.GetStd() > 0.47 * cm);

}

TEST(Spallation, ZeroDiameter)
{

	Spallation spallation;
	spallation.SetDiameter(0.0);

	auto const pos = spallation.GeneratePosition();
	EXPECT_DOUBLE_EQ(0.0, pos.getX());
	EXPECT_DOUBLE_EQ(0.0, pos.getY());

}

}

}
