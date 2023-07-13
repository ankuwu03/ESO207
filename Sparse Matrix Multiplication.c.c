//////////////////////////////      C O D E   1      //////////////////


////////////////            OVERVIEW of DATA STRUCTURE           /////////////
/*
A matrix is post multiplied by B matrix
so we multiply rows of A with cols of B
So we need rowlinks only in matA aand collinks only in matB
So column links in mat A and rowlinks in mat B are redundant and would consume space
so for A{ the cells a[i,j] store: 
    we have just rowhead array  (no column head) which each point to first elements of respective rows
    other cells are connected by cells right and left (not up and down)
    we have cells that store value and j of that cell
}
for mat B{the cells b[i,j] store: 
    we have just colhead array  (no row head) which each point to first elements of respective columns
    other cells are connected by cells up and down (not left and right)
    we have cells that store value and i of that cell
}

1.  First we create rowhead and column head pointers that will point tpo first element in that row/col

2.  We create auxilliary temprow and tempcol pointer arrays to aid in insertion of cells 

3.  we scanf the input and check the matrix number, create node and then add to teh row/colhead using temp pointers

4. While multiplying we select ith rowhead of mat A and jth colhead of mat B

5. Now we keep on going next until the j value in first matrix's cell is same as i vakue in second matrix's cell

6. we add this to sum variable

7. when we reach end of row of A or end of col of B, we print output in desired format

8.  repeat for next i,j
*/

#include <stdio.h>
#include <stdlib.h>

//denotes cell in matrix
struct node{
    int val;
    int index;  //stores j in matrix A and i in matrix B
    struct node* next;
};

//creates node
struct node* createnode(int val, int index){
    struct node* tempo;
    tempo = (struct node*)malloc(sizeof(struct node));
    tempo->val=val;
    tempo->index=index;
    tempo->next=NULL;
    return tempo;
}

//input is rowhead of A and colhead of B
void matmul(struct node** rowhead, struct node** colhead,int n){
    int flagnull=1;
    struct node* X; //current cell pointer in matrix 1
    struct node* Y; //current cell pointer in matrix 2
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            X = rowhead[i];
            Y = colhead[j];
            int sum=0;
            while(X!=NULL && Y!=NULL){
                if( (X->index) == (Y->index) ) {
                    sum+= (X->val)*(Y->val);
                    X=X->next;
                    Y=Y->next;
                }
                else if( (X->index) > (Y->index) ) Y=Y->next;
                //here we incrase Y's index in hope of getting thi equal to X's
                else X=X->next;
                //vice versa of abovev comment
            }
            if (sum!=0) {
                printf("%d %d %d\n",i+1,j+1,sum);
                flagnull=0;
            }
        }
    }
    if (flagnull==1) printf("NULL MATRIX!");
}


//When  called, displays input used for multiplication after forming necessary links and error if found any
void check_if_input_done_correctcheck_if_input_done_correct(struct node** rowhead, struct node** colhead, int n){
    for(int i=0;i<n;i++){
            struct node* ptr = rowhead[i];
            if(ptr==NULL) printf("error@ i=%d\n",i+1);
            while(ptr!=NULL) {
                printf("1 %d %d %d\n",i+1,(ptr->index)+1,ptr->val);
                ptr = ptr->next;
            }
        }
        for(int j=0;j<n;j++){
            struct node* ptr = colhead[j];
            if(ptr==NULL) printf("error@ j=%d\n",j+1);
            while(ptr!=NULL) {
                printf("2 %d %d %d\n",(ptr->index)+1,j+1,ptr->val);
                ptr = ptr->next;
            }
        }
}

