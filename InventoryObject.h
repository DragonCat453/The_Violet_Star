#ifndef InventoryObject_H
#define InventoryObject_H
#include <string>
#include <vector>
#include <iostream>

class InventoryObject
{
public:
  std::string Name = "DefaultInventoryObject";
  int Quantity = 1;
  int StackSize = 64;
  virtual void Use(int&, bool&, std::string);
  InventoryObject();
};
#endif
