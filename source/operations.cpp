#include "../include/operations.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void load_user_from_csv(vector<User>& users_list){
    ifstream file("../data/user.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open user.csv file."<<endl;
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
        getline(ss,newUser.status);

        newUser.id=stoi(id_str);
        users_list.push_back(newUser);
    }

    file.close();
    cout<<"Users loaded successfully!"<<endl;

}

void save_user_to_csv(const vector<User>& users_list){
    ofstream file("../data/user.csv");
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

void load_unit_from_csv(vector <Unit>& units_list){
    ifstream file("../data/unit.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannnot open the units.csv file."<<endl;
        return;
    }
    
    string line;
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        string unit_id_str,capacity_str,current_enrollment_str,teacher_id_str;
        Unit newUnit;

        getline(ss,unit_id_str,',');
        getline(ss,newUnit.unit_code,',');
        getline(ss,newUnit.unit_name,',');
        getline(ss,capacity_str,',');
        getline(ss,current_enrollment_str,',');
        getline(ss,teacher_id_str);
        try{
            newUnit.unit_id=stoi(unit_id_str);
            newUnit.capacity=stoi(capacity_str);
            newUnit.current_enrollment=stoi(current_enrollment_str);
            newUnit.teacher_id=stoi(teacher_id_str);
            units_list.push_back(newUnit);
        }catch(const exception& e){
            cerr<<"Error parsing line: "<< line<<endl;
        }
        file.close();
        cout<<"Units loaded successfully!"<<endl;
    }
}

void save_unit_to_csv(const vector<Unit>& units_list){
    ofstream file("../data/unit.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open the unit.csv file."<<endl;
        return;
    }
    file<<"unit_id,unit_code,unit_name,capacity,current_enrollment,teacher_id"<<endl;
    for(const Unit& unit: units_list){
        file <<unit.unit_id<<",";
        file << unit.unit_code<<",";
        file <<unit.unit_name<<",";
        file << unit.capacity<<",";
        file <<unit.current_enrollment<<",";
        file << unit.teacher_id<<endl;
    }
    file.close();
    cout<<"Saved successfully!"<<endl;
}

void load_enrollment_from_csv(vector<Enrollment>& enrollments_list){
    ifstream file("../data/enrollment.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open the enrollment.csv file."<<endl;
        return;
    }
    string line;
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        string student_id_str,unit_id_str,score_str;
        Enrollment newEnrollment;
        getline(ss,student_id_str,',');
        getline(ss,unit_id_str,',');
        getline(ss,score_str);

        newEnrollment.student_id=stoi(student_id_str);
        newEnrollment.unit_id=stoi(unit_id_str);
        newEnrollment.score=stoi(score_str);
        enrollments_list.push_back(newEnrollment);
    }
    file.close();
    cout<<"Enrollments loaded successfully!"<<endl;
}

void save_enrollment_to_csv(const vector<Enrollment>& enrollments_list){
    ofstream file("../data/enrollment.csv");
    while(!file.is_open()){
        cerr<<"Error! Cannot open the enrollment.csv file.";
        return;
    }
    
    file<<"student_id,unit_id,score"<<endl;

    for(const Enrollment& enrollment: enrollments_list){
        file<<enrollment.student_id<<",";
        file<<enrollment.unit_id<<",";
        file<<enrollment.score<<endl;
    }
    file.close();
    cout<<"Saved successfully!"<<endl;
}

void save_all_data(){
    cout<<"Saving all data..."<<endl;
    save_user_to_csv(users_list);
    save_unit_to_csv(units_list);
    save_enrollment_to_csv(enrollments_list);
    cout<<"All data saved successfully!"<<endl;
}