int main(){

//uncomment below to take input from input .txt and output in output.txt

// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
// #endif

///////////////////////////////////////////////////////////////////
    int n;
    scanf("%d",&n);
    struct node* temprow[n+1]; //temporary pointer arrays to assist row/col head while makiing matrix
    struct node* tempcol[n+1]; //will be freed later
    for(int i=0;i<=n;i++){
        temprow[i]=NULL;
        tempcol[i]=NULL;  //forced to use this for loop...else had an error due to no initialization
    }

    struct node* rowhead[n];
    for(int i=0;i<=n;i++){
        rowhead[i]=NULL;   //initialization is important...without it I was getting error
    }
    struct node* colhead[n];
    for(int i=0;i<n;i++){
        colhead[i]=NULL;
    }

    int matname;
    int i,j,val;
    struct node* node; //holds created node briefly
    scanf("%d",&matname);
    while(matname){
        scanf("%d %d %d",&i,&j,&val);
        i--;
        j--;
        if(val!=0){
            if (matname==1){
                //add node in matrix 1
                if(rowhead[i]==NULL){
                    node = createnode(val,j);
                    rowhead[i]=node;
                    temprow[i] = node; //temprow[i] points to last current cell in that row
                }
                else{
                    node=createnode(val,j);
                    temprow[i]->next=node;
                    temprow[i]=node;
                }
            
            }
            else if (matname==2){
                //add node in matrix 2
                if(colhead[j]==NULL){
                    node = createnode(val,i);
                    colhead[j]=node;
                    tempcol[j] = node;//tempcol[i] points to last current cell in that col
                }
                else{
                    node=createnode(val,i);
                    tempcol[j]->next=node;
                    tempcol[j]=node;
                }
            }
        }
        scanf("%d",&matname);
    }
    free(temprow[n]);
    free(tempcol[n]);
    //matrices created!!

    matmul(rowhead,colhead,n);   //line 57
    // check_if_input_done_correct(rowhead,colhead,n);

    
    return 0;
}
////CODE END/////

//BELOW IS AN ALTERNATE SOLUTION: CODE 2//








////////////////////////// C O D E 2 (uncomment everything below once to see) ///////////////////////


// ////////////////            OVERVIEW of DATA STRUCTURE           /////////////
// /*
// 1.  first we create a struct table for both matrices containing (i,j,val) values 
//     function used: create_and_multiply_matrices()
//     Auxilliary Space Complexiy= O(m)

// 2.  Now we make a linked list of rowhead nodes for each row, consisting of the row number, a pointer to next rowhead, and a pointer to first cell of that row.
//     here we ignore those rows that have no cell in them
//     Eg: if struct table had i  = {1 2 2 4}...we make  1->2->4->NULL
//     Function used: rowhead_create()
//     Auxilliary Space Complexity = O(m)
//     Time Complexity = O(m)

// 3.  Do the similar to create column head linked list with j values
//     Function used = colhead_create()
//     same space and time complexities as above

// 4.  Now comes creating matrix.

//         Creating matrix 1:

//     ->  first create a cell pointer array for row and col sepatately with size n. This is temporary and will be used to help rowhead and colhead to link the cells
//     ->  R[i] points to the last(currently) cell of a row 
//     ->  I then use it as reference to connect the incoming node
//     ->  also we will free this memory after links are formed

// Similarly create matrix 2
// now both matrices  can be accessed by 1 rowhead pointer and 1 colhead pointer each
// ////////////////////////////////////////////////////////////////////////////////
// */
// #include  <stdio.h>
// #include  <stdlib.h>


// //////////////////////////  NECESSARY STRUCT DEFINITIONS ///////////////////////////////////


// // we first create a struct table  for both matrices consisting all (i,j,value)
// //This is done via datanode structure below
// struct datanode{  //for initial matrix
//     int i;
//     int j;
//     int val; //value
// };

// //node structure of cell in matrix
// struct cell{
//     int val;
//     int i;
//     int j;
//     struct cell* right;  //pointer link to right cell
//     struct cell* down;   //pointer link to below cell
// };

// //node structure for rowhead and columnhead linked lists
// //it consists index(i for rowhead||j for colhead) , 
// //            *next pointing to rowhead below || to column head on right
// //            *enter pointing to first cell in that  row/column 
// struct rowcol { 
//     int index;
//     struct rowcol* next;
//     struct cell* enter;
// };

