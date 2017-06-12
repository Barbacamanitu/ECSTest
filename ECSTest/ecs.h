#pragma once
#include <string>
#include <vector>
#include <assert.h>
#include <cassert>
#include <iostream>
#include <tuple>
#include <array>
#include <boost\hana.hpp>
#include <map>

namespace hana = boost::hana;
using namespace hana::literals;

struct Component {
	int theNumber = 100;
};

struct CompA : Component {
	int theNumber = 69;
};
struct CompB : Component {
	int theNumber = 70;
};
struct CompC : Component {
	int theNumber = 71;
};


struct Entity {
	/*
		Component table is a one to many table representing 
		the components making up this entity.

		The key represents the type of the component and the key
		is the index inside that component array.
	*/
	typedef std::map<int,std::vector<int>> ComponentTable;

	ComponentTable mTable;
};

template<typename ...ComponentTypes>
struct ECS {
	//Public interface
	template<typename T>
	std::vector<T>& getComponents() {
		return std::get<std::vector<T>>(mComponentStorage);
	}

	template<typename T>
	auto componentsBegin() {
		return std::get<std::vector<T>>(mComponentStorage).begin();
	}

	template<typename T>
	auto componentsEnd() {
		return std::get<std::vector<T>>(mComponentStorage).begin();
	}

	template<typename T>
	void addComponent(T& component) {
		std::get<std::vector<T>>(mComponentStorage).push_back(component);
	}

	template<typename T>
	void addComponent(T component) {
		std::get<std::vector<T>>(mComponentStorage).push_back(component);
	}



	template<typename ...DependentComponents>
	struct System {

		template<typename T>
		void setECS(T* ecs) {
			mEcs = ecs;
		}

		/*
		processComponents automatically iterates over this system's dependent
		component types and calls "process" on each one.
		*/
		void process() {

			hana::for_each(mDependentComponents, [this](auto compType) {
				using cType = decltype(compType);
				auto beg = mEcs->componentsBegin<cType>();
				auto end = mEcs->componentsEnd<cType>();
				
				procComps(mEcs->getComponents<cType>());
				
			});
		}

		template<typename T>
		void procComps(std::vector<T>& comps) {
			std::cout << "Default Component Handler. Count: " << comps.size() << std::endl;
		}


	protected:
		hana::tuple<DependentComponents...> mDependentComponents;
		ECS* mEcs;
	};

private:
	std::tuple<std::vector<ComponentTypes>...> mComponentStorage;
	std::vector<Entity> mAllEntities;
	std::vector<int> mActiveEntities;

};





