#include "InventoryObject.h"
#include "AbyssalMirror.h"
#include <iostream>

void AbyssalMirror::Use(int& Sanity, bool& MonsterAggravated, std::string UselessString)
{
  //AbyssalMirror::Quantity -= 1;
  Sanity -= 1;
  if (Sanity <= 3)
  {
    MonsterAggravated = true;
  }
  std::cout << "You gaze into the strange mirror and feel your sanity slip ever so slightly" << std::endl;
};

AbyssalMirror::AbyssalMirror()
{
  InventoryObject::Name = "AbyssalMirror";
  //std::cout << "Created InventoryObject " << InventoryObject::Name << std::endl;
}