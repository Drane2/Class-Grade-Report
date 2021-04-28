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

// Global variables
int class1_size = 25;
int class2_size = 20;
int allStudents = class1_size + class2_size;

string newl = "\n";

// Declare file names
string inputFile = "CIT1325.txt";
string inputFile2 = "CIT1350.txt";
string outputFile = "ClassGradeReport.txt";

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
    ifstream myfile(file);
    ifstream myfile2(file2);
    
    if((myfile.is_open())&&(myfile2.is_open()))
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

static void printData(struct info *student, vector<double> &studentAvg)
{
    ofstream classreport("ClassGradeReport.txt");
    classreport << "First   Last    T1     T2     T3     T4    Final   Avg    Grade" << newl << newl;
    
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
        
        // Formats the data
        classreport << setw(8) << left << first
        << setw(8) << last << setw(7) << t1
        << setw(7) << t2   << setw(7) << t3
        << setw(7) << t4   << setw(7) << final
        << setw(9) << avg  << setw(7) << letterGrade(avg) << newl;
        
        // Stores the student average into a vector
        studentAvg[i] = avg;
    }
}

int main()
{
    // Open the output file
    ofstream classreport("ClassGradeReport.txt", std::ios_base::app | std::ios_base::out);
    
    // Create an array where each index represents a student
    // and store info from both .txt files
    struct info student[allStudents];
    storeInfo(inputFile, inputFile2, student);
    
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
    classreport << newl << setw(16) << left << "Test Averages:"
    << setw(7) << average(t1) << setw(7)  << average(t2)
    << setw(7) << average(t3) << setw(7)  << average(t4)
    << setw(7) << average(final);
    
    // Print the highest grade of each test
    classreport << newl << setw(16) << left << "Highest Grade:"
    << setw(7) << max(t1) << setw(7)  << max(t2)
    << setw(7) << max(t3) << setw(7)  << max(t4)
    << setw(7) << max(final);
    
    // Print average of every test
    double totalAvg = ((average(t1)/t1.size()) + (average(t2)/t2.size()) + (average(t3)/t3.size()) + (average(t4)/t4.size()) + (average(final)/final.size()))/(5*allStudents);
    classreport << newl << "Total Average:  " << totalAvg << newl;
    
    // Print highest class grade
    classreport << newl << setw(16) << left << "Highest Avg: " << setw(6) << left << max(studentAvg) << " ";
    for (int i=0;i<allStudents;i++)
    {
        if(studentAvg[i] == max(studentAvg))
        {
            classreport << student[i].firstName << " " << student[i].lastName << newl;
        }
    }
    
    classreport.close();
    return 0;
}
