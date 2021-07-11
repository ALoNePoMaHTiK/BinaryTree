#include "BinaryTree.h"

void BinaryTree::insertBefore(int destNode, int newNode)
{
    if (!hasNode(destNode) || destNode == elements[0])
        throw;
    int* newArr = new int[size + 1];
    bool diff = false;
    for (int i = 0; i < size; i++) {
        newArr[i + diff] = elements[i];
        if (elements[i] == destNode && diff == false) {
            newArr[i] = newNode;
            diff = true;
            i--;
        }
    }
    delete[] elements;
    elements = newArr;
    size++;
}
void BinaryTree::insertAfter(int destNode, int newNode)
{
    if (!hasNode(destNode))
        throw;
    int* newArr = new int[size + 1];
    bool diff = false;
    for (int i = 0; i < size; i++) {
        newArr[i + diff] = elements[i];
        if (elements[i] == destNode && diff == false) {
            newArr[i + 1] = newNode;
            diff = true;
        }
    }
    delete[] elements;
    elements = newArr;
    size++;
}
void BinaryTree::insertNode(int destNode, int newNode, int deep)
{
    static int newDeep = 0;
    if (!hasNode(newNode)) {
        if (hasNode(destNode)) {
            int left = getLeftChild(destNode);
            if (newNode < destNode) {
                if (left != NaN)
                    insertNode(left, newNode, deep + 1);
                else {
                    insertAfter(destNode, newNode);
                    if (deep >= this->deep)
                        newDeep = deep + 1;
                }
            }
            else {
                int right = NaN;
                if (left != NaN)
                    right = getRightBrother(left);
                if (right != NaN)
                    insertNode(right, newNode, deep + 1);
                else {
                    int index = getIndex(destNode);
                    if (getParent(elements[index + 1]) == destNode) //Если текущий destNode является родителем для следующего
                        insertNode(elements[index + 1], newNode, deep + 1);
                    else {
                        insertAfter(destNode, newNode);
                        if (deep >= this->deep)
                            newDeep = deep + 1;
                    }
                }
            }
        }
        else {
            throw;
        }
    }
    if (deep == 1) {
        delPrint();
        if (newDeep != 0)
            this->deep = newDeep;
        newDeep = 0;
        createPrint();
        initPrint(elements[0]);
    }
}

int* BinaryTree::bubleSort(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int b = arr[j]; // создали дополнительную переменную
                arr[j] = arr[j + 1]; // меняем местами
                arr[j + 1] = b; // значения элементов
            }
        }
    }
    return arr;
}
int BinaryTree::initElements(int* arr, int size, int deep)
{
    static int last = -1;
    if (size != 0) {
        last++;
        if (size == 1) {
            elements[last] = arr[0];
        }
        else {
            elements[last] = arr[size / 2 - (1 - size % 2)];
            int leftDeep = initElements(arr, size / 2 - (1 - size % 2), deep + 1);
            int rightDeep = initElements(&arr[size / 2 + size % 2], size / 2, deep + 1);
            if (leftDeep > rightDeep)
                deep = leftDeep;
            else
                deep = rightDeep;
        }
    }
    if (size == this->size)
        last = -1;
    return deep;
}
void BinaryTree::initPrint(int node, int deep) {
    static int counter = 1;
    static int* index = nullptr;
    if (index == nullptr) {
        index = new int[this->deep];
        for (int i = 0; i < this->deep; i++)
            index[i] = 0;
    }
    printArr[deep - 1][index[deep - 1]] = node;
    index[deep - 1] += 1;
    if (node != NaN) {
        counter++;
        int left = getLeftChild(node);
        int right = NaN;
        if (getParent(elements[counter - 1]) == node)
            right = elements[counter - 1];
        if (left != NaN)
            right = getRightBrother(left);
        if (deep != this->deep) {
            initPrint(left, deep + 1);
            initPrint(right, deep + 1);
        }
    }
    else {
        for (int i = 0; i < this->deep - deep; i++)
            index[deep + i] += (int)pow(2, i + 1);
    }
    if (deep == 1) {
        counter = 1;
        delete[] index;
        index = nullptr;
    }
}

wstring BinaryTree::getPrintStr()
{
    wstringstream str;  //Поток Unicode-символов
    const wchar_t left = L'┌';  //Уголовой левый символ псевдографики
    const wchar_t right = L'┐'; //Уголовой правый символ псевдографики
    for (int i = 0; i < deep; i++) {
        int width = getPrintWidth(deep - i - 1);    //Ширина вывода
        wstring sideSpaces = getSpaces((width - 1) / 2);    //Пробелы по краям
        int linesCount = (deep - i) == 2 ? (width - 1) / 2 : (width - 1) / 2 - 1;   //Количество линий псевдографики
        wstring lines = getLines(linesCount);
        str << sideSpaces;
        for (int j = 0; j < (int)pow(2, i); j++) {
            if (i < deep - 1 && printArr[i + 1][j * 2] != NaN)  //Если это не крайний элемент и у него есть левый сын
                str << left << lines;
            else
                str << getSpaces(linesCount + 1);
            if (printArr[i][j] != NaN)   //Если это существующий элемент
                str << setw(3) << to_wstring(printArr[i][j]);
            else
                str << getSpaces(3);
            if (i < deep - 1 && printArr[i + 1][j * 2 + 1] != NaN) //Если это не крайний элемент и у него есть правый сын
                str << lines << right;
            else
                str << getSpaces(linesCount + 1);
            //Вывод пробелов между элементами в строке
            if (j != (int)pow(2, i) - 1) {
                if (i != deep - 1)
                    str << getSpaces(width);
                else
                    str << getSpaces(j % 2 == 0 ? 3 : 1);
            }

        }
        str << sideSpaces;
        str << endl;
    }
    wstring result = str.str();
    str.clear();
    return result;
}
wstring BinaryTree::getLines(int count)
{
    wstring result;
    for (int i = 0; i < count; i++)
        result.push_back(L'─');
    return result;
}
wstring BinaryTree::getSpaces(int count)
{
    wstring result;
    for (int i = 0; i < count; i++)
        result.push_back(' ');
    return result;
}
int BinaryTree::getPrintWidth(int deep)
{
    if (deep < 1)
        return 1;
    else {
        if (deep == 1)
            return 3;
        return (int)pow(2, deep - 2) * (3 * maxDigitNumb + 1) - 1;
    }
}

