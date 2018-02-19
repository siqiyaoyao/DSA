//
//  main.cpp
//  bigdata2.0
//
//  Created by siqiyaoyao on 15/4/11.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <map>
#include "ReadDate.h"
//#include "command.h"
//#include "class.h"

using namespace std;





int main()
{
    // Read_Data();
    
    
    
    //-------------------insert the data-------------------
    
    //vector<data> UserId[23907634];
    multimap<size_t,data> MapUser; //size_t无符号整数
    std::multimap<size_t,data>::iterator itu;
    multimap<size_t,AdData>MapAd;
    Read_Data(MapUser,MapAd);
    
    //--------------------Read command--------------------
     
     string command;
     cin >> command;
     ReadCommand(command,MapUser,MapAd);
    
    
    
    
    
    
    
    
    
    return 0;
}
