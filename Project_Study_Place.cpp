#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Abstract class
class StudyItem
{
protected:
    string sTitle;
    string sCreatedAt;

public:
    // Constructor
    StudyItem(string title, string createdAt) : sTitle(title), sCreatedAt(createdAt) {};

    //virtual fuction 
    virtual void displayInfo() = 0;
    virtual ~StudyItem() {}; // Virtual destructor, khi nao co ham ao thi cung phai di kem mot ham huy ao
    virtual void saveToFile(ofstream& outFile) = 0;
};

//Class Assigment (Baitap)
class Assignment : public StudyItem
{
private:
    string sDeadline;
    bool bIsCompleted;

public:
    //Constructor
    Assignment(string title, string createdAt, string deadline) : StudyItem(title, createdAt), sDeadline(deadline), bIsCompleted(false) {};

    //override virtual function
    void displayInfo() override { cout << "Assignment: " << sTitle << ", Created At: " << sCreatedAt << ", Deadline: " << sDeadline << ", Completed: " << (bIsCompleted ? "Yes" : "No") << endl; }
    void saveToFile(ofstream& outFile) override 
    {
        outFile << "[ASSIGNMENT]" << endl;
        outFile << sTitle << endl;
        outFile << sCreatedAt << endl;
        outFile << sDeadline << endl;
        outFile << bIsCompleted << endl;
    }
    //behavioral methods
    void markAsCompleted() { bIsCompleted = true; }
};

//Class Note (GHICHU)
class Note : public StudyItem
{
private:
    string sContent;
public:
    //Constructor
    Note(string title, string createdAt, string content) : StudyItem( title, createdAt), sContent(content) {};

    void displayInfo() override 
    {
        cout << "[Ghi chu] " << sTitle << "-" << sCreatedAt << endl;
        cout << " Noi dung: " << sContent << endl;
    }
    void saveToFile(ofstream& outFile) override
    {
        outFile << "[NOTE]" << endl;
        outFile << sTitle << endl;
        outFile << sCreatedAt << endl;
        outFile << sContent << endl;
    }
};

//Luu dia chi cua cac studyitem
class Course
{
private:
    string sCourseName;
    vector<StudyItem*> vItems;
public:
    Course(string coursename) : sCourseName(coursename) {};

    void addItem(StudyItem* item)
    {
        vItems.push_back(item);
    }

    void displayALL()
    {
        cout << "Mon hoc: " << sCourseName << endl;
        for(int i=0; i < vItems.size(); i++)
        {
            vItems[i]->displayInfo();
        }
    }

    void saveData()
    {
        ofstream outFile("Data.txt");

        if(outFile.is_open())
        {
            for(int i=0; i<vItems.size(); i++)
            {
                vItems[i]->saveToFile(outFile);
            }
            outFile.close();
            cout << "Da luu thanh cong!";
        }
        else 
            cout << "Loi khong luu duoc!";
    }

    virtual ~Course()
    {
        for(int i=0; i < vItems.size(); i++)
            delete vItems[i];
    }

    void loadData()
    {
        ifstream inFile("Data.txt");

        //File khong mo duoc. Co the lan dau hoac chua co file
        if(!inFile.is_open())
        {
            cout << "Chao ban lan dau den voi StudyItem!" << endl;
            return;
        }

        string line;
        while(getline(inFile, line))
        {
            if(line == "[ASSIGNMENT]")
            {
                string title, createdAt, deadline, isCompletedStr;

                getline(inFile, title);
                getline(inFile, createdAt);
                getline(inFile, deadline);
                getline(inFile, isCompletedStr);

                StudyItem* a = new Assignment(title, createdAt, deadline);

                Assignment* ptr = dynamic_cast<Assignment*>(a);
                if(ptr != NULL && isCompletedStr == "1")
                {
                    ptr->markAsCompleted();
                }

                addItem(a);
            }

            if(line == "[NOTE]")
            {
                string title, createdAt, content;

                getline(inFile, title);
                getline(inFile, createdAt);
                getline(inFile, content);

                StudyItem* a = new Note(title, createdAt, content);

                addItem(a);
            }
        }
    };
};

int main()
{
    Course myCourse("Ky thuat du lieu");

    myCourse.loadData();

    int choice;
    do
    {
        cout << "--- QUAN LY MON HOC ---" << endl;
        cout << "1. Them bai tap (Assignment)" << endl;
        cout << "2. Them ghi chu (Note)" << endl;
        cout << "3. Xem toan bo danh sach" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon:";

        cin >> choice;
        cin.ignore();

        //switch-case
        switch(choice)
        {
            case 1://Assignment
            {
                string sTitle;
                cout << "Nhap ten bai tap: ";
                getline(cin, sTitle);

                string sCreatedAt;
                cout << "Nhap thoi gian dang bai tap: ";
                getline(cin, sCreatedAt);

                string sDeadline;
                cout << "Nhap thoi han nop bai tap: ";
                getline(cin, sDeadline);

                StudyItem* a1 = new Assignment(sTitle, sCreatedAt, sDeadline);
                myCourse.addItem(a1);
                cout << "=> Da them bai tap thanh cong!\n";
                break;
            } 

            case 2: // Note
            {
                string sTitle;
                cout << "Nhap ten ghi chu: ";
                getline(cin, sTitle);

                string sCreatedAt;
                cout << "Nhap thoi gian dang ghi chu: ";
                getline(cin, sCreatedAt);

                string sContent;
                cout << "Nhap noi dung ghi chu: ";
                getline(cin, sContent);

                StudyItem* a2 = new Note(sTitle, sCreatedAt, sContent);
                myCourse.addItem(a2);
                cout << "=> Da them ghi chu thanh cong !\n";
                break;
            }

            case 3: // Xem toan bo danh sach
            {
                myCourse.displayALL();
                break;
            }

            case 0:
            {
                myCourse.saveData();
                cout << "Dang thoat chuong trinh...\n";
                break;
            }

            default:
                cout << "Lua chon khong hop le, vui long nhap lai!\n";
        }        
    } while (choice != 0);

    return 0;
}