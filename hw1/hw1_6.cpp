//
//  main.cpp
//  Eulid
//
//  Created by siqiyaoyao on 15/3/11.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//

#include <iostream>
#include <stdio.h>

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}
int min(int a, int b){

    int n = a;
    if (a > b)
        n = b;
    return n;
}

int max(int a, int b){
    int n = b;
    if (a > b)
        n = a;
    return n;
    
}
int  Search(int a, int b, int& counts){
    

    int n = min(a,b);

    for (int i = n;i > 0; i--) {
        if ((a % i == 0 )& (b % i == 0)){
            counts++;
            return i;
        }
         counts++;
    }
    return 0;
}
void prisearch(int a, int b){
    int counts = 0;
    int gcd = Search(a, b,counts);

    printf("Case (%d, %d): GCD-By-Reverse-Search = %d, taking %d iterations\n",a,b,gcd,counts);
    
}


int  Filter(int a, int b, int& countf){
    int n = min(a,b);
    
    for (int i = 2; i <= n ;i++) {
        countf++;
        if (a % i == 0 & b % i == 0){
            
            return (i * Filter(a / i, b / i, countf));
        }
        
    }
    return 1;
}
    
void  priFilter(int a, int b){
    int countf = 0;
    int gcd = 0;
    gcd = Filter(a,b,countf);
    printf("Case (%d, %d): GCD-By-Filter = %d, taking %d iterations\n",a,b,gcd,countf);
    
}

int  Filterfaster(int a, int b, int& s,int& countff){
    int n = min(a,b);
    
    for (int i = s; i <= n ;i++) {
        countff++;
        if (a % i == 0 & b % i == 0){
            
            return (i * Filterfaster(a / i, b / i, i,countff));
        }
        
    }
    return 1;
}
/*int Filterfaster_o(int a, int b,int& countff){
   
    return Filterfaster (a, b,  2, countff);
    
}*/

void  priFilterfaster(int a, int b){
    int countff = 0;
    int gcd = 0;
    int i = 2;
    gcd = Filterfaster(a,b,i,countff);
    printf("Case (%d, %d): GCD-By-Filter-Faster = %d, taking %d iterations\n",a,b,gcd,countff);
    
}

void Binary (int a, int b){
    int n = min(a,b);
    int m = max(a,b);
    int ans = 1;
    int countb = 0;
    int gcd = 0;
    
    while (n != 0 & m != 0) {
        if (n % 2 == 0 && m % 2 ==0){
            ans = ans * 2;
            n = n / 2;
            m = m / 2;
        }else if (n % 2 == 0 & m % 2 != 0){
            n = n / 2;
        }else if (n % 2 != 0 & m % 2 == 0){
            m = m / 2;
        }
        if (n > m){
            swap(n,m);
        }
        
        m = m - n;
        countb++;

    }
    gcd = n * ans;
    printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n",a,b,gcd,countb);
    
    
}
void Euclide (int a, int b){
    int n = min(a,b);
    int m = max(a,b);
    int temp = 0;
    int counte = 0;
    while (m % n != 0) {
        temp = n;
        n = m % n;
        m = temp;
        counte++;
    }
    printf("Case (%d, %d): GCD-By-Euclide = %d, taking %d iterations \n",a,b,n,counte);
    
}


void runall(int a, int b){
    prisearch(a, b);
    priFilter(a,b);
    priFilterfaster(a,b);
    Binary(a,b);
    Euclide(a,b);
    
}

int main() {
    std::vector<std::pair<int, int> > vecInputList;
    while(1){
        int a, b;
        cin >> a;
        if( a == 0){
            break;
        }
        cin >> b;
        
        vecInputList.push_back(std::pair<int, int>(a, b));
    }
    for(size_t i = 0 ; i < vecInputList.size(); ++i){
        run(vecInputList[i].first, vecInputList[i].second);
    }
    return 0;
}
