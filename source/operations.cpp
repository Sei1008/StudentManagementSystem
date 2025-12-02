#include "../include/operations.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void load_user_from_csv(vector<User>& users_list){
    ifstream file("data/user.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open user.csv file.";
        return;
    }
    string line;
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        User newUser;
        string id_str;

        getline(ss,id_str,',');
        getline(ss,newUser.username,',');
        getline(ss,newUser.password,',');
        getline(ss,newUser.role,',');
        getline(ss,newUser.status,',');

        newUser.id=stoi(id_str);
        users_list.push_back(newUser);
    }

    file.close();
    cout<<"Users loaded successfully!"<<endl;

}

void save_user_to_csv(const vector<User>& users_list){
    ofstream file("data/user.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open user.csv for writing";
        return;
    }

    file<<"id,username,password,role,status"<<endl;
    
    for(const User& user: users_list){
        file <<user.id<<",";
        file << user.username<<",";
        file <<user.password<<",";
        file << user.role<<",";
        file <<user.status<<endl;
    }
    file.close();
    cout <<"Saved successfully!"<<endl;
}