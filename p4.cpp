#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
    //start of linked list
    Person *next;
};

class HashTable {
    // closed addressing with seperate chaining
    private:
    uint64_t bucketNum;
    vector<Person*> list; //pointer to a vector containing buckets
    string keyName;

    public:
    HashTable(int mapTable, string keyName); // constructor
    // mapping function
        // int index = djb2(person info) % size
    string getKeyName() {
        return keyName;
    }

    uint64_t getIndex(Person *apple) {
        uint64_t index;
        if (keyName == "Id") {
            index = djb2(apple->id);
        }
        else if (keyName == "FirstName") {
            index = djb2(apple->first);
        }
        else if (keyName == "LastName") {
            index = djb2(apple->last);
        }
        else if (keyName == "Email") {
            index = djb2(apple->email);
        }
        else if (keyName == "Phone") {
            index = djb2(apple->phone);
        }
        else if (keyName == "City") {
            index = djb2(apple->city);
        }
        else if (keyName == "State") {
            index = djb2(apple->state);
        }
        else if (keyName == "PostalCode") {
            index = djb2(apple->postalCode);
        }
        return index;
    }


    // hash function = use the djb2 hash function provided to turn a string into an unsigned 64-bit int
    void hashInsert(Person *apple) {
        uint64_t indexasaurus = getIndex(apple);
        indexasaurus %= bucketNum;
        
        if (list[indexasaurus] == nullptr) {
            list[indexasaurus] = apple;
        } 
        else {
            Person *orange = list[indexasaurus];
            while (orange->next != nullptr) {
                orange = orange->next;
            }
            orange->next = apple;
            apple->next = nullptr;
        }

    }

