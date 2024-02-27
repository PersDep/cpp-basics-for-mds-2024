#include <algorithm>
#include <chrono>
#include <iostream>
#include <cmath>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>

// C++ style
#include <fstream>
// C style
#include <cstdio>

using namespace std;

void my_custom_destructor_for_smart_pointer(std::map<string, int *> *ptr)
{
    delete ptr;
}

//RAII -- Resource Acquisition Is Initialization
// on object creation we allocate the needed resources
// on object destruction we deallocate all the allocated previously

// tricky moment are the exceptions. When you meet an exception it is easy to fail to deallocate some of the resources

template <typename T> // <class T> -- just the same thing
class SmartPointer {
public:
  SmartPointer(T* ptr = nullptr, std::function<void(T*)> custom_delete = nullptr) : ptr(ptr), custom_delete(custom_delete) {}

  ~SmartPointer() {
    //delete ptr1; 
    //delete[] ptr2;
    if (ptr != nullptr) {
      if (custom_delete != nullptr) {
        custom_delete(ptr);
      } else {
        delete ptr;
      }
    }
  }

  // Dereference operators
  T* operator->() {
    return ptr;
  }

  T& operator*() {
    return *ptr;
  }

  // Move assignment operator
  SmartPointer& operator=(SmartPointer&& other) noexcept {
    std::swap(ptr, other.ptr);
    std::swap(custom_delete, other.custom_delete);
    other.ptr = nullptr;
    other.custom_delete = nullptr;
    return *this;
  }

  // Copy assignment operator
  SmartPointer& operator=(const SmartPointer& other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = new T(*other.ptr); // use non-throwing new operator
      custom_delete = other.custom_delete;
    }
    return *this;
  }

  void SetCustomDelete(std::function<void(T*)> custom_delete) {
    this->custom_delete = custom_delete;
  }

  // Release the pointer to the caller, the caller takes the ownership of the data and now is responsible for deleting it
  T* release() {
    T* ptr = this->ptr;
    this->ptr = nullptr;
    this->custom_delete = nullptr;
    return ptr;
  }

  // Check if the pointer is nullptr
  bool isNullptr() const {
    return ptr == nullptr;
  }

  // Get the raw pointer
  T* get() const {
    return ptr;
  }

private:
  T* ptr;
  std::function<void(T*)> custom_delete;
};

void threadFunction(int id) {
  cout << "Hello from a thread " << id << endl;
}

class DivideByZeroException : public exception {
public:
  const char* what() const throw() {
    return "Division by zero";
  }
};

int divide(int a, int b) {
  if (b == 0) {
    throw DivideByZeroException(); // https://en.cppreference.com/w/cpp/error/exception
    // throw invalid_argument("Division by zero");
  }

  return a / b;
}

template <typename T>
struct TypeInfo {
  static const char* name() {
    return typeid(T).name();
  }
};

//RAII concept followed
template <typename T>
class Array {
public:
  Array(int size) : size(size) {
    data = new T[size];
    // data = new T;
  }

  ~Array() {
    delete[] data;
  }

  T& operator[](int index) {
    return data[index];
  }

  int getSize() {
    return size;
  }

  // T& get(int index) {
  //   return data[index];
  // }
private:
  T* data;
  int size;
};

//unique_ptr

class SmartPointerSimple {
public:
    SmartPointerSimple(int* ptr) : ptr(ptr) {}

    ~SmartPointerSimple() {
    if (ptr != nullptr) {
        delete ptr;
    }
    }

    /**
     * Overloads the '->' operator to provide access to the underlying pointer.
     * @return A pointer to the underlying object.
     */
    int* operator->() {
        return ptr;
    }

    int& operator*() {
        return *ptr;
    }

    //__mul__
    //__div__

private:
    int* ptr;
};

class PersonClass {
private:
    string name;
    int age;
    double height;
    double weight;
    double geo_position_x, geo_position_y;

public:
    PersonClass() {
      name = "";
      age = 0;
      height = 0.0;
    }

    PersonClass(string name, int age, double height, double weight) {
      this->name = name;
      this->age = age;
      this->height = height;
      this->weight = weight;
    }

    void SetName(string name) {
        this->name = name;
    }

    void SetAge(int age) {
        this->age = age;
    }

    const string &GetName() { // vs string GetName()
        return name;
    }

    int GetAge() {
        return age;
    }

    double GetBodyMassIndex() {
        return weight / pow(height, 2);
    }

    void MovePerson(double x, double y) {
        geo_position_x = x;
        geo_position_y = y;
    }

    void PrintInfo() {
      cout << name << " is " << age << " years old and " << height << " meters tall." << endl;
    }
};

// inherited by class Student, class Teacher, class Worker, 

struct Person {
  string name;
  int age;
  double height;
};

//class Figure;
//inherited: class Circle, class triangle;

// OOP: incapsulation, polymorphism, inheritance

