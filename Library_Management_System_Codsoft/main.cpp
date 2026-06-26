#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Book
{
public:
    int book_Id;
    string title;
    string author;
    string category;
    bool issued;
    int issued_To_MemberId;
    string issue_Date;
};

class Member
{
public:
    int member_Id;
    string member_Name;
    string phone_Number;
};

class Library
{
public:
    int generate_BookId();
    int generate_MemberId();
    void add_Book();
    void display_Books();
    void add_Member();
    void display_Members();
    void search_MemberById();
    void search_By_Title();
    void search_By_Author();
    void issue_Book();
    void return_Book();
};
int Library::generate_BookId()
{
    ifstream file("books.txt");
    if (!file) return 1;

    string line;
    int max_id = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id_str;
        if (getline(ss, id_str, ',')) {
            try {
                int current_id = stoi(id_str);
                if (current_id > max_id) max_id = current_id;
            }
            catch (...) {}
        }
    }
    file.close();
    return max_id + 1;
}
int Library::generate_MemberId()
{
    ifstream file("members.txt");
    if (!file) return 101;

    string line;
    int max_id = 100;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id_str;
        if (getline(ss, id_str, ',')) {
            try {
                int current_id = stoi(id_str);
                if (current_id > max_id) max_id = current_id;
            }
            catch (...) {}
        }
    }
    file.close();
    return max_id + 1;
}

void Library::add_Book()
{
    Book b;
    b.book_Id = generate_BookId();
    b.issued = false;
    b.issued_To_MemberId = 0;
    b.issue_Date = "NA";

    cout << "Enter Book Title : ";
    getline(cin, b.title);

    cout << "Enter Author Name : ";
    getline(cin, b.author);

    cout << "Enter Category : ";
    getline(cin, b.category);

    ofstream file("books.txt", ios::app);
    file << b.book_Id << ","
        << b.title << ","
        << b.author << ","
        << b.category << ","
        << b.issued << ","
        << b.issued_To_MemberId << ","
        << b.issue_Date << endl;
    file.close();

    cout << "Book Added Successfully! Generated ID: " << b.book_Id << endl;
}

