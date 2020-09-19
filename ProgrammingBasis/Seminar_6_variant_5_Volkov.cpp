/*
   Волков Юрий Владимирович, (ИВТз-191) ИВТз19-205

   Семинар 6
   Вариант 5
      Описать структуру с именем AEROFLOT, содержащую следующие поля: 
            название пункта назначения рейса; 
            номер рейса; 
            тип самолета. 
      Написать программу, выполняющую следующие действия:
        - ввод с клавиатуры данных в массив, состоящий из семи элементов типа AEROFLOT; 
        - записи должны быть размещены в алфавитном порядке по названиям пунктов назначения;
        - вывод на экран пунктов назначения и номеров рейсов, обслуживаемых самолетом, тип которого введен с клавиатуры;
        - если таких рейсов нет, выдать на дисплей соответствующее сообщение. 

   Использован стандарт языка С++17, если у вас не компилируется
   необходимо в "Проект -> настройки проекта -> Язык -> Стандарт языка" выбрать ISO С++17
*/

#include <iostream>    // заголовок для использования потоков ввода/вывода
#include <string>      // заголовок для использования строк
#include <algorithm>   // для использования алгоритмов сортировки

struct AEROFLOT {
  size_t m_number_flight;    // номер рейса
  std::string m_destination; // пункт назначения
  std::string m_plane_type;  // тип самолета
};

// оператор сравнения для сортировки в массиве
bool operator<(AEROFLOT const& a, AEROFLOT const& b) {
  return a.m_destination < b.m_destination;
}

// вывод пункта назначения и номера рейса для AEROFLOT
std::ostream& operator<<(std::ostream& os, AEROFLOT const& val) {
  os << "Destionation: " << val.m_destination << "; Number flight: " << val.m_number_flight << ';';
  return os;
}

// вывод всей информации для типа самолета
template<size_t size>
  std::ostream& print_all_informaion_for_plane(AEROFLOT (&arr)[size], std::string_view planetype, std::ostream& os = std::cout) {
    bool is_exists_plane = false;                // для проверки наличия информации для типа самолета

    os << "Plane type: " << planetype << '\n';
    for (size_t i = 0; i < size; ++i) {
      if (arr[i].m_plane_type == planetype) {    // если типы самолетов совпадают
        os << '\t' << arr[i] << '\n';            // выводим информацию для этого типа самолета
        is_exists_plane = true;
      }
    }

    // если для типа самолета нет совпадающих структур в массиве
    if (!is_exists_plane) {
      os << "\tFor your plane type information not found\n";
    }

    return os;
  }

std::istream& operator>>(std::istream& is, AEROFLOT& flot) {
  is >> flot.m_plane_type >> flot.m_destination >> flot.m_number_flight;
  return is;
}

int main(int argc, char** argv) {
  AEROFLOT list[7];                  // список из 7 объектов AEROFLOT

  // заполнение списка рейсов
  std::cout << "Input 7 rows for plane list in format: planetype destionation numberflight.\nExample: boeng737 Moscow 045\n";
  for (int i = 0; i < 7; ++i) {
    std::cin >> list[i];
  }

  std::sort(std::begin(list), std::end(list));           // сортировка списка по пунктам назначения в алфавитном порядке

  std::string buffer;                                    // буффер для вводимых данных
  
  while (buffer != "q") {
    std::cout << "Input plane type for information (or 'q' for exit): ";  
    std::cin >> buffer;                                                  // получаем введенную пользователем строку

    print_all_informaion_for_plane(list, buffer);                        // вывод информации для введенного типа самолета
  }

  return 0;
}