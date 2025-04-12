#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <stdexcept>



template <typename T>
class DynamicArray {

private:
	T* data;
	size_t capacity;
	size_t size;


public:
	DynamicArray(size_t initial_capacity)
		: capacity(initial_capacity), size(0) {
		data = new T[capacity];
	}

	~DynamicArray() {
		delete[] data;
	}

	void display() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

	void resize() {
		capacity *= 2;
		T* new_data = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			new_data[i] = data[i];        // kopiuje stare elementy do nowej tablicy o rozmiarze *2
		}
		delete[] data;
		data = new_data;
	}

	void addFront(T element) {
		if (size == capacity) {
			resize();
		}
		for (size_t i = size; i > 0; --i) {
			data[i] = data[i - 1];			// przesuwa elementy i wstawia nowy na pocz¹tek
		}
		data[0] = element;
		++size;
	}

	void addBack(T element) {
		if (size == capacity) {
			resize();
		}
		data[size] = element;		// dodaje element na koñcu kiedy jest miejsce
		++size;
	}

	void addChosen(T element, size_t index) {
		if (index > size) {
			throw std::out_of_range("Index outside of capacity");
		}
		if (size == capacity) {
			resize();
		}
		for (size_t i = size; i > index; --i) {
			data[i] = data[i - 1];		// przesuwa elementy w prawo od indeksu i wstawia element w indeksie 
		}
		data[index] = element;
		++size;
	}

	void removeFront() {
		if (size == 0) {
			throw std::out_of_range("Array is empty");
		}
		for (size_t i = 0; i < size - 1; ++i) {
			data[i] = data[i + 1];		// przesuwa elementy w lewo i zmniejsza rozmiar
		}
		--size;
	}

	void removeBack() {
		if (size == 0) {
			throw std::out_of_range("Array is empty");
		}
		--size;						// zmniejsza rozmiar
	}

	void removeChosen(size_t index) {
		if (index >= size) {
			throw std::out_of_range("Index outside of capacity");
		}
		for (size_t i = index; i < size - 1; ++i) {
			data[i] = data[i + 1];		// przesuwa elementy w lewo od indeksu i zmniejsza rozmiar
		}
		--size;
	}

	size_t findIndex(T element) const {
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == element) {
				return i;				// zwraca indeks elementu
			}
		}
		throw std::out_of_range("Element not found");
	}


};

#endif // ARRAY_HPP