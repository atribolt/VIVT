/*
   Волков Юрий Владимирович, (ИВТз-191) ИВТз19-205

   Семинар 10
   Вариант 5
      Составить описание класса для представления комплексных чисел. Обеспечить
      выполнение операций сложения, вычитания и умножения комплексных чисел.
      Написать программу, демонстрирующую работу с этим классом. Программа долж-
      на содержать меню, позволяющее осуществить проверку всех методов класса

   Использован стандарт языка С++17, если у вас не компилируется
   необходимо в "Проект -> настройки проекта -> Язык -> Стандарт языка" выбрать ISO С++17
*/

#include <regex>       // для поиска комплексного числа во входной строке
#include <string>      // заголовок для использования строк
#include <iostream>    // заголовок для использования потоков ввода/вывода
#include <algorithm>   // для использования алгоритмов сортировки

// структура описания комплексного числа
// a - число реальной части
// b - число мнимой части
// оба числа принадлежат R
struct ComplexDefine {
  double a, b;
};

// объект комплексного числа
class Complex {
public:
  // оператор присвоения для структуры, описывающей комплексное число
  Complex& operator=(ComplexDefine define) {  
    _define = define;
    return *this;
  }

  // перегрузка оператора сложения с присваиванием
  Complex& operator+=(const Complex& b) {
    _define.a += b._define.a;
    _define.b += b._define.b;
    return *this;
  }

  // перегрузка оператора вычитания с присваиванием
  Complex& operator-=(const Complex& b) {
    _define.a -= b._define.a;
    _define.b -= b._define.b;
    return *this;
  }

  // перегрузка оператора умножения с присваиванием
  Complex& operator*=(const Complex& complex) {
    const auto& [_a, _b] = _define;
    const auto& [ a,  b] = complex._define;

    _define.a = (_a * a) - (_b * b);
    _define.b = (_b * a) + (_a * b);
    return *this;
  }
private:
  // обявление оператора вывода в поток как дружественного, чтобы иметь доступ к private полям
  friend std::ostream& operator<<(std::ostream& os, const Complex& complex);

  ComplexDefine _define{ 0.0, 0.0 };
};

/* 
*  перегруженные операторы ниже вынесены за пределы класса, чтобы не загромождать описание класса
*  также, эти операторы не изменяют входные объекты и не имеют доступа к их закрытым членам
*  что уменьшает вероятность ошибок во время написания кода
*  все перегрузки относятся к классу Complex
*/

Complex operator+(const Complex& a, const Complex& b) {
  Complex result = a;
  result += b;
  return result;
}
Complex operator-(const Complex& a, const Complex& b) {
  Complex result = a;
  result -= b;
  return result;
}
Complex operator*(const Complex& a, const Complex& b) {
  Complex result = a;
  result *= b;
  return result;
}
/* конец перегрузок математических операторов */

std::ostream& operator<<(std::ostream& os, const Complex& complex) { // оператор вывода комплексного числа в поток
  os << complex._define.a                                            // вывод действительной части
    << ((complex._define.b >= 0) ? " + " : " - ")                    // определение и вывод знака
    << std::fabs(complex._define.b)                                  // вывод мнимого числа без знака, так как знак поставили на прошлой строке
    << "i";                                                          // добавление мнимой единицы к записи
  return os;
}

// функция возвращающая первое совпадение регулярного выражения (reg) в строке (str)
// с возможностью вернуть любую строку, если совпадений не найдено (_default)
std::string getValueOrDefault(const std::regex& reg, std::string str, std::string _default = "") {
  std::string result = _default;                                          // присваиваем значение по умолчанию сразу
                                                                          
  auto iter = std::sregex_iterator(str.begin(), str.end(), reg);          // находим первое совпадение
  if (iter != std::sregex_iterator()) {                                   // если совпадание найдено
    result = iter->str();                                                 // присваиваем результату строку-совпадение
  }                                                                       
                                                                          
  return result;                                                          // возвращаем результат
}

// функция удаления определенного символа (simbol) из входной строки (src)
std::string& remove_simbols(std::string& src, char simbol) {
  auto iter = std::copy_if(src.begin(), src.end(), src.begin(), [simbol](char& ch) { return ch != simbol; }); // производим копирование всех символов кроме simbol и запоминаем итератор на последний скопированный
  src.resize(std::distance(src.begin(), iter));                                                               // обрезаем строку до размера без удаленных символов
  return src;                                                                                                 // возвращаем измененную строку
}

// перегрузка оператора чтения ввода в комплексное число
std::istream& operator>>(std::istream& is, Complex& complex) {
  std::string buffer;                                                   // буфер для сохранения введенной строки
  std::regex complex_exp(R"([-+]?\d*,?\d+[-+]\d*,?\d+[iI])")            // шаблон для поиска первого совпадения комплексной записи числа
           , numb_exp   (R"(^([-+]?\d*,?\d+))")                         // шаблон для поиска числа сначала входной строки
           , mean_exp   (R"(([-+]?\d*,?\d+[iI])$)");                    // шаблон для поиска мнимой части
                                                                        //
  if (std::getline(is, buffer)) {                                       // считываем строку из ввода в buffer
    remove_simbols(buffer, ' ');                                        // удаление всех пробелов из считанной строки                       

    buffer = getValueOrDefault(complex_exp, buffer);                    // поиск первого совпадения шаблона комплекного числа               
    
    std::string real = getValueOrDefault(numb_exp, buffer);             // поиск обычного числа в реальной части
    std::string mean = getValueOrDefault(mean_exp, buffer);             // поиск мнимой части
    mean = getValueOrDefault(numb_exp, mean);                           // поиск реального числа в мнимой части

    // записываем результат в комплексное число                         
    complex = ComplexDefine {                                           
      std::atof(real.data()),                                           
      std::atof(mean.data())                                            
    };                                                                  
  }                                                                     
                                                                        
  return is;                                                            // возвращаем поток ввода в управляющий поток
}

