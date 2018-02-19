//
//  DealData.cpp
//  bigdata2.0
//
//  Created by siqiyaoyao on 15/4/11.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
// [UserID][AdID][QueryID][Position][Depth]

#include "ReadDate.h"

/*

void get(multimap<size_t,data> &MapUser,multimap<size_t,AdData> &MapAd, vector<size_t> GetData)
{
    multimap<size_t,data>::iterator it;
    for ( it = MapUser.begin();it!= MapUser.end();it++ )
    {
        if (it->first == GetData.at(0))
        {
            //cout << "MapUser.find(55984)：";
            //cout << "(" << it->first << "," << it->second.AdID<< ")"
            //<< endl;
            if (it->second.AdID == GetData.at(1) || it->second.QueryID == GetData.at(2)
                || it->second.Position == GetData.at(3) || it->second.Depth == GetData.at(4))
            {
                cout << "********************" << endl;
                cout << it->second.Click <<""<< it->second.Impression << endl;
                cout << "********************" << endl;
            }
        }
    }
}
*/