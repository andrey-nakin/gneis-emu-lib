#include <gtest/gtest.h>
#include <G4SystemOfUnits.hh>
#include "isnp/util/RectangleProps.hh"

namespace isnp {

namespace util {

TEST(RectangleProps, GetXWidth)
{

	RectangleProps props(120 * mm, 50 * mm);
	EXPECT_EQ(120 * mm, props.GetXWidth());
	EXPECT_EQ(60 * mm, props.GetXHalfWidth());

}

TEST(RectangleProps, SetXWidth)
{

	RectangleProps props(120 * mm, 50 * mm);
	EXPECT_EQ(120 * mm, props.GetXWidth());
	EXPECT_EQ(60 * mm, props.GetXHalfWidth());
	EXPECT_EQ(50 * mm, props.GetYWidth());
	EXPECT_EQ(25 * mm, props.GetYHalfWidth());

	props.SetXWidth(200 * mm);
	EXPECT_EQ(200 * mm, props.GetXWidth());
	EXPECT_EQ(100 * mm, props.GetXHalfWidth());
	EXPECT_EQ(50 * mm, props.GetYWidth());
	EXPECT_EQ(25 * mm, props.GetYHalfWidth());

	props.SetXHalfWidth(140 * mm);
	EXPECT_EQ(280 * mm, props.GetXWidth());
	EXPECT_EQ(140 * mm, props.GetXHalfWidth());
	EXPECT_EQ(50 * mm, props.GetYWidth());
	EXPECT_EQ(25 * mm, props.GetYHalfWidth());

}

TEST(RectangleProps, GetYWidth)
{

	RectangleProps props(120 * mm, 50 * mm);
	EXPECT_EQ(50 * mm, props.GetYWidth());
	EXPECT_EQ(25 * mm, props.GetYHalfWidth());

}

TEST(RectangleProps, SetYWidth)
{

	RectangleProps props(120 * mm, 50 * mm);
	EXPECT_EQ(120 * mm, props.GetXWidth());
	EXPECT_EQ(60 * mm, props.GetXHalfWidth());
	EXPECT_EQ(50 * mm, props.GetYWidth());
	EXPECT_EQ(25 * mm, props.GetYHalfWidth());

	props.SetYWidth(100 * mm);
	EXPECT_EQ(120 * mm, props.GetXWidth());
	EXPECT_EQ(60 * mm, props.GetXHalfWidth());
	EXPECT_EQ(100 * mm, props.GetYWidth());
	EXPECT_EQ(50 * mm, props.GetYHalfWidth());

	props.SetYHalfWidth(140 * mm);
	EXPECT_EQ(120 * mm, props.GetXWidth());
	EXPECT_EQ(60 * mm, props.GetXHalfWidth());
	EXPECT_EQ(280 * mm, props.GetYWidth());
	EXPECT_EQ(140 * mm, props.GetYHalfWidth());

}

}

}
