#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

class Student
{
    public:
    string name;
	int id_no;
	string stream;
	string book1,book2;
	int book_no,issuedbook;
    public:
    Student(string name, int id_no, string stream) {
        this->name = name;
        this->id_no = id_no;
        this->stream = stream;
        this->book_no = 0;
        this->issuedbook = 0;
	}
};
void selectionSort(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].id_no < arr[min_idx].id_no)
                min_idx = j;

        swap(arr[min_idx], arr[i]);
    }
}
void display(const vector<Student>& arr) {
    for (size_t i = 0; i < arr.size(); i++)
    {
        const Student &student = arr[i];
        cout << "\nName of Student: " << student.name;
        cout << "\nId of Student: " << student.id_no;
        cout << "\nStream of Student: " << student.stream;
    }
}

class Node {
public:
    string key;
    Node* left;
    Node* right;

    Node(string item) {
        key = item;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insertRec(Node* root, string key) {
        if (root == nullptr) {
            root = new Node(key);
            return root;
        }

        if (key < root->key)
            root->left = insertRec(root->left, key);
        else if (key > root->key)
            root->right = insertRec(root->right, key);

        return root;
    }

    bool containsNodeRecursive(Node* current, string key) {
        if (current == nullptr) return false;
        if (key == current->key) return true;
        return key < current->key ?
            containsNodeRecursive(current->left, key) :
            containsNodeRecursive(current->right, key);
    }

    Node* deleteRec(Node* root, string key) {
        if (root == nullptr) return root;

        if (key < root->key)
            root->left = deleteRec(root->left, key);
        else if (key > root->key)
            root->right = deleteRec(root->right, key);
        else {
            if (root->left == nullptr) return root->right;
            else if (root->right == nullptr) return root->left;

            root->key = minValue(root->right);
            root->right = deleteRec(root->right, root->key);
        }
        return root;
    }

    string minValue(Node* root) {
        string minv = root->key;
        while (root->left != nullptr) {
            minv = root->left->key;
            root = root->left;
        }
        return minv;
    }

    void printInorder(Node* node) {
        if (node == nullptr) return;
        printInorder(node->left);
        cout << node->key << " ";
        printInorder(node->right);
    }

    void printTreeRec(Node* t, int space) {
        if (t == nullptr) return;
        space += 5;
        printTreeRec(t->right, space);
        cout << endl;
        for (int i = 5; i < space; i++) cout << " ";
        cout << "[" << t->key << "]";
        printTreeRec(t->left, space);
    }

public:
    BST() { root = nullptr; }

    void insert(string key) {
        root = insertRec(root, key);
    }

    void update(string key, string key1) {
        deleteKey(key);
        insert(key1);
    }

    bool containsNode(string value) {
        return containsNodeRecursive(root, value);
    }

    void deleteKey(string key) {
        root = deleteRec(root, key);
    }

    void printInorder() {
        printInorder(root);
        cout << endl;
    }

    void printTree() {
        printTreeRec(root, 0);
        cout << endl;
    }
};

int main() {
    BST tree;
    map<string, int> hashmapping;
    vector<Student> array;
    array.push_back(Student("Aayushmaan", 761, "B.Tech-CHEMICAL"));
    array.push_back(Student("Priyanshu", 279, "B.Tech-CHEMICAL"));
    array.push_back(Student("Nirmal", 479, "B.Tech-CHEMICAL"));
    array.push_back(Student("Himanshu", 321, "B.Tech-CSE"));
    array.push_back(Student("Samrat", 701, "B.Tech-MINNING"));
    array.push_back(Student("Rudransh", 631, "B.Tech-FOOD"));
    int arr[100][2] = {0};

    ifstream infile1("subject.txt");
    ifstream infile2("Available_book.txt");
    ifstream infile3("Total_book.txt");

    string line;
    int i = 0;

    while (getline(infile1, line)) {
        tree.insert(line);
        hashmapping[line] = i;
        i++;
    }
    infile1.close();

    int j = i, o = 0, pq = 0;
    string number;

    while (getline(infile2, number)) {
        int result = stoi(number);
        if (j != o) arr[o][0] = result;
        o++;
    }
    infile2.close();

    while (getline(infile3, number)) {
        int result1 = stoi(number);
        if (j != pq) arr[pq][1] = result1;
        pq++;
    }
    infile3.close();

    // Choosing student or Librarian
    bool e1 = false;
    int choice_1;
    while (!e1) {
        cout << "\n.....................................";
        cout << "\n1. Librarian Login.";
        cout << "\n2. Student Login.";
        cout << "\n3. Exit.";
        cout << "\n.....................................";

        cout << "\nEnter Your choice:";
        cin >> choice_1;

        switch (choice_1) {
            case 1: {
                string pwd1 = "Aayushmaan";
                string id1 = "NITR";

                cout << "\nEnter UserId: ";
                string id2;
                cin >> id2;

                cout << "\nEnter Password: ";
                string pwd2;
                cin >> pwd2;

                if (id1 != id2)
                    cout << "Invalid Userid.";
                else if (pwd1 != pwd2)
                    cout << "Invalid Password.";
                else {
                    cout << "Login successfully.";
                    bool e2 = false;
                    while (!e2) {
                        cout << "\n.....................................";
                        cout << "\n1. Add book.";
                        cout << "\n2. Delete book.";
                        cout << "\n3. Update book.";
                        cout << "\n4. Print Books Details.";
                        cout << "\n5. Print Books in-order.";
                        cout << "\n6. Print tree.";
                        cout << "\n7. Exit";
                        cout << "\n.....................................";

                        cout << "\nEnter Your choice:";
                        int choice_2;
                        cin >> choice_2;
                        switch (choice_2) {
                            case 1: {
                                ifstream infile("subject.txt");
                                while (getline(infile, line)) {
                                    tree.insert(line);
                                    hashmapping[line] = i;
                                    i++;
                                }
                                infile.close();

                                cout << "\nEnter name of book:";
                                string name;
                                cin >> name;

                                if (tree.containsNode(name)) {
                                    cout << "\nIt already exists.";
                                } else {
                                    cout << "\nEnter quantity of book:";
                                    int quantity;
                                    cin >> quantity;

                                    ofstream outfile1("subject.txt", ios::app);
                                    ofstream outfile2("Available_book.txt", ios::app);
                                    ofstream outfile3("Total_book.txt", ios::app);
                                    outfile1 << name << endl;
                                    outfile2 << quantity << endl;
                                    outfile3 << quantity << endl;
                                    outfile1.close();
                                    outfile2.close();
                                    outfile3.close();

                                    tree.insert(name);
                                    hashmapping[name] = i;
                                    arr[i][0] += quantity;
                                    arr[i][1] += quantity;
                                    i++;
                                }
                                break;
                            }
                            case 2: {
                                cout << "\nEnter name of book:";
                                string b1;
                                cin >> b1;

                                if (tree.containsNode(b1)) {
                                    tree.deleteKey(b1);
                                    hashmapping.erase(b1);
                                }
                                break;
                            }
                            case 3: {
                                cout << "\nEnter name of book:";
                                string b2;
                                cin >> b2;

                                if (tree.containsNode(b2)) {
                                    int a = hashmapping[b2];
                                    cout << "\nEnter quantity of book to add more:";
                                    int q;
                                    cin >> q;
                                    arr[a][0] += q;
                                }
                                break;
                            }
                            case 4: {
                                for (const auto& entry : hashmapping) {
                                    int r = entry.second;
                                    cout << "Name of book is: " << entry.first << endl;
                                    cout << "Total Quantity of book is: " << arr[r][0] << endl;
                                    cout << "Available Quantity of book is: " << arr[r][1] << endl;
                                }
                                break;
                            }
                            case 5: {
                                tree.printInorder();
                                break;
                            }
                            case 6: {
                                tree.printTree();
                                break;
                            }
                            case 7: {
                                e2 = true;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 2:
            {
                cout<< "\n.....................................";
                cout<<"\n1. New User.";
                cout<<"\n2. Existing User.";
                cout<<"\n.....................................";
            }
            cout << "\nEnter Your choice:";
            int choice_2;
            cin >> choice_2;
            switch(choice_2)
            {
                case 1:
                {
                    cout << "\nEnter name:";
                    string name;
                    cin >> name;

                    cout << "\nEnter id:";
                    int id;
                    cin >> id;

                    cout<<"\nEnter Stream";
                    string stream;
                    cin>>stream;

                    array.push_back(Student(name, id, stream));
                    selectionSort(array);
                    display(array);
                    break;
                }
                case 2: {
                        cout << "\nEnter id:";
                        int id;
                        cin >> id;

                        auto it = find_if(array.begin(), array.end(), [id](const Student& student) {
                            return student.id_no == id;
                        });
                        if (it != array.end()) {
                            Student& student = *it;
                            bool e2 = false;
                            while (!e2) {
                                cout << "\n.....................................";
                                cout << "\n1. Display.";
                                cout << "\n2. Issue Book.";
                                cout << "\n3. Return Book.";
                                cout << "\n4. Exit.";
                                cout << "\n.....................................";

                                cout << "\nEnter Your choice:";
                                int choice_3;
                                cin >> choice_3;

                                switch (choice_3) {
                                    case 1: {
                                        selectionSort(array);
                                        display(array);
                                        break;
                                    }
                                    case 2: {
                                        if (student.issuedbook == 2) {
                                            cout << "\nYou already have issued 2 books.";
                                            cout << "\nPlease return them to issue another.";
                                            break;
                                        }
                                        cout << "\nEnter name of book:";
                                        string b;
                                        cin >> b;

                                        if (tree.containsNode(b)) {
                                            int u = hashmapping[b];
                                            if (arr[u][1] > 0) {
                                                student.issuedbook++;
                                                arr[u][1]--;

                                                time_t currentTime = time(0);
                                                cout << "Issue Date: " << put_time(localtime(&currentTime), "%d-%m-%Y") << endl;

                                                time_t returnTime = currentTime + 604800;
                                                cout << "Return Date: " << put_time(localtime(&returnTime), "%d-%m-%Y") << endl;

                                                if (student.book_no == 0) {
                                                    student.book1 = b;
                                                } else {
                                                    student.book2 = b;
                                                }
                                                student.book_no++;
                                            } else {
                                                cout << "\nNo copies of book are available.";
                                            }
                                        } else {
                                            cout << "\nBook not found in library.";
                                        }
                                        break;
                                        }
                                    case 3: {
                                        cout << "\nEnter name of book to return:";
                                        string r;
                                        cin >> r;

                                        if (r == student.book1) {
                                            student.book_no--;
                                            student.book1.clear();
                                            student.issuedbook--;
                                        } else if (r == student.book2) {
                                            student.book_no--;
                                            student.book2.clear();
                                            student.issuedbook--;
                                        } else {
                                            cout << "Invalid Input. Please try again.";
                                        }

                                        if (tree.containsNode(r)) {
                                            int a = hashmapping[r];
                                            arr[a][1]++;
                                        }
                                        break;
                                    }
                                    case 4: {
                                        e2 = true;
                                        break;
                                    }
                                }
                            }
                        } else {
                            cout << "Student not found.";
                        }
                        break;
                    }
                }
                break;
            
            case 3: {
                e1 = true;
                break;
            }
        }
    }
    return 0;
}
