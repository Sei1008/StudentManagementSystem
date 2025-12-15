#ifndef user_management_h
#define user_management_h

using namespace std;

void teacher_menu(User* teacher);
void student_menu(User* student);

User* login_user();
User* find_user_by_username(string username);

Unit* find_unit_name_by_id(int unit_id);
Unit* find_unit_by_code(string code);

void enroll_unit(User* student);
void list_available_units_for_student();
void list_enrolled_units(int student_id);

bool is_unit_full(const Unit& unit);
bool is_student_enrolled_in(int student_id, int unit_id);
void check_my_scores(int student_id);

int get_student_enrollment_count(int student_id);
void drop_unit(User* student);

unsigned long encrypt_djb2(string password);

void generate_random_scores(int student_id);
#endif