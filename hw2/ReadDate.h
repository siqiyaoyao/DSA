//
//  head.h
//  debug
//
//  Created by siqiyaoyao on 15/4/15.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//

#ifndef __debug__head__
#define __debug__head__

#include <stdio.h>
#ifndef __bigdata1__ReadDate__
#define __bigdata1__ReadDate__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <map>
//#include "command.h"
//#include "class.h"
using namespace std;
#endif /* defined(__bigdata1__ReadDate__) */

class data
{
public:
    unsigned UserID;
    unsigned   AdID;
    int  Depth;
    int  Position;
    unsigned   QueryID;
    int Click;
    int Impression;
    unsigned   AdvertiserID;
    unsigned   KeywordID;
    unsigned   TitleID;
    unsigned   DescriptionID;
    string  DisplayURL;
    
    
    
    
};


void Read_Data(multimap<size_t,data> &MapUser,multimap<size_t,data> &MapAd,string strFileAddress);

void ReadCommand( string &command,multimap<size_t,data> &MapUser,multimap<size_t,data> &MapAd);
void ImpressedCommand(vector<size_t>& ImpressedData, string command);
void ProfitCommand(vector<size_t>& ProfitData, string command,multimap<size_t,data> &MapAd);


// deal with data
void get(multimap<size_t,data> &MapUser, vector<size_t> GetData);
void CallClick(multimap<size_t,data> MapUser,string command);

#endif /* defined(__debug__head__) */
