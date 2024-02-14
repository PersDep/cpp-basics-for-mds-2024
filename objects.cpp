#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <thread>
#include <typeinfo>

using namespace std;


void threadFunction() {
  cout << "Hello from a thread" << endl;
}

class DivideByZeroException : public exception {
public:
  const char* what() const throw() {
    return "Division by zero";
  }
};

int divide(int a, int b) {
  if (b == 0) {
    throw DivideByZeroException();
  }

  return a / b;
}

template <typename T>
struct TypeInfo {
  static const char* name() {
    return typeid(T).name();
  }
};


template <typename T>
class Array {
public:
  Array(int size) : size(size) {
    data = new T[size];
  }

  ~Array() {
    delete[] data;
  }

  T& operator[](int index) {
    return data[index];
  }

private:
  T* data;
  int size;
};

//unique_ptr

class SmartPointer {
public:
    SmartPointer(int* ptr) : ptr(ptr) {}

    ~SmartPointer() {
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

// using incomplete declaration in the current file
// class Figure; // let's imagone we want to use class PersonClass as a field

//however we need to put the full implementation somewhere else

// inherit from ostream is possible but rarely used
class PersonClass {
private:
    string name; // 8 bytes
    int age; // shift: 8 bytes
    double height;
    double weight;
    double geo_position_x, geo_position_y;
    // Figure *figure; // I can't use figure class without pointer here, because it is not completely defined

protected:
public:
    //__init__
    // PersonClass() {
    //   name = "";
    //   age = 0;
    //   height = 0.0;
    // }

    PersonClass(string name1="", int age=0, double height=0, double weight=0) {
      //this is like self
      // if you just put 
      // name -- it will have the value argument
      // if you put
      // this->name -- it will have the class field value
      name = name1;
      this->age = age;
      this->height = height;
      this->weight = weight;
    }

// copy constructor
// default copy constructor
    PersonClass(const PersonClass& person) {
      name = person.name;
      age = person.age;
      height = person.height;
      weight = person.weight;
      // reference_counter
    }

// move constructor
    PersonClass(PersonClass&& person) {
      name = std::move(person.name);
      age = std::move(person.age);
      height = std::move(person.height);
      weight = std::move(person.weight);
    }

    void SetName(string name) {
        this->name = name;
    }

    void SetAge(int age) {
        this->age = age;
    }

    string GetName() {
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

// class Figure {
// protected:
//     int x, y;
//     PersonClass personClass; // OK, I can use personclass here without a pointer

// public:
//     Figure() {}

//     virtual void Draw() = 0;

//     double getArea() {
//         return x * y;
//     }
// };

// class Triangle : Figure {
//   public:
//     virtual void Draw() {
//         cout << "Drawing a triangle" << endl;
//     }
// }

// class Circle : Figure {
//   public:
//     virtual void Draw() {
//         cout << "Drawing a circle" << endl;
//     }
// }

// inherited by class Student, class Teacher, class Worker, 

// structs are just the same as classes but all fields are public by default
// struct Person {
//   string name;
//   int age;
//   double height;
// };

//class Figure;
//inherited: class Circle, class triangle;

// OOP: incapsulation, polymorphism, inheritance

void f() {
  int a;
  int *b = new int;
  // return a; // means copy
  // return &a; //this will be a problem, because a will be destroyed
  // return b; // means return actualy object and you can use this object later
  // type of &a is the same as b
} // a is destroyed here
// b is not destroyed here

int main(void)
{
    // Circle circle;
    // circle.getArea();
    // // Figure -> circle
    // //        -> triangle  

    std::cout << "\n";
    std::cout << "________________________________________" << std::endl;

    // PersonClass person5; // pointer *(&person1 + byte_size) to access any field if we no it's byte shift: it is also the way to
    // create an object
    //automatically access some field "n"
    // PersonClass  *person1; // don't create raw pointers
    shared_ptr<PersonClass> person1;  //nothing is actually created here
    // use smart pointers instead to allow them effectively manage memory
    // std::cout << person1 << std::endl;
    person1 = make_shared<PersonClass>(PersonClass("John Doe", 99)); // calloc(), malloc(sizeof(PersonClass))
    std::cout << person1 << std::endl;
    std::cout << person1.get() << std::endl; // when you access class shared_ptr method, use .
    std::cout << person1->GetAge() << std::endl; // when you acces class PersonClass method, use ->
    std::cout << (long long unsigned)(person1.get() + 8) << std::endl;


    // use dot if your class is not a pointer
    // use arrow if your class is a pointer


    // Figure *figure1;

    // auto person2 = person1; // copy constructor is being called
    // Person person3(person1); // copy constructor is being called

    // auto person4 = std::move(person1); // move constructor is being called
    // person1 is no longer valid after that. The purpose is to make it faster: in case the class is big enough

    // imagined_function(std::move(person1));

    //we don't need person1 instance anymore in this function
    // then we can use std::move(person1)

    // std::cout << person1 << std::endl;

    person1->PrintInfo();

    // person1.name = "John Doe";
    // person1.age = 30;
    // person1.height = 1.80;

    // cout << person1.name << " is " << person1.age << " years old and " << person1.height << " meters tall." << endl;

    // std::cout << std::endl << std::endl;

    // delete person1;

    // PersonClass person2("John Doe", 30, 1.80, 80);
    // // PersonClass person2(string("John Doe"), 30, 1.80);
    // person2.PrintInfo();
    // cout << person2.GetBodyMassIndex() << endl;

    // try {
    //     int result = divide(10, 0);
    // } catch (DivideByZeroException& e) {
    //     cout << e.what() << endl;
    // }

    // cout << TypeInfo<int>::name() << endl; // Prints "int"
    // cout << TypeInfo<string>::name() << endl; // Prints "std::string"

    // Array<int> intArray(10);
    // intArray[0] = 1;

    // Array<string> stringArray(10);
    // stringArray[0] = "Hello";

    // SmartPointer smartPointer(new int(10));

    // cout << *smartPointer << endl; // Prints 10

    // delete smartPointer; // Memory is automatically freed

    // std::thread thread(threadFunction);

    // thread.join();

    return 0;
}