//
//  binomial_heap.h
//  hw5
//
//  Created by siqiyaoyao on 5/24/15.
//  Copyright (c) 2015 siqiyaoyao. All rights reserved.
//

#ifndef __hw5__binomial_heap__
#define __hw5__binomial_heap__

#include <utility>
#include <list>
#include <vector>

struct EmptyHeap: public std::exception {};

template<class T>

class BinomialHeap {
private:
    /* inner class: binomial tree */
    struct BinomialTree {
        int _size;
        T element;
        std::list<BinomialTree*> children;
        
        BinomialTree(T _ele): _size(1), element(_ele) {
            children.clear();
        }
        
        /* return the size of BinomialTree
         * #note that nullptr->size() == 0
         * (nullptr is a null pointer (like NULL in C))
         */
        int size() {
            return (this!=nullptr)?this->_size:0;
        }
    };
    /* some definition for convinience
     */
    typedef BinomialTree BT;
    typedef BinomialHeap<T> BH;
    typedef std::pair<BT*, BT*> CarrySum;
    typedef std::pair<T, BH> MaxRemainder;
    
    /* Merge three binomial trees which have the same sizes
     *
     * INPUT:   a: operand a, b: operand b, c: carry in
     *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
     *
     * OUTPUT:  a pair consist of two variables.
     *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
     *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
     *
     * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
     */
    CarrySum merge_tree(BT *a, BT *b, BT *c) {
        BT * carry_out=nullptr;
        BT * sum=nullptr;
        std::vector<BT*> candidate;
        BT * subtree;
        
        if(a) candidate.push_back(a);
        if(b) candidate.push_back(b);
        if(c) candidate.push_back(c);
        
        int csize=candidate.size();
        if(csize==1){
            sum=candidate[0];
        }
        else if(csize==2 || csize==3){
            //merge 2 tree
            if(candidate[0]->element > candidate[1]->element){
                carry_out=candidate[0];
                subtree=candidate[1];
            }
            else{
                carry_out=candidate[1];
                subtree=candidate[0];
            }
            carry_out->children.push_back(subtree);
            carry_out->_size+=subtree->_size;
            if(csize==3)
                sum=candidate[2];
        }
        
        return std::make_pair(carry_out,sum);
        
    };
    
    /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
     *
     * INPUT:   a: a pointer of BinomialTree
     *
     * OUTPUT:  a pair consist of two variables.
     *          first: the maximum element
     *          second: a binomial heap consists of other elements
     */
    MaxRemainder pop_max(BT *a) {
        T maximum = a->element;
        BH remain =  BH();
        int i = 0;
        typename std::list<BT *>::iterator V;
        for(V=a->children.begin();V!=a->children.end();V++){
            remain.trees[i++]=*V;
            //remain.trees[i]=a->children.front();
            //a->children.pop_front();
        }
        remain.size=a->size()-1;
        return std::make_pair(maximum,remain);
    }
    
    int size;
    BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.
    
public:
    BinomialHeap(): size(0) {
        for(int i=0; i<32; ++i) trees[i] = nullptr;
    }
    BinomialHeap(T element): size(1) {
        for(int i=0; i<32; ++i) trees[i] = nullptr;
        trees[0] = new BT(element);
    }
    
    /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
     *
     * INPUT:   b: a pointer of BinomialHeap
     */
    void merge(BH &b) {
        // write your code here.
        size=size+b.size;
        BT * carry_out=nullptr;
        for(int i=0;i<32;i++){
            CarrySum cs=merge_tree(trees[i],b.trees[i],carry_out);
            b.trees[i]=nullptr;
            carry_out=cs.first;
            trees[i]=cs.second;
            
        }
        b.size = 0;
    }
    
    void insert(const T &element) {
        BH tmp = BH(element);
        merge(tmp);
    }
    T pop() {
        if(size==0) throw EmptyHeap();
        else {
            //find the tree contains maximum element
            int max_tree = -1;
            for(int i=0; i<32; ++i)
                if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                    max_tree = i;
            
            MaxRemainder m_r = pop_max(trees[max_tree]);
            T &max_element = m_r.first;
            BH &remainder = m_r.second;
            
            size-=trees[max_tree]->size();
            trees[max_tree] = nullptr;
            merge(remainder);
            return max_element;
        }
    }
    T frontelement(BT *a){
        T max = a->element;
        return max;
    }
 T fakepop() {
        
            if(size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                
                T max = frontelement(trees[max_tree]);
                return max;
    }
 }
int hsize()
    {
        return size;
    }
    void PrintBinHeap() {
        if (size == 0) {
            return ;
        }
        else
        {
            std::cout <<"size= "<<size<<std::endl;
            for(int i = 0; i < 32; i++)
            {
                if (trees[i] != nullptr) std::cout << "i="<<i << std::endl;
            }
            
        }
       
    }

};



#endif /* defined(__hw5__binomial_heap__) */
