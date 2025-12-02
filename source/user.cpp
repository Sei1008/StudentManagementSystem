#include "operations.h"
#include "struct.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
void main_menu(void){

}
void teacher_menu(User* teacher){
    int choice;
    do {
        cout << "\n---- TEACHER MENU ----\n";
        cout << "1. List my teaching units\n";
        cout << "2. Add a new unit\n";
        cout << "3. Delete a unit\n";
        cout << "4. List students in a unit\n";
        cout << "5. Show unit statistics\n";
        cout << "6. Log out\n";
        cout << "Enter your choice (1-6) : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- Your Teaching Units ---\n";
                for (const Unit& unit : units_list) {
                    if (unit.teacher_id == teacher->id) {
                        cout << unit.unit_code << " - " << unit.unit_name << " (Enrolled: " << unit.current_enrollment << "/" << unit.capacity << ")\n";
                    }
                }
                break;
            }

            case 2: {
                Unit new_unit;
                cout << "\n--- Add New Unit ---\n";
                cout << "Enter unit code: ";
                cin >> new_unit.unit_code;
                cout << "Enter unit name: ";
                cin.ignore();
                getline(cin, new_unit.unit_name);
                cout << "Enter capacity: ";
                cin >> new_unit.capacity;

                new_unit.unit_id = units_list.size() + 1;
                new_unit.current_enrollment = 0;
                new_unit.teacher_id = teacher->id;

                units_list.push_back(new_unit);
                cout << "Unit added successfully!\n";
                break;
            }

            case 3: {
                string code;
                cout << "\n--- Delete Unit ---\n";
                cout << "Enter unit code to delete: ";
                cin >> code;

                bool found = false;
                for (auto it = units_list.begin(); it != units_list.end(); ++it) {
                    if (it->unit_code == code && it->teacher_id == teacher->id) {
                        units_list.erase(it);
                        cout << "Unit deleted successfully.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Unit not found or not owned by you.\n";
                break;
            }

            case 4: {
                string code;
                cout << "\n--- List Students in Unit ---\n";
                cout << "Enter unit code: ";
                cin >> code;

                int unit_id = -1;
                for (const Unit& u : units_list) {
                    if (u.unit_code == code && u.teacher_id == teacher->id) {
                        unit_id = u.unit_id;
                        break;
                    }
                }

                if (unit_id == -1) {
                    cout << "Unit not found or not owned by you.\n";
                    break;
                }

                cout << "Students enrolled in " << code << ":\n";
                for (const Enrollment& e : enrollments_list) {
                    if (e.unit_id == unit_id) {
                        for (const User& u : users_list) {
                            if (u.id == e.student_id) {
                                cout << "- " << u.username << " (Score: " << e.score << ")\n";
                            }
                        }
                    }
                }
                break;
            }

            case 5: {
                cout << "\n--- Unit Statistics ---\n";
                for (const Unit& unit : units_list) {
                    if (unit.teacher_id == teacher->id) {
                        cout << unit.unit_code << " - " << unit.unit_name
                             << " | Enrolled: " << unit.current_enrollment
                             << " / " << unit.capacity << "\n";
                    }
                }
                break;
            }

            case 6:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }
    } while (choice != 6);
}

