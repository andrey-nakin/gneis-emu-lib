#include <gtest/gtest.h>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>

namespace isnp {

namespace repository {

TEST(Materials, BR05C5S5) {
	auto const nist = G4NistManager::Instance();
	auto const material = nist->FindOrBuildMaterial("BR05C5S5");
	EXPECT_EQ("BR05C5S5", material->GetName());
	EXPECT_EQ(kStateSolid, material->GetState());
	EXPECT_EQ(8.800 * g / cm3, material->GetDensity());
}

TEST(Materials, DUR_AMG3) {
	auto const nist = G4NistManager::Instance();
	auto const material = nist->FindOrBuildMaterial("DUR_AMG3");
	EXPECT_EQ("DUR_AMG3", material->GetName());
	EXPECT_EQ(kStateSolid, material->GetState());
	EXPECT_EQ(2.660 * g / cm3, material->GetDensity());
}

TEST(Materials, FOREVACUUM_100) {
	auto const nist = G4NistManager::Instance();
	auto const material = nist->FindOrBuildMaterial("FOREVACUUM_100");
	EXPECT_EQ("FOREVACUUM_100", material->GetName());
	EXPECT_EQ(kStateGas, material->GetState());
	EXPECT_NEAR(0.00120479e-2 * g / cm3, material->GetDensity(),
			1.0e-6 * 0.00120479e-2 * g / cm3);
}

}

}
