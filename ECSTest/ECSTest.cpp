// ECSTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "ecs.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <utility>
#include "mECS.h"
#include "boost\hana\fwd\at.hpp"
/*
typedef ECS<CompA, CompB, CompC> MyECS;

struct ABSystem : MyECS::System<CompA, CompB> {
	template<typename T>
	void procComps(std::vector<T>& comps) {
		std::cout << "AB Component Handler. Count: " << comps.size() << std::endl;
	}
};


struct ACSystem : MyECS::System<CompA, CompC> {
	
};*/

struct AStruct {

};

struct BStruct {

};
using namespace std;
using namespace mECS;

int main()
{
	/*MyECS ecs;
	ABSystem abSys;
	abSys.setECS(&ecs);


	//Add some components to the ECS
	ecs.addComponent<CompA>(CompA());
	ecs.addComponent<CompA>(CompA());
	ecs.addComponent<CompB>(CompB());
	ecs.addComponent<CompC>(CompC());
	//ACSystem acSys;
	abSys.process();
	//acSys.process();
	*/
	//auto MyComponentTypes = ComponentTypes<AStruct, BStruct>;
	//auto MyECSSettings = ECSSettings<ComponentTypes<int,float>,SystemTypes<double, char>>;

	//ECS<CompTypes<int, double, char>, SysTypes<int, float >> mECS;
	//std::cout << "ECS Created! Type: " << typeid(mECS.MySettings).name();

	struct CompA {
		int val = 4;
	};
	struct CompB {
		int val = 55;
	};

	struct CompC {
		int val = 44;
	};
	
	typedef ECS<CompA, CompB> ECSType;
	ECSType mEcs;

	//hana::at(mEcs.CompTable, 0_c).push_back(CompA());

	ECSType::Entity AEntity;
	AEntity.parentECS = &mEcs;
	AEntity.addComponent<CompA>(CompA());
	std::cout << typeid(mEcs).name();
	cout << endl << endl << "Entity tests..." << endl << endl;
	cout << "Creating entity with CompA and CompB types." << endl;


	//Entities
	
	//End Entities


	struct ASystem : System <CompA> {
	};

	struct BSystem : System <CompB> {
	};

	struct CSystem : System <CompC> {
	};

	struct ABSystem : System <CompA,CompB> {
	};

	struct ACSystem : System <CompA, CompC> {
	};

	struct BCSystem : System <CompB, CompC> {
	};

	struct ABCSystem : System <CompA,CompB, CompC> {
	};

	bool result = true;

	cout << "--------------------" << endl;
	cout << "Beginning System Tests..." << endl;
	cout << "--------------------" << endl;

	
	//result = ASystem.canProcessEntity(AEntity);
	//cout << "Trying System [A] with Entity [A]. Result: " << ((result) ? "Passed." : "Failed") << "." << endl;

	

	cout << "--------------------" << endl;
	cout << "Finished System Tests..." << endl;
	cout << "--------------------" << endl;


	cout << "Entity created and hopefully initialized..." << endl;

	/*cout << "CompA Index: [" << ABEntity.getComponentIndex<CompA>() << "]" << endl;
	cout << "CompB Index: [" << ABEntity.getComponentIndex<CompB>() << "]" << endl;

	cout << "Settings CompA to 1 and CompB to 69." << endl;

	ABEntity.setComponentIndex<CompA>(1);
	ABEntity.setComponentIndex<CompB>(69);*/

	//cout << "CompA Index: [" << ABEntity.getComponentIndex<CompA>() << "]" << endl;
	//cout << "CompB Index: [" << ABEntity.getComponentIndex<CompB>() << "]" << endl;
	cout << "Finished running tests!" << endl;
	system("pause");
    return 0;
}

