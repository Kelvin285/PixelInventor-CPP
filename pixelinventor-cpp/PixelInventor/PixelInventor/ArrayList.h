#pragma once
#include <vector>
#include <iostream>


namespace PixelInventor {
	
	


	template <typename T>
	class ArrayList {
	public:
		ArrayList<T>(bool locked) {
			list = std::vector<T>();
			this->locked = locked;
		}
		ArrayList<T>() {
			list = std::vector<T>();
		}
		~ArrayList<T>() {
			list.~vector<T>();
		}
		T get(unsigned int i) {
			if (i > size()) {
				std::cout << "index out of bounds " << i << std::endl;
				exit(EXIT_FAILURE);
			}
			return list[i];
		}
		bool contains(T t) {
			for (unsigned int i = 0; i < size(); i++) {
				if (get(i) == t) {
					return true;
				}
			}
			return false;
		}
		int indexof(T t) {
			if (size() == 0) return -1;
			for (unsigned int i = 0; i < size(); i++) {
				T a = list[i];
				if (a == t) {
					return i;
				}
			}
			return -1;
		}

		ArrayList<T> asList() {
			ArrayList<T> list = ArrayList<T>(true);
			for (unsigned int i = 0; i < size(); i++) {
				list.add(get(i));
			}
			list.setFinished();
			return list;
		}

		void setFinished() {
			finished = true;
		}

		unsigned int size() {
			return SIZE;
		}
		void remove(T t) {
			if (locked) return;
			list.erase(std::remove(list.begin(), list.end(), t), list.end());
			SIZE--;
		}
		void remove(unsigned int i) {
			if (locked) return;
			if (i > size()) {
				std::cout << "index out of bounds " << i << std::endl;
				exit(EXIT_FAILURE);
			}
			T t = list[i];
			list.erase(std::remove(i, i, t), list.end());
			SIZE--;
		}
		void add(T t) {
			if (locked && finished) return;
			list.insert(list.end(), t);
			SIZE++;
		}
		void add(unsigned int i, T t) {
			if (locked && finished) return;
			if (i > size()) {
				std::cout << "index out of bounds " << i << std::endl;
				exit(EXIT_FAILURE);
			}
			list.insert(i, t);
			SIZE++;
		}
		void addAll(T first) {
			add(first);
		}
		void set(unsigned int i, T t) {
			if (locked) return;
			if (i > size()) {
				std::cout << "index out of bounds " << i << std::endl;
				exit(EXIT_FAILURE);
			}
			list[i] = t;
		}
		void clear() {
			if (locked) return;
			list.clear();
			SIZE = 0;
		}

		template<typename First, typename...Rest>
		void addAll(First first, Rest... t) {
			add(first);
			addAll(t...);
		}
	private:
		std::vector<T> list;
		unsigned int SIZE = 0;
		bool locked = false;
		bool finished = false;
	};
	
}