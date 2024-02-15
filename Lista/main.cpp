#include "List.h"
#include <iostream>
#include <exception>

int main()
{

  List list{1, 2, 3, 4, 5};

  // Test case: Check if providing invalid indices throws an exception
  try
  {
    List *subList = list.sub({2, 1, 2});
    std::cout << "Sublist created successfully. This was not expected." << std::endl;

    for (auto it = subList->begin(); it != subList->end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << std::endl;

    delete subList;
  }
  catch (const std::exception &e)
  {

    std::cout << "Exception caught as expected: " << e.what() << std::endl;
  }

  return 0;
}
