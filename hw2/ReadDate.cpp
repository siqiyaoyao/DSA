///
//  ReadDate.cpp
//  bigdata1
//
//  Created by siqiyaoyao on 15/4/11.
//  Copyright (c) 2015年 siqiyaoyao. All rights reserved.
//
#include <algorithm>
#include "ReadDate.h"
#include <sstream>
/*
 multimap<size_t,data> MapUser; //size_t无符号整数
 std::multimap<size_t,data>::iterator itu;
 multimap<size_t,AdData>MapAd;
 using namespace std;
 */
void Read_Data(multimap<size_t,data> &MapUser,multimap<size_t,data> &MapAd,string strFileAddress)
{    // ----------------------open file-----------------------------
    
    FILE *fp;
    const char* address = strFileAddress.c_str();
    fp = fopen(address,"r");    if (fp == NULL) {
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
        data adtemp;
        vector<data> UserBase;
        size_t UserIndex  = 0;
        size_t AdIndex = 0;
        
        
        
        temp = atoi(p[11]);
        tempdata.UserID = atoi(p[11]);
        tempdata.Impression = atoi(p[1]);
        tempdata.AdID=atoi(p[3]);
        tempdata.Click=atoi(p[0]);
        tempdata.Depth=atoi(p[5]);
        
        tempdata.Position=atoi(p[6]);
        tempdata.QueryID=atoi(p[7]);
        
        
        tempdata.AdvertiserID = atoi(p[4]);
        tempdata.DescriptionID = atoi(p[10]);
        tempdata.KeywordID = atoi(p[8]);
        tempdata.TitleID = atoi(p[9]);
        tempdata.DisplayURL = p[2];
        
        UserBase.push_back(tempdata);
        
        
        
        
        MapAd.insert(std::multimap<size_t,data>::value_type(tempdata.AdID,UserBase[AdIndex]));
        AdIndex++;
        
        
        MapUser.insert(std::multimap<size_t,data>::value_type(temp,UserBase[UserIndex]));
        UserIndex++;
        p.clear();
        
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

//-------------------------- get command -----------------------
void getmm(multimap<size_t,data> MapUser, vector<size_t> GetData)
{
    cout << "********************" << endl;
    // multimap<size_t,data>::iterator it;
    int SumClick = 0;
    int SumImpression = 0;
    /*
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
     
     SumClick = SumClick+it->second.Click;
     SumImpression = SumImpression + it->second.Impression;
     
     }
     }
     }
     */
    pair<multimap<size_t,data>::iterator, multimap<size_t,data>::iterator> position;
    position = MapUser.equal_range(GetData.at(0));
    while (position.first != position.second)
    {
        if (position.first->second.AdID == GetData.at(1) && position.first->second.QueryID == GetData.at(2)
            && position.first->second.Position == GetData.at(3) && position.first->second.Depth == GetData.at(4))
        {
            
            SumClick = SumClick+position.first->second.Click;
            SumImpression = SumImpression + position.first->second.Impression;
            
        }
        
        position.first++;
    }
    
    cout << SumClick<<" "<< SumImpression<< endl;
    cout << "********************" << endl;
}

void GetCommand(vector<size_t>& GetData, string command,multimap<size_t,data> &MapUser)
{
    for(int i = 0; i < 5; i++){
        cin >> command;
        GetData.push_back(atoi(command.c_str()));
        
    }
    
    getmm(MapUser,GetData);
}


//--------------------------click command -----------------------
bool comparer(data& a , data&b)
{
    // 按ad升序 + query升序排列
    if(a.AdID == b.AdID)
        return (a.QueryID < b.QueryID);
    else
        return (a.AdID < b.AdID);
}

void CallClick(multimap<size_t,data> MapUser,string command)
{
    cout << "********************" << endl;
    //multimap<size_t,data>::iterator it;
    vector<data>SortData;
    size_t User =atoi(command.c_str());
    /*
     for ( it = MapUser.begin();it!= MapUser.end();it++ )
     {
     if (it->first == User)
     {
     
     if (it->second.Click > 0)//just test should be 0!!!!!
     {
     SortData.push_back(it->second);
     }
     }
     }
     */
    pair<multimap<size_t,data>::iterator, multimap<size_t,data>::iterator> position;
    position = MapUser.equal_range(User);
    while (position.first != position.second)
    {
        if (position.first->second.Click > 0)
        {
            
            SortData.push_back(position.first->second);
            
        }
        
        position.first++;
    }
    sort(SortData.begin(),SortData.end(),comparer);
    
    vector<data>::iterator iter;
    for(iter = SortData.begin(); iter != SortData.end(); ++iter)
    {
        if ((iter+1) != SortData.end() && (*(iter+1)).AdID ==(*iter).AdID && (*(iter+1)).QueryID == (*iter).QueryID)
        {
            continue;
        }
        cout << (*iter).AdID << " " << (*iter).QueryID << endl;
    }
    
    cout << "********************" << endl;
}

void ClickedCommand(string& ClickedData, string command,multimap<size_t,data> MapUser)
{
    cin >> command;
    ClickedData = command;
    CallClick(MapUser,command);
}

//--------------------------impressed command -----------------------
bool comparerim(data& a , data&b)
{
    // 按ad升序 + query升序排列
    if(a.AdID == b.AdID)
        return (a.AdvertiserID < b.AdvertiserID);
    else
        return (a.AdID < b.AdID);
}
void show_svec(vector<string> &vec){
    vector<string>::iterator m;
    for (m = vec.begin(); m != vec.end(); m++) {
        cout<<*m;
    }
}
void CallIm(vector<string>& ImpressedData,multimap<size_t,data> MapUser)
{
    cout << "********************" << endl;
    vector<data> User1Data;
    vector<data> User2Data;
    vector<unsigned> SameId;
    size_t user1 = atoi(ImpressedData.at(0).c_str());
    size_t user2 = atoi(ImpressedData.at(1).c_str());
    
    //-----get user1 data----------
    pair<multimap<size_t,data>::iterator, multimap<size_t,data>::iterator> position;
    position = MapUser.equal_range(user1);
    while (position.first != position.second)
    {
        User1Data.push_back(position.first->second);
        //cout <<position.first->first<<" "<< position.first->second.AdID<<endl;// debug
        position.first++;
    }
    //-----get user2 data-----------
    pair<multimap<size_t,data>::iterator, multimap<size_t,data>::iterator> position2;
    position2 = MapUser.equal_range(user2);
    while (position2.first != position2.second)
    {
        User2Data.push_back(position2.first->second);
        // cout << position2.first->first<<" "<<position2.first->second.AdID<<endl;// debug
        position2.first++;
    }
    
    //-----sort user1 & user2----------
    sort(User1Data.begin(),User1Data.end(),comparerim);
    sort(User2Data.begin(),User2Data.end(),comparerim);
    //-----get same data---------------
    int i = 0, j = 0;
    while(i < User1Data.size() && j < User2Data.size())
    {
        if(User1Data.at(i).AdID < User2Data.at(j).AdID)
        {
            i++;
        }else if(User1Data.at(i).AdID > User2Data.at(j).AdID)
        {
            j++;
        }else if(User1Data.at(i).AdID == User2Data.at(j).AdID)
        {
            if(User1Data.at(i).Impression > 0 && User2Data.at(j).Impression > 0)
            {
                SameId.push_back(User1Data.at(i).AdID);
                //SameId.push_back(User2Data.at(j));
                //cout <<"same "<< User1Data.at(i).AdID<<endl;//debug
            }
            i++;
            j++;
        }
    }
    vector<unsigned>::iterator deal;
    sort(SameId.begin(),SameId.end());
    deal = unique(SameId.begin(),SameId.end());
    SameId.erase(deal,SameId.end());
    
    vector<string> output;
    vector<string>::iterator eraseit;
    stringstream out;
    
    for(int k = 0; k < SameId.size();k++)
    {
        output.erase(output.begin(), output.end());
        cout << SameId[k] << endl;
        output.push_back(out.str());
        for (i = 0; i < User1Data.size();i++)
        {
            if(User1Data[i].AdID == SameId[k])
            {
                out<<"\t"<< User1Data.at(i).DisplayURL <<" "<<User1Data.at(i).AdvertiserID<<" "<<User1Data.at(i).KeywordID<<" "
                << User1Data.at(i).TitleID <<" "<< User1Data.at(i).DescriptionID << endl;
                output.push_back(out.str());
                out.str("");
            }
        }
        for (j = 0; j < User2Data.size();j++)
        {
            if(User2Data[j].AdID == SameId[k])
            {
                out<<"\t"<< User2Data.at(j).DisplayURL <<" "<<User2Data.at(j).AdvertiserID<<" "
                <<User2Data.at(j).KeywordID<<" "<< User2Data.at(j).TitleID <<" "<< User2Data.at(j).DescriptionID << endl;
                output.push_back(out.str());
                out.str("");
            }
        }
        sort(output.begin(),output.end());
        eraseit = unique(output.begin(),output.end());
        output.erase(eraseit,output.end());
        show_svec(output);
    }
    
    cout << "********************" << endl;
}

void ImpressedCommand(vector<string>& ImpressedData, string command,multimap<size_t,data> MapUser)
{
    for(int i = 0; i < 2; i++)
    {
        cin >> command;
        ImpressedData.push_back(command);
        
    }
    CallIm(ImpressedData,MapUser);
    
    
}

//--------------------------profit command -----------------------
bool comparerAd(data& a , data&b)
{
    // 按ad升序 + query升序排列
    
    return (a.UserID < b.UserID);
}
void CallProfit(vector<string> ProfitData,multimap<size_t,data> &MapAd)
{
    cout << "********************" << endl;
    size_t InputAd = atoi(ProfitData.at(0).c_str());
    float Inputrate = atof(ProfitData.at(1).c_str());
    int SumClick = 0;
    int SumIm = 0;
    // float sum = 0;
    float ddd = 0;
    vector<data> SortData;
    pair<multimap<size_t,data>::iterator, multimap<size_t,data>::iterator> position;
    position = MapAd.equal_range(InputAd);
    while (position.first != position.second)
    {
        SortData.push_back(position.first->second);
        // cout <<position.first->first<<" "<< position.first->second.AdID<<endl;// debug
        position.first++;
    }
    sort(SortData.begin(),SortData.end(),comparerAd);
    /*
     for(int k = 0; k < SortData.size();k++)
     {
     if(k >0 && SortData.at(k).UserID == SortData.at(k-1).UserID )
     {
     SumClick = SumClick + SortData.at(k).Click;
     SumIm = SumIm + SortData.at(k).Impression;
     
     
     }
     else
     {
     if (sumclick/sumim >= Inputrate)
     {
     cout << SortData.at(k).UserID<<endl;
     
     }
     else if ((SortData.at(k).Click / SortData.at(k).Impression) >= Inputrate)
     {
     cout << SortData.at(k).UserID<<endl;
     }
     }
     }
     */
    
    SumClick = SortData.at(0).Click;
    SumIm = SortData.at(0).Impression;
    //cout << Inputrate << endl;
    for(int k = 1; k < SortData.size();k++)
    {
        if(SortData.at(k).UserID == SortData.at(k-1).UserID )
        {
            SumClick = SumClick + SortData.at(k).Click;
            SumIm = SumIm + SortData.at(k).Impression;
        }
        else
        {
            if (SumIm == 0)
            {
                if (SumClick == 0)
                {
                    ddd = 0;
                }
                else
                {
                    ddd = Inputrate;
                }
            }
            else
            {
                // cout << k <<" "<<SumClick <<SumIm << endl;
                ddd = float(SumClick) / float(SumIm);
                // cout << ddd<< endl;
            }
            
            
            if (ddd >= Inputrate)
            {
                //cout << Inputrate <<endl;
                cout << SortData.at(k-1).UserID << endl;
                
            }
            SumClick = SortData.at(k).Click;
            SumIm = SortData.at(k).Impression;
        }
    }
    
    if (SumIm == 0)
    {
        if (SumClick == 0)
        {
            ddd = 0;
        }
        else
        {
            ddd = Inputrate;
        }
    }
    else
    {
        // cout << "k = 0 "<<SumClick<<"" <<SumIm << endl;
        ddd = float(SumClick) / float(SumIm);
    }
    
    if (ddd >= Inputrate)
    {
        cout << SortData.at(SortData.size()-1).UserID << endl;
    }
    
    
    cout << "********************" << endl;
}

void ProfitCommand(vector<string>& ProfitData, string command,multimap<size_t,data> &MapAd)
{
    for(int i = 0; i < 2; i++)
    {
        cin >> command;
        ProfitData.push_back(command);
        
    }
    
    CallProfit(ProfitData,MapAd);
}


void ReadCommand( string &command,multimap<size_t,data> &MapUser,multimap<size_t,data> &MapAd)
{
    vector<size_t> GetData;
    vector<string> PrifitData;
    vector<string> ImpressedData;
    string ClickedData;
    while(command != "quit")
    {
        if (command == "get"){
            GetCommand(GetData,command,MapUser);
            
            //cout <<"get" <<GetData[0]<<GetData[1]<<GetData[2]<<GetData[3] << GetData[4] << endl;
            
        }
        
        if (command == "clicked")
        {
            ClickedCommand(ClickedData,command,MapUser);
            
            // cout <<"clicked" <<ClickedData << endl;
            
        }
        
        if (command == "profit")
        {
            ProfitCommand(PrifitData,command,MapAd);
            
            
            //cout <<"profit" <<PrifitData[0]<<PrifitData[1] << endl;
            
            
        }
        
        
        if (command == "impressed")
        {
            ImpressedCommand(ImpressedData,command,MapUser);
            
            // cout <<"impressed" <<ImpressedData[0]<<ImpressedData[1] << endl;
            
            
        }
        //
        
        
        cin >> command;
        
        
        
    }
    
}
