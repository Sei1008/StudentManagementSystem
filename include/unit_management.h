#ifndef unit_management_h
#define unit_management_h

#include "../include/struct.h"

void list_all_teaching_units_by_teacher_id(int teacher_id);
int get_the_next_id();
void add_new_unit();
bool is_unit_full(const Unit& unit);
int get_student_enrollment_count(int student_id);
bool is_student_enrolled_in(int student_id, int unit_id);
vector<Unit>::iterator find_it_by_unit_id(int unit_id);
void delete_unit();
void list_all_units();
void list_students_in_unit();
void show_unit_statistic();
#endif