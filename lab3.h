#ifndef LAB3_H_
#define LAB3_H_

#include <iostream>
#include <string>
#include <vector>

class Time {
 public:
  explicit Time(int total_seconds);

  std::string toString() const;
  void print() const;

 private:
  int total_seconds_;
};

class House {
 public:
  explicit House(int floors);

  std::string toString() const;
  void print() const;

 private:
  const int floors_;
};

class Employee;

class Department {
 public:
  explicit Department(const std::string& name);

  void addEmployee(Employee* employee);
  void setManager(Employee* manager);
  std::string getName() const;
  Employee* getManager() const;
  const std::vector<Employee*>& getEmployees() const;
  void printEmployees() const;

 private:
  std::string name_;
  Employee* manager_;
  std::vector<Employee*> employees_;
};

class Employee {
 public:
  explicit Employee(const std::string& name);

  void setDepartment(Department* department);
  Department* getDepartment() const;
  std::string getName() const;
  void print() const;

 private:
  std::string name_;
  Department* department_;
};

class Pistol {
 public:
  explicit Pistol(int cartridges = 5);

  void shoot();
  void print() const;

 private:
  int cartridges_;
};

void runTask1();
void runTask2();
void runTask3();
void runTask4();
void runTask5();

#endif  // LAB3_H_
