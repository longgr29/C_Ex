#include <iostream>
#include <string>
#include <vector>   
#include <windows.h>

using namespace std;

enum gender
{
    MALE,
    FEMALE
};

class Student
{
private:
    int id;
    std::string name;
    gender sex;
    int age;
    double mathScore;
    double physicsScore;
    double chemistryScore;
    double gpa;

public:
    Student(int id, std::string name, gender sex, int age, double mathScore, double physicsScore, double chemistryScore);
    int getId() const;
    string getName() const;
    gender getSex() const;
    int getAge() const;
    double getMathScore() const;
    double getPhysicsScore() const;
    double getChemistryScore() const;
    double getGpa() const;
};

Student::Student(int id, std::string name, gender sex, int age, double mathScore, double physicsScore, double chemistryScore)
{
    this->id = id;
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->mathScore = mathScore;
    this->physicsScore = physicsScore;
    this->chemistryScore = chemistryScore;
    this->gpa = (mathScore + physicsScore + chemistryScore) / 3.0;
}

int Student::getId() const
{
    return this->id;
}

string Student::getName() const
{
    return this->name;
}

gender Student::getSex() const
{
    return this->sex;
}

int Student::getAge() const
{
    return this->age;
}

double Student::getMathScore() const
{
    return this->mathScore;
}

double Student::getPhysicsScore() const
{
    return this->physicsScore;
}

double Student::getChemistryScore() const
{
    return this->chemistryScore;
}

double Student::getGpa() const
{
    return this->gpa;
}

class StudentManager
{
private:
    // stored students in a vector
    vector<Student> students;

public:
    void add_student(Student student);
    void update_student_by_id(int id, Student newStudent);
    void delete_student_by_id(int id);
    void search_students_by_name(std::string name);
    void sort_students_by_gpa();
    void sort_students_by_name();
    void display_students() const;
    void display_students(const vector<Student> studentList) const;
};

void StudentManager::add_student(Student student)
{
    students.push_back(student);
}

void StudentManager::update_student_by_id(int id, Student newStudent)
{
    for (auto &student : students)
    {
        if (student.getId() == id)
        {
            student = newStudent;
            break;
        }
    }
}

void StudentManager::delete_student_by_id(int id)
{
    for (auto student = students.begin(); student != students.end(); ++student)
    {
        if (student->getId() == id)
        {
            this->students.erase(student);
            break;
        }
    }
}

void StudentManager::search_students_by_name(std::string name)
{
    std::vector<Student> result;
    for (auto student = students.begin(); student != students.end(); ++student)
    {
        if (student->getName() == name)
        {
            result.push_back(*student);
        }
    }
    cout << "Search result:" << endl;
    display_students(result);
}

