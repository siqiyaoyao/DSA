//
//  ReadDate.cpp
//  bigdata1
//
//  Created by siqiyaoyao on 15/4/11.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//

#include "ReadDate.h"
/*
multimap<size_t,data> MapUser; //size_t无符号整数
std::multimap<size_t,data>::iterator itu;
multimap<size_t,AdData>MapAd;
using namespace std;
*/
void Read_Data(multimap<size_t,data> &MapUser,multimap<size_t,AdData> &MapAd)
{
    // ----------------------open file-----------------------------
    
    FILE *fp;
    fp = fopen("/Users/siqiyaoyao/ntu/dsa/home2/data/testdata.txt","r");
    if (fp == NULL) {
        cout << "can not open file" << endl;
    }
    
    // ----------------------read by line -----------------------------
    int size = 1024;
    char s[1024];
    while(fgets(s,size,fp) != NULL)
    {
        //fputs (s, stdout);
        
        int i = 0;
        char *ptr = NULL;
        char *ss = s;
        vector<char*>p;
        ptr = strtok(ss, "\t");
        
        
        while(ptr != NULL){
            //test.push_back(p);
            p.push_back(ptr);
            //cout << i << "=" << p[i] << endl;
            i++;
            ss = NULL;
            ptr = strtok(ss, "\t");
            
        }
        //cout <<0 << "=" << p[1]<< endl;
  
    // ----------------------insert the data -----------------------------
        
        unsigned long int temp = 0;
        data tempdata;
        AdData adtemp;
        vector<data> UserBase;
        vector<AdData>AdBase;
        size_t UserIndex  = 0;
        size_t AdIndex = 0;

    
        
        temp = atoi(p[11]);
        tempdata.Impression = atoi(p[1]);
        tempdata.AdID=atoi(p[3]);
        tempdata.Click=atoi(p[0]);
        tempdata.Depth=atoi(p[5]);
        
        tempdata.Position=atoi(p[6]);
        tempdata.QueryID=atoi(p[7]);
        UserBase.push_back(tempdata);
        MapUser.insert(std::multimap<size_t,data>::value_type(temp,UserBase[UserIndex]));
        UserIndex++;
        
        adtemp.AdvertiserID = atoi(p[4]);
        adtemp.DescriptionID = atoi(p[10]);
        adtemp.KeywordID = atoi(p[8]);
        adtemp.TitleID = atoi(p[9]);
        adtemp.DisplayURL = atoi(p[2]);
        AdBase.push_back(adtemp);
        MapAd.insert(std::multimap<size_t,AdData>::value_type(tempdata.AdID,AdBase[AdIndex]));
        AdIndex++;
        
        
       // delete *p;
        
        //cout << "Read from file: " << s << endl;
        
        i = 0;
        
    }

    //cout << test[11] << endl;
    //for (int j = 0; j < 1000; j++){
    //  cout << data.AdID[j] << endl;
    //}
    
    //cout<< UserBase[2].AdID<<endl;
    
    
    fclose(fp);
}

//--------------------------deal with data---------------------

//--------------------------get command -----------------------
void GetCommand(vector<size_t>& GetData, string command,multimap<size_t,data> &MapUser,multimap<size_t,AdData> &MapAd)
{
    for(int i = 0; i < 5; i++){
        cin >> command;
        GetData.push_back(atoi(command.c_str()));
        
    }
    
    get(MapUser,MapAd,GetData);
}

void get(multimap<size_t,data> &MapUser,multimap<size_t,AdData> &MapAd, vector<size_t> GetData)
{
    cout << "********************" << endl;
    multimap<size_t,data>::iterator it;
    for ( it = MapUser.begin();it!= MapUser.end();it++ )
    {
        if (it->first == GetData.at(0))
        {
            //cout << "MapUser.find(55984)：";
            //cout << "(" << it->first << "," << it->second.AdID<< ")"
            //<< endl;
            if (it->second.AdID == GetData.at(1) && it->second.QueryID == GetData.at(2)
                && it->second.Position == GetData.at(3) && it->second.Depth == GetData.at(4))
            {
                
                cout << it->second.Click <<" "<< it->second.Impression << endl;
                
            }
        }
    }
    cout << "********************" << endl;
}


void ReadCommand( string &command,multimap<size_t,data> &MapUser,multimap<size_t,AdData> &MapAd)
{
    vector<size_t> GetData;
    vector<string> PrifitData;
    vector<string> ImpressedData;
    string ClickedData;
    while(command != "quit")
    {
        if (command == "get"){
            GetCommand(GetData,command,MapUser,MapAd);
            //cout <<"get" <<GetData[0]<<GetData[1]<<GetData[2]<<GetData[3] << GetData[4] << endl;
            
        }
        /*
        if (command == "clicked")
        {
            ClickedCommand(ClickedData,command);
            cout <<"clicked" <<ClickedData << endl;
            
        }
        if (command == "profit")
        {
            ProfitCommand(PrifitData,command);
            
            cout <<"profit" <<PrifitData[0]<<PrifitData[1] << endl;
            
            
        }
        if (command == "impressed")
        {
            ImpressedCommand(ImpressedData,command);
            cout <<"impressed" <<ImpressedData[0]<<ImpressedData[1] << endl;
            
            
        }
        cin >> command;
        */
        
        
        
        
    }
}
