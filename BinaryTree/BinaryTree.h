#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class BinaryTree
{
	const int NaN = 999;
	const int maxDigitNumb = 3;
	int deep;
	int size;
	int* elements;	//Массив элемментов (Прямой порядок обхода)
	int** printArr;	//Матрица элементов для вывода

	//Вставить значение в массив после перед указанным числом
	void insertBefore(int destNode, int newNode);
	//Вставить значение в массив после указанного числа
	void insertAfter(int destNode, int newNode);

	//Сортировка для входного массива
	int* bubleSort(int* arr, int size);
	//Рекурсивная инициализвация массива элементов
	int initElements(int* arr, int size, int deep = 1);
	//Рекурсивная инициализвация массива вывода
	void initPrint(int node, int deep = 1);

	//Составление строки вывода
	wstring getPrintStr();
	//Генерация строки из символов "─" указанного размера
	wstring getLines(int count);
	//Генерация строки из символов " " указанного размера
	wstring getSpaces(int count);
	//Вычисление ширины вывода
	int getPrintWidth(int deep);

	//Проверка на ниличие узла в дереве
	bool hasNode(int node);
	//Вычисление индекса узла дерева в массиве NaN при отсутсвии
	int getIndex(int node);
	//Вычиление левого сына указанного узла NaN при отсутсвии
	int getLeftChild(int node);
	//Вычиление правого брата указанного узла NaN при отсутсвии
	int getRightBrother(int node);
	//Вычиление родителя указанного узла NaN при отсутсвии
	int getParent(int node);

	//Удаление массива вывода
	void delPrint();
	//Выделение пямяти и инициализация массива вывода NaN
	void createPrint();
public:

	BinaryTree(int*, int);
	void print();
	~BinaryTree();
	int getSize();
	int getHead();
	//Вставить значение в дерево
	void insertNode(int destNode, int newNode, int deep = 1);
	//Заполение указанного массива элементами дерева в порядке обратного обхода
	int* getPostOrderArray(int* arr, int node);
	//Заполение указанного массива элементами дерева в порядке прямого обхода
	int* getPreOrderArray(int* arr, int node);
	//Заполение указанного массива элементами дерева в порядке симметричного обхода
	int* getInOrderArray(int* arr, int node);
	//Балансировка дерева
	void balanceTree();
};

#endif // !BINARY_TREE_H