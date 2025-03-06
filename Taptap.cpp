#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

#define MAX_SIZE 1000000
using namespace std;

unsigned int M[MAX_SIZE];

void ArrayZeros(unsigned int n) {
	for (unsigned int i = 0; i < n; i++) {
		M[i] = 0;
	}
}
void PrintArray(unsigned int n) {
	for (unsigned int i = 0; i < n; i++) {
		cout << M[i]<<' ';
	}
	cout << endl;

}
int rand_uns(unsigned int min, unsigned int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}
void ArrayRand(unsigned int n, unsigned int min, unsigned int max) {
	for (unsigned int i = 0; i < n; i++) {
		M[i] = rand_uns(min, max);
	}
}
void SortBubble(unsigned int n) {
	for(unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n - 1; j++) {
			unsigned int tmp;
			if (M[j] > M[j + 1]) {
				tmp = M[j + 1];
				M[j + 1] = M[j];
				M[j] = tmp;
			}
		}	
}
void SortInsert(unsigned int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && M[j - 1] > M[j]; j--) 
			swap(M[j - 1], M[j]);

}

double last = 0;
double GetTime() {
	double T = std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::steady_clock::now().time_since_epoch()).count() / 1e6;
	double res = T - last;
	last = T;
	return res;
}

void SortBubble2(unsigned int n) {
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n - 1; j++) {
			unsigned int tmp;
			if (M[j] > M[j + 1]) {
				tmp = M[j + 1];
				M[j + 1] = M[j];
				M[j] = tmp;
			}
		}
}
using namespace std;

bool CheckArray(unsigned int n) {
	for (unsigned int i = 0; i < n - 1; i++) {
		if (M[i] > M[i + 1]) {
			cout << "NOT OK" << endl;
			return false;
		}
	}
	cout << "OK"; 
	return true;
}
void SortShaker(unsigned int n) {
	int left, right, i;
	left = 0;
	right = n - 1;
	while (left <= right) {
		for (i = right; i >= left; i--) {
			if (M[i - 1] > M[i]) {
				swap(M[i - 1], M[i]);
			}
		}
		left++;
		for (i = left; i <= right; i++) {
			if (M[i - 1] > M[i]) {
				swap(M[i - 1], M[i]);
			}
		}
		right--;
	}
}

//
void heapify(unsigned int n, int i = 15) {
	int largest = i; // Инициализируем корень как самый большой
	int left = 2 * i + 1; // Левый узел
	int right = 2 * i + 2; // Правый узел

	// Если левый дочерний элемент больше корня
	if (left < n && M[left] > M[largest])
		largest = left;

	// Если правый дочерний элемент больше самого большого элемента
	if (right < n && M[right] > M[largest])
		largest = right;

	// Если самый большой элемент не корень
	if (largest != i) {
		std::swap(M[i], M[largest]); // Меняем местами

		// Рекурсивно преобразуем поддерево в кучу
		heapify(n, largest);
	}
}

void SortHeap(unsigned int n) {
	// Построение кучи (перегруппировка массива)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i > 0; i--) {
		std::swap(M[0], M[i]); // Меняем местами
		heapify(i, 0);
	}
}
void SortСomb(unsigned int n) {
	// Начальный шаг
	unsigned int gap = n;
	bool swapped = true;

	while (gap != 1 || swapped) {
		// Уменьшаем шаг
		gap = (gap * 10) / 13; // Пример уменьшения шага, можно использовать 1.3

		if (gap < 1) {
			gap = 1;
		}

		swapped = false;

		// Сравниваем элементы с текущим шагом
		for (unsigned int i = 0; i < n - gap; i++) {
			if (M[i] > M[i + gap]) {
				// Меняем местами
				std::swap(M[i], M[i + gap]);
				swapped = true;
			}
		}
	}
}
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(int low, int high) {
	int pivot = M[high]; // выбираем последний элемент как опорный
	int i = low - 1; // индекс меньшего элемента

	for (int j = low; j < high; j++) {
		if (M[j] < pivot) {
			i++;
			swap(M[i], M[j]);
		}
	}
	swap(M[i + 1], M[high]); // помещаем опорный элемент на правильную позицию
	return i + 1;
}

void quickSort(int low, int high) {
	if (low < high) {
		int pi = partition(low, high); // индекс опорного элемента

		quickSort(low, pi - 1); // сортируем элементы до опорного
		quickSort(pi + 1, high); // сортируем элементы после опорного
	}
}


int main()
{
	unsigned int n;
	cin >> n;
	ofstream file("Bubble.txt", ios::out);
	double sumary = 0;
	for (int i = 0; i < 10; i++) {
	
		ArrayZeros(MAX_SIZE);
		ArrayRand(n, 5, 15);
		GetTime();   // Первый запуск

		SortBubble(n);

		double t = GetTime(); // Второй запуск
		PrintArray(20);
		//SortBubble2(n);
		cout << "n = " << n << " T = " << t << endl;
		sumary += t;
		CheckArray(n);

		cout << '\n';
		file << t << endl; // работаете как с привычным cout	
	}
	cout << sumary / 10;
	file.close();
	return 0;
}
//int main() {
//	int a; 
//	cin >> a;
//	auto start = std::chrono::high_resolution_clock::now(); //auto - подставиться любой тип данных
//	cin >> a;
//	
//	auto end = std::chrono::high_resolution_clock::now();
//	auto nsec = end - start;
//	std::cout << nsec.count() << " нсек." << std::endl;
//	return 0;
//}

