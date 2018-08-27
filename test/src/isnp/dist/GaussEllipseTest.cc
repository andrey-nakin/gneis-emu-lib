#include <cmath>
#include <G4SystemOfUnits.hh>
#include <gtest/gtest.h>

#include "isnp/dist/GaussEllipse.hh"
#include "isnp/testutil/Stat.hh"

namespace isnp {

namespace dist {

TEST(GaussEllipse, GetXWidth)
{

	GaussEllipse generator(GaussEllipseProps(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());

}

TEST(GaussEllipse, SetXWidth)
{

	GaussEllipse generator(GaussEllipseProps(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());

	generator.GetProps().SetXWidth(200 * mm);
	EXPECT_EQ(200 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());

}

TEST(GaussEllipse, GetYWidth)
{

	GaussEllipse generator(GaussEllipseProps(120 * mm, 50 * mm));
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());

}

TEST(GaussEllipse, SetYWidth)
{

	GaussEllipse generator(GaussEllipseProps(120 * mm, 50 * mm));
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(50 * mm, generator.GetProps().GetYWidth());

	generator.GetProps().SetYWidth(100 * mm);
	EXPECT_EQ(120 * mm, generator.GetProps().GetXWidth());
	EXPECT_EQ(100 * mm, generator.GetProps().GetYWidth());

}

TEST(GaussEllipse, Generate)
{

	using namespace isnp::testutil;

	static G4double const FWHM = 2 * std::sqrt(2 * std::log(2));
	EXPECT_NEAR(2.354820045, FWHM, 0.5e-10);
	static G4double const expectedXWidth[] = {-1, 500 * mm, 1 * angstrom};
	static G4double const expectedYWidth[] = {-1, 20 * mm, 2 * angstrom};
	static G4double const expectedRMax[] = {114.78 * mm, 300.50 * mm, 2 * angstrom};
	static std::size_t nTests = sizeof(expectedXWidth) / sizeof(expectedXWidth[0]);

	for (std::size_t testNo = 0; testNo < nTests; testNo++) {

		GaussEllipse generator(GaussEllipseProps(200 * mm, 50 * mm));

		if (expectedXWidth[testNo] > 0) {
			generator.GetProps().SetXWidth(expectedXWidth[testNo]);
		}
		if (expectedYWidth[testNo] > 0) {
			generator.GetProps().SetYWidth(expectedYWidth[testNo]);
		}

		Stat x, y, z, r;

		for (int i = 0; i < 1000000; i++) {
			auto const pos = generator.Generate();
			x += pos.getX();
			y += pos.getY();
			z += pos.getZ();
			r += std::sqrt(pos.getX() * pos.getX() + pos.getY() * pos.getY());
		}

		EXPECT_TRUE(x.Is(0.0 * mm));
		G4double const eXWidth = expectedXWidth[testNo] > 0 ? expectedXWidth[testNo] : 200 * mm;
		EXPECT_NEAR(eXWidth / FWHM, x.GetStd(), 0.1 * mm);

		EXPECT_TRUE(y.Is(0.0 * mm));
		G4double const eYWidth = expectedYWidth[testNo] > 0 ? expectedYWidth[testNo] : 50 * mm;
		EXPECT_NEAR(eYWidth / FWHM, y.GetStd(), 0.1 * mm);

		EXPECT_DOUBLE_EQ(0.0 * mm, z.GetMean());

		EXPECT_NEAR(expectedRMax[testNo] / FWHM, r.GetStd(), 0.5 * mm);

	}

}

}

}
