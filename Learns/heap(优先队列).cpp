#include<iostream>

struct Heap;
typedef Heap* heapTree;
#define PRINT(X) std::cout<<X<<std::ends
struct Heap {
	int cap;
	int size;
	int* Elements;
};

heapTree InitHeapTree(int MaxSize);
void Insert(heapTree T,int val);
void Destory(heapTree T);
void MakeEmpty(heapTree T);
int DeleteMin(heapTree T);
int FindMin(heapTree T);
int isEmpty(heapTree T);
int isFull(heapTree T);
void print(heapTree T);

heapTree InitHeapTree(int MaxSize)
{
	heapTree T;
	if (MaxSize < 1) return NULL;
	T = (heapTree)malloc(sizeof(struct Heap));
	if (T == NULL) std::cerr << "Out of space!" << std::endl;
	T->Elements = (int*)malloc((MaxSize + 1) * sizeof(int));
	if (T->Elements == NULL)std::cerr << "Out of space!" << std::endl;
	T->cap = MaxSize;
	T->size = 0;
	T->Elements[0] = 0;
	return T;
}
//ÉÏÂË²åÈëÔªËØ
void Insert(heapTree T, int val)
{
	int i;

	if (isFull(T))
	{
		std::cerr << "Heap is full!" << std::endl;
		return;
	}
	
	for (i = ++T->size; T->Elements[i / 2] > val; i /= 2) T->Elements[i] = T->Elements[i / 2];
	T->Elements[i] = val;
}

int DeleteMin(heapTree T)
{
	if (isEmpty(T))
	{
		std::cerr << "Heap is empty!" << std::endl;
		return -1;
	}
	int min = T->Elements[1];
	int i,lastElement=T->Elements[T->size--];
	for (i = 1;i*2<=T->size;)
	{
		if (i * 2 != T->size&&T->Elements[2 * i] > T->Elements[2 * i + 1])
		{
			i = i * 2 + 1;
		}
		else
		{
			i *= 2;
		}
		if (T->Elements[i] > lastElement)break;
		else T->Elements[i / 2] = T->Elements[i];
	}
	T->Elements[i] = lastElement;
	return min;
}

int FindMin(heapTree T)
{
	return T->Elements[1];
}

int isEmpty(heapTree T)
{
	return (bool)!T->size;
}

int isFull(heapTree T)
{
	return T->size >= T->cap ? true : false;
}

void print(heapTree T)
{
	if (T == NULL)return;
	for (int i = 1; i <= T->size; ++i)
	{
		PRINT(T->Elements[i]);
	}
	std::cout << std::endl;
}

int main()
{
	heapTree heap = InitHeapTree(114514);
	Insert(heap, 1);
	Insert(heap, 3);
	Insert(heap, 2);
	Insert(heap, 66);
	Insert(heap, 33);
	Insert(heap, 9);
	Insert(heap, 114);
	Insert(heap, 1919);
	Insert(heap, 514);
	Insert(heap, 50);
	Insert(heap, 5);
	Insert(heap, 810);
	print(heap);
	DeleteMin(heap);
	print(heap);
	DeleteMin(heap);
	print(heap);
	DeleteMin(heap);
	print(heap);
	DeleteMin(heap);
	print(heap);
	DeleteMin(heap);
	print(heap);
	DeleteMin(heap);
	print(heap);
	system("pause");
	return 0;
}
