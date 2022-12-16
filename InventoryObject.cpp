#include "InventoryObject.h"
#include <iostream>

void InventoryObject::Use(int& UselessInt, bool& UselessBool, std::string UselessString)
{
  //InventoryObject::Quantity -= 1;
  std::cout << "Used 1 Cum " << InventoryObject::Quantity << std::endl;
};

InventoryObject::InventoryObject()
{
  //std::cout << "Created InventoryObject " << InventoryObject::Name << std::endl;
}