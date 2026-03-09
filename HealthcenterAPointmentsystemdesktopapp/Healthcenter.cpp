#include <iostream>
#include <queue>
#include <chrono>
#include <ctime>
#include<string>
using namespace std;


struct patient {
    string name;
    string ecase;
    int priority;          
    int arrival_total;    

    bool operator<(const patient& other) const {
        return priority < other.priority;  
    }
};


int getCurrentTimeInMinutes() {
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    tm* local_time = localtime(&current_time);

    return local_time->tm_hour * 60 + local_time->tm_min;
}


int main() {

    int choice, priority;
    string npatient, name_case, arrival;

    queue<patient> consultation;
    priority_queue<patient> emergency;

    bool times = true;

    while (times) {

        cout << "\nPress number to get help\n";
        cout << "1. Add regular patient\n";
        cout << "2. Add emergency case\n";
        cout << "3. See daily operations\n";
        cout << "4. Quit\n";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "Enter patient name: ";
            cin >> npatient;

            cout << "Enter arrival time (HH:MM): ";
            cin >> arrival;

            int hour = stoi(arrival.substr(0,2));
            int min  = stoi(arrival.substr(3,2));

            int total = hour * 60 + min;

            consultation.push({npatient, "Regular", 0, total});
            cout << "Regular patient added successfully.\n";
            break;
        }

        case 2: {
            cout << "Enter patient name: ";
            cin >> npatient;

            cout << "Enter emergency level (1-10): ";
            cin >> priority;

            cout << "Enter emergency case description: ";
            cin >> name_case;

            cout << "Enter arrival time (HH:MM): ";
            cin >> arrival;

            int hour = stoi(arrival.substr(0,2));
            int min  = stoi(arrival.substr(3,2));

            int total = hour * 60 + min;

            emergency.push({npatient, name_case, priority, total});
            cout << "Emergency patient added successfully.\n";
            break;
        }

        case 3: {

            int current_total = getCurrentTimeInMinutes();

            cout << "\n===== DAILY OPERATIONS =====\n";

            // Emergency first
            while (!emergency.empty()) {

                patient p = emergency.top();
                emergency.pop();

                int waiting = current_total - p.arrival_total;

                cout << "\nEMERGENCY\n";
                cout << "Name: " << p.name << endl;
                cout << "Case: " << p.ecase << endl;
                cout << "Priority: " << p.priority << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
            }

            // Then regular patients
            while (!consultation.empty()) {

                patient p = consultation.front();
                consultation.pop();

                int waiting = current_total - p.arrival_total;

                cout << "\nREGULAR\n";
                cout << "Name: " << p.name << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
            }

            cout << "\n===== END OF REPORT =====\n";
            break;
        }

        case 4:
            times = false;
            cout << "System closed.\n";
            break;

        default:
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}