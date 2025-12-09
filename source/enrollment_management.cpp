#include "../include/operations.h"
#include "../include/struct.h"
#include "../include/user_management.h"
#include "../include/unit_management.h"
#include "../include/enrollment_management.h"

vector<Enrollment> find_enrollments_by_unit_id(int unit_id){
    vector<Enrollment> student_list;
    for(const Enrollment& rec:enrollments_list){
        if(rec.unit_id==unit_id){
            student_list.push_back(rec);
        }
    }
    return student_list;
}