#include <iostream>
#include <queue>
#include <chrono>
#include <ctime>
#include <string>

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

string convertTime(int total) {
    int hour = total / 60;
    int min = total % 60;

    return to_string(hour) + ":" + (min < 10 ? "0" : "") + to_string(min);
}

int main() {

    int choice, priority;
    string npatient, name_case;

    queue<patient> consultation;
    priority_queue<patient> emergency;

    bool running = true;

    while (running) {

        cout << "\nCOMMUNITY HEALTH CENTER SYSTEM \n";
        cout << "1. Add regular patient\n";
        cout << "2. Add emergency patient\n";
        cout << "3. Serve next patient\n";
        cout << "4. Show queue status\n";
        cout << "5. Show full waiting list\n";
        cout << "6. Quit\n";
        cout << "Choice: ";

        cin >> choice;

        switch (choice) {

        case 1: {

            cout << "Enter patient name: ";
            cin >> npatient;

            int total = getCurrentTimeInMinutes();

            consultation.push({npatient, "Regular", 0, total});

            cout << "Patient added at time: " << convertTime(total) << endl;
            break;
        }

        case 2: {

            cout << "Enter patient name: ";
            cin >> npatient;

            cout << "Enter emergency level (1-10): ";
            cin >> priority;

            cin.ignore();
            cout << "Enter emergency case description: ";
            getline(cin, name_case);

            int total = getCurrentTimeInMinutes();

            emergency.push({npatient, name_case, priority, total});

            cout << "Emergency patient added at time: " << convertTime(total) << endl;
            break;
        }

        case 3: {

            int current_total = getCurrentTimeInMinutes();

            if (!emergency.empty()) {

                patient p = emergency.top();
                emergency.pop();

                int waiting = current_total - p.arrival_total;

                cout << "\nEMERGENCY PATIENT SERVED \n";
                cout << "Name: " << p.name << endl;
                cout << "Case: " << p.ecase << endl;
                cout << "Priority: " << p.priority << endl;
                cout << "Arrival: " << convertTime(p.arrival_total) << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
            }

            else if (!consultation.empty()) {

                patient p = consultation.front();
                consultation.pop();

                int waiting = current_total - p.arrival_total;

                cout << "\nREGULAR PATIENT SERVED \n";
                cout << "Name: " << p.name << endl;
                cout << "Arrival: " << convertTime(p.arrival_total) << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
            }

            else {
                cout << "No patients waiting.\n";
            }

            break;
        }

        case 4: {

            cout << "\nQUEUE STATUS \n";
            cout << "Emergency patients waiting: " << emergency.size() << endl;
            cout << "Regular patients waiting: " << consultation.size() << endl;
            break;
        }

        case 5: {

            cout << "\nFULL WAITING LIST \n";

            priority_queue<patient> tempEmergency = emergency;
            queue<patient> tempRegular = consultation;

            cout << "\nEmergency Patients \n";

            while (!tempEmergency.empty()) {
                patient p = tempEmergency.top();
                tempEmergency.pop();

                cout << "Name: " << p.name
                     << " | Case: " << p.ecase
                     << " | Priority: " << p.priority
                     << " | Arrival: " << convertTime(p.arrival_total)
                     << endl;
            }

            cout << "\nRegular Patients \n";

            while (!tempRegular.empty()) {
                patient p = tempRegular.front();
                tempRegular.pop();

                cout << "Name: " << p.name
                     << " | Arrival: " << convertTime(p.arrival_total)
                     << endl;
            }

            break;
        }

        case 6:
            running = false;
            cout << "System closed.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}