// перечисление, для сохранения описания элементов меню
enum class MenuItem {
  ADDITIVE   = '1', 
  DIFFERENCE = '2', 
  MULTIPLY   = '3', 
  HELP       = '4',
  SHOWMENU   = '5',
  EXIT       = '6',
  UNKNOWN
};
// оператор для чтения ввода в перечисление
std::istream& operator>>(std::istream& is, MenuItem& item) {
  char simbol;
  is >> simbol;

  // присвоение item и проверка, что ввод был верный
  item = MenuItem(simbol);
  switch (item) {
    case MenuItem::EXIT:       break;
    case MenuItem::HELP:       break;
    case MenuItem::ADDITIVE:   break;
    case MenuItem::MULTIPLY:   break;
    case MenuItem::SHOWMENU:   break;
    case MenuItem::DIFFERENCE: break;
    default:
      item = MenuItem::UNKNOWN;
  }

  return is;
}

// объект для представления работы с комплексными числами
class Program
{
public:
  // конструктор; 
  // при создании объекта сразу говорим, что программа работает
  Program() {
    _isExit = false; 
  }

  // показываем внешнему коду состояние программы
  bool isExit() const { 
    return _isExit; 
  }

  // печать меню в консоль
  void showMenu() const {
    std::cout << "Меню программы."
              << "\n  1. Найти сумму двух комплексных чисел;"
              << "\n  2. Найти разность двух комплексных чисел;"
              << "\n  3. Найти произведение двух комплексных чисел;"
              << "\n  4. Показать справку;"
              << "\n  5. Показать это меню;"
              << "\n  6. Завершить программу;\n";
  }

  // метод для чтения ввода и выполнения соотвествующей команды меню
  void changeMenuItem() {
    std::cout << "Введите номер пункта меню для продолжения: ";
    MenuItem item;
    std::cin >> item;

    switch (item) {
    case MenuItem::EXIT: {
        std::cout << "Выбран выход;\n";
        _isExit = true;
        break;
      }
      case MenuItem::ADDITIVE: {
        execAdditive();
        break;
      }
      case MenuItem::MULTIPLY: {
        execMultiply();
        break;
      }
      case MenuItem::DIFFERENCE: {
        execDifference();
        break;
      }
      case MenuItem::HELP: {
        printHelp();
        break;
      }
      case MenuItem::SHOWMENU: {
        showMenu();
        break;
      }
      case MenuItem::UNKNOWN: {
        showMenu();
        break;
      }
    }
  }

private:
  using operands_t = std::pair<Complex, Complex>;  // создаем псевдоним для типа std::pair, для облегчения читаемости кода

  // метод для получения двух комплексных чисел и их возврата
  operands_t input() {
    operands_t result;

    std::cin.seekg(0); // обнуляем буффер

    std::cout << "Введите первое комплексное число: ";
    std::cin >> result.first;
    std::cout << "Введите второе комплексное число: ";
    std::cin >> result.second;

    return result;
  }

  // метод печати справки в консоль
  void printHelp() {
    std::cout << "Программа демонстрирует выполенение операций над комплексными числами: сложение, вычитание, умножение;\n";
    std::cout << "Формат ввода ([+-] a [+-] bi), где a,b ϵ R; между a и b стоит плюс, если b >= 0 и минус в обратном случае.\n"
              << "\tПример вводимых чисел -5,45 + 4i | 5 - 0,3i;\n"
              << "\tЕсли число с плавающей точкой и нулевой целой частью, то необходимо записывать такое число в формате 0,xx (знаков после точки может быть больше)\n"
              << "У вещественных чисел целая часть от дробной отделяется запятой (,)\n";
  }

  // демонстрация выполнения суммы комплексных чисел
  void execAdditive() {
    std::cout << "Выполнение операции сложения для двух комплексных чисел:\n";
    auto [a, b] = input();

    std::cout << "Результат операции: " << a + b << '\n';
  }
  // демонстрация выполнения произведения комплексных чисел
  void execMultiply() { 
    std::cout << "Выполнение операции умножения для двух комплексных чисел:\n";
    auto [a, b] = input();

    std::cout << "Результат операции: " << a + b << '\n';
  }
  // демонстрация выполнения разности комплексных чисел
  void execDifference() {
    std::cout << "Выполнение операции разности для двух комплексных чисел:\n";
    auto [a, b] = input();

    std::cout << "Результат операции: " << a + b << '\n';
  }

  bool _isExit;
};

int main(int argc, char** argv) {
  setlocale(LC_ALL, "RU");            // установка локали для распознавания кириллицы
                                      //
  Program program;                    // создание объекта программы
  program.showMenu();                 // отображение меню
                                      //
  do {                                // начало цикла выполнения
    std::cout << '\n';                // печать переноса строки, чтобы было приятнее визуальное оформление
    program.changeMenuItem();         // выполнение пользовательской операции
  } while( !program.isExit() );       // выполняем пока пользователь не выберет пункт "выход" в меню
                                      
  return 0;
}