void Library::display_Books()
{
    ifstream file("books.txt");
    if (!file) {
        cout << "No book records found.\n";
        return;
    }
    string line;
    cout << "\n===== BOOK RECORDS =====\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, title, author, cat, issued, memId, date;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, cat, ',');
        getline(ss, issued, ',');
        getline(ss, memId, ',');
        getline(ss, date, ',');

        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
            << " | Status: " << (issued == "1" ? "Issued to Member " + memId : "Available") << "\n";
    }
    file.close();
}
void Library::add_Member()
{
    Member m;
    m.member_Id = generate_MemberId();
    cout << "Enter Member Name: ";
    getline(cin, m.member_Name);
    cout << "Enter Phone Number: ";
    getline(cin, m.phone_Number);
    ofstream file("members.txt", ios::app);
    file << m.member_Id << "," << m.member_Name << "," << m.phone_Number << endl;
    file.close();
    cout << "Member Added Successfully! Generated Member ID: " << m.member_Id << endl;
}
void Library::display_Members()
{
    ifstream file("members.txt");
    if (!file) {
        cout << "No member records found.\n";
        return;
    }
    string line;
    cout << "\n===== MEMBER RECORDS =====\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, phone;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone << "\n";
    }
    file.close();
}
void Library::search_MemberById()
{
    int id;
    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore();
    ifstream file("members.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string m_id, name, phone;
        getline(ss, m_id, ',');
        if (m_id == to_string(id)) {
            getline(ss, name, ',');
            getline(ss, phone, ',');
            cout << "\nFound Member -> ID: " << m_id << " | Name: " << name << " | Phone: " << phone << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Member Not Found!" << endl;
    file.close();
}
void Library::search_By_Title()
{
    string title;
    cout << "Enter Book Title: ";
    getline(cin, title);
    ifstream file("books.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line.find(title) != string::npos)
        {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) cout << "Book Not Found!" << endl;
    file.close();
}
void Library::search_By_Author()
{
    string author;
    cout << "Enter Author Name: ";
    getline(cin, author);
    ifstream file("books.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line.find(author) != string::npos)
        {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) cout << "Author Not Found!" << endl;
    file.close();
}
void Library::issue_Book()
{
    int b_id, m_id = 0;
    char memberType;
    cout << "Enter Book ID to Issue: ";
    cin >> b_id;
    cout << "Is the borrower a Regular Member (R) or New Member (N)? [R/N]: ";
    cin >> memberType;
    cin.ignore();
    if (memberType == 'R' || memberType == 'r') {
        cout << "Enter existing Member ID: ";
        cin >> m_id;
        cin.ignore();
        ifstream memFile("members.txt");
        string memLine;
        bool memberExists = false;
        while (getline(memFile, memLine)) {
            stringstream ss(memLine);
            string m_id_str;
            getline(ss, m_id_str, ',');
            if (m_id_str == to_string(m_id)) {
                memberExists = true;
                break;
            }
        }
        memFile.close();

        if (!memberExists) {
            cout << "Error: Member ID not found in the system! Please register first using Option 3.\n";
            return;
        }
    }
    else if (memberType == 'N' || memberType == 'n') {
        Member m;
        m.member_Id = generate_MemberId();
        m_id = m.member_Id;
        cout << "Enter New Member Name: ";
        getline(cin, m.member_Name);
        cout << "Enter Phone Number: ";
        getline(cin, m.phone_Number);
        ofstream file("members.txt", ios::app);
        file << m.member_Id << "," << m.member_Name << "," << m.phone_Number << endl;
        file.close();
        cout << "New Member Registered Automatically! Generated Member ID: " << m.member_Id << endl;
    }
    else {
        cout << "Invalid Option! Process Cancelled.\n";
        return;
    }
    ifstream file("books.txt");
    vector<string> records;
    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, cat, issued, memId, date;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, cat, ',');
        getline(ss, issued, ',');
        getline(ss, memId, ',');
        getline(ss, date, ',');
        if (id == to_string(b_id)) {
            if (issued == "1") {
                cout << "Book is already issued to someone else!\n";
                file.close();
                return;
            }
            issued = "1";
            memId = to_string(m_id);
            date = "22-06-2026";
            found = true;
        }
        records.push_back(id + "," + title + "," + author + "," + cat + "," + issued + "," + memId + "," + date);
    }
    file.close();
    if (found) {
        ofstream outFile("books.txt");
        for (const auto& rec : records) outFile << rec << endl;
        outFile.close();
        cout << "Book Issued Successfully to Member ID " << m_id << "!" << endl;
    }
    else {
        cout << "Book ID not found." << endl;
    }
}
void Library::return_Book()
{
    int b_id, days;
    cout << "Enter Book ID to Return: ";
    cin >> b_id;
    cout << "Enter number of days the book was kept by borrower: ";
    cin >> days;
    cin.ignore();
    ifstream file("books.txt");
    vector<string> records;
    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, cat, issued, memId, date;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, cat, ',');
        getline(ss, issued, ',');
        getline(ss, memId, ',');
        getline(ss, date, ',');
        if (id == to_string(b_id)) {
            issued = "0";
            memId = "0";
            date = "NA";
            found = true;
        }
        records.push_back(id + "," + title + "," + author + "," + cat + "," + issued + "," + memId + "," + date);
    }
    file.close();
    if (found) {
        ofstream outFile("books.txt");
        for (const auto& rec : records) outFile << rec << endl;
        outFile.close();
        cout << "\nBook Returned Successfully!" << endl;
        if (days > 14) {
            int fine = (days - 14) * 2;
            cout << "⚠️ Overdue Notice: Book kept for " << days << " days (Limit: 14 days)." << endl;
            cout << "💰 Late Return Fine Calculated: Rs. " << fine << endl;
        }
        else {
            cout << "✅ Returned on time within 14 days. No fine!" << endl;
        }
    }
    else {
        cout << "Book ID not found." << endl;
    }
}
int main()
{
    Library lib;
    int choice;
    while (true)
    {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n2. Display Books\n3. Add Member\n4. Display Members\n";
        cout << "5. Search Member By ID\n6. Search By Title\n7. Search By Author\n";
        cout << "8. Issue Book\n9. Return Book\n10. Exit\n";
        cout << "Enter Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore();
        if (choice == 1) lib.add_Book();
        else if (choice == 2) lib.display_Books();
        else if (choice == 3) lib.add_Member();
        else if (choice == 4) lib.display_Members();
        else if (choice == 5) lib.search_MemberById();
        else if (choice == 6) lib.search_By_Title();
        else if (choice == 7) lib.search_By_Author();
        else if (choice == 8) lib.issue_Book();
        else if (choice == 9) lib.return_Book();
        else if (choice == 10) break;
        else cout << "Invalid Choice!" << endl;
    }
    return 0;
}