void calculations(int i) {
    double result = 0;
    int stop = i + 99999;
    for (int j = 0; j < stop; j++) {
      for (int k = 0; k < j; k++) {
          result += i * j * k;
      }
      // cout << "thread " << i - 100 << " finished " << i << " iterations" << endl;
    }
    cout << "thread " << i << " result: " << result << endl;

    // if (i == 0) {
    //   function1();
    // } else if (i == 1) {
    //   do_something_else()
    // }
}


int main(void)
{
    //C++ style or C style

    // new / delete -- C++ style -- more "safe", more convenient delete [] array;
    // calloc + malloc / free -- C style (sometimes a bit more faster)

    // cout << ... << end; -- C++ style
    // cin << -- C++ style
    // printf("%d %f %s", 10, 10.10, array_of_chars)

    // int d = 10;
    // float x = 10.1;

    //C++ style file management
    // ofstream f1("../filename-C++.txt", ios_base::out);
    // f1 << "wpoekfwpokfwp " << d << " " << x << std::endl; // same as cout
    // f1.close();
    // | -- binary "or"
    // || -- "or"
    // & -- binary "and"
    // && -- "and"
    // ! -- not
    // == -- equal
    // ^ -- xor
    // std::string input1, input2, input3, input;
    // ifstream f2("../filename-C++.txt", ios_base::in); //| ios_base flags https://en.cppreference.com/w/cpp/io/ios_base
    // // f2 >> input1 >> input2 >> input3; // same as cin; reads until separator which is a broad termin here
    // // instead of separator you just read until the "separator" character
    // // getline(f2, input); // reads full line until linefeed "\n" (and also some alternatives)
    // char symbol;
    // while (symbol != EOF) {
    //   symbol = f2.get(); // reads exactly one symbol (reads one byte)
    //   input.push_back(symbol);
    //   cout << symbol << " | ";
    // }
    // f2.close();
    // std::cout << input << std::endl << std::endl << std::endl;
    // auto integer_number = stoi(input2);
    // auto float_number = stof(input3);
    // std::cout << input1 << " " << integer_number << " " << float_number << std::endl;


    // //C style file management
    // FILE *f = fopen("../filename-C++.txt", "r");
    // // char *buf = new char[100];
    // // fread(buf, 100, 100, f);
    // // std::cout << buf << std::endl;
    // symbol = fgetc(f); // check EOF
    // // fwrite()
    // fclose(f);
    // // delete [] buf;


    //Smart pointers in STL:
    // unique_ptr
    // shared_ptr
    // weak_ptr -- more rarely used
    // auto_ptr -- more rarely used

    // cout << TypeInfo<int>::name() << endl; // Prints "int"
    // cout << TypeInfo<string>::name() << endl; // Prints "std::string"

    // Array<int> intArray(10);
    // intArray[0] = 1;

    // Array<string> stringArray(10);
    // stringArray[0] = "Hello";

    // auto add = [](int a, int b) {
    //     return a + b;
    // };
    
    // std::cout << add(1, 2) << std::endl;

    // python does not have common multithreading
    // python has GIL: it makes all the threads run asynchronously but not in parallel
    std::vector<std::thread> threads;

    // for (int i = 0; i < 10; i++) {
    //     threads.emplace_back(std::thread([&](int id) {
    //         cout << "Hello from the thread " << id << "; threads amount:" << threads.size() << endl;
    //     }, i));
    // }

    auto start = chrono::system_clock::now();

    for (int i = 0; i < 32; i++) {
        threads.emplace_back(std::thread(calculations, i));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = chrono::system_clock::now();

    cout << "Time spent: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

    // {
    //     SmartPointer<std::map<string, int *>> smartPointerA(new std::map<string, int *>());
    //     SmartPointer<std::map<string, int *>> smartPointerB(new std::map<string, int *>());

    //     // int *a = new int(10);
    //     // (*smartPointerA)["smartPointerB"] = a;
    //     // (*smartPointerB)["smartPointerA"] = a;

    //     (*smartPointerA)["smartPointerB"] = (int *)(&smartPointerB);
    //     (*smartPointerB)["smartPointerA"] = (int *)(&smartPointerA);

    //     smartPointerA.SetCustomDelete(my_custom_destructor_for_smart_pointer);
    // }


    // int a = 10;
    // int b = 0;

    // cout << a / b << endl;
    // cout << divide(a, b) << endl;

    // try {
    //   cout << divide(a, b) << endl;
    // } catch (invalid_argument const& exception) {
    //   cout << exception.what() << endl;
    // } catch (DivideByZeroException exception) {
    //   cout << exception.what() << endl;
    // } catch (...) {
    //   cout << "Some other exception" << endl;
    // }

    // Array<int> array(3);
    // array[0] = 1;
    // array[1] = 2;
    // array[2] = 3;

    // for (int i = 0; i < array.getSize(); i++) {
    //     cout << array[i] << endl;
    // }

    return 0;
}