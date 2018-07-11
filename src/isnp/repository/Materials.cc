#include <vector>
#include <G4NistManager.hh>
#include "G4SystemOfUnits.hh"
#include "isnp/repository/Materials.hh"

namespace isnp {

namespace repository {

Materials::Materials() {

	CreateMaterials();

}

Materials::~Materials() {

}

Materials* Materials::GetInstance() {

	static Materials* instance = nullptr;

	if (!instance) {
		instance = new Materials;
	}
	return instance;

}

void Materials::CreateMaterials() {

	auto const nist = G4NistManager::Instance();
	std::vector < G4String > elements;
	std::vector < G4double > fractionMass;

	// Bronze of БрО5Ц5С5 type

	elements.push_back("Cu");
	fractionMass.push_back(0.839);

	elements.push_back("Sn");
	fractionMass.push_back(0.05);

	elements.push_back("Zn");
	fractionMass.push_back(0.05);

	elements.push_back("Pb");
	fractionMass.push_back(0.05);

	elements.push_back("Sb");
	fractionMass.push_back(0.005);

	elements.push_back("Fe");
	fractionMass.push_back(0.004);

	elements.push_back("P");
	fractionMass.push_back(0.001);

	elements.push_back("Al");
	fractionMass.push_back(0.0005);

	elements.push_back("Si");
	fractionMass.push_back(0.0005);

	nist->ConstructNewMaterial("BR05C5S5", elements, fractionMass, 8.800);

}

}

}
