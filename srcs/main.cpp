#include "vector.hpp"
#include <iostream>
#include <vector>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

int main()
{
  ///////////////////////////////////**VECTOR**///////////////////////////////////
  std::cout << KYEL "///////////////////////////////////**VECTOR**";
  std::cout << "///////////////////////////////////" KWHT << std::endl;
  std::cout << std::endl;
  //  CONSTRUCTING VECTORS FT
  {
    std::cout << KYEL "CONSTRUCTOR TEST WITH FT..." KWHT << std::endl;
    // The contents of fifth are: 16 2 77 29
    ft::vector<int> first;                               // empty vector of ints
    ft::vector<int> second(4, 100);                      // four ints with value 100
    ft::vector<int> third(second.begin(), second.end()); // iterating through second
    ft::vector<int> fourth(third);                       // a copy of third

    int myints[] = {16, 2, 77, 29};
    ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  //  CONSTRUCTING VECTORS STD
  {
    std::cout << KYEL "CONSTRUCTOR TEST WITH STD..." KWHT << std::endl;
    // The contents of fifth are: 16 2 77 29
    std::vector<int> first;                               // empty vector of ints
    std::vector<int> second(4, 100);                      // four ints with value 100
    std::vector<int> third(second.begin(), second.end()); // iterating through second
    std::vector<int> fourth(third);                       // a copy of third

    int myints[] = {16, 2, 77, 29};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  std::cout << std::endl;
  /////////////////////////////////////////////////////////////////////////////////
  // OPERATOR = WITH FT
  {
    std::cout << KYEL "OPERATOR = TEST WITH FT..." KWHT << std::endl;
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
  }
  // OPERATOR = WITH STD
  {
    std::cout << KYEL "OPERATOR = TEST WITH STD..." KWHT << std::endl;
    std::vector<int> foo(3, 0);
    std::vector<int> bar(5, 0);

    bar = foo;
    foo = std::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
  }
  std::cout << std::endl;
  /////////////////////////////////////////////////////////////////////////////////
  // INSERT TESTS WITH FT
  {
    std::cout << KYEL "INSERT TEST WITH FT..." KWHT << std::endl;
    ft::vector<int> myvector(3, 100);
    ft::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    it = myvector.begin();

    ft::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin(); it < myvector.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  //  INSERT TESTS WITH STD
  {
    std::cout << KYEL "INSERT TEST WITH STD..." KWHT << std::endl;
    std::vector<int> myvector(3, 100);
    std::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    it = myvector.begin();

    std::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin(); it < myvector.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  std::cout << std::endl;
  /////////////////////////////////////////////////////////////////////////////////
  // RESIZE TESTS WITH FT
  {
    std::cout << KYEL "RESIZE TEST WITH FT..." KWHT << std::endl;
    ft::vector<int> myvector;

    for (int i = 1; i < 10; i++)
      myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (int i = 0; i < static_cast<int>(myvector.size()); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  // RESIZE TESTS WITH STD
  {
    std::cout << KYEL "RESIZE TEST WITH STD..." KWHT << std::endl;
    std::vector<int> myvector;

    for (int i = 1; i < 10; i++)
      myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (int i = 0; i < static_cast<int>(myvector.size()); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  std::cout << std::endl;
  /////////////////////////////////////////////////////////////////////////////////
  //  ASSIGN TESTS WITH FT
  {
    std::cout << KYEL "ASSIGN TEST WITH FT..." KWHT << std::endl;
    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;

    first.assign(7, 100); // 7 ints with a value of 100

    ft::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1); // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3); // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
  }
  //  ASSIGN TESTS WITH STD
  {
    std::cout << KYEL "ASSIGN TEST WITH STD..." KWHT << std::endl;
    std::vector<int> first;
    std::vector<int> second;
    std::vector<int> third;

    first.assign(7, 100); // 7 ints with a value of 100

    std::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1); // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3); // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
  }
  std::cout << std::endl;

  /////////////////////////////////////////////////////////////////////////////////
}
