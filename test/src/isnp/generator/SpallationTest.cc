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

TEST(Spallation, PositionX)
{

	using namespace isnp::testutil;

	Spallation spallation;

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionX());

	spallation.SetPositionX(20 * mm);
	EXPECT_DOUBLE_EQ(20 * mm, spallation.GetPositionX());

	Stat x;
	G4Transform3D const zeroTransform;

	for (int i = 0; i < 100000; i++) {
		auto const pos = spallation.GeneratePosition(zeroTransform);
		x += pos.getX();
	}

	EXPECT_TRUE(x.Is(20.0 * mm));
	EXPECT_NEAR(x.GetMin(), -spallation.GetDiameter() / 2 + 20.0 * mm, 1e-1 * mm);
	EXPECT_NEAR(x.GetMax(), spallation.GetDiameter() / 2 + 20.0 * mm, 1e-1 * mm);
	EXPECT_TRUE(x.GetStd() > 0.99 * cm);

}

TEST(Spallation, PositionY)
{

	using namespace isnp::testutil;

	Spallation spallation;

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionY());

	spallation.SetPositionY(20 * mm);
	EXPECT_DOUBLE_EQ(20 * mm, spallation.GetPositionY());

	Stat y;
	G4Transform3D const zeroTransform;

	for (int i = 0; i < 100000; i++) {
		auto const pos = spallation.GeneratePosition(zeroTransform);
		y += pos.getY();
	}

	EXPECT_TRUE(y.Is(20.0 * mm));
	EXPECT_NEAR(y.GetMin(), -spallation.GetDiameter() / 2 + 20.0 * mm, 1e-1 * mm);
	EXPECT_NEAR(y.GetMax(), spallation.GetDiameter() / 2 + 20.0 * mm, 1e-1 * mm);
	EXPECT_TRUE(y.GetStd() > 0.99 * cm);

}

TEST(Spallation, GeneratePositionStatistics)
{

	using namespace isnp::testutil;

	Spallation spallation;
	Stat x, y, z, r;
	G4Transform3D const zeroTransform;

	for (int i = 0; i < 1000000; i++) {
		auto const pos = spallation.GeneratePosition(zeroTransform);
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

	EXPECT_DOUBLE_EQ(-200.0 * mm, z.GetMean());

	EXPECT_NEAR(2 * cm, r.GetMax(), 0.01 * cm);
	EXPECT_NEAR(0.47 * cm, r.GetStd(), 0.01 * cm);

}

TEST(Spallation, ZeroDiameter)
{

	Spallation spallation;
	spallation.SetDiameter(0.0);
	G4Transform3D const zeroTransform;

	auto const pos = spallation.GeneratePosition(zeroTransform);
	EXPECT_DOUBLE_EQ(0.0, pos.getX());
	EXPECT_DOUBLE_EQ(0.0, pos.getY());

}

TEST(Spallation, GenerateDirection)
{

	Spallation spallation;

	{
		G4Transform3D const zeroTransform;
		auto const dir = spallation.GenerateDirection(zeroTransform);
		EXPECT_DOUBLE_EQ(0.0, dir.getX());
		EXPECT_DOUBLE_EQ(0.0, dir.getY());
		EXPECT_DOUBLE_EQ(1.0, dir.getZ());
	}

	{
		G4double const angle = 30.0 * deg;
		G4RotationMatrix rotm = G4RotationMatrix();
		rotm.rotateY(angle);
		G4ThreeVector const position = G4ThreeVector(1.0 * m, 1.0 * m, 1.0 * m);
		G4Transform3D const transform = G4Transform3D(rotm, position);
		auto const dir = spallation.GenerateDirection(transform);
		EXPECT_DOUBLE_EQ(std::sin(angle), dir.getX());
		EXPECT_DOUBLE_EQ(0.0, dir.getY());
		EXPECT_DOUBLE_EQ(std::cos(angle), dir.getZ());
	}

}

TEST(Spallation, GeneratePosition)
{

	Spallation spallation;
	spallation.SetDiameter(0.0);

	{
		G4Transform3D const zeroTransform;
		auto const pos = spallation.GeneratePosition(zeroTransform);
		EXPECT_DOUBLE_EQ(0.0, pos.getX());
		EXPECT_DOUBLE_EQ(0.0, pos.getY());
		EXPECT_DOUBLE_EQ(-200 * mm, pos.getZ());
	}

	{
		G4double const angle = 30.0 * deg;
		G4RotationMatrix rotm = G4RotationMatrix();
		rotm.rotateY(angle);
		G4ThreeVector const position = G4ThreeVector(1.0 * m, 2.0 * m, 3.0 * m);
		G4Transform3D const transform = G4Transform3D(rotm, position);
		auto const pos = spallation.GeneratePosition(transform);
		EXPECT_DOUBLE_EQ(std::sin(angle) * -200 * mm + 1 * m, pos.getX());
		EXPECT_DOUBLE_EQ(2 * m, pos.getY());
		EXPECT_DOUBLE_EQ(std::cos(angle) * -200 * mm + 3 * m, pos.getZ());
	}

}

}

}
