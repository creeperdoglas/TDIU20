#include "List.h"
#include <iostream>
<<<<<<< HEAD

int main()
{
  try
  {
    List list{0, 1, 2, 3, 4, 5};               // Initialize the list with some values
    List *subList = list.sub({1, 2, 1, 2, 0}); // This should throw an exception

    // If the above line does not throw an exception, the following lines will execute
    std::cout << "Sublist created successfully. This was not expected." << std::endl;
    std::cout << *subList << std::endl;

    delete subList; // Clean up dynamically allocated memory
  }
  catch (const std::invalid_argument &ia)
  {
    std::cout << "Caught an invalid_argument exception as expected: " << ia.what() << std::endl;
  }
  catch (const std::out_of_range &oor)
  {
    std::cout << "Caught an out_of_range exception, which was not expected for these indices: " << oor.what() << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Caught an unexpected exception: " << e.what() << std::endl;
=======
#include <exception>

int main()
{
  List list{1, 2, 3, 4, 5, 6};

  // list.setSortOnInsert(false);

  // Test case: Check if providing invalid indices throws an exception
  try
  {
    List sublist{list.sub({2, 1, 2})};
    std::cout << "Sublist created) successfully. This was not expected." << std::endl;

    for (auto it = sublist.begin(); it != sublist.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
  catch (const std::exception &e)
  {

    std::cout << "Exception caught as expected: " << e.what() << std::endl;
>>>>>>> 8c6831d87ed4969c7d5ab888e0aa150d3ebe7497
  }

  return 0;
}
