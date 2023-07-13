#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000000 //macros for upper limit

typedef struct node{
    int VAL; 
    int size; //size of subtree at th node
    struct node* right;
    struct node* left;
}Node;

double timedata[N];
Node* arrptr[N]; //holds array of pointers of nodes for balancing
int arrindex = 0; //handles max index currently while making array
int flagimbalance=0; //flag for imbalance while checking

Node* createnewnode(int n){  //creates node
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->VAL = n;
    temp->left = NULL;
    temp->right = NULL;
    temp->size = 1;
    return temp;
}

int subtreesize(Node* curr){ //gives tree size by looking into its children
//had to make this functions as it is used many times and was struggling to handle 
//null cases everytime explicitely(redutant lines of code)
    if(curr==NULL) return 0;
    else if(curr->left==NULL && curr->right==NULL) return 1;
    else if(curr->left==NULL && curr->right!=NULL) return 1 + curr->right->size;
    else if(curr->left!=NULL && curr->right==NULL) return 1 + curr->left->size;
    else if(curr->left!=NULL && curr->right!=NULL) return 1 + curr->left->size + curr->right->size;
}

//inserts newnode which is maximum among current nodes to the rightmost position via right traversal
Node* insertnewnode(Node* subroot,int n){    
    if(subroot==NULL) return createnewnode(n);
    else subroot->right = insertnewnode(subroot->right,n);
    subroot->size = subtreesize(subroot);
    return subroot;   
}

//searches for imbalance via right traversal
void balancecheck(Node* tree){ 
    Node* temp = tree; 
    //temp will follow the path we took to insert last node to check imbalance at each of node in path
    while(temp->right!=NULL){
        if(4*subtreesize(temp->left)>3*subtreesize(temp) || 4*subtreesize(temp->right)>3*subtreesize(temp)) {
            flagimbalance = 1; //checking size(subtree)<(3/4 * size(tree)) condition
            break; //break the search and come ou of loop...imbalance found
        }
        else{ //if imbalance not found...keep moving right
            temp = temp->right;
        }
    }
}

//inorder traversal for array formation from BST(unbalanced)
void createArray(Node* curr_root){
    if(curr_root==NULL) return;
    createArray(curr_root->left);
    arrptr[arrindex] = curr_root;
    arrindex++;
    createArray(curr_root->right);
}

Node* reconstructBST(Node* balance_root, int start,int end){
    if(start>end) return NULL;  //when null node is reached
    int mid = (start+end)/2;
    balance_root = arrptr[mid];  //new root is midpoint of array
    balance_root->left = reconstructBST(balance_root->left,start, mid-1); //leftconstruct
    balance_root->right = reconstructBST(balance_root->right,mid+1, end); //right construct
    balance_root->size = subtreesize(balance_root); //size declared at end of code so it adds subsize of left and right which will be calculated via recursion
	return balance_root; 
}

Node* balance(Node* curr_root){
    createArray(curr_root); //create (SORTED) array from BST
    Node* new_root = reconstructBST(curr_root , 0 , arrindex-1); 
    //remake the tree via recursion so it is perfectly balanced
    arrindex=0; //initilie index of array as 0 for future
    return new_root;
}

int main() {
    Node* tree; //root node of tree---access point
    tree = createnewnode(1); //makes tree with 1 as root
    for(int i=2 ; i<N ; i++){

        clock_t start_t, end_t;
        double total_t;
        start_t = clock();
        
        flagimbalance = 0 ; 
        tree = insertnewnode(tree,i);   //adds newnode without via recursive right traversal
        balancecheck(tree); //checks if imbalance occurs via right traversal
        if(flagimbalance == 1){
            tree = balance(tree);  //if imbalance found...balance it
        }

        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        timedata[i] = total_t;
        printf(" %d || time(sec): %f\n",i,timedata[i]);
    }
	return 0;
}