    vector<Person*> hashLookup(string key) {
        uint64_t indexasaurus = djb2(key);
        indexasaurus %= bucketNum;

        vector<Person*> people;
        if (list[indexasaurus] == nullptr) {
            return people;
        } 
        // else if (list.size() == 1) {
        //     Person* orange = list[indexasaurus];
        //     people.push_back(orange);
        //     return people;
        // }
        else {
            Person* orange = list[indexasaurus];
            while (orange != nullptr) {
                if (keyName == "Id") {
                    if (orange->id == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "FirstName") {
                    if (orange->first == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "LastName") {
                    if (orange->last == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "Email") {
                    if (orange->email == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "Phone") {
                    if (orange->phone == key) {
                        people.push_back(orange);
                    }
                }
                else if (keyName == "City") {
                    if (orange->city == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "State") {
                    if (orange->state == key) {
                        people.push_back(orange);
                    } 
                }
                else if (keyName == "PostalCode") {
                    if (orange->postalCode == key) {
                        people.push_back(orange);
                    } 
                }
                orange = orange->next;
            }
            return people;
        }
    
    }

    void hashPrint() {
        for (uint64_t i = 0; i < bucketNum; i++) {
            Person *dog = list[i];
            if (dog != nullptr) {
                //int count1= 0;

                //TODO: how does one do this?
                //TODO: For each person at the index, if you have seen the key before (search the list until 
                //the current index), then don’t do anything. If you have not come across this key before, 
                //then count the number of occurrences in the index and print it.

                /*for (Person* cat = list[i]; cat != nullptr; cat = cat->next) { 
                    // going thru the seperate chain
                    // for (Person* cur = list[i]; cur != nullptr; cur = cur->next) { //anothee loop
                    //     // if (cur == cur->next) {
                    //     //     flag = 1;
                    //     //     break;
                    //     // }
                    //     for (Person* inner = list[i]; inner != nullptr; inner = inner->next) {
                    //         if (cur-)
                    //     }
                    // }
                    count1++;
                } // compare keyName to current and past keys in if statements
                */
                vector<std::string> uniqueKeys;
                vector<int> uniqueKeysCount;
                Person* person = list[i];
                int j = 0;
                cout << i << ": ";
                if (keyName == "Id") {
                    /*if (count1 == 1) {
                    cout << i << ": " << dog->id << " (" << count1 << ")," << endl;
                    }
                    else {
                        cout << i << ": ";
                        for (Person* cat = list[i]; cat != nullptr; cat = cat->next) {
                            for (Person* curNode = list[i]; curNode != nullptr; curNode = curNode->next) {
                                int miniCount = 0;
                                for (Person* comparedNode = list[i]; comparedNode != nullptr; comparedNode = comparedNode->next) {
                                    if (keyName == comparedNode->id) {
                                        miniCount++;
                                        cout << "hihi";
                                    }
                                }
                                cout << dog->id << " (" << miniCount << "),";
                            }
                            cout << endl;
                        }
                    }*/
                    for (; person != nullptr; person = person->next) {
                        string value = person->id;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "FirstName") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->first;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "LastName") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->last;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "Email") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->email;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "Phone") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->phone;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "City") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->city;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "State") {
                    /*if (count1 == 1) {
                    cout << i << ": " << dog->state << " (" << count1 << ")," << endl;
                    }
                    else {
                        cout << i << ": "<< dog->state;
                        for (Person* cat = list[i]; cat != nullptr; cat = cat->next) {
                            int miniCount = 0;
                            for (Person* curNode = list[i]; curNode != nullptr; curNode = curNode->next) {
                                //int miniCount = 0;
                                for (Person* comparedNode = list[i]; comparedNode != nullptr; comparedNode = comparedNode->next) {
                                    if (comparedNode->state == curNode->state) {
                                        miniCount++;
                                        
                                    }
                                    
                                }
                                //if (miniCount != 1) {
                                //cout << dog->state << " (" << miniCount << "),";
                                
                            }
                            cout << " (" << miniCount << "),";
                            cout << endl;
                        }
                    }*/
                    for (; person != nullptr; person = person->next) {
                        string value = person->state;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                else if (keyName == "PostalCode") {
                    for (; person != nullptr; person = person->next) {
                        string value = person->postalCode;
                        for (int k = 0; k <= j; k++) {
                            if (k < uniqueKeys.size()) {
                                if (value == uniqueKeys[k]) {
                                    uniqueKeysCount[k]++;
                                    break;
                                }
                            } else if (k == j) {
                                j++;
                                uniqueKeys.push_back(value);
                                uniqueKeysCount.push_back(1);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < j; k++) {
                        cout << uniqueKeys[k] << " (" << uniqueKeysCount[k] << "),";
                    }
                }
                cout << endl;
            }
        }
    }

    ~HashTable();
};

HashTable::HashTable(int map, string keyName) { //constructor
    this->bucketNum = map;
    list.resize(map);
    this->keyName = keyName;
}

HashTable::~HashTable() {
    for (uint64_t i = 0; i < this->bucketNum; i++) {
        if (list[i] != nullptr) {
            Person* dog = list[i];
            while (dog != nullptr) {
                Person* temp = dog;
                dog = dog->next;
                delete temp;
            }
        }
    }
}

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];
    
    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    //CONSTRUCTOR FUNC
    HashTable WantToNap(tableSize, key);
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);
        Person *p = new Person;
        p->next = nullptr;
        int i = 0;
        while (getline(iss, token, '\t')) {
            if (i == 0) {
                p->id = token;
            }
            else if (i == 1) {
                p->first = token;
            }
            else if (i == 2) {
                p->last = token;
            }
            else if (i == 3) {
                p->email = token;
            }
            else if (i == 4) {
                p->phone = token;
            }
            else if (i == 5) {
                p->city = token;
            }
            else if (i == 6) {
                p->state = token;
            }
            else if (i == 7) {
                p->postalCode = token;
            }
            i++;            
            //cout << token << "\t"; 
        }
        //cout << endl;
        //cout << p->id << "," << p->first << "," << p->last << "," << p->email << "," << p->phone << "," << p->city << "," << p->state << "," << p->postalCode << endl;
        WantToNap.hashInsert(p);
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            WantToNap.hashPrint();
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            vector<Person*> dog = WantToNap.hashLookup(val);
            if (dog.size() == 0) {
                cout << "No results" << endl;
            }
            else {
            cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
            for (int x = 0; x < dog.size(); x++) {
                if (WantToNap.getKeyName() == "Id") {
                    if (dog[x]->id != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "FirstName") {
                    if (dog[x]->first != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "LastName") {
                    if (dog[x]->last != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "Email") {
                    if (dog[x]->email != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "Phone") {
                    if (dog[x]->phone != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "City") {
                    if (dog[x]->city != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "State") {
                    if (dog[x]->state != val) {
                        continue;
                    }
                }
                else if (WantToNap.getKeyName() == "PostalCode") {
                    if (dog[x]->postalCode != val) {
                        continue;
                    }
                }
                cout << dog[x]->id << "," << dog[x]->first << "," << dog[x]->last << "," << dog[x]->email << "," << dog[x]->phone << "," << dog[x]->city << "," << dog[x]->state << "," << dog[x]->postalCode << endl;
            }
            }
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