bool BinaryTree::hasNode(int node)
{
    for (int i = 0; i < size; i++)
        if (elements[i] == node)
            return true;
    return false;
}
int BinaryTree::getIndex(int node)
{
    for (int i = 0; i < size; i++) {
        if (elements[i] == node)
            return i;
    }
    return -1;
}
int BinaryTree::getLeftChild(int node)
{
    for (int i = 0; i < size - 1; i++) {
        if (elements[i] == node && elements[i + 1] < elements[i])
            return elements[i + 1];
    }
    return NaN;
}
int BinaryTree::getRightBrother(int node)
{
    for (int i = 1; i < size - 1; i++) {
        if (elements[i] == node) {
            if (elements[i - 1] < elements[i])    //Если это не левый сын
                return NaN;
            for (int j = i + 1; j < size; j++)
                if (elements[j] > elements[i - 1] && elements[i - 1] == getParent(elements[j]))
                    return elements[j];
        }
    }
    return NaN;
}
int BinaryTree::getParent(int node)
{
    if (node == elements[0] || !hasNode(node))
        return NaN;
    for (int i = 1; i < size; i++) {    //Если это левый сын
        if (elements[i] == node) {
            if (elements[i - 1] > node)
                return elements[i - 1];
            else
                break;
        }
    }
    for (int i = size - 1; i >= 0; i--) {
        if (elements[i] == node) {
            int* max = new int[i];
            for (int j = i - 1; j >= 0; j--)
                max[i - j - 1] = elements[j];
            bubleSort(max, i);
            for (int j = i - 1; j >= 0; j--)
                if (max[j] < node) {
                    int result = max[j];
                    delete[] max;
                    return result;
                }
        }
    }
    return NaN;
}
int BinaryTree::getSize()
{
    return size;
}
int BinaryTree::getHead()
{
    return elements[0];
}

int* BinaryTree::getPostOrderArray(int* arr, int node)
{
    static int counter = 0;
    int left = getLeftChild(node);
    int right = NaN;
    int index = getIndex(node);
    if (getParent(elements[index + 1]) == node)
        right = elements[index + 1];
    if (left != NaN) {
        getPostOrderArray(arr, left);
        right = getRightBrother(left);
    }
    if (right != NaN)
        getPostOrderArray(arr, right);
    arr[counter] = node;
    counter++;
    if (node == elements[0])
        counter = 0;
    return arr;
}
int* BinaryTree::getPreOrderArray(int* arr, int node)
{
    for (int i = 0; i < size; i++)
        arr[i] = elements[i];
    return arr;
}
int* BinaryTree::getInOrderArray(int* arr, int node)
{
    static int counter = 0;
    int left = getLeftChild(node);
    int right = NaN;
    int index = getIndex(node);
    if (getParent(elements[index + 1]) == node)
        right = elements[index + 1];
    if (left != NaN) {
        getInOrderArray(arr, left);
        right = getRightBrother(left);
    }
    arr[counter] = node;
    counter++;
    if (right != NaN)
        getInOrderArray(arr, right);
    if (node == elements[0])
        counter = 0;
    return arr;
}

void BinaryTree::delPrint()
{
    for (int i = 0; i < deep; i++) {
        delete[] printArr[i];
    }
    delete[] printArr;
}
void BinaryTree::createPrint()
{
    printArr = new int* [this->deep];
    for (int i = 0; i < this->deep; i++) {
        printArr[i] = new int[(int)pow(2, i)];
        for (int j = 0; j < (int)pow(2, i); j++)
            printArr[i][j] = NaN;
    }

}

void BinaryTree::balanceTree() {
    int* arr = elements;
    arr = bubleSort(arr, size);
    elements = new int[size];
    deep = initElements(arr, size, 1);
    delPrint();
    createPrint();
    initPrint(elements[0]);
}

void BinaryTree::print()
{
    wcout << endl << getPrintStr() << endl;
}

BinaryTree::BinaryTree(int* arr, int size)
{
    elements = new int[size];
    arr = bubleSort(arr, size);
    this->size = size;
    deep = initElements(arr, size, 1);
    createPrint();
    initPrint(elements[0]);
}
BinaryTree::~BinaryTree()
{
    size = 0;
    deep = 0;
    delete[]elements;
    delPrint();
}