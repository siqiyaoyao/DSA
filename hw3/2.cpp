//
//  main.cpp
//  home3.1
//
//  Created by siqiyaoyao on 15/4/23.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int pre(char a) //操作符优先级比较
{
    int prepority = 0;
    
    if(a == ',' )
        prepority = 0;
    else if(a == '+' || a == '-')
        prepority = 1;
    else if(a == '*' || a == '/' )
        prepority = 2;
    else if (a == '#'|| a=='&')
        prepority = 3;
    else if (a == 's'||a == 'c'||a == 'e'||a == 'l'||a == 'p'|| a == 'f'||a == 'q')
        prepority = 4;
    
    
    return prepority;
}
void MINUS(char *p, int &k)
{
    if(!(p[k-1] == ')' || (p[k-1] >= '0' && p[k-1] <= '9')))
    {
        if(p[k]=='-')p[k]= '#';
        else if(p[k] == '+') p[k] = '$';
    }
}
void SINGLE(char *p , int &k)
{
    if (p[k+1] == 'q')
    {
        k=k+3;
        p[k]='q';
    }else
    {
        k=k+2;
        p[k]='s';
    }


}
void culculate( stack<double> &value, char temp)
{
    double x = 0, y = 0,result = 0;
    
    
    
    if( temp == '#' || temp == 'c'|| temp == 'e'|| temp == 'l'|| temp == 'q'|| temp == 'f'||temp =='s'||temp =='$'||temp == ',')
    {
        
        x = value.top();
        value.pop();
        switch (temp) {
            case ',':
                result = x;
                value.push(result);
                break;
            case '$':
                result = x;
                value.push(result);
                break;

            case '#':
                result = -x;
                value.push(result);
                break;
                
            case 'c':
                result = cos(x);
                value.push(result);
                break;
                
            case 'e':
                result = exp(x);
                value.push(result);
                break;
            case 'l':
                result = log(x);
                value.push(result);
                break;
            case 'q':
                result = sqrt(x);
                value.push(result);
                break;
            case 'f':
                result = fabs(x);
                value.push(result);
                break;
            case 's':
                result = sin(x);
                value.push(result);
                break;
        }
    }else
    {
        x = value.top();
        value.pop();
        y = value.top();
        value.pop();
        
        switch (temp) {
            case '+':
                result = x+y;
                value.push(result);
                break;
                
            case '-':
                result = y-x;
                value.push(result);
                break;
                
            case '*':
                result = y * x;
                value.push(result);
                break;
            case '/':
                result = y / x;
                value.push(result);
                break;
            case 'p':
                result = pow(y, x);
                value.push(result);
                break;
           

        }

    }
    //cout<<temp<<endl;
    //cout<<value.top()<<endl;
    
}
void skip(char *p , int &k)
{
    switch (p[k])
    {
        case 'c':
            k=k+2;
            p[k]='c';
            break;
        case 'e':
            k=k+2;
            p[k]='e';
            break;
        case 'l':
            k=k+2;
            p[k]='l';
            break;
        case 'p':
            k=k+2;
            p[k]='p';
            break;
        case 'f':
            k=k+3;
            p[k]='f';
            break;
    }
}

