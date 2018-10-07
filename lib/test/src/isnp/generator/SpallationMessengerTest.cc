#include <cmath>

#include <G4RunManager.hh>
#include <QGSP_INCLXX_HP.hh>
#include <G4SystemOfUnits.hh>
#include <G4UImanager.hh>

#include <gtest/gtest.h>

#include <isnp/generator/Spallation.hh>

namespace isnp {

namespace generator {

constexpr G4double GET_CURRENT_DOUBLE_VALUE_DELTA = 1.e-6;

TEST(SpallationMessenger, GetDiameter) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_NEAR(40 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/diameter"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetUniformCircle().GetProps().SetDiameter(50 * mm);
	EXPECT_NEAR(50 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/diameter"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetDiameter) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_DOUBLE_EQ(40 * mm,
			spallation.GetUniformCircle().GetProps().GetDiameter());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/spallation/diameter 50 mm"));
	EXPECT_DOUBLE_EQ(50 * mm,
			spallation.GetUniformCircle().GetProps().GetDiameter());

}

TEST(SpallationMessenger, GetXWidth) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_NEAR(200 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/xWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetGaussEllipse().GetProps().SetXWidth(300 * mm);
	EXPECT_NEAR(300 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/xWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetXWidth) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_DOUBLE_EQ(200 * mm,
			spallation.GetGaussEllipse().GetProps().GetXWidth());
	EXPECT_DOUBLE_EQ(120 * mm,
			spallation.GetUniformRectangle().GetProps().GetXWidth());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun/spallation/xWidth 300 mm"));
	EXPECT_DOUBLE_EQ(300 * mm,
			spallation.GetGaussEllipse().GetProps().GetXWidth());
	EXPECT_DOUBLE_EQ(300 * mm,
			spallation.GetUniformRectangle().GetProps().GetXWidth());

}

TEST(SpallationMessenger, GetYWidth) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_NEAR(50 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/yWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.GetGaussEllipse().GetProps().SetYWidth(20 * mm);
	EXPECT_NEAR(20 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/yWidth"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetYWidth) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_DOUBLE_EQ(50 * mm,
			spallation.GetGaussEllipse().GetProps().GetYWidth());
	EXPECT_DOUBLE_EQ(50 * mm,
			spallation.GetUniformRectangle().GetProps().GetYWidth());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun/spallation/yWidth 20 mm"));
	EXPECT_DOUBLE_EQ(20 * mm,
			spallation.GetGaussEllipse().GetProps().GetYWidth());
	EXPECT_DOUBLE_EQ(20 * mm,
			spallation.GetUniformRectangle().GetProps().GetYWidth());

}

TEST(SpallationMessenger, GetPositionX) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_NEAR(0 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/positionX"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.SetPositionX(5 * mm);
	EXPECT_NEAR(5 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/positionX"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetPositionX) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionX());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/spallation/positionX 5 mm"));
	EXPECT_DOUBLE_EQ(5 * mm, spallation.GetPositionX());

}

TEST(SpallationMessenger, GetPositionY) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_NEAR(0 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/positionY"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);
	spallation.SetPositionY(5 * mm);
	EXPECT_NEAR(5 * mm,
			uiManager->GetCurrentDoubleValue("/isnp/gun/spallation/positionY"),
			GET_CURRENT_DOUBLE_VALUE_DELTA);

}

TEST(SpallationMessenger, SetPositionY) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_DOUBLE_EQ(0 * mm, spallation.GetPositionY());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/spallation/positionY 5 mm"));
	EXPECT_DOUBLE_EQ(5 * mm, spallation.GetPositionY());

}

TEST(SpallationMessenger, GetVerboseLevel) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_EQ(1, uiManager->GetCurrentIntValue("/isnp/gun/spallation/verbose"));
	spallation.SetVerboseLevel(0);
	EXPECT_EQ(0, uiManager->GetCurrentIntValue("/isnp/gun/spallation/verbose"));

}

TEST(SpallationMessenger, SetVerboseLevel) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_EQ(1, spallation.GetVerboseLevel());
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/gun/spallation/verbose 2"));
	EXPECT_EQ(2, spallation.GetVerboseLevel());
	EXPECT_EQ(0x18f,
			uiManager->ApplyCommand("/isnp/gun/spallation/verbose -1"));
	EXPECT_EQ(0x18f, uiManager->ApplyCommand("/isnp/gun/spallation/verbose 4"));

}

TEST(SpallationMessenger, GetMode) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_EQ("UniformRectangle",
			uiManager->GetCurrentStringValue("/isnp/gun/spallation/mode"));
	spallation.SetMode(Spallation::Mode::GaussianEllipse);
	EXPECT_EQ("GaussianEllipse",
			uiManager->GetCurrentStringValue("/isnp/gun/spallation/mode"));
	spallation.SetMode(Spallation::Mode::UniformRectangle);
	EXPECT_EQ("UniformRectangle",
			uiManager->GetCurrentStringValue("/isnp/gun/spallation/mode"));
	spallation.SetMode(Spallation::Mode::UniformCircle);
	EXPECT_EQ("UniformCircle",
			uiManager->GetCurrentStringValue("/isnp/gun/spallation/mode"));

}

TEST(SpallationMessenger, SetMode) {

	auto const uiManager = G4UImanager::GetUIpointer();
	EXPECT_EQ(0, uiManager->ApplyCommand("/isnp/physList QGSP_INCLXX_HP"));

	Spallation spallation;

	EXPECT_EQ(Spallation::Mode::UniformRectangle, spallation.GetMode());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/gun/spallation/mode GaussianEllipse"));
	EXPECT_EQ(Spallation::Mode::GaussianEllipse, spallation.GetMode());
	EXPECT_EQ(500,
			uiManager->ApplyCommand("/isnp/gun/spallation/mode badValue"));
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/spallation/mode UniformCircle"));
	EXPECT_EQ(Spallation::Mode::UniformCircle, spallation.GetMode());
	EXPECT_EQ(0,
			uiManager->ApplyCommand(
					"/isnp/gun/spallation/mode UniformRectangle"));
	EXPECT_EQ(Spallation::Mode::UniformRectangle, spallation.GetMode());
	EXPECT_EQ(0,
			uiManager->ApplyCommand("/isnp/gun/spallation/mode UniformCircle"));
	EXPECT_EQ(Spallation::Mode::UniformCircle, spallation.GetMode());

}

}

}
