#include "InventoryObject.h"
#include "KeyCard.h"
#include <iostream>

void KeyCard::Use(int& Sanity, bool&TargetBool, std::string TargetName)
{
  if(TargetName == InventoryObject::Name)
  {
    TargetBool = true;
    std::cout << "You use the " << InventoryObject::Name << " successfully." << std::endl;
  }
  else
  {
    std::cout << "You cannot use the " << InventoryObject::Name << " in that way." << std::endl;
  }
};

void KeyCard::SetName(std::string NewName)
{
  InventoryObject::Name = NewName;
};