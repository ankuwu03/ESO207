#include <stdio.h>
#include<stdlib.h>
#define NILNUM -999999
/*
in below functions I didnt write else condition where it was not necessary but
hackerrank was giving compilation error due to that so I used above integer as dummy for else condition
this problem wasnt there in VSCode, codechef and codeforces so it is hackerrank specific problem
NILNUM wont be used if the expression is valid and hence doesnt matter what it is


Operator and RESPECTIVE numcode mapping used here:

    +  10
    -  20
    *  30
    /  40
    ^  50
    (  60
    $  70
    #  80

*/

//stack
typedef struct node {
    int val;
    struct node * next;
} stack;

//initializing head node and count( used in size() )
//used separate stacks for numbers and operators
stack * headn = NULL; //N stack
stack * heado = NULL; //O stack
int countn = 0; //keeps track of size of N stack
int counto = 0; //keeps track of size of O stack



///////////////FUNCTIONS/////////////////////

//maps operator with its num code
int chartonum(char ch){
    if (ch== '+') return 10;
    else if(ch== '-') return 20;
    else if(ch== '*') return 30;
    else if(ch== '/') return 40;
    else if(ch== '^') return 50;
    else if(ch== '(') return 60;
    else if(ch== '$') return 70;
    else if(ch== '#') return 80;
    else return NILNUM;
}

//calculates base^pow
int power(int base, int pow){
    int sum=1;
    for(int i=0;i<pow;i++){
        sum=sum*base;
    }
    return sum;
}

//Adds an element to top of stack:

    // FOR N STACK
    void pushn(int v) {  
        countn++;  //size increase
        stack * new_node;
        new_node = (stack * ) malloc(sizeof(stack));
        new_node -> val = v;
        if (headn!= NULL) { //finally:  head->new_node->...->NULL
            new_node -> next = headn;
            headn = new_node;
        } 
        else {  //finally:  head->new_node->NULL
            new_node -> next = NULL;
            headn = new_node;
        }
    }

    //FOR O STACK
    void pusho(int v) {  
        counto++;  //size increase
        stack * new_node;
        new_node = (stack * ) malloc(sizeof(stack));
        new_node -> val = v;
        if (heado!= NULL) { //finally:  head->new_node->...->NULL
            new_node -> next = heado;
            heado = new_node;
        } 
        else {  //finally:  head->new_node->NULL
            new_node -> next = NULL;
            heado = new_node;
        }
    }

/*
here I tried using one function for pushing in both stacks by passing its pointer
but that gave some error which was resolved when i globally declare the head pointers 
rather than passing it through function
Hence I created 2 separate functions for both stack manipulations
*/


//pops out element from top of stack and returns it for printing or using further
    //FOR N STACK
    int popn() {  
        int popdata;
        if (headn == NULL) return NILNUM ;  
        else {
            countn--;  //decrease size
            popdata = headn -> val;
            stack * next_node = headn;
            headn = headn-> next;
            free(next_node);  //unallocate deleted node memory
            return popdata;
        }
    }

    //FOR O STACK
    int popo() {  
        int popdata;
        if (heado == NULL) return NILNUM;            
        else {
            counto--;  //decrease size
            popdata = heado -> val;
            stack * next_node = heado;
            heado = heado-> next;
            free(next_node);  //unallocate deleted node memory
            return popdata;
        }
    }

//returns top element of stack
int topn() { //N STACK
    if ((headn) != NULL) return headn->val;
    else return NILNUM;    
}
int topo() { //O STACK
    if ((heado) != NULL) return heado->val;
    else return NILNUM;    
}

//executes < n2 o n1 >
int execute(int n1 , int n2, char o){
    if      (o == 10) return n2 + n1 ;
    else if (o == 20) return n2 - n1 ;
    else if (o == 30) return n2 * n1 ;
    else if (o == 40) return n2 / n1 ;
    else return power( n2 , n1 ) ;
}

int insidepriority(char o ){
    if     (o == 10) return 1;
    else if(o == 20) return 1;
    else if(o == 30) return 3;
    else if(o == 40) return 3;
    else if(o == 50) return 5;
    else if(o == 60) return 0;
    else if(o == 70) return -1;
    else return NILNUM;
}
int outsidepriority(char o ){
    if     (o==10) return 1;
    else if(o==20) return 2;
    else if(o==30) return 3;
    else if(o==40) return 4;
    else if(o==50) return 6;
    else if(o==60) return 7;    
    else if(o==80) return 0; 
    else return NILNUM;
}
//////////////////////////////////////////

//created two separate stacks for numbers and operators
int main(){
    int n;
    scanf("%d\n",&n);
    char exp[n+2];
    //string input in char array and will be used further
    //example for 3+2 the array is = { '$' , '3' , '+' , '2' , '#' }

    exp[0]='$';
    exp[n+1]='#';
    for(int i=1;i<=n;i++){
        scanf("%c",&exp[i]);
    }
    int i=0;
    pusho(chartonum(exp[i]));
    i++;

    while(topo()!=80){     // 80 = '#'
        //CASE NUMBER 0-9
        if(exp[i] <='9' && exp[i] >='0'){
            int num=0;
            while(1){
                num = num*10 + exp[i]-'0';
                i++;
                if(exp[i]>'9' || exp[i]<'0') break;
            }
            pushn(num); //push number to N stack
            num=0;
            continue;
        }

        //CASE '('
        else if(exp[i]==')'){
            while(topo()!=60){  // 60 = '('
            //execute < n2 operator n1 > 
                int operator = popo();
                int n1 = popn();
                int n2 = popn();
                int n3 = execute(n1,n2,operator);
                pushn(n3); //keep executing and pushing result until ')' is found
            }
            popo();  //pop mathcing '('
            i++;
            continue;
        }

        //CASE EXECUTION
        else {
            while( insidepriority(topo()) >= outsidepriority (chartonum (exp[i]) ) ){
                //deals with priority(associative thing)
                //execute < n2 operator n1 > 
                int operator = popo();
                int n1 = popn();
                int n2 = popn();
                int n3 = execute(n1,n2,operator);
                pushn(n3);  //push to N stack after execution
            }
            pusho(chartonum(exp[i]));
            if(i!=n+1) i++; //cant do i++ at last element of array(i=n+1)
            continue;
        }
    }
    printf("%d",topn());
    //after executions result is pushed to N stack...so answer is top(Nstack)
    return 0;
}