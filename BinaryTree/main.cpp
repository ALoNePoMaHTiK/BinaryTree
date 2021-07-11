#include <time.h>
#include "BinaryTree.h"
using namespace std;

void randGen(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		int temp = rand() % 998 + 1;
		bool duplicate = false;
		for (int j = i; j >= 0; --j)
			if (temp == arr[j]) {
				duplicate = true;
				i--;
				break;
			}
		if (duplicate)
			continue;
		else
			arr[i] = temp;
	}
}
int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	srand(time(NULL));
	int sizeA;
	int sizeB;
	cout << "Enter count of elements A: ";
	cin >> sizeA;
	cout << "Enter count of elements B: ";
	cin >> sizeB;
	int* A = new int[sizeA];
	int* B = new int[sizeB];
	randGen(A, sizeA);
	randGen(B, sizeB);
	BinaryTree treeA(A, sizeA);
	delete[] A;
	BinaryTree treeB(B, sizeB);
	delete[] B;
	cout << "Tree A:\n";
	treeA.print();
	cout << "\nTree A pre-order:";
	int* treeATravers = new int[sizeA];
	treeA.getPreOrderArray(treeATravers, treeA.getHead());
	for (int i = 0; i < sizeA; i++)
		cout << setw(4) << treeATravers[i];
	cout << endl << endl;
	cout << "Tree B:\n";
	treeB.print();
	cout << "\nTree B in-order:";
	int* treeBTravers = new int[sizeB];
	treeB.getInOrderArray(treeBTravers, treeB.getHead());
	for (int i = 0; i < sizeB; i++)
		cout << setw(4) << treeBTravers[i];
	for (int i = 0; i < sizeB; i++) {
		treeA.insertNode(treeA.getHead(), treeBTravers[i]);
		treeA.print();
	}
	cout << "\nBalanced Tree:\n";
	treeA.balanceTree();
	treeA.print();
	return 0;
}
