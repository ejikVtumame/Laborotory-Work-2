#include "lab3.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

Time::Time(int total_seconds) : total_seconds_(total_seconds) {
  if (total_seconds < 0) {
    throw std::invalid_argument("Количество секунд не может быть "
                                "отрицательным.");
  }
}

std::string Time::toString() const {
  const int seconds_per_day = 24 * 60 * 60;
  const int seconds = total_seconds_ % seconds_per_day;
  const int hours = seconds / 3600;
  const int minutes = (seconds % 3600) / 60;
  const int remaining_seconds = seconds % 60;

  std::ostringstream result;
  result << std::setfill('0') << std::setw(2) << hours << ":"
         << std::setw(2) << minutes << ":"
         << std::setw(2) << remaining_seconds;
  return result.str();
}

void Time::print() const {
  std::cout << toString() << std::endl;
}

House::House(int floors) : floors_(floors) {
  if (floors <= 0) {
    throw std::invalid_argument("Количество этажей должно быть "
                                "положительным.");
  }
}

std::string House::toString() const {
  int last_two_digits = floors_ % 100;
  int last_digit = floors_ % 10;
  std::string ending = "этажами";

  if (last_two_digits < 11 || last_two_digits > 14) {
    if (last_digit == 1) {
      ending = "этажом";
    }
  }

  return "Дом с " + std::to_string(floors_) + " " + ending;
}

void House::print() const {
  std::cout << toString() << std::endl;
}

Department::Department(const std::string& name)
    : name_(name), manager_(nullptr) {}

void Department::addEmployee(Employee* employee) {
  if (employee == nullptr) {
    return;
  }

  for (Employee* current : employees_) {
    if (current == employee) {
      employee->setDepartment(this);
      return;
    }
  }

  employees_.push_back(employee);
  employee->setDepartment(this);
}

void Department::setManager(Employee* manager) {
  manager_ = manager;

  if (manager_ != nullptr) {
    addEmployee(manager_);
  }
}

std::string Department::getName() const {
  return name_;
}

Employee* Department::getManager() const {
  return manager_;
}

const std::vector<Employee*>& Department::getEmployees() const {
  return employees_;
}

void Department::printEmployees() const {
  std::cout << "Сотрудники отдела " << name_ << ":" << std::endl;

  for (const Employee* employee : employees_) {
    if (employee != nullptr) {
      std::cout << "  " << employee->getName() << std::endl;
    }
  }
}

Employee::Employee(const std::string& name)
    : name_(name), department_(nullptr) {}

void Employee::setDepartment(Department* department) {
  department_ = department;
}

Department* Employee::getDepartment() const {
  return department_;
}

std::string Employee::getName() const {
  return name_;
}

void Employee::print() const {
  if (department_ == nullptr) {
    std::cout << name_ << " не состоит в отделе." << std::endl;
    return;
  }

  if (department_->getManager() == this) {
    std::cout << name_ << " начальник отдела "
              << department_->getName() << std::endl;
    return;
  }

  Employee* manager = department_->getManager();
  std::string manager_name = "не назначен";

  if (manager != nullptr) {
    manager_name = manager->getName();
  }

  std::cout << name_ << " работает в отделе "
            << department_->getName()
            << ", начальник которого " << manager_name << std::endl;
}

Pistol::Pistol(int cartridges) : cartridges_(cartridges) {
  if (cartridges < 0) {
    throw std::invalid_argument("Количество патронов не может быть "
                                "отрицательным.");
  }
}

void Pistol::shoot() {
  if (cartridges_ > 0) {
    std::cout << "Бах!" << std::endl;
    --cartridges_;
  } else {
    std::cout << "Клац!" << std::endl;
  }
}

void Pistol::print() const {
  std::cout << "Количество патронов: "
            << cartridges_ << std::endl;
}

void runTask1() {
  std::cout << std::endl;
  std::cout << "Задание 1.4. Время" << std::endl;

  const Time first_time(10);
  const Time second_time(10000);
  const Time third_time(100000);

  std::cout << "10 секунд: ";
  first_time.print();
  std::cout << "10000 секунд: ";
  second_time.print();
  std::cout << "100000 секунд: ";
  third_time.print();

  std::cout << std::endl;
  std::cout << "Задание 1.5. Дом" << std::endl;

  const House first_house(1);
  const House second_house(5);
  const House third_house(23);

  first_house.print();
  second_house.print();
  third_house.print();
}

void runTask2() {
  std::cout << std::endl;
  std::cout << "Задание 2.4. Сотрудники и отделы" << std::endl;

  Department it_department("IT");
  Employee petrov("Петров");
  Employee kozlov("Козлов");
  Employee sidorov("Сидоров");

  it_department.addEmployee(&petrov);
  it_department.addEmployee(&kozlov);
  it_department.addEmployee(&sidorov);
  it_department.setManager(&kozlov);

  petrov.print();
  kozlov.print();
  sidorov.print();
}

void runTask3() {
    std::cout << std::endl;
    std::cout << "Задание 3.4. Список сотрудников отдела" << std::endl;

    Department it_department("IT");
    Employee petrov("Петров");
    Employee kozlov("Козлов");
    Employee sidorov("Сидоров");

    it_department.addEmployee(&petrov);
    it_department.addEmployee(&kozlov);
    it_department.addEmployee(&sidorov);
    it_department.setManager(&kozlov);

    // Список сотрудников, через которых можно получить отдел
    Employee* employees[] = { &petrov, &kozlov, &sidorov };
    const int employees_count = 3;

    std::cout << "Выберите сотрудника, через которого узнать список "
        "сотрудников отдела:" << std::endl;
    for (int i = 0; i < employees_count; ++i) {
        std::cout << "  " << i + 1 << ". " << employees[i]->getName()
            << std::endl;
    }

    int choice = 0;
    std::cout << "Введите номер сотрудника: ";
    if (!(std::cin >> choice) || choice < 1 || choice > employees_count) {
        std::cout << "Некорректный выбор. Показываем список через Петрова."
            << std::endl;
        choice = 1;
    }

    Employee* selected_employee = employees[choice - 1];
    std::cout << "Получаем список через сотрудника "
        << selected_employee->getName() << "." << std::endl;

    Department* department = selected_employee->getDepartment();
    if (department != nullptr) {
        department->printEmployees();
    }
}

void runTask4() {
    std::cout << std::endl;
    std::cout << "Задание 4.3. Дом с неизменяемым числом этажей"
        << std::endl;

    int floors = 0;
    std::cout << "Введите количество этажей для дома: ";
    if (!(std::cin >> floors) || floors <= 0) {
        std::cout << "Некорректное количество этажей. "
            "Используем значение по умолчанию (1)."
            << std::endl;
        floors = 1;
    }

    const House house(floors);
    house.print();

    std::cout << "Количество этажей хранится в поле const."
        << std::endl;
    std::cout << "Метод изменения этажей не предусмотрен."
        << std::endl;
}


void runTask5() {
    std::cout << std::endl;
    std::cout << "Задание 5.1. Пистолет стреляет" << std::endl;

    Pistol pistol(3);

    std::cout << "Создан пистолет с тремя патронами."
        << std::endl;

    for (int shot = 1; shot <= 5; ++shot) {
        std::cout << "Выстрел " << shot << ": ";
        pistol.shoot();
    }

    pistol.print();
}