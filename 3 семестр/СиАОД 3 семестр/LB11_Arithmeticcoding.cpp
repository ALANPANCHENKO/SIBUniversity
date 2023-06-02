#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cmath>



/*
арифм. кодирование - способ кодирования, который показывает наилучший результат даже в случае оч низкой жнтропии источника сообщения!
особенность ариф кодирования - таблица не строится!!
предлагается идея - исх сообщение преоброзовать и получить сообщение в закодированном виде с помощью других символов(закодированно оптимальным образом)
ИДЕЯ - есть слова, этих слов много. У нас есть отрезок от 0 до 1 на котором бесконечно много точек, если мы найдем способ сопоставить каждую точку со словом
к каждому слову сопоставляется какая-то точка, то это и будет способ кодирования данного слова. ТОчка - это и есть закодированное сообщение.
декодирование арифм кода - наоборот. находим точку и должны понять что за слово




tuple - коллекция элементов с фиксированным размером. Любая связанная пара, тройка, 
четверка и т. д элементов является кортежем. В качестве элементов кортежа могут выступать 
переменные произвольного типа




*/
using namespace std;

constexpr int BLOCK = 64;

static size_t search(std::vector<std::pair<char, long double>>& pair, const char& el) {
	for (size_t i = 0; i < pair.size(); i++) if (pair[i].first == el) return i;
	return std::string::npos;
}

std::tuple<std::string, int> itobs(int number) {
	std::string binaryNumber = "";
	int powerOfTwo = 0;

	if (number) {
		do {
			binaryNumber += std::to_string(number % 2);
			powerOfTwo++;
		} while (number /= 2);
		reverse(binaryNumber.begin(), binaryNumber.end()); // убывающий порядок
	}

	return std::make_tuple(binaryNumber, powerOfTwo); // фомируем кортж из двоичного числа и его разрядов
}

std::tuple<std::string, std::string> ftobs(long double number) {
	int intPart = (int)(number); // сумма верхней и правой границ деленая на 2
	std::string intPartS = std::get<0>(itobs(intPart)); // обращаемся к 0 элементу кортежа 
	long double floatPart = number - intPart;
	std::string floatPartS = "";
	for (int i = 0; i < 64; i++) {
		floatPart = floatPart * 2;
		if (floatPart >= 1) {
			floatPartS += '1';
			floatPart -= 1;
		}
		else {
			floatPartS += '0';
		}
	}

	return make_tuple(intPartS, floatPartS);
}

string Arithmetic(vector<pair<char, long double>> alphabet, const string& text) {
	vector<long double> r(text.size() + 1, 0); // вектор который хранит длину отрезка
	vector<pair<long double, long double>> border(text.size() + 1); // отрезок(за его границы мы будем цепляться)
	vector<long double> Q(alphabet.size() + 1, 0); // вектор для длин отрезков 

	r[0] = 1;
	border[0].second = 1;

	for (int i = 0; i < (int)alphabet.size(); i++) {
		Q[i + 1] = alphabet[i].second + Q[i]; // формируем массив вероятностей(который нужен нам для формирования отрезков)
	}

	int m = 0;
	int i = 0;
	for (int i = 1; i <= (int)text.size(); i++) {
		int m = search(alphabet, text[i - 1]) + 1; // порядковый номер кодируемой буквы в алфавите источника
		border[i].first = border[i - 1].first + r[i - 1] * Q[m - 1]; // вычисляем нижнюю границу отрезка
		border[i].second = border[i - 1].first + r[i - 1] * Q[m]; // вычисляем верхнюю границу отрезка
		r[i] = border[i].second - border[i].first; // находим длину этого отрезка(просто вычислям разницу)
	}

	int count = (int)ceil(-log2(r.back())); // последнее число в векторе запихиваем в логарифм, тем самым вычисляя кол-во разрядов

	return (get<1>(ftobs((border.back().second + border.back().first) / 2)).substr(0, (count > (int)text.size() ? text.size() : count))); // перевод в двоичную систему счисления 
}

int main()
{
	string getlineBuffer = "";
	string text = "";
	ifstream file;

	file.open("file.txt", ios::in);
	if (!file) return 1;
	while (getline(file, getlineBuffer)) text += getlineBuffer;
	file.close();
	getlineBuffer.clear();

	// Создаём вектор пар для букв алфавита и их вероятностей
	std::vector<std::pair<char, long double>> alphabet;

	// Заполняем уникальными буквами и частотой встречи её в тексте
	for (size_t i = 0; i < text.size(); i++) {
		size_t index = search(alphabet, text[i]);

		if (index != std::string::npos) alphabet[index].second += 1.0;
		else alphabet.push_back(std::make_pair(text[i], 1.0));
	}

	long double ver = 0;
	// Расчитываем вероятности
	for (size_t i = 0; i < alphabet.size(); i++) {
		alphabet[i].second /= (long double)text.size();
		cout << alphabet[i].first << " " << alphabet[i].second << endl;
		ver += alphabet[i].second;
	}
	cout << endl << "Sum of probability: " << ver << endl << endl;

	int size = (int)ceil(text.size() / (double)BLOCK);
	cout << size << " blocks:" << endl << endl;

	for (int i = 0; i < (int)text.size(); i += BLOCK) {
		cout << Arithmetic(alphabet, text.substr(i, BLOCK)); // цепляем алфавит и наше слово
	}
	return 0;
}
