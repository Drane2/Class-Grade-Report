//
//  main.cpp
//  PP1-Code
//
//  Created by Taj on 4/28/21.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int fileLength(string file)
{
    ifstream myfile(file);
    int numLines = 0;
    string line;

    while(getline(myfile, line))
    {
        numLines++;
    }

    return numLines;
}

// Declare file names
string inputFile = "CIT1325.txt";
string inputFile2 = "CIT1350.txt";
string outputFile = "ClassGradeReport.txt";

// Open files
ifstream myfile(inputFile);
ifstream myfile2(inputFile2);

// Global variables
int class1_size = fileLength(inputFile)-1;
int class2_size = fileLength(inputFile2);
int allStudents = class1_size + class2_size;
int width = 10;

string newl = "\n";

// Declare a struct with variables
struct info
{
    string firstName, lastName;
    double t1, t2, t3, t4, final;
    double avg;
    char letterGrade;
};

// Return letter grade based on average
char letterGrade(double avg)
{
    char grade;
    
    if(avg<60){
        grade = 'F';
    }
    else if((avg>60)&&(avg<70)){
        grade = 'D';
    }
    else if((avg>70)&&(avg<80)){
        grade = 'C';
    }
    else if((avg>80)&&(avg<90)){
        grade = 'B';
    }
    else grade = 'A';
    
    return grade;
}

// Read text from file and store into an array
void storeInfo(string file, string file2, struct info arr[])
{
    for(int i=0;i<class1_size;i++)
    {
        myfile >> arr[i].firstName;
        myfile >> arr[i].lastName;
        myfile >> arr[i].t1;
        myfile >> arr[i].t2;
        myfile >> arr[i].t3;
        myfile >> arr[i].t4;
        myfile >> arr[i].final;
    }
    for(int i=class1_size;i<allStudents;i++)
    {
        myfile2 >> arr[i].firstName;
        myfile2 >> arr[i].lastName;
        myfile2 >> arr[i].t1;
        myfile2 >> arr[i].t2;
        myfile2 >> arr[i].t3;
        myfile2 >> arr[i].t4;
        myfile2 >> arr[i].final;
    }
}

double max(vector<double> data)
{
    double temp = 0.0;
    for(int i=0;i<data.size();i++)
    {
        if(data[i]>temp)
        {
            temp = data[i];
        }
    }
    return temp;
}

double average(vector<double> data)
{
    double temp = 0.0;
    for(int i=0;i<data.size();i++)
    {
        temp += data[i];
    }
    return temp/data.size();
}

static void extracted(std::ofstream &classreport) {
    vector<string> labels = {"First", "Last", "Test 1",
        "Test2", "Test 3", "Test 4",
        "Final", "Average", "Grade"};
    
    for(int i=0;i<labels.size();i++)
    {
        classreport << setw(width) << left << labels[i];
    }
}

static void printData(struct info *student, vector<double> &studentAvg)
{
    ofstream classreport("ClassGradeReport.txt");
    extracted(classreport);
    classreport << "\n\n";
    
    for(int i=0;i<allStudents;i++)
    {
        string first = student[i].firstName;
        string last = student[i].lastName;
        double t1 = student[i].t1;
        double t2 = student[i].t2;
        double t3 = student[i].t3;
        double t4 = student[i].t4;
        double final = student[i].final;
        double avg = (t1+t2+t3+t4+final)/5;
        
        // Formats and prints the data
        classreport << setw(width) << left << first
        << setw(width) << last << setw(width) << t1
        << setw(width) << t2   << setw(width) << t3
        << setw(width) << t4   << setw(width) << final
        << setw(width) << avg  << setw(width) << letterGrade(avg) << newl;
        
        // Stores the student average into a vector
        studentAvg[i] = avg;
    }
}

