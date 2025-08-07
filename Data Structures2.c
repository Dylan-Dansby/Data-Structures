//Written By Dylan Dansby, Aug6th 2025
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Heap{
    int* data;
    int size;
    int capacity;
    //This is a minheap implementation
} Heap;

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
} Node;


//BST Node Initialization
Node* createNode(int val){
    struct Node* newNode = malloc(sizeof(Node));
    newNode ->left = NULL;
    newNode -> right = NULL;
    newNode->key = val;
    return newNode;
}

//Find Min value in BST
struct Node* findMin(struct Node* root){
    if(root==NULL){
        return NULL;
    } else if(root->left == NULL){
        return root;
    } else return findMin(root->left);
}

//Find Max value in BST
struct Node* findMax(struct Node* root){
    if(root == NULL){
        return NULL;
    } else if(root->right==NULL){
        return root;
    } else return findMax(root->right);
}

//BST Search
struct Node* search(struct Node* root , int key){
    printf("Seacrhing...\n");
    if(root==NULL){
        printf("Could Not Find Value.\n");
        return NULL;
    } else if (key<root->key){
        return search(root->left,key);
    } else if (key>root->key){
        return search(root->right,key);
    }
}


//BST Insert
struct Node* BSTinsert(struct Node* root,int key){
    if(root == NULL){
        return createNode(key);
    }
    if(key<root->key){
        root->left = BSTinsert(root->left,key);
    } else if (key>root->key){
        root->right = BSTinsert(root->right,key);
    }
    return root;
}

//BST Delete
struct Node* BSTdelete(struct Node* root,int key){
    struct Node* tmp;
    if(root == NULL){ //Tree Empty
        return NULL;
    } else if(key<root->key){ //Go left to find delNode
        root->left = BSTdelete(root->left,key);
    } else if(key>root->key){ //Go right to find delNode
        root->right = BSTdelete(root->right,key); 
    } else if(root->left && root->right){ //key = root->key
        tmp = findMin(root->right);
        root->key = tmp->key;
        root->right = BSTdelete(root->right,root->key);
    } else {
        tmp = root;
        if(root->left == NULL){
            root = root->right;
        } else if(root->right == NULL){
            root = root->left;
        }
        free(tmp);
    }
    return root;
}

//BST Traversal/Print Function
void BSTtraverse(struct Node* root){
    if(root == NULL){
        //printf("BST is empty.\n");
        return;
    }
    BSTtraverse(root->left);
    printf("%d->",root->key);
    BSTtraverse(root->right);
}

//Heap Initialization
Heap* createHeap(int capacity){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->data = (int*)malloc(sizeof(int) * capacity);
    h->capacity = capacity;
    h->size = 0;
    return h;
}

//swapper function for bubble up
void swap(int* a,int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//Heap Helper Functions
int parent(int i){
    return (i - 1) / 2;
}
int leftChild(int i) {
    return 2 * i + 1;
    
}
int rightChild(int i){
    return 2 * i + 2; 
    
}

bool isFull(Heap* h) {
    return h->size == h->capacity;
}
bool isEmpty(Heap* h){
    return h->size == 0; 
    
}


//Bubble Up used for insert function
void bubbleUp(Heap* h,int index){
    while(index != 0 && h->data[parent(index)] > h->data[index]){
        swap(&h->data[parent(index)], &h->data[index]);
        index = parent(index);
    }
}

//Bubble Down used for insert function
void bubbleDown(Heap* h,int index){
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if(left < h->size && (h->data[left] < h->data[smallest])){
        smallest = left;
    }
    
    if(right < h->size && h->data[right] < h->data[smallest]){
        smallest = right;
    }
    
    if(smallest != index){ //if index isn`t the smallest, it can keep going down
        swap(&h->data[index],&h->data[smallest]);
        bubbleDown(h,smallest);
    }
}

//Heap Insert
void heapInsert(Heap* h,int val){
    if(isFull(h)){
        printf("Heap is full.\n");
        return;
    }
    h->data[h->size] = val; //latest arr index = value
    bubbleUp(h,h->size); //bubble up new index
    printf("%d ",h->data[h->size]);
    h->size++;
}

//Extract Minimum Value from the Heap
int deleteMin(Heap* h){
    if(isEmpty(h)){
        printf("Heap is empty.\n");
        return -1;
    }
    
    int root = h->data[0]; //save min value
    h->data[0]=h->data[h->size-1];
    h->size--;
    bubbleDown(h,0); //bubble down the deleted index value
    return root; //return saved value
}

//Peek Min value on the Heap
int peekMin(Heap* h){
    if(isEmpty){
        printf("Heap is empty.\n");
        return -1;
    }
    return h->data[0];
}

void printHeap(Heap* h, int index, char* prefix, bool isLeft) {
    if (index >= h->size)
        return;

    // Print current node with prefix
    printf("%s", prefix);
    printf(isLeft ? "├── " : "└── ");
    printf("%d\n", h->data[index]);

    // Build new prefix for children
    char newPrefix[100];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "│   " : "    ");

    // Recurse left and right
    int left = leftChild(index);
    int right = rightChild(index);
    bool hasLeft = left < h->size;
    bool hasRight = right < h->size;

    if (hasLeft)
        printHeapVertical(h, left, newPrefix, true);
    if (hasRight)
        printHeapVertical(h, right, newPrefix, false);
}



int main()
{
    //HEAPS
    int arr[10] = {4,8,90,12,62,78,3,1,79,0};
    Heap* myHeap = createHeap(100); //create a heap with capacity 100 indexes
    printf("List: \n");
    for(int i=0;i<10;i++){
        printf("%d,",arr[i]);
    }
    
    for(int i=0;i<10;i++){
        heapInsert(myHeap,arr[i]);
    }
    printf("\nHeap:\n");
    printHeap(myHeap, 0, "", false);
    
    printf("\nHeap Min Deletion: \n");
    for(int i=0;i<10;i++){
        printf("%d ",deleteMin(myHeap));
    }
    
    free(myHeap->data);
    free(myHeap);
    //END OF HEAPS
    
    //BINARY SEARCH TREES
    Node* Broot = BSTinsert(NULL,arr[0]);
    for(int i=1;i<10;i++){
        BSTinsert(Broot,arr[i]);
    }
    printf("BST Tree:\n");
    BSTtraverse(Broot);
    //Implement BST deletion
    

    /*
    IMPLEMENT HASH TABLE
    */
    
    return 0;
}