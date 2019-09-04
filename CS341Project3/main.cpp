//
//  main.cpp
//  CS341Project3
//
//  Created by Raja Patel on 2/7/19.
//  Copyright © 2019 Raja Patel. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <map>
#include "gradeutil.h"
using namespace std;


int numOfStudents(Dept d)
{
    int total=0;
    for(int i=0; i<d.Courses.size(); i++)
    {
        total+=d.Courses[i].getNumStudents();
    }
    return total;
}

void printCourseInfo(const Course c)
{
    cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
    cout << " # students: " << c.getNumStudents() << endl;
    if(c.getGradingType() == Course::Letter)
    {
        cout << " course type: letter" << endl;
    }
    else if(c.getGradingType() == Course::Satisfactory)
    {
        cout << " course type: satisfactory" << endl;
    }
    else if(c.getGradingType() == Course::Unknown)
    {
        cout << " course type: unknown" << endl;
    }
    
    int DFW;
    int N;
    cout << " grade distribution (A-F): "
    << GetGradeDistribution(c).PercentA << "%, "
    << GetGradeDistribution(c).PercentB << "%, "
    << GetGradeDistribution(c).PercentC << "%, "
    << GetGradeDistribution(c).PercentD << "%, "
    << GetGradeDistribution(c).PercentF << "%"
    << endl;
    cout << " DFW rate: " << GetDFWRate(c, DFW, N) << "%" << endl;
}


void summaryAll(vector <Dept> d)
{
    int N;
    int DFW;
    for(auto i: d)
    {
        cout<<i.Name<<":\n";
        cout<<" # courses taught: "<<i.Courses.size()<<endl;
        int totStudent=numOfStudents(i);
        cout<<" # students taught: "<<totStudent<<endl;
        cout<<" grade distribution (A-F): "
        <<GetGradeDistribution(i).PercentA<<"%, "
        <<GetGradeDistribution(i).PercentB<<"%, "
        <<GetGradeDistribution(i).PercentC<<"%, "
        <<GetGradeDistribution(i).PercentD<<"%, "
        <<GetGradeDistribution(i).PercentF<<"%"
        <<endl;
        cout<<" DFW rate: "<<GetDFWRate(i,DFW,N)<<"%"<<endl;
    }
    
}


void summaryDept(vector <Dept> d, string choice, bool deptnamecheck)
{
    int DFW, N;
    for(auto i: d)
    {
        if(choice == i.Name)
        {
            cout<<i.Name<<":\n";
            cout<<" # courses taught: "<<i.Courses.size()<<endl;
            int totStudent=numOfStudents(i);
            cout<<" # students taught: "<<totStudent<<endl;
            cout<<" grade distribution (A-F): "
            <<GetGradeDistribution(i).PercentA<<"%, "
            <<GetGradeDistribution(i).PercentB<<"%, "
            <<GetGradeDistribution(i).PercentC<<"%, "
            <<GetGradeDistribution(i).PercentD<<"%, "
            <<GetGradeDistribution(i).PercentF<<"%"
            <<endl;
            cout<<" DFW rate: "<<GetDFWRate(i,DFW,N)<<"%"<<endl;
            deptnamecheck=1;
            break;
        }
    }
    if(deptnamecheck==0)
    {
        cout<<"**dept not found"<<endl;
    }
    
}


void searchDept(vector <Dept> d, string choice, string instructorPrefix, int courseNum, stringstream& ss )
{
    Dept tempDept;
    for(auto i : d)
    {
        if(i.Name==choice)
        {
            tempDept = i;
            break;
        }
    }
    
    vector <Course> courseVec;
    if(ss.fail())
    {
        courseVec = FindCourses(tempDept,instructorPrefix);
        if(courseVec.size() == 0)
        {
            cout<<"**none found"<<endl;
        }
    }
    else
    {
        courseVec = FindCourses(tempDept,courseNum);
        if(courseVec.size() == 0)
        {
            cout<<"**none found"<<endl;
        }
    }
    
    for(int j=0; j<courseVec.size(); j++)
    {
        printCourseInfo(courseVec[j]);
    }
}


void searchAll(College C , string instructorPrefix, int courseNum, stringstream& ss)
{
    vector <Course> courseVec;
    
    if(ss.fail())
    {
        courseVec = FindCourses(C,instructorPrefix);
        if(courseVec.size() == 0)
        {
            cout<<"**none found"<<endl;
        }
    }
    else
    {
        courseVec = FindCourses(C,courseNum);
        if(courseVec.size() == 0)
        {
            cout<<"**none found"<<endl;
        }
    }
    
    for(int j=0; j<courseVec.size(); j++)
    {
        printCourseInfo(courseVec[j]);
    }
}


