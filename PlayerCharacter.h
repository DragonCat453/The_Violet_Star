#define PlayerCharacter_H
#include <string>
#include <vector>
#include <iostream>
#include "InventoryObject.h"

class PlayerCharacter
{
public:
std::vector<int> position;
std::vector<InventoryObject*> TMPInventory;
std::vector<InventoryObject*> inventory;
int Sanity = 4;
void ConsolidateInventory();
void ShowInventory();
PlayerCharacter();
};