int main()
{
    char Mid[1000000];
    stack<char> ope;
    stack<double> value;
    vector<string> ans;//后缀表达式
    char temp[3];
    string token;
    double valueA=0;
    
    
    
    
    while (fgets(Mid,1000000,stdin)!=NULL)
    {
//------------------初始化------------------
        unsigned long count = 1;
        while(!ope.empty())
            ope.pop();
        ans.clear();
   
//------------------remove the white space------------------
        unsigned long len = strlen(Mid)-1;
        char *p = (char *)malloc((len+1)*sizeof(char));
        int i = 0,j = 0;
        while(i < len)
        {
            if(Mid[i]==' ')
            {
                i++;
                continue;
            }
            p[j++] = Mid[i++];
        }
        p[j] = '\0';
        j = 0;
        len = strlen(p);
       // cout << p << endl;
 //------------------deal with data------------------
        int k = 0;
        int begin = 0;
        for(k = 0; k < len; k++)
        {
            cout << "Step "<< count<<endl;
            count++;
            if((p[k] >= '0' && p[k] <= '9') || p[k] == '.') //操作数直接存入ans
            {
                begin = k;
                while((p[k] >= '0' && p[k] <= '9')|| p[k] == '.')
                {
                    k++;
                }
                char *opd = (char *)malloc(k-begin+1);
                strncpy(opd,p+begin,k-begin);
                opd[k-begin]='\0';
                token=opd;
                ans.push_back(token);
                valueA = atof(opd);
                cout <<"Get the number "<< valueA << endl;//outout
                //printf("RESULT: %.6f\n", valueA);
                value.push(valueA);
                free(opd);
                k--;
                
    
            }
                //ans.push_back(p[k]);
            else if(p[k] == '(') //左括号入栈
            {
                ope.push(p[k]);
                cout <<"Push ( into stack"<<endl;//output
            //cout << ope.top();//
            }
            else if(p[k] == ')') //右括号，将匹配的左括号内容存入ans,左括号出栈
            {
                cout <<"Get ) and output the operators in (): ";
                while (ope.top() != '(')
                {
                    temp[0] = ope.top();
                    //temp[1] = '\n';
                    token = temp;
                     cout << token <<" ";;//output
                    //cout << token << endl;
                    ans.push_back(token);
                    culculate(value,temp[0]);
                    
                    ope.pop();
                    
                }
                ope.pop(); //左括号出栈
                cout <<"pop ( "<<endl;//output
            }
            else
            {
                if(p[k] == '-' ||p[k] == '+')
                {
                    MINUS(p,k);
                }
                if(p[k] == 's')
                {
                    SINGLE(p,k);
                }
                if(p[k] == 'c'||p[k] == 'e'||p[k] == 'l'||p[k] == 'p'|| p[k] == 'q'||p[k] == 'f')
                {
                    skip(p,k);
                }
             
                if(ope.empty())
                {
                    ope.push(p[k]);
                    cout <<"If stack is empty , push operator in stack: "<< p[k]<<endl;//output
                }
                    
                else if(pre(p[k]) > pre(ope.top())) //优先级大于栈顶元素则入栈
                {
                        ope.push(p[k]);
                    cout <<"Push the operators with higher precedence into stack: "<< p[k]<<endl;//output
                }
                else if (pre(p[k]) <= pre(ope.top())) //小于栈顶元素
                {
                    if (p[k] == '#' ||p[k] == '$')
                    {
                        ope.push(p[k]);
                         cout <<"Push the unary operators with some precedence into stack: "<< p[k]<<endl;//output
                    }
                    else
                    {
                    cout <<"Pop the operators with higher precedence form stack to output: ";
                    while(pre(p[k]) <= pre(ope.top()))
                        {
                        if(ope.top()=='(')break;
                        temp[0] = ope.top();
                    //temp[1] = '\n';
                        token = temp;
                        cout << token<<" ";
                        ans.push_back(token);
                        //cout<<temp<<endl;//
                        culculate(value,temp[0]);
                    //ans.push_back(ope.top());
                        ope.pop();
                        if (ope.empty())
                            break;
                        }
                    cout <<"then push the current operator to stack: "<< p[k]<<endl;//output

                    ope.push(p[k]);
                    }
                }
            }
            int index = 0;
            cout << "Current output: ";
            for(index = 0; index < ans.size();index++)
            {
                
                cout<< ans[index]<<" ";
            }
            cout << endl;

           
        }
        
     
        cout << "Step "<< count<<endl;
        cout <<"Output the remind operators from stack: ";

        
        while(!ope.empty()) //其余操作符存入后缀表达式中
        {
            
           temp[0] = ope.top();
           //temp[1] = '\n';
           token = temp;
            ans.push_back(token);
            //ans.push_back(ope.top());
            culculate(value,temp[0]);
            cout<< temp<<" ";//output
            ope.pop();
        }
        //cout << ans.size()<<endl;
        cout << endl;

        cout << "Postfix Exp: ";
        for(i = 0; i < ans.size();i++)
        {
            if (ans[i] == "s") cout << "sin" << " ";
            else if (ans[i] == "c") cout << "cos" << " ";
            else if (ans[i] == ",") cout << "";
            else if (ans[i] == "e") cout << "exp" << " ";
            else if (ans[i] == "l") cout << "log" << " ";
            else if (ans[i] == "p") cout << "pow" << " ";
            else if (ans[i] == "q") cout << "sqrt" << " ";
            else if (ans[i] == "f") cout << "fabs" << " ";
            else if (ans[i] == "#") cout << "-" << " ";
            else if (ans[i] == "$") cout << "+" << " ";
            
            else
            {
                valueA=atof(ans[i].c_str());
                if(valueA != 0)printf("%.6f ",valueA );
                else cout<<ans[i]<<" ";
            }
        }
        cout <<endl;
        printf("RESULT: %.6f\n", value.top());
       
       
        
        
        
        free(p);

        
       
        //cout<< Mid << endl;
    }
    
    
    
    
    
    
    return 0;
}