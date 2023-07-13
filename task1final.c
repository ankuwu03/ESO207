#include <stdio.h>
#include<stdlib.h>
#define EMPTY -99999999

typedef struct stack_node {
    int val;
    struct stack_node * next;
} stack_node;

//initializing head node and count( used in size() )
stack_node * head = NULL;
int count = 0; //keeps track of size of stack



///////////////FUNCTIONS/////////////////////

//adds an element to top of stack
void push(int v) {
    count++;  //size increase
    stack_node * new_node;
    new_node = (stack_node * ) malloc(sizeof(stack_node));
    new_node -> val = v;
    if (head != NULL) { //finally:  head->new_node->...->NULL
        new_node -> next = head;
        head = new_node;
    } 
    else {  //finally:  head->new_node->NULL
        new_node -> next = NULL;
        head = new_node;
    }
}

//pops out element from top of stck and returns it for printing or using further
int pop() {
    int popdata;
    if (head == NULL) return EMPTY;
    else {
        count--;  //decrease size
        popdata = head -> val;
        stack_node * next_node = head;
        head = head -> next;
        free(next_node);  //unallocate deleted node memory
        return popdata;
    }
}

//returns top element of stack
int top() {
    if (head != NULL) return head->val;
    else return EMPTY;    
}

//returns size of stack
int size(){
    return count;
}
//////////////////////////////////////////



int main() {
    int n;
    int k;
    /*
    k = 0 : push()
    k = 1 : pop()
    k = 2 : top()
    k = 3 : size()
    */
    int v;  //stores value temporarily
    int temp; //stores function return (if any) temporarily
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {
        scanf("%d", & k);

        if (k == 0) {
            scanf("%d", &v);
            push(v);
            // count ++;
        } 
        else if (k == 1) {
            temp = pop();
            if(temp==EMPTY) printf("!\n");
            else printf ("%d\n",temp);
            // if (count) count--;
        } 
        else if (k == 2) {
            temp = top();
            if(temp == EMPTY) printf("!\n");
            else printf("%d\n",temp);
        } 
        else {
            printf("%d\n", size());
        }
    }
    return 0;
}