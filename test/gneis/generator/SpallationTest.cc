#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>

#include <gtest/gtest.h>

#include "gneis/generator/Spallation.hh"

namespace gneis {

namespace generator {

TEST(Spallation, GeneratePosition)
{
	G4RunManager runManager;
	runManager.SetUserInitialization(new QGSP_INCLXX_HP);

	using namespace gneis::generator;
	Spallation spallation;

	spallation.GeneratePosition();
}

}

}
