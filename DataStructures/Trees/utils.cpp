#include "utils.h"
#include<iostream>
#include<ctime>
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std; 


void printSpace(int space){for(int i =0 ; i < space ; i++)cout<<" " ;}
Node * newNode(int data) { Node * newnode = new Node ; newnode->l = newnode->r = 0 ; newnode->data = data ; return newnode ;  }


void Tree::addNode( int data )
{
    Node * temp  = this->getRoot() ; 
    while(temp->l){
        temp = temp->l ;
    }
    temp->l = newNode(data)  ; 
}


Node * Tree::buildTreeFromInorderPreorderHelper(std::vector<int> inorder , std::vector<int> preorder , int inS , int inE , int preS , int PreE , unordered_map<int , int>& node_to_inorder_idx )
{
    if(inS>inE || preS>PreE) return  0 ; 
    Node * root = new Node ; 

    root->data = preorder[preS] ; 

    int leftSize = node_to_inorder_idx[preorder[preS]] - inS ; 
    // int rightSize = inE -  node_to_inorder_idx[preorder[preS]] ; 

    root->l = buildTreeFromInorderPreorderHelper(inorder , preorder , inS , node_to_inorder_idx[root->data]-1 , preS+1 , preS+leftSize , node_to_inorder_idx) ;
    root->r = buildTreeFromInorderPreorderHelper(inorder , preorder , node_to_inorder_idx[root->data]+1 , inE , preS+leftSize+1 , PreE  , node_to_inorder_idx) ;

    return root ; 
}

Tree::~Tree()
{
    deallocateAllNodes(root) ; 
}

void Tree::deallocateAllNodes(Node * root)
{
    if(!root) return ; 
    deallocateAllNodes(root->l) ; 
    deallocateAllNodes(root->r) ; 
    delete root ; 
}

void Tree::setRoot(Node * root)
{
    this->root = root ; 
}


Node * Tree::buildTreeFromInorderPreorder(std::vector<int> inorder , std::vector<int> preorder)
{
    unordered_map<int , int >  node_to_inorder_idx ; 
    for(int i =0 ;i < inorder.size() ; i++) node_to_inorder_idx[inorder[i]] = i ; 

    deallocateAllNodes(root) ; 
    root = buildTreeFromInorderPreorderHelper(inorder , preorder , 0 , inorder.size()-1 , 0 , preorder.size()-1 , node_to_inorder_idx ) ; 
}




void Tree::insertBST(int data)
{
    Node * newnode  = new Node; 
    newnode->l = newnode->r = 0 ; 
    newnode->data = data ; 
    Node * temp = this->root  , * parent = root ; 
    this->n++ ; 

    while(temp){
       parent = temp ; 
       if(data<temp->data) temp = temp->l ;  
       else temp = temp->r ; 
    }
    if(data < parent->data ) parent->l = newnode; 
    else parent->r = newnode; 
}

bool isQueueNull(queue<Node*> myqueue){
   //* Checks if all the elments in queue are null and returns true if so  */ 
   while(!myqueue.empty())
   { 
        if(myqueue.front())return false ; 
        myqueue.pop() ; 
   }
    return true ; 
}

Tree::Tree(int data ){

        srand(time(NULL)) ; 
        root = new Node ; 
        root->l = root->r = 0 ;
        root->data = data?data : rand()%50 ; 
        n = 1 ; 
    }



void Tree::prettyPrint(int centerPosition){
    queue<Node*> myqueue  ; 
    myqueue.push(root) ; 
    while(!isQueueNull(myqueue))
    {
        printSpace(centerPosition) ; 
        int rowsize = myqueue.size() ; 
        for(int i =0 ; i < rowsize ;i++)
        {
            if(myqueue.front()) cout<< myqueue.front()->data ; 
            else cout<<"_" ; 
            printSpace(2); 
            myqueue.front()? myqueue.push(myqueue.front()->l) : myqueue.push(0) ;
            myqueue.front()? myqueue.push(myqueue.front()->r) : myqueue.push(0) ;
            myqueue.pop(); 
        }
        centerPosition-=2 ;
        cout<<endl; 
    }
}


Node * Tree::getRoot(){return root ; }

Tree Tree::buildCustomTree(vector<int> levelOrderList)
{
    Tree res = *new Tree(levelOrderList[0]) ; 
    queue<Node * > myqueue ; 
    Node * root = res.getRoot() ; 
    myqueue.push(root) ;

    int j =1 ;
    bool breakflag = false ;  ;

    while(!myqueue.empty())
    {
        for(int i = 0 ; i<myqueue.size() ; i++ , j+=2)
        {
            if(j>levelOrderList.size()){ breakflag = true  ; break ; } 
            if(levelOrderList[j]==0)
                myqueue.front()->l = 0 ; 
            else {
                         myqueue.front()->l = newNode(levelOrderList[j]) ; 
                         myqueue.push(myqueue.front()->l) ; 
            }
        
            if(j+1<levelOrderList.size())
            {
                if(levelOrderList[j+1]==0)
                    myqueue.front()->r =  0 ; 
                else {
                    myqueue.front()->r = newNode(levelOrderList[j+1]) ; 
                    myqueue.push(myqueue.front()->r) ; 
                }
            }
            myqueue.pop() ; 
        }
        if(breakflag) break ; 
    }
    return res ;
}



void Tree::inorder(Node * rootvar )
{
    if(!rootvar) return  ;     
    if(rootvar==(Node *)-1)
    {

        inorder(this->root) ;
        return ; 
    }
    inorder(rootvar->l) ; 
    cout<<rootvar->data<<" " ; 
    inorder(rootvar->r) ; 
}

void Tree::postorder(Node * root )
{
    if(!root) return  ;     
    if(root==(Node *)-1)
    {
        this->postorder(this->root) ; 
        return ; 
    }
    postorder(root->l) ; 
    postorder(root->r) ; 
    cout<<root->data<<" " ; 
}


void Tree::preorder(Node * root)
{
    if(!root) return  ;     
    if(root==(Node *)-1)
    {

        this->preorder(this->root) ;
        return ;
    }
    cout<<root->data<<" " ; 
    preorder(root->l) ; 
    preorder(root->r) ; 
}


int Tree::findMax(Node * root )
{
    if(!root) return 0 ;
    int l = findMax(root->l) ;
    int r = findMax(root->r) ;
    return max(root->data , max(l ,r)) ;
}


bool Tree::isBST(Node * root)
{
    if(!root) return true;
    int l = findMax(root->l) ;
    int r = findMax(root->r) ;
    
    if(root->data<l || root->data>r)
        return false ; 
    return true ; 
}


Tree Tree::generateRandBST(int no_of_nodes , int randmin , int randmax )
{
    for(int i =0; i < no_of_nodes  ; i++)
    {
        this->insertBST((rand()%(randmax-randmin)) + randmin) ; 
    }
    return *this ; 
}


Tree Tree::generateRandBT(int no_of_nodes)
{
    srand(time(0)) ;
    vector<int> arr ; 
    for(int i =0 ; i < no_of_nodes ; i++)
    {
        arr.push_back(rand()%100) ; 
    }
    return buildCustomTree(arr) ; 
}


ostream& operator<<(ostream& out, Tree& T)
{ 
    deque<Node *> Q ; 
    Q.emplace_back(T.root) ; 
    
}


ostream& operator<<(ostream& out , Node * root)
{
    if(!root) return out ;

    cout<<root->data<<"  ---  " ; 
    cout<<root->l ;
    cout<<root->r <<endl;  
}