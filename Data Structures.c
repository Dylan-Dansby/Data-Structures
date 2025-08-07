//Written by Dylan Dansby, Aug5th 2025
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct{
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* end;
    int size;
} Queue;

//Queue Initialization
Queue* CreateQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->end = NULL;
    q->size = 0;
    return q;
}

//Enque function
void Enqueue(Queue *q, int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    if(q->end == NULL){
        newNode->next = NULL;
        q->front = q->end = newNode;
        q->size++;
        return;
    }else{
        q->end->next = newNode;
        q->end = newNode;
    }
    q->size++;
    return;
    
}

//Dequeue Function
int Dequeue(Queue* q){
    if(q->front==NULL){
        printf("Queue is empty.\n");
        return -1;
    }
    
    Node* tmp = q->front;
    int val = q->front->data;
    q->front = q->front->next;
    if(q->front==NULL){
        q->end = NULL;
    }
    free(tmp);
    q->size--;
    return val;
}

//Queue Deallocation 
void FreeQueue(Queue* q){
    printf("Front");
    while(q->front!=NULL){
        printf("<-%d",Dequeue(q)); //Dequeue entire Queue
    }
    printf("<-End\n");
    free(q); //Free memory taken by the Queue
}

//Stack Initialization
void init(Stack *s){
    s->top = -1;
}

bool isFull(Stack *s){
    if(s->top==MAX_STACK_SIZE-1){
        return true;
    } else {
        return false;
    }
}
bool isEmpty(Stack *s){
    return s->top == -1;
}

//Push function
void push(Stack *s,int val){
    if(isFull(&s)){
        printf("Stack is full.\n");
        return;
    }
    s->top++;
    s->items[s->top] = val;
}

//Pop Function
int pop(Stack *s){
    if(isEmpty){
        printf("Stack is empty.\n");
    }
    int x = s->items[s->top];
    s->top--;
    return x;
    
}

//Function used for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}


int main()
{
    
    //LISTS
    int list[6] ={3,8,10,9,0,5};
    int x = sizeof(list)/sizeof(list[0]); //total size divided by one element
    
    printf("List:\n");
    for(int i=0;i<x;i++){
        printf("%d ",list[i]); //print each element
    }

    printf("\nSorted:\n");
    
    qsort(list,x,sizeof(int),compare);
    for(int i=0;i<x;i++){
        printf("%d ",list[i]); //print each sorted element
    }
    //END OF LISTS
    
    //STACK
    Stack myStack;
    init(&myStack);
    printf("\nAdd ints to the stack. (E to exit)\n");
    
    char input[10];
    while(1){
        printf("Enter Value: ");
        scanf("%s",input);
        printf("\n");
        
        if(strcmp(input,"E")==0 || strcmp(input,"e")==0){
            break; //leave when E is entered
        }
        
        int newVal = atoi(input); //convert to integer
        push(&myStack, newVal);//push
        
    }
    
    
    printf("Stack Contents: \n");
    // -> used for changing the value
    // . used for getting the value
    for(int i=0;i<=myStack.top;i++){
        printf("%d \n", myStack.items[i]);
    }
    //END OF STACKS
    
    //QUEUES
    printf("\nAdd elements to the Queue (E to exit).\n");
    Queue* myQueue = CreateQueue();
    char Qinput[10];
    while(1){
        printf("Enter Value: ");
        scanf("%s",Qinput);
        printf("\n");
        
        if(strcmp(Qinput,"E")==0 || strcmp(Qinput,"e")==0){
            break; //leave when E is entered
        }
        
        int newQVal = atoi(Qinput);
        Enqueue(myQueue,newQVal);
    }
    
    printf("Queue Conetnts: \n");
    FreeQueue(myQueue);
    //END OF QUEUES
    
    return 0;
}