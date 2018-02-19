//
//  main.cpp
//  hw5
//
//  Created by siqiyaoyao on 5/24/15.
//  Copyright (c) 2015 siqiyaoyao. All rights reserved.
//

#include <iostream>
#include <string>
#include<algorithm>
#include "binomial_heap.h"
using namespace std;
class data {
public:
    int id;
    int p;
    data(){
        id=0;
        p=0;
    }
    data(int a,int b)
    {
        id = a;
        p =b;
    }
    bool operator<(data &a)
    {
        return this->p < a.p;
    }
    bool operator>(data &a)
    {
        return this->p > a.p;
    }
};

//template<class T = data>;


int main() {
    int c, w;
    cin >> c>>w;
    BinomialHeap<data> *computer = new BinomialHeap<data>[c];
    data task;
    
    string input;
    int cm,id,p,cm1,cm2;
    
    while (cin >> input ) {
        if (input == "assign")
            {
                cin>> cm >> id>>p;
                task.id = id;
                task.p = p;
                computer[cm].insert(task);
                int n = computer[cm].hsize();
                
                cout <<"There are "<<n <<" tasks on computer "<<cm<<"."<<endl;
                
                
            }
        else if (input == "merge")
            {
                cin>>cm1>>cm2;
               
                if(computer[cm2].hsize() >= w)
                {
                    computer[cm1].merge(computer[cm2]);
                    int max = computer[cm1].fakepop().p;
                    cout<<"The largest priority number is now "<<max<<" on "<<cm1<<"."<<endl;
                    
                }else
                {
                    cout<<"Merging request failed."<<endl;
                }
                
            }
        else if(input == "execute")
            {
                cin>>cm;
                
                vector<int> ans;
               int max = computer[cm].fakepop().p;
                
                int id = computer[cm].pop().id;
                ans.push_back(id);
          
                while(computer[cm].hsize() > 0 && computer[cm].fakepop().p == max)
                {
                   
                    id = computer[cm].pop().id;
                    ans.push_back(id);
                }
               
                sort(ans.begin(),ans.end());
                for(int i = 0; i < ans.size();i++)
                {
                    cout <<"Computer "<<cm<<" executed task "<<ans[i]<<"."<<endl;
                }
                
            }
    }
    
    //BinomialHeap<int> test;
    
    delete computer;
    
    
    
    
   
}
