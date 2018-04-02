#include <cmath>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>

#include <gtest/gtest.h>

#include <gneis/generator/Spallation.hh>
#include "gneis/testutil/Geant4Runner.hh"
#include "gneis/testutil/Stat.hh"

namespace gneis {

namespace generator {

TEST(Spallation, GeneratePosition)
{
	gneis::testutil::Geant4Runner::Run([]() {
				using namespace gneis::testutil;

				Spallation spallation;
				Stat x, y, r;

				for (int i = 0; i < 1000000; i++) {
					auto const pos = spallation.GeneratePosition();
					x += pos.getX();
					y += pos.getY();
					r += std::sqrt(pos.getX() * pos.getX() + pos.getY() * pos.getY());
				}

				EXPECT_TRUE(x.Is(0.0 * cm));
				EXPECT_TRUE(x.GetMin() > -2.5 * cm);
				EXPECT_TRUE(x.GetMax() < 2.5 * cm);
				EXPECT_TRUE(x.GetStd() > 1.2 * cm);

				EXPECT_TRUE(y.Is(0.0 * cm));
				EXPECT_TRUE(y.GetMin() > -2.5 * cm);
				EXPECT_TRUE(y.GetMax() < 2.5 * cm);
				EXPECT_TRUE(y.GetStd() > 1.2 * cm);

				EXPECT_TRUE(r.GetMax() < 2.5 * cm);
				EXPECT_TRUE(r.GetStd() > 0.5 * cm);
			});
}

}

}
