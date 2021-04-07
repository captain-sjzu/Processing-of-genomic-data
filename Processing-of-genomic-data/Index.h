//
// Created by WZZ on 2021/4/1.
//

#ifndef PROJECTMAIN_INDEX_H
#define PROJECTMAIN_INDEX_H
#include <unordered_map>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;


class  Index
{
private:
    static unordered_map<char,vector<unsigned int>> hash_map;
public:

    static int Traverse()
    {
        cout<<"The index had be implemented!";
        return 1;
    }
    static unordered_map<char,vector<unsigned int>> GetIndex()
    {

        cout<<"The index had backed to the main program";
        return  hash_map;
    }
};

class GeneralIndex: public Index{
private:
    unordered_map<char, vector <int>> hash_map;
public:

    unordered_map<char,vector<int>> GetIndex(char ch,int a)
    {
        return hash_map;
    }

    int Traverse()
    {
        std::ifstream file("../data/Align2.txt");
        if(!file.is_open())
        {
            cout<<"Error opening file!";
            exit(001);
        }
        int j=0;
        while (!file.eof())
        {
            char buffer[1005];
            file.getline(buffer,1005);
            string string1=buffer;
            for(int i=0;i<string1.length();i++)
            {
                hash_map[string1[i]].push_back(i+j*1000);
            }
            j++;
        }
        return  hash_map['A'].size()+hash_map['C'].size()+hash_map['G'].size()+hash_map['T'].size();
    }

    void Getlocation(string str)
    {
        char ch=str[0];
        vector<vector<int>> back;
        clock_t start=clock();
        for(int i=0;i<hash_map[ch].size();++i)
        {
            int key=hash_map[ch][i]+1;
            bool flag;
            for(int j=1;j<str.size();j++)
            {

                flag= false;
               for(int k=0;k<hash_map[str[j]].size();++k)
                   if(hash_map[str[j]][k]==key)
                       flag= true;
                if(!flag)
                    break;
                key++;
            };
            if(flag)
                back.push_back({hash_map[ch][i],key-1});
        }
        clock_t finish=clock();
        double time=(double)(finish - start) / CLOCKS_PER_SEC;
        cout<<"Spend time\n";
        cout<<time<<"seconds"<<endl;

    }
};

class CompressedIndex: public Index
{
private:
    unordered_map<char,vector<unsigned int >> hash_map;
public:
    unordered_map<char,vector<unsigned int>> GetIndex()
    {
        return hash_map;
    }

    int  Traverse()
    {
        std::ifstream file("../data/Align2.txt");
        if(!file.is_open())
        {
            cout<<"Error opening file!";
            exit(001);
        }
        while (!file.eof())
        {
            char buffer[1005];
            file.getline(buffer,1005);
            string string1=buffer;
            unsigned  int a=0,b=0,c=0,d=0;
            unsigned  int j=1<<31;
            for(int i=0;i<string1.length();i++)
            {
                if(i%31==0&&i!=0)
                {
                    hash_map['A'].push_back(a);
                    hash_map['C'].push_back(b);
                    hash_map['G'].push_back(c);
                    hash_map['T'].push_back(d);
                    a=0,b=0,c=0,d=0;
                    j=1<<31;
                }
                if(string1[i]=='A')
                    a=a^j;
                else if(string1[i]=='C')
                    b=b^j;
                else if(string1[i]=='G')
                    c=c^j;
                else
                {
                    d=d^j;
                }
                j=j>>1;
            }
        }
        return  hash_map.size();
    }
};



#endif //PROJECTMAIN_INDEX_H
