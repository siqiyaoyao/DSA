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
using namespace std;
int pre(char a) //操作符优先级比较
{
    int prepority = 0;
    
    if(a == 'q')
        prepority = 0;
    else if (a == 'w')
        prepority = 1;
    else if (a == '|')
        prepority = 2;
    else if (a == '^')
        prepority = 3;
    else if (a == '&')
        prepority = 4;
    else if(a == 'e' || a == 'r')
        prepority = 5;
    else if(a == '+' || a == '-')
        prepority = 6;
    else if(a == '*' || a == '/' || a == '%')
        prepority = 7;
    else if (a == '#' || a == '!' || a == '~'||a == '$')
        prepority = 8;
    
    
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
    if (p[k] == '|')
    {
        if (p[k+1] == '|')
        {
            k++;
            p[k] = 'q';
        }
        
    }
    if (p[k] == '&')
    {
        if (p[k+1] == '&')
        {
            k++;
            p[k] = 'w';
        }
        
    }
    if (p[k] == '<')
    {
        if (p[k+1] == '<')
        {
            k++;
            p[k] = 'e';
        }
        
    }
    if (p[k] == '>')
    {
        if (p[k+1] == '>')
        {
            k++;
            p[k] = 'r';
        }
        
    }
    
    
    
}
void culculate( stack<long int> &value, char temp)
{
    long int x = 0, y = 0,result = 0;
    
    
    
    if( temp == '#' || temp == '!' || temp == '~'|| temp == '$')
    {
        
        x = value.top();
        value.pop();
        switch (temp) {
            case '$':
                result = x;
                value.push(result);
                break;
            case '#':
                result = -x;
                value.push(result);
                break;
                
            case '!':
                if(x == 0) result = 1;
                else result = 0;
                value.push(result);
                break;
                
            case '~':
                result = ~x;
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
            case '%':
                result = y % x;
                value.push(result);
                break;
            case '&':
                result = y & x;
                value.push(result);
                break;
            case '|':
                result = y | x;
                value.push(result);
                break;
            case '^':
                result = y ^ x;
                value.push(result);
                break;
            case 'e':
                result = y << x;
                value.push(result);
                break;
            case 'r':
                result = y >> x;
                value.push(result);
                break;
            case 'q':
                if(x != 0 || y != 0) result = 1;
                else result = 0;
                
                value.push(result);
                break;
            case 'w':
                if(x != 0 && y != 0) result = 1;
                else result = 0;
                
                value.push(result);
                break;
                
                
                
                
                
                
                
                
                
        }
        
    }
    
    
}

int main()
{
    char Mid[1000000];
    stack<char> ope;
    stack<long int> value;
    vector<string> ans;//后缀表达式
    char temp[3];
    string token;
    long int valueA=0;
    
    
    
    
     while (fgets(Mid,1000000,stdin)!=NULL)
    {
        unsigned long count = 1;
        //------------------初始化------------------
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
            if(p[k] >= '0' && p[k] <= '9') //操作数直接存入ans
            {
                begin = k;
                while(p[k] >= '0' && p[k] <= '9')
                {
                    k++;
                }
                char *opd = (char *)malloc(k-begin+1);
                strncpy(opd,p+begin,k-begin);
                opd[k-begin]='\0';
                token=opd;
                ans.push_back(token);
                valueA = atoi(opd);
                cout <<"Get the number "<< valueA << endl;//output
                value.push(valueA);
                free(opd);
                k--;
                
                
            }
            //ans.push_back(p[k]);
            else if(p[k] == '(') //左括号入栈
            {
                ope.push(p[k]);
                cout <<"Push ( into stack"<<endl;//output
            }
            else if(p[k] == ')') //右括号，将匹配的左括号内容存入ans,左括号出栈
            {
                cout <<"Get ) and output the operators in (): ";
                while (ope.top() != '(')
                {
                    temp[0] = ope.top();
                    //temp[1] = '\n';
                    token = temp;
                    //cout << token << endl;
                    ans.push_back(token);
                    cout << token <<" ";;//output
                    culculate(value,temp[0]);
                    
                    ope.pop();
                    
                }
                cout<< endl;
                ope.pop(); //左括号出栈
                cout <<"pop ( "<<endl;//output
                
            }
            else
            {
                if(p[k] == '-'||p[k] == '+')
                {
                    MINUS(p,k);
                }
                if(p[k] == '|' || p[k] == '&' || p[k] == '<' || p[k] == '>')
                {
                    SINGLE(p,k);
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
                    if (p[k] == '#' || p[k] == '!' || p[k] == '~'||p[k] == '$')
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
                        ans.push_back(token);
                           cout << token<<" ";//output
                        culculate(value,temp[0]);
                        //ans.push_back(ope.top());
                        ope.pop();
                        if (ope.empty())
                            break;
                        }
                        cout<<endl;
                        
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
        cout << endl;
        cout << "Postfix Exp: ";
        for(i = 0; i < ans.size();i++)
        {
            if (ans[i] == "q") cout << "||" << " ";
            else if (ans[i] == "w") cout << "&&" << " ";
            else if (ans[i] == "#") cout << "-" << " ";
            else if (ans[i] == "$") cout << "+" << " ";
            else if (ans[i] == "e") cout << "<<" << " ";
            else if (ans[i] == "r") cout << ">>" << " ";
            else cout << ans[i] << " ";
            
        }
        cout <<endl;
        cout<<"RESULT: " << value.top()<<endl;
        
        
        
        
        
        free(p);
        
        
        
        //cout<< Mid << endl;
    }
    
    
    
    
    
    
    return 0;
}