void StudentManager::sort_students_by_gpa()
{
    for (size_t i = 1; i < students.size(); i++)
    {
        Student selectedStudent = students[i];
        size_t j = i - 1;
        while (j >= 0 && selectedStudent.getGpa() < students[j].getGpa())
        {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = selectedStudent;
    }
}

void StudentManager::sort_students_by_name()
{
    for (size_t i = 1; i < students.size(); i++)
    {
        Student selectedStudent = students[i];
        size_t j = i - 1;
        while (j >= 0 && selectedStudent.getName() < students[j].getName())
        {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = selectedStudent;
    }
}

void StudentManager::display_students() const
{
    cout << "Students list: " << endl;
    display_students(students);
}

void StudentManager::display_students(const vector<Student> studentList) const
{
    for (const auto &student : studentList)
    {
        std::cout << "ID: " << student.getId() << ", Name: " << student.getName();
        std::cout << ", Sex: " << (student.getSex() == gender::MALE ? "Male" : "Female") << ", Age: " << student.getAge() << ", Math Score: " << student.getMathScore() << ", Physics Score: " << student.getPhysicsScore() << ", Chemistry Score: " << student.getChemistryScore() << ", GPA: " << student.getGpa() << std::endl;
    }
}

struct MenuOption
{
    char choice;
    char const *selectionText;
    void (*processingFunction)(void);
};

StudentManager class1;

void add_student(void) {
    int id;
    std::string name;
    gender sex;
    string strSex;
    int age;
    double mathScore;
    double physicsScore;
    double chemistryScore;

    system("cls");
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Add A New Student\n"
        "------------------------------\n";
    cout << menu_title;
    cout << "Enter ID: " ;
    cin >> id;
    cout << endl << "Enter name: ";
    cin >> name;

    while(strSex != "male" && strSex != "female") {
        cout << endl << "Enter sex (male/female): ";
        cin >> strSex;
        (strSex == "male")?(sex = MALE):(sex = FEMALE);
    }
    
    cout << endl << "Enter age: ";
    cin >> age;
    cout << endl << "Enter math score: ";
    cin >> mathScore;
    cout << endl << "Enter physics score: ";
    cin >> physicsScore;
    cout << endl << "Enter chemistry score: ";
    cin >> chemistryScore;

    class1.add_student({id, name, sex, age, mathScore, physicsScore, chemistryScore});
    cout << endl << "Add student successful" ;
    Sleep(1);
}

void update_student_by_id(){
    int id;
    std::string name;
    gender sex;
    string strSex;
    int age;
    double mathScore;
    double physicsScore;
    double chemistryScore;

    system("cls");
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Update A Student By ID\n"
        "------------------------------\n";
    cout << menu_title;
    cout << "Enter ID: " ;
    cin >> id;
    cout << endl << "Enter name: ";
    cin >> name;

    while((strSex != "male") && (strSex != "female")) {
        cout << endl << "Enter sex (male/female): ";
        cin >> strSex;
        (strSex == "male")?(sex = MALE):(sex = FEMALE);
    }
    
    cout << endl << "Enter age: ";
    cin >> age;
    cout << endl << "Enter math score: ";
    cin >> mathScore;
    cout << endl << "Enter physics score: ";
    cin >> physicsScore;
    cout << endl << "Enter chemistry score: ";
    cin >> chemistryScore;

    class1.update_student_by_id(id, {id, name, sex, age, mathScore, physicsScore, chemistryScore});
    cout << endl << "Update student successful" ;
    Sleep(1);
}

void delete_student_by_id(){
    int id;
    system("cls");
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Delete A Student By ID\n"
        "------------------------------\n";
    cout << menu_title;
    cout << "Enter ID: " ;
    cin >> id;

    class1.delete_student_by_id(id);
    cout << endl << "Delete student successful" ;
    Sleep(1);
}

void search_students_by_name(){
    string name;
    system("cls");
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Search Students By Name\n"
        "------------------------------\n";
    cout << menu_title;
    cout << "Enter name: " ;
    cin >> name;

    class1.search_students_by_name(name);
    Sleep(1);
}

void sort_students_by_gpa(){
    system("cls");
    class1.sort_students_by_gpa();
    cout << endl << "Sort student successful" ;
    Sleep(1);
}

void sort_students_by_name(){
    system("cls");
    class1.sort_students_by_name();
    cout << endl << "Sort student successful" ;
    Sleep(1);
}

void display_students(){
    system("cls");
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Display Students\n"
        "------------------------------\n";
    cout << menu_title;
    class1.display_students();
    system("pause");
}

MenuOption mainMenu[] =
{
        {'1', "Add a new student", add_student},
        {'2', "Update a student by ID", update_student_by_id},
        {'3', "Delete a student by ID", delete_student_by_id},
        {'4', "Search students by name", search_students_by_name},
        {'5', "Sort students by GPA", sort_students_by_gpa},
        {'6', "Sort students by name", sort_students_by_name},
        {'7', "Display students", display_students},
};

int main()
{
    size_t quantitySelections = sizeof(mainMenu) / sizeof(mainMenu[0]);
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Main Menu\n"
        "------------------------------\n";
    
    while(1){
        cout << menu_title;
        for (size_t i = 0; i < quantitySelections; ++i)
        {
            std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
        }
        char choice;
        cin >> choice;
        for (size_t i = 0; i < quantitySelections; ++i)
        {
            if (choice == mainMenu[i].choice)
            {
                (mainMenu[i].processingFunction)();
                break;
            }
        }
        
    }
    return 0;
}