//
//  main.cpp
//  Assignment-5
//
//  Created by Fayed Barno on 28/10/22.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
 
struct Job{
    int start,end,val;
};
bool jobcompare(Job a, Job b){
    return (b.start >= a.end);
}
void findallsubsets(std::vector<Job>joblists,std::vector<Job>subjob, int n=-1){
    
    
    int len = joblists.size();
    if (n == len){
        return;
    }
    
    for(int i=n+1;i<len;i++){
        if (jobcompare(joblists[n],joblists[i])){
            subjob.push_back(joblists[i]);
            findallsubsets(joblists,subjob,i);
            subjob.pop_back();
        }
    }
    
    for(auto a:subjob){

        std::cout<<"["<<a.start<<","<<a.end<<"]";
    }
    
    std::cout<<std::endl;
    return;
    
};

int findmax(std::vector<Job>joblists, int n){
    
    
    if (n == 1){
        return joblists[n-1].val;
    }
    int first = joblists[n-1].val;
    int next = -1;
    for(int i=n-1; i>=0;i--){
        if(jobcompare(joblists[i],joblists[n-1])){
            next = i;
            break;
        }
    }
    if (next!=-1){
        first += findmax(joblists,next+1);
    }
    int withoutfirst = findmax(joblists,n-1);
    return std::max(first, withoutfirst);
};
void findmaxdynamic(std::vector<Job>joblists, int n){
    
    std::vector<std::vector<Job>> master(joblists.size());
    int* maxval = new int[n];
    maxval[0]=joblists[0].val;
    master[0].push_back(joblists[0]);
    for(int j = 1; j<n;j++){
        int nextjob = joblists[j].val;
        int next = -1;
        for(int i=j-1; i>=0;i--){
            if(jobcompare(joblists[i],joblists[j])){
                next = i;
                break;
            }
        }
        if (next!=-1){
            nextjob += maxval[next];
            
            
        }
        if (nextjob>maxval[j-1]){
            maxval[j] = nextjob;
            if (next!=-1){
                for(auto a: master[next]){
                    master[j].push_back(a);
                    
                }
            }
            master[j].push_back(joblists[j]);
            
        }
        else{
            maxval[j] = maxval[j-1];
            for(auto a: master[j-1]){
                master[j].push_back(a);
                
            }
        }
    }
    int maxed =maxval[n-1];
    delete[] maxval;
    for (auto a: master[n-1]){
        std::cout<<"["<<a.start<<","<<a.end<<"]"<<"("<<a.val<<") ";
    }
    std::cout<<std::endl;
    

};


int main(){
    std::vector<Job>joblist;
    std::ifstream input;
    input.open("shedule.txt");
    int start,end,val;
    while (input >> start >> end >> val){
        Job newjob = Job();
        newjob.start = start;
        newjob.end = end;
        newjob.val = val;
        joblist.push_back(newjob);
    }
    input.close();
    std::vector<Job>subjob;
    int len = joblist.size();
    std::cout << "This is the third problem" << std::endl;
    findmaxdynamic(joblist,len);
    std::cout << "This is the second problem" << std::endl;
    std::cout << findmax(joblist, len) << std::endl;
    std::cout << "This is the first problem" << std::endl;
    findallsubsets(joblist, subjob);
}
//Nafis and I collaborated in this project
