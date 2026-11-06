#include "lab3.h"


int main() {
  setlocale(LC_ALL, ".UTF8");
  int choice = 0;

  do {
    std::cout << std::endl;
    std::cout << "Лабораторная работа №3. Вариант 6" << std::endl;
    std::cout << "1. Задание 1: время и дом" << std::endl;
    std::cout << "2. Задание 2: сотрудники и отделы" << std::endl;
    std::cout << "3. Задание 3: список сотрудников отдела" << std::endl;
    std::cout << "4. Задание 4: неизменяемый дом" << std::endl;
    std::cout << "5. Задание 5: пистолет" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите задание: ";

    if (!(std::cin >> choice)) {
      std::cout << "Ошибка ввода. Завершение программы."
                << std::endl;
      return 1;
    }

    switch (choice) {
      case 1:
        runTask1();
        break;
      case 2:
        runTask2();
        break;
      case 3:
        runTask3();
        break;
      case 4:
        runTask4();
        break;
      case 5:
        runTask5();
        break;
      case 0:
        std::cout << "Завершение программы." << std::endl;
        break;
      default:
        std::cout << "Такого пункта меню нет. Повторите ввод."
                  << std::endl;
        break;
    }
  } while (choice != 0);

  return 0;
}