// //points to current cell
// struct tempptr{ 
//     struct cell* ptr;
// };



// ///////////////////////////FUNCTIONS/////////////////////////////////

// //function to make cell
// struct cell* makecell(int val,int i,int j){
//     struct cell* temp;
//     temp = (struct cell*)malloc(sizeof(struct cell));
//     temp->val = val;
//     temp->i=i;
//     temp->j=j;
//     temp->down = NULL;
//     temp->right= NULL;
//     return temp;
// }

// //function to make rowhead/colhead node
// struct rowcol* addhead(int index){
//     struct rowcol* temp;
//     temp=(struct rowcol*)malloc(sizeof(struct rowcol));
//     temp->next=NULL;
//     temp->enter=NULL;
//     temp->index = index;
//     return temp;
// }

// //this uses addhead() function to create rowhead nodes and links them in an order
// struct rowcol* rowhead_create(struct rowcol* head, struct datanode* mat, int lim, int* size){
//     //self explanatory names
//     struct rowcol* prev = NULL;
//     struct rowcol* curr = NULL;

//     //creates links
//     int temp=69;
//     for(int t=0;t<lim;t++){
//         if(temp != mat[t].i){
//             temp = mat[t].i;
//             if(head==NULL) {
//                 head = addhead(mat[t].i); //refer line 88 for definition
//                 head->enter=NULL;
//                 prev = head;
//                 curr = head;
//             }
//             else{
//                 curr = addhead(mat[t].i);
//                 curr->enter=NULL;
//                 prev->next = curr;
//                 prev = curr;
//             }
//         }
//     }

//     int cc=0; //no of unique rows with atleast 1 entry
//     prev = head;
//     while(prev!=NULL){
//         cc++;
//         prev = prev->next;
//     }
//     *size = cc;
//     return head;
// }

// //this uses addhead() function to create rowhead nodes and links them in an order
// struct rowcol* colhead_create(struct rowcol* head, struct datanode* mat, int lim, int* size){
//     struct rowcol* prev = NULL;
//     struct rowcol* curr = NULL;

//     int temp=69;
//     for(int t=0;t<lim;t++){
//         if(temp != mat[t].j){
//             temp = mat[t].j;
//             if(head==NULL) {
//                 head = addhead(mat[t].j);  //refer line 88
//                 head->enter=NULL;
//                 prev = head;
//                 curr = head;
//             }
//             else{
//                 curr = addhead(mat[t].j);
//                 curr->enter=NULL;
//                 prev->next = curr;
//                 prev = curr;
//             }
//         }
//     }

//     int cc=0; //no of unique columns with atleast 1 entry
//     prev = head;
//     while(prev!=NULL){
//         cc++;
//         prev = prev->next;
//     }
//     *size = cc;
//     return head;
// }

// void swap(struct datanode* mat, int j){
//     struct datanode temp = *(mat+j);
//     *(mat + j) = *(mat+j+1);
//     *(mat+j+1) = temp;
// }
// //sort table a/c to i values
// void sorti(struct datanode* mat,int lim){
//     for(int x=0;x<lim-1;x++){
//         for(int y=0;y<lim-x-1;y++){
//             if(mat[y].i > mat[y+1].i){
//                 swap(mat,y); //swaps mat[y] and mat[y+1]  
//             }
//         }
//     }
// }
// //sort table a/c to i values
// void sortj(struct datanode* mat,int lim){
//     for(int x=0;x<lim-1;x++){
//         for(int y=0;y<lim-x-1;y++){
//             if(mat[y].j > mat[y+1].j){
//                 swap(mat,y); //swaps mat[y] and mat[y+1]
//             }
//         }
//     }
// }



// //////////////////////      MULTIPLICATION       /////////////////////

