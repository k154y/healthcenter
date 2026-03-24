#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <limits>

using namespace std;

struct Patient {
    string name;
    string ecase;
    int priority;
    int arrival_total;
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

// ---------------- REGULAR QUEUE USING ARRAY ----------------
class ArrayQueue {
private:
    static const int MAX = 100;
    Patient arr[MAX];
    int count;

public:
    ArrayQueue() {
        count = 0;
    }

    bool empty() {
        return count == 0;
    }

    bool full() {
        return count == MAX;
    }

    int size() {
        return count;
    }

    void push(Patient p) {
        if (full()) {
            cout << "Regular queue is full.\n";
            return;
        }

        arr[count] = p;
        count++;
    }

    void pop() {
        if (empty()) {
            return;
        }

        for (int i = 0; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }

        count--;
    }

    Patient front() {
        return arr[0];
    }

    void display() {
        if (empty()) {
            cout << "No regular patients waiting.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "Name: " << arr[i].name
                 << " | Arrival: " << convertTime(arr[i].arrival_total)
                 << endl;
        }
    }
};

// ---------------- PRIORITY QUEUE USING ARRAY ----------------
class ArrayPriorityQueue {
private:
    static const int MAX = 100;
    Patient arr[MAX];
    int count;

public:
    ArrayPriorityQueue() {
        count = 0;
    }

    bool empty() {
        return count == 0;
    }

    bool full() {
        return count == MAX;
    }

    int size() {
        return count;
    }

    void push(Patient p) {
        if (full()) {
            cout << "Emergency queue is full.\n";
            return;
        }

        arr[count] = p;
        count++;
    }

    int highestPriorityIndex() {
        int index = 0;

        for (int i = 1; i < count; i++) {
            if (arr[i].priority > arr[index].priority) {
                index = i;
            }
        }

        return index;
    }

    Patient top() {
        int index = highestPriorityIndex();
        return arr[index];
    }

    void pop() {
        if (empty()) {
            return;
        }

        int index = highestPriorityIndex();

        for (int i = index; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }

        count--;
    }

    void display() {
        if (empty()) {
            cout << "No emergency patients waiting.\n";
            return;
        }

        // display from highest priority to lowest
        Patient temp[MAX];
        int tempCount = count;

        for (int i = 0; i < count; i++) {
            temp[i] = arr[i];
        }

        while (tempCount > 0) {
            int highest = 0;

            for (int i = 1; i < tempCount; i++) {
                if (temp[i].priority > temp[highest].priority) {
                    highest = i;
                }
            }

            cout << "Name: " << temp[highest].name
                 << " | Case: " << temp[highest].ecase
                 << " | Priority: " << temp[highest].priority
                 << " | Arrival: " << convertTime(temp[highest].arrival_total)
                 << endl;

            for (int i = highest; i < tempCount - 1; i++) {
                temp[i] = temp[i + 1];
            }

            tempCount--;
        }
    }
};

int main() {
    ArrayQueue consultation;
    ArrayPriorityQueue emergency;

    int choice, priority;
    string name, case_desc;

    while (true) {
        cout << "\n===== COMMUNITY HEALTH CENTER SYSTEM =====\n";
        cout << "1. Add regular patient\n";
        cout << "2. Add emergency patient\n";
        cout << "3. Serve next patient\n";
        cout << "4. Show queue status\n";
        cout << "5. Show full waiting list\n";
        cout << "6. Quit\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter patient name: ";
                getline(cin, name);

                int total = getCurrentTimeInMinutes();
                Patient p = {name, "Regular", 0, total};

                consultation.push(p);

                cout << "Regular patient added at time: "
                     << convertTime(total) << endl;
                break;
            }

            case 2: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter patient name: ";
                getline(cin, name);

                cout << "Enter emergency level (1-10): ";
                cin >> priority;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid priority.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter emergency case description: ";
                getline(cin, case_desc);

                int total = getCurrentTimeInMinutes();
                Patient p = {name, case_desc, priority, total};

                emergency.push(p);

                cout << "Emergency patient added at time: "
                     << convertTime(total) << endl;
                break;
            }

            case 3: {
                int current_total = getCurrentTimeInMinutes();

                if (!emergency.empty()) {
                    Patient p = emergency.top();
                    emergency.pop();

                    cout << "\n----- EMERGENCY PATIENT SERVED -----\n";
                    cout << "Name: " << p.name << endl;
                    cout << "Case: " << p.ecase << endl;
                    cout << "Priority: " << p.priority << endl;
                    cout << "Arrival Time: " << convertTime(p.arrival_total) << endl;
                    cout << "Waiting Time: "
                         << current_total - p.arrival_total
                         << " minutes\n";
                }
                else if (!consultation.empty()) {
                    Patient p = consultation.front();
                    consultation.pop();

                    cout << "\n----- REGULAR PATIENT SERVED -----\n";
                    cout << "Name: " << p.name << endl;
                    cout << "Arrival Time: " << convertTime(p.arrival_total) << endl;
                    cout << "Waiting Time: "
                         << current_total - p.arrival_total
                         << " minutes\n";
                }
                else {
                    cout << "No patients waiting.\n";
                }

                break;
            }

            case 4: {
                cout << "\n----- QUEUE STATUS -----\n";
                cout << "Emergency patients waiting: " << emergency.size() << endl;
                cout << "Regular patients waiting: " << consultation.size() << endl;
                break;
            }

            case 5: {
                cout << "\n----- FULL WAITING LIST -----\n";

                cout << "\nEmergency Patients:\n";
                emergency.display();

                cout << "\nRegular Patients:\n";
                consultation.display();

                break;
            }

            case 6:
                cout << "System closed.\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}