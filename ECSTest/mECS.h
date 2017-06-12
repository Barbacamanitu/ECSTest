#pragma once
#include <boost\hana.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "boost\hana\ext\std\integral_constant.hpp"
#include <xutility>

namespace mECS {
	namespace hana = boost::hana;
	using namespace hana::literals;

	//Template parameters are the list of components that this system works with.
	template<typename...T>
	struct System {

		//Runtime process function
		void process() {
		}

		
		bool canProcessEntity() {
			return true;
		}

	private:
		hana::tuple<hana::type<T>...> ComponentTypes;
	};

	template<typename CompType>
	using CompPair = hana::pair<hana::type<CompType>, std::vector<CompType> >;
	
	template<typename ...ComponentTypes>
	struct ECS {
		//Table of components. 
		hana::map<CompPair<ComponentTypes>...> CompMap;

		template<typename T>
		std::vector<T>& getComponentsOfType() {
			auto theEntry = hana::find(CompMap, hana::type<T>());
			if (!hana::is_nothing(theEntry)) {
				//Found the type in the map.
				return theEntry.value();
			}
		}

		template<typename T>
		size_t addComponent(T& comp) {
			auto theVec = getComponentsOfType<T>();
			size_t a = std::distance(theVec.begin(), theVec.end());
			theVec.push_back(comp);
			a = std::distance(theVec.begin(), theVec.end());
			theVec.push_back(comp);
			a = std::distance(theVec.begin(), theVec.end());
			theVec.push_back(comp);
			a = std::distance(theVec.begin(), theVec.end());
			theVec.push_back(comp);
			
			return theVec.size() - 1;
		}
		
			



		struct Entity {

			//Convenience function that adds a component to the ECS but also saves the reference to the ComponentReference map.
			template<typename T>
			void addComponent(T comp) {
				int pos = parentECS->addComponent<T>(comp);
				setComponentReference<T>(pos);
			}

			template<typename T>
			void setComponentReference(int position) {
				auto theEntry = hana::find(ComponentReferences, hana::type<T>());
				if (!hana::is_nothing(theEntry)) {
					//Found the type in the map.
					theEntry = position;
				}
			}

			ECS<ComponentTypes...>* parentECS;

			hana::map<hana::pair<hana::type<ComponentTypes>,int>...> ComponentReferences;
		};
	};


	
}