void unknownSearch(string choice, College College, vector <Dept> d )
{
    bool check = 0;
    vector<Course> courseVec;
    
    if(choice == "all")
    {
        for(Dept d : College.Depts)
        {
            for(Course c : d.Courses)
            {
                if(c.getGradingType() == Course::Unknown)
                {
                    courseVec.push_back(c);
                }
            }
        }
        
        if(courseVec.size()<= 0){
            cout << "**none found" << endl;
        }
        
        sort(courseVec.begin(), courseVec.end(), [](const Course& c1, const Course& c2) -> bool
      {
            
            if(c1.Dept < c2.Dept)
            {
                return true;
            }
            else if( (c1.Dept == c2.Dept) && (c1.Number < c2.Number) )
            {
                return true;
            }
            else if( (c1.Dept == c2.Dept) && (c1.Number == c2.Number) && (c1.Section < c2.Section) )
            {
                return true;
            }
            else return false;
            
        });
    }
    
    
    else
    {
        for(Dept d : College.Depts)
        {
            if(d.Name == choice)
            {
                for(Course c : d.Courses)
                {
                    if(c.getGradingType() == Course::Unknown)
                    {
                        courseVec.push_back(c);
                    }
                }
                check = 1;
                break;
            }
        }
        
        if(!check)
        {
            cout << "**dept not found" << endl;
        }
        
        if(courseVec.size()<= 0)
        {
            cout << "**none found" << endl;
        }
        
        sort(courseVec.begin(), courseVec.end(), [](const Course& c1, const Course& c2) -> bool
             {
                 if(c1.Number < c2.Number)
                 {
                     return true;
                 }
                 else if(c1.Number == c2.Number)
                 {
                     return c1.Section < c2.Section;
                 }
                 else
                 {
                     return false;
                 }
             });
    }
    
    
    for(Course c : courseVec)
    {
        printCourseInfo(c);
    }
}


void dfwfunction(string choice, College College,vector <Dept> d, double threshold)
{
    int DFW,N;
    vector <Course> courseVec;
    
    if(choice=="all")
    {
        courseVec = FindCourses(College,"");
    }
    else
    {
        bool check=0;
        for(auto i: d)
        {
            if(choice==i.Name)
            {
                check=1;
                courseVec = FindCourses(i,"");
                break;
            }
        }
        if(check == 0)
        {
            cout<<"**none found\n";
        }
    }
    
    sort(courseVec.begin(),courseVec.end(),[](Course a,Course b)
         {
             int DFW,N;
             double x1 = GetDFWRate(a,DFW,N);
             double x2 = GetDFWRate(b,DFW,N);
             if(x1 == x2)
             {
                 if(a.Dept == b.Dept)
                 {
                     if(a.Number==b.Number)
                     {
                         return a.Section<b.Section;
                     }
                     return a.Number<b.Number;
                 }
                 return a.Dept<b.Dept;
             }
             return x1>x2;
             
         });
    
    for(int j=0; j<courseVec.size(); j++)
    {
        bool check = 0;
        if( GetDFWRate(courseVec[j],DFW,N) < threshold)
        {
            check=1;
            continue;
        }
        
        if (check == 1)
        {
            cout<<"**none found"<<endl;
        }
        
        printCourseInfo(courseVec[j]);
        
    }
    
    
}


void letterA(string choice, College College,vector <Dept> d, double threshold)
{
    vector<Course> courseVec;
    bool check = 0;
    
    if(choice == "all")
    {
        for(Dept d : College.Depts)
        {
            for(Course c : d.Courses)
            {
                if(GetGradeDistribution(c).PercentA > threshold)
                {
                    courseVec.push_back(c);
                }
            }
        }
        
        if(courseVec.size() == 0)
        {
            cout << "**none found" << endl;
        }
        
    }
    
    else
    {
        for(Dept d : College.Depts)
        {
            if(d.Name == choice)
            {
                for(Course c : d.Courses)
                {
                    if(GetGradeDistribution(c).PercentA > threshold)
                    {
                        courseVec.push_back(c);
                    }
                }
                check = 1;
                break;
            }
        }
        
        if(!check)
        {
            cout << "**dept not found" << endl;
        }
        
        if(courseVec.size() == 0)
        {
            cout << "**none found" << endl;
        }
    }
    
    
    sort(courseVec.begin(), courseVec.end(), [](const Course& c1, const Course& c2) -> bool
         {
             double t1 = GetGradeDistribution(c1).PercentA;
             double t2 = GetGradeDistribution(c2).PercentA;
             if(t1 > t2)
             {
                 return true;
             }
             
             else if( (t1 == t2) && (c1.Dept < c2.Dept) )
             {
                 return true;
             }
             else if( (t1 == t2) && (c1.Dept == c2.Dept) && (c1.Number < c2.Number) )
             {
                 return true;
             }
             else if( (t1 == t2) && (c1.Dept == c2.Dept) && (c1.Number == c2.Number) && ( c1.Section < c2.Section) )
             {
                 return true;
             }
             else
             {
                 return false;
             }
             
         });
    
    for(Course c : courseVec)
    {
        printCourseInfo(c);
    }
}


