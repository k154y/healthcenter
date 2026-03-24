#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <limits>

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


class ArrayQueue {
private:
    patient* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

    void resize() {
        int newCapacity = capacity * 2;
        patient* newArr = new patient[newCapacity];

        for (int i = 0; i < count; i++) {
            newArr[i] = arr[(frontIndex + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count;
    }

public:
    ArrayQueue(int initialCapacity = 2) {
        capacity = initialCapacity;
        arr = new patient[capacity];
        frontIndex = 0;
        rearIndex = 0;
        count = 0;
    }

    // Copy constructor
    ArrayQueue(const ArrayQueue& other) {
        capacity = other.capacity;
        frontIndex = other.frontIndex;
        rearIndex = other.rearIndex;
        count = other.count;

        arr = new patient[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = other.arr[i];
        }
    }

    // Copy assignment operator
    ArrayQueue& operator=(const ArrayQueue& other) {
        if (this != &other) {
            delete[] arr;

            capacity = other.capacity;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            count = other.count;

            arr = new patient[capacity];
            for (int i = 0; i < capacity; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~ArrayQueue() {
        delete[] arr;
    }

    void push(const patient& value) {
        if (count == capacity) {
            resize();
        }

        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    void pop() {
        if (empty()) {
            return;
        }

        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    patient& front() {
        return arr[frontIndex];
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};


class ArrayPriorityQueue {
private:
    patient* arr;
    int capacity;
    int count;

    void resize() {
        int newCapacity = capacity * 2;
        patient* newArr = new patient[newCapacity];

        for (int i = 0; i < count; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < count && arr[largest] < arr[left]) {
                largest = left;
            }

            if (right < count && arr[largest] < arr[right]) {
                largest = right;
            }

            if (largest != index) {
                swap(arr[index], arr[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    ArrayPriorityQueue(int initialCapacity = 2) {
        capacity = initialCapacity;
        arr = new patient[capacity];
        count = 0;
    }

    // Copy constructor
    ArrayPriorityQueue(const ArrayPriorityQueue& other) {
        capacity = other.capacity;
        count = other.count;

        arr = new patient[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = other.arr[i];
        }
    }

    // Copy assignment operator
    ArrayPriorityQueue& operator=(const ArrayPriorityQueue& other) {
        if (this != &other) {
            delete[] arr;

            capacity = other.capacity;
            count = other.count;

            arr = new patient[capacity];
            for (int i = 0; i < capacity; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~ArrayPriorityQueue() {
        delete[] arr;
    }

    void push(const patient& value) {
        if (count == capacity) {
            resize();
        }

        arr[count] = value;
        heapifyUp(count);
        count++;
    }

    void pop() {
        if (empty()) {
            return;
        }

        arr[0] = arr[count - 1];
        count--;
        if (!empty()) {
            heapifyDown(0);
        }
    }

    patient& top() {
        return arr[0];
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
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

    ArrayQueue consultation;
    ArrayPriorityQueue emergency;

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
            getline(cin, npatient);

            int total = getCurrentTimeInMinutes();

            consultation.push({npatient, "Regular", 0, total});

            cout << "Regular patient added at time: " << convertTime(total) << endl;
            break;
        }

        case 2: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter patient name: ";
            getline(cin, npatient);

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

                cout << "\n----- EMERGENCY PATIENT SERVED -----\n";
                cout << "Name: " << p.name << endl;
                cout << "Case: " << p.ecase << endl;
                cout << "Priority: " << p.priority << endl;
                cout << "Arrival Time: " << convertTime(p.arrival_total) << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
            }
            else if (!consultation.empty()) {
                patient p = consultation.front();
                consultation.pop();

                int waiting = current_total - p.arrival_total;

                cout << "\n----- REGULAR PATIENT SERVED -----\n";
                cout << "Name: " << p.name << endl;
                cout << "Arrival Time: " << convertTime(p.arrival_total) << endl;
                cout << "Waiting Time: " << waiting << " minutes\n";
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

            ArrayPriorityQueue tempEmergency = emergency;
            ArrayQueue tempRegular = consultation;

            cout << "\nEmergency Patients:\n";
            if (tempEmergency.empty()) {
                cout << "No emergency patients waiting.\n";
            } else {
                while (!tempEmergency.empty()) {
                    patient p = tempEmergency.top();
                    tempEmergency.pop();

                    cout << "Name: " << p.name
                         << " | Case: " << p.ecase
                         << " | Priority: " << p.priority
                         << " | Arrival: " << convertTime(p.arrival_total)
                         << endl;
                }
            }

            cout << "\nRegular Patients:\n";
            if (tempRegular.empty()) {
                cout << "No regular patients waiting.\n";
            } else {
                while (!tempRegular.empty()) {
                    patient p = tempRegular.front();
                    tempRegular.pop();

                    cout << "Name: " << p.name
                         << " | Arrival: " << convertTime(p.arrival_total)
                         << endl;
                }
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