// To access a specific students info
void findStudent(struct info *student, vector<double> avg)
{
    string first, last;
    
    cout << newl << "+ First name (case-sensitive): ";
    cin >> first;
    cout << newl << "+ Last name (case-sensitive): ";
    cin >> last;
    
    for(int i=0;i<allStudents;i++)
    {
        if((first==student[i].firstName) && (last==student[i].lastName))
        {
            cout << newl << setw(width) << left << first
            << setw(width) << last << setw(width) << student[i].t1
            << setw(width) << student[i].t2   << setw(width) << student[i].t3
            << setw(width) << student[i].t4   << setw(width) << student[i].final
            << setw(width) << avg[i]  << setw(width) << letterGrade(avg[i]) << newl;
        }
    }
}
int main()
{
    // Declare variables
    char yesno;
    
    // Open the output file
    ofstream classreport("ClassGradeReport.txt", std::ios_base::app | std::ios_base::out);
    
    if((classreport.is_open()) && (myfile.is_open()) && (myfile2.is_open()))
    {
        // Title
        cout << "Class Grade Report\n\n";
        
        // Create an array where each index represents a student
        // and store info from both .txt files
        struct info student[allStudents];
        storeInfo(inputFile, inputFile2, student);
        
        cout << "[1/6] Storing info from " << inputFile << " and " << inputFile2 << "..." << newl;
        
        // Create vector for each test
        // and store the grades
        vector<double> t1(allStudents);
        vector<double> t2(allStudents);
        vector<double> t3(allStudents);
        vector<double> t4(allStudents);
        vector<double> final(allStudents);
        vector<double> studentAvg(allStudents);
        
        for(int i=0;i<allStudents;i++)
        {
            t1[i] = student[i].t1;
            t2[i] = student[i].t2;
            t3[i] = student[i].t3;
            t4[i] = student[i].t4;
            final[i] = student[i].final;
        }
        
        // Print the class report
        printData(student, studentAvg);
        classreport << newl;
        
        // Print the average for each test
        classreport << setprecision(4);
        classreport << newl << setw(width*2) << left << "Test Averages:"
        << setw(width) << average(t1) << setw(width)  << average(t2)
        << setw(width) << average(t3) << setw(width)  << average(t4)
        << setw(width) << average(final);
        
        cout << "[2/6] Calculating average..." << newl;
        
        // Print the highest grade of each test
        classreport << newl << setw(width*2) << left << "Highest Grade:"
        << setw(width) << max(t1) << setw(width)  << max(t2)
        << setw(width) << max(t3) << setw(width)  << max(t4)
        << setw(width) << max(final);
        
        cout << "[3/6] Calculating highest grade for each test..." << newl;
        
        // Print average of every test
        double totalAvg = ((average(t1)/t1.size()) + (average(t2)/t2.size()) + (average(t3)/t3.size())
                        +  (average(t4)/t4.size()) + (average(final)/final.size()))/(5*allStudents);
        classreport << newl << setw(width*2) << "Total Average:" << totalAvg << newl;
        
        cout << "[4/6] Calculating average of every test..." << newl;
        
        // Print highest class grade
        classreport << newl << setw(width*2) << left << "Highest Avg:"
                    << setw(width) << left << max(studentAvg);
        for (int i=0;i<allStudents;i++)
        {
            if(studentAvg[i] == max(studentAvg))
            {
                classreport << student[i].firstName << " " << student[i].lastName << newl;
            }
        }
        
        cout << "[5/6] Calculating highest class grade..." << newl;
        
        cout << "[6/6] Printing report to " << outputFile << "..." << newl;
        cout << newl << "Done!\n";
        
        for(int i=0;i<1;)
        {
            cout << newl << "+ Would you like to view a student's info? (y/n): ";
            cin >> yesno;
            
            if(yesno=='y')
            {
                findStudent(student, studentAvg);
            }
            if(yesno=='n')
            {
                cout << newl;
                i++;
            }
        }
    }
    
    else cout << "\nError: file missing\n";
    
    classreport.close();
    return 0;
}