int main(int argc, const char * argv[])
{
    // insert code here...
    string filename;
    cin >> filename;
    ifstream file(filename);
    
    if (!file.good())
    {
        cout << "cannot open file!" << endl;
        return 0;
    }
    
    string line;
    getline(file,line);
    getline(file,line);
    
    cout << fixed;
    cout << setprecision(2);
    
    vector <Dept> dept;
    College College;
    
    int allStudents = 0;
    
    while(getline(file, line))
    {
        Course C = ParseCourse(line);
        
        allStudents += C.getNumStudents();
        
        bool deptCheck = 0;
        for(int i=0; i < dept.size(); i++)
        {
            if(C.Dept==dept[i].Name)
            {
                dept[i].Courses.push_back(C);
                deptCheck = 1;
                break;
            }
        }
        if (deptCheck == 0)
        {
            Dept d;
            d.Name = C.Dept;
            d.Courses.push_back(C);
            dept.push_back(d);
        }
    }
    
    
    int allCourses = 0;
    
    for(int i = 0; i<dept.size(); i++)
    {
        allCourses += dept[i].Courses.size();
    }
    
    sort(dept.begin(),dept.end(),[](Dept a, Dept b)
         {
             return a.Name<b.Name;
         });
    
    College.Depts = dept;
    
    if(filename == "fall-2018.csv")
    {
        College.Name="College of Engineering, Fall 2018";
    }
    else if (filename == "spring-2018.csv")
    {
        College.Name="College of Engineering++, Spring 2018";
    }
    
    cout<<"** "<<College.Name<<" **"<<endl;
    cout<<"# of courses taught: "<<allCourses<<endl;
    cout<<"# of students taught: "<<allStudents<<endl;
    cout<<"grade distribution (A-F): "
    <<GetGradeDistribution(College).PercentA<<"%, "
    <<GetGradeDistribution(College).PercentB<<"%, "
    <<GetGradeDistribution(College).PercentC<<"%, "
    <<GetGradeDistribution(College).PercentD<<"%, "
    <<GetGradeDistribution(College).PercentF<<"%"
    <<endl;
    
    
    int N;
    int DFW;
    cout<<"DFW rate: "<<GetDFWRate(College,DFW,N)<<"%"<<endl;
    
    string commands;
    cout<<endl;
    
    while(1)
    {
        cout<<"Enter a command> ";
        cin>> commands;
        
        if (commands == "#")
            break;
        
        else if (commands == "summary")
        {
            cout<<"dept name, or all? ";
            string choice;
            cin>> choice;
            bool deptnamecheck=0;
            if(choice=="all")
            {
                summaryAll(dept);
            }
            else
            {
                summaryDept(dept, choice, deptnamecheck);
                
            }
        }
        
        else if (commands == "search")
        {
            cout<<"dept name, or all? ";
            string choice;
            cin>>choice;
            cout<<"course # or instructor prefix? ";
            string instructorPrefix;
            int courseNum;
            cin >> instructorPrefix;
            stringstream ss(instructorPrefix);
            ss >> courseNum;
            
            if(choice=="all")
            {
                //void searchAll(College C , string instructorPrefix, int courseNum, stringstream ss)
                searchAll(College, instructorPrefix, courseNum, ss);
            }
            
            else
            {
                //void summaryDept(vector <Dept> dept, string choice, string instructorPrefix, int courseNum, stringstream& ss )
                searchDept(dept, choice, instructorPrefix, courseNum, ss);
            }
        }
        else if (commands == "unknown")
        {
            cout<<"dept name, or all? ";
            string choice;
            cin>> choice;
            
            //void unknownSearch(string choice, College College,vector <Dept> dept )
            unknownSearch(choice, College, dept);
        }
        
        else if (commands == "dfw")
        {
            cout<<"dept name, or all? ";
            string choice;
            cin>>choice;
            cout<<"dfw threshold? ";
            double threshold;
            cin>>threshold;
            
            //dfwfunction(string choice, College College,vector <Dept> dept, double threshold)
            dfwfunction(choice, College, dept, threshold);
        }
        
        else if(commands == "letterA")
        {
            cout<<"dept name, or all? ";
            string choice;
            cin>>choice;
            cout<<"letter A threshold? ";
            double threshold;
            cin>>threshold;
            
            //letterA(string choice, College College,vector <Dept> dept, double threshold)
            letterA(choice, College, dept, threshold);
        }
        
        else
        {
            cout<<"**unknown command\n";
        }
    }
    return 0;
}
