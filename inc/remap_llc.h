#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "champsim.h"
#include "block.h"

using namespace std;

class REMAP_LLC 
{
    public:

    vector<pair<uint64_t,uint64_t>> temp;
    vector<long long> links;
    vector<int> is_hot;
    int no_sets;
    bool linked = false;
    bool flag = false;

    //constructor
    REMAP_LLC(uint32_t num_sets = 2048, int num_ways = 16)
    {
        no_sets = num_sets;
        temp.resize(num_sets, {0, 0});
        is_hot.resize(num_sets+1,0);
        for(int i=0;i<num_sets;i++)
        {
            temp[i].first = i;
        }
        links.resize(num_sets+1,0);
    };

    void update_temp(uint64_t set, uint64_t cpu)
    {
        int ctr=0;
        if(!warmup_complete[cpu])
        {
            temp[set].second+=1;
        }
        else if(ctr==0)
        {
            link_sets(cpu);
            ctr=1;
        }
    }

    static bool compareSecond(pair<uint64_t, uint64_t>& a, pair<uint64_t, uint64_t>& b)
    {
        return a.second > b.second;
    }
    void sort_temp() 
    {
        sort(temp.begin(), temp.end(), compareSecond);
        
    }

    void link_sets(uint64_t cpu)
    {
        if(linked==false)
        {
            sort_temp();
            for(int i=0;i<no_sets/2;i++)
            {
                links[temp[i].first]=temp[no_sets-i-1].first;
                is_hot[temp[i].first] = 1;
            }
            linked = true;
        }
    }
};