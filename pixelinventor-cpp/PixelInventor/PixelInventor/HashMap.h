#pragma once
#include <map>
#include <unordered_map>
#include <iostream>
#include "ArrayList.h"


namespace PixelInventor {
	template <typename A, typename B>
	class HashMap {

	private:
		std::unordered_map<A, B> map;
		ArrayList<A> keys;
	
	public:
		HashMap() {
			
		}
		~HashMap() {
			keys.~ArrayList();
		}

		void put(A a, B b) {
			map.insert(std::make_pair(a, b));
			keys.add(a);
		}

		A getKeyAt(unsigned int i) {
			return keys.get(i);
		}

		B get(A a) {
			if (map.find(a) != map.end()) {
				return map[a];
			}
			return nullptr;
		}

		ArrayList<A> getKeySet() {
			return keys.asList();
		}

		bool containsKey(A a) {
			return keys.contains(a);
		}

		void clear() {
			keys.clear();
			map.clear();
		}

		void remove(A a) {
			map.erase(a);
			keys.remove(a);
		}

		unsigned int size() {
			return keys.size();
		}

	
	};
}