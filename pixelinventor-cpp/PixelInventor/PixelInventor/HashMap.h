#pragma once
#include <unordered_map>
#include <iostream>

namespace PixelInventor {
	template <typename A, typename B>
	class HashMap {
	public:
		HashMap() {
			
		}
		~HashMap() {
			keys.~ArrayList();
		}

		void put(A a, B b) {
			std::pair<A, B> p(a, b);
			map.insert(p);
			keys.add(a);
		}

		A getKeyAt(unsigned int i) {
			return keys.get(i);
		}

		B get(A a) {
			return map.at(a);
		}

		ArrayList<A> getKeySet() {
			return keys.asList();
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
			return sizeof(map.count);
		}

	private:
		ArrayList<A> keys;
		std::unordered_map<A, B> map;
	};
}