// /*
// for AB(i,j) = summation(k=o to n ) [ A(i,k) * B(i,j) ]
// so we traverse to ith row of MAT 1 via rowhead1
// and to jth col if MAT 2 via colhead2
// then we assume sum = 0
// and traverse in ith row of mat1 and jth col of mat2
// whenever j value of cell in mat1 is same as i value of cell in mat2 then multiply them and add to sum
// after one of the cells reach null print (i,j,sum) (if sum!=0)
// */
// void multiply(struct rowcol* r1, struct rowcol* r2, struct rowcol* c1, struct rowcol* c2){
//     struct rowcol* ptrrow = r1; //in mat 1
//     struct rowcol* ptrcol = c2; //in mat 2
//     struct cell* gridrow; //in mat 1
//     struct cell* gridcol; //in mat 2
//     int flagnull=1;  //if 1, multiplication is null matrix
//     while(ptrrow!=  NULL ){
//         ptrcol=c2;
//         while (ptrcol!=NULL){
//             gridrow = ptrrow->enter; //points current cell in current row in mat 1 during multiplication
//             gridcol = ptrcol->enter; //points current cell in current row in mat 2 during multiplication
//             int sum = 0;
//             while(gridrow!= NULL && gridcol!=NULL){
//                 if( (gridrow->j) > (gridcol->i)) gridcol = gridcol->down;
//                 else if ((gridrow->j) < (gridcol->i) ) gridrow = gridrow->right;
//                 else if ((gridrow->j) == (gridcol->i)) {
//                     flagnull=0;
//                     sum += (gridrow->val) * (gridcol->val);
//                     gridrow = gridrow->right;
//                     gridcol = gridcol->down;
//                 }
//             }
//             if(sum!=0) printf("%d %d %d\n",ptrrow->index,ptrcol->index,sum);
//             ptrcol = ptrcol->next;
//         }
//         ptrrow = ptrrow->next;
//     }
//     if(flagnull==1) printf("NULL MATRIX!");
//     //return to create_and_multiply_matrices()
// }

// void create_and_multiply_matrices(struct rowcol* rowhead1,struct rowcol* rowhead2,struct rowcol* colhead1, struct rowcol* colhead2 ,int n){

//     /////////////////////pre processing/////////////////////

//     //making struct table of (i,j,val)

//     struct datanode mat1[n];
//     struct datanode mat2[n];
//     int i1=0;
//     int i2=0;
//     int matname ;
//     scanf("%d",&matname);
//     while(matname){ //make struct table
//         if(matname==1){
//             scanf("%d",&mat1[i1].i);
//             scanf("%d",&mat1[i1].j);            
//             scanf("%d",&mat1[i1].val);
//             i1++;
//         }
//         else if(matname==2){
//             scanf("%d",&mat2[i2].i);
//             scanf("%d",&mat2[i2].j);            
//             scanf("%d",&mat2[i2].val);
//             i2++;
//         }
//         scanf("%d",&matname);
//     }

//     //MATRIX1 = m1 x n1  ||  MATRIX2= m2 x n2
//     int m1,m2,n1,n2;

//     //creates a linked list of unique rowhead in ordered manner and returns head dof list
//     //does not  contain rowhead of rows containing zero elements...hence optimizing space n time
//     rowhead1= rowhead_create(rowhead1,mat1,i1,&m1);     //refer line 98
//     rowhead2= rowhead_create(rowhead2,mat2,i2,&m2);     //refer line 98

//     sortj(mat1,i1); //sort struct table a/c to j values
//     sortj(mat2,i2); //defined on line 183

//     //create colhead list for both matrices
//     colhead1=colhead_create(colhead1,mat1,i1,&n1);      //refer line 134
//     colhead2=colhead_create(colhead2,mat2,i2,&n2);      //refer line 134
    
//     sorti(mat1,i1);  //sort a/c to j values to get original struct table
//     sorti(mat2,i2); //defined on line 173


//     ///////////////     CREATING MATRIX 1       ////////////////

//     //temporary cell pointer array for both rows and cols of matrix 1
//     struct cell* R1[n+1];
//     struct cell* C1[n+1];
//     ////////////without nullifying it was giving error forcing me to use O(n) operation here
//     for(int i=1;i<=n;i++){
//         R1[i] = NULL;
//         C1[i] = NULL;
//     }
//     //points to urrent row/col during construction of matrix
//     struct rowcol* rowptr = rowhead1;
//     struct rowcol* colptr = colhead1;
//     struct cell* hold; //temporarily holds the cell
//     int i,j;

//     //take one by one cell data from datanode struct table, create a node for it and connect it accorfdingly to the matrix row/col heads using R[i], C[j]
//     for(int x=0 ; x<i1 ; x++ ){
//         //make cell
//         hold = (struct cell*)malloc(sizeof(struct cell));
//         i=mat1[x].i;
//         j=mat1[x].j;
//         hold->val = mat1[x].val;
//         hold->i=i;
//         hold->j=j;
//         hold->right = NULL;
//         hold->down = NULL;

//         //go to desired row and col heads
//         while(rowptr->index != i) rowptr = rowptr->next;
//         while(colptr->index != j) colptr = colptr->next;

//         //enter the matrix and connect the current(hold) cell in the matrix with the help of R1[i], C1[j] pointers
//         if(rowptr->enter == NULL) {
//             rowptr->enter = hold;
//             R1[i] = hold;
//         }
//         else {
//             R1[i]->right = hold;
//             R1[i] = hold;
//         }

//         if(colptr->enter == NULL) {
//             colptr->enter = hold;
//             C1[j] = hold;
//         }
//         else {
//             C1[j]->down = hold;
//             C1[j] = hold;
//         }

        
//         //return to begining of head lists for next connection
//         rowptr = rowhead1;
//         colptr = colhead1;        
//     }

//     ///////////////////////////////ENDOF MAT1//////////////////////

//     ////////////////////////////////MAT 2///////////////////////////////
//     // <similar approach>
//     struct cell* R2[n+1];
//     struct cell* C2[n+1];
//     ////////////without nullifying it was giving error forcing me to use O(n) operation here
//     for(int i=1;i<=n;i++){
//         R2[i] = NULL;
//         C2[i] = NULL;
//     }
//     rowptr = rowhead2;
//     colptr = colhead2;

//     for(int x=0 ; x<i2 ; x++ ){
//         hold = (struct cell*)malloc(sizeof(struct cell));
//         i=mat2[x].i;
//         j=mat2[x].j;
//         hold->val = mat2[x].val;
//         hold->i=i;
//         hold->j=j;
//         hold->right = NULL;
//         hold->down = NULL;

//         while(rowptr->index != i) rowptr = rowptr->next;
//         while(colptr->index != j) colptr = colptr->next;

//         if(rowptr->enter == NULL) {
//             rowptr->enter = hold;
//             R2[i] = hold;
//         }
//         else {
//             R2[i]->right = hold;
//             R2[i] = hold;
//         }

//         if(colptr->enter == NULL) {
//             colptr->enter = hold;
//             C2[j] = hold;
//         }
//         else {
//             C2[j]->down = hold;
//             C2[j] = hold;
//         }

//         rowptr = rowhead2;
//         colptr = colhead2;
//     }
//     /////////////////////////END OF MAT2///////////////////////

//     multiply(rowhead1,rowhead2,colhead1,colhead2);      // refer line 206
//     //VOID FUNCTION(automatically prints after multiplication)
//     //return to main
// }


// int main(){
// //uncomment below to take input from input .txt and output in output.txt

// // #ifndef ONLINE_JUDGE
// // 	freopen("input.txt", "r", stdin);
// // 	freopen("output.txt", "w", stdout);
// // #endif
// //////////////////////////////////////////////////////////////////////

//     int n;
//     scanf("%d",&n);
//     struct rowcol* rowhead1=NULL;
//     struct rowcol* rowhead2=NULL;
//     struct rowcol* colhead1=NULL;
//     struct rowcol* colhead2=NULL;
//     create_and_multiply_matrices(rowhead1,rowhead2,colhead1,colhead2,n);
//     return 0;
// }

// ////FIN//


///////////////// END OF CODE 2 /////////////////////////////