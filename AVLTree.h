//
//
// Templeting
// Created by MNGal on 11/11/2024.
//
//placeholder values

#ifndef PROJECT4_AVLTREE_H
#define PROJECT4_AVLTREE_H

#endif //PROJECT4_AVLTREE_H

#include <iostream>
#include <map>
using namespace std;

template<typename key, typename value>


class AVLTree {

private:
    struct AVLNode{
        key k;
        //the document and how many times it appeared
        map <value, int> v;

        //moving left and right in the tree
        AVLNode* left;
        AVLNode* right;


        //how many levels down it is
        int height;

        AVLNode(key k, AVLNode* lef = nullptr, AVLNode* rig = nullptr, int hei = 0){
            //setting parameters
            this->k = k;
            left = lef;
            right = rig;
            height = hei;
        }
    };

private:
    AVLNode* root;

    //The number of node we have
    int size;


    //recursive functions that will be called

    void clear(AVLNode*&);
    map<value, int> getNode(const key &, AVLNode *&);
    void insert(const key&, const value&, AVLNode*&);


    void balance(AVLNode*&);
    int height(AVLNode*h);


    void clone(AVLNode*&, const AVLNode*);


    void printTree(ostream&, AVLNode*&);


    void rotateLeft(AVLNode*&);


    void rotateDoubleLeft(AVLNode*&);


    void rotateRight(AVLNode*&);


    void rotateDoubleRight(AVLNode*&);

    void insert(const key&, const value&, const int&, AVLNode*&);

public:
    AVLTree();
    //Copy Constructor
    AVLTree(const AVLTree&);

    //Assignment
    AVLTree operator = (const AVLTree&);

    //destructor
    ~AVLTree();

    void clear();
    map <value, int> getNode(const key&);

    void insert(const key&, const value&);
    int getSize();


    //private one will call the public one with the root and
    void printTree(ostream&);

    void insert(const key&, const value&, const int&);



};

template<typename key, typename value>
void AVLTree<key, value>::insert(const key &k, const value &val, const int &f, AVLNode *&n) {
    if (n == nullptr){
        n = new AVLNode(k);
        //setting to one since it is the first time seeing it in the document
        n -> v[val] = f;
        //adding a node as size increases
        size ++;
        //go left
    } else if(k<n->k){
        insert(k, val, f, n-> left);
        //go right
    }else if (k> n->k){
        insert (k, val, f, n->right);
        //k==n->k, found the key that matches
    }else {
        n->v[val] = f;

    }
    balance(n);
}

template<typename key, typename value>
void AVLTree<key, value>::insert(const key &k, const value &v, const int &f) {
    insert(k, v, f, root);
}

//Change the n variable to no for aestetics(~--~)

template<typename key, typename value>
int AVLTree<key, value>::getSize() {
    return size;
}

template<typename key, typename value>
map<value, int> AVLTree<key, value>::getNode(const key & k) {
    return getNode(k, root);
}

template<typename key, typename value>
AVLTree<key, value>::~AVLTree() {
    clear();
}

template<typename key, typename value>
AVLTree<key, value> AVLTree<key, value>::operator=(const AVLTree & copy) {
    clear();
    clone(root, copy.root);
    return *this;
}

template<typename key, typename value>
AVLTree<key, value>::AVLTree(const AVLTree & copy) {
    clone(root, copy.root);
}

template<typename key, typename value>
AVLTree<key, value>::AVLTree() {
    size =0;
    root = nullptr;
}

template<typename key, typename value>
void AVLTree<key, value>::printTree(ostream &out) {
    printTree(out, root);
}

template<typename key, typename value>
void AVLTree<key, value>::insert(const key &k, const value &v) {
    insert(k, v, root);
}

template<typename key, typename value>
void AVLTree<key, value>::clear(AVLNode*& n) {
    if(n == nullptr){
        return;
    }

    //post order, the action is doing being done at last. It will go to the bottom and then delete and go up
    clear (n-> left);
    clear(n-> right);

    //Will delete a node
    delete n;
}


//






template<typename key, typename value>
void AVLTree<key, value>::rotateDoubleRight(AVLTree::AVLNode *& n) {

    //mirrored what the  double rotate will do
    rotateLeft(n->right);
    //Will have to spin the opposite of what the rotate left did
    rotateRight(n);

}

template<typename key, typename value>
void AVLTree<key, value>::rotateRight(AVLTree::AVLNode *& n) {
//copy the same process form the left tree

    AVLNode* curr = n->right;
    n->right = curr->left;
    curr->left = n;
    //taking the bigger one and then adding 1 to the larger of the children
    n->height = max(height(n-> right), height(n->left))+1;
    curr->height = max(height(curr-> right), height(curr->left))+1;

    //same thing with curr
    //4 is the left pointer instead of n
    n = curr ;//-> height =
}

template<typename key, typename value>
void AVLTree<key, value>::rotateDoubleLeft(AVLTree::AVLNode *& n) {
    rotateRight(n->left );

    //call the rotate left function so that it repeat the same process once we get it to
    //look like the rotate left tree
    rotateLeft(n);
}

template<typename key, typename value>
void AVLTree<key, value>::rotateLeft(AVLTree::AVLNode *& n) {
//this will be a mirror to the rotate right
//shallow copy refrencing an existing pointer
    AVLNode* curr = n->left;
    n->left = curr->right;
    curr->right = n;
    //taking the bigger one and then adding 1 to the larger of the children
    n->height = max(height(n-> left), height(n->right))+1;
    curr->height = max(height(curr-> right), height(curr->left))+1;

    //same thing with curr
    //4 is the left pointer instead of n
    n = curr ;//-> height =

}

template<typename key, typename value>
//included in the parent function
void AVLTree<key, value>::printTree(ostream & out, AVLTree::AVLNode *&n) {
    if(n != nullptr){
        //using in order
        //alphabetically for better human readibility
        printTree(out,n -> left);

        //end of the pair now print out the frequency
        out << n->k;
        //using two delimeter

        //for each loop that will go trhough each document that references the map that we created that contained
        //every document with the word count of the frequency
        for(const pair<value, int>& itr: n->v){
            //grab each pari from the map into the node
            out  << ";" << itr.first << "," << itr.second;
            //the first one is the document and the second one is the frequency
        }
        out << endl;
        printTree(out, n->right);
    }
}

template<typename key, typename value>
void AVLTree<key, value>::clone(AVLTree::AVLNode *& curr, const AVLTree::AVLNode * copy) {

    //Since it is by reference we can go backwards and we can look back at the parent functions


    if (copy!= nullptr){
        //creat a deep copy of this
        //Left and right is equal to null
        curr = new AVLNode(copy->k, nullptr, nullptr, copy->height);

        //The map we created at the very beggining
        curr -> v = copy->v;

        clone(curr->left , copy ->left);
        clone (curr-> right, copy->right);

        size ++;
    }
}

template<typename key, typename value>
int AVLTree<key, value>::height(AVLTree::AVLNode *n) {
    if(n == nullptr){
        return -1;
    }else {
        return n->height;
    }

}

template<typename key, typename value>
void AVLTree<key, value>::balance(AVLTree::AVLNode *& n) {

    //if it is not defined then no need to rotate
    if ( n!= nullptr){

        //if the height of the left is greater thant the right then flip

        //counting the height of the node to see the length of the nodes that follow
        if(height(n->left)-height(n->right)> 1){
            if(height(n->left->left) >= height(n->left->right)){
                rotateLeft(n);
            }else{
                rotateDoubleLeft(n);
            }

            //mirroring the top conditionals for the right rotation
        }else if(height(n->right)- height(n->left)>1){
            if (height(n-> right ->right) >= height(n->right->left)){
                rotateRight(n);

            }else{
                rotateDoubleRight(n);
            }
        }
    }
    //updating the height of the tree after the rotations
    n->height = max(height(n->left), height(n->right))+1;
}

//There is four cases different iterations to the different values of the keys
template<typename key, typename value>
void AVLTree<key, value>::insert(const key & k, const value & val, AVLTree::AVLNode *& n) {
   //does not exist
    if (n == nullptr){
        n = new AVLNode(k);
        //setting to one since it is the first time seeing it in the document
        n -> v[val] = 1;
        //adding a node as size increases
        size ++;
        //go left
    } else if(k<n->k){
        insert(k, val, n-> left);
        //go right
    }else if (k> n->k){
        insert (k, val, n->right);
        //k==n->k, found the key that matches
    }else {
        if (n->v.find(val) == n->v.end()) {
            n->v[val] = 1;

        } else {
            n->v[val]++;
        }

    }
    balance(n);
}

template<typename key, typename value>
map<value, int> AVLTree<key, value>::getNode(const key & k, AVLTree::AVLNode *& n) {



    if (n == nullptr){
        return map<value, int>();


        //go left
    } else if(k<n->k){
        return getNode(k, n-> left);
        //go right
    }else if (k> n->k){
        return getNode(k, n->right);
        //k==n->k, found the key that matches
    }else {
        return n-> v;
}

}

template<typename key, typename value>
void AVLTree<key, value>::clear() {
    clear(root);
}
