#include "PlayerCharacter.h"

void PlayerCharacter::ConsolidateInventory()
{
  for (InventoryObject* obj : inventory)
    {
     TMPInventory.push_back(obj);
    }
  inventory.clear();
  for (InventoryObject* obj : TMPInventory)
    {
    if (obj->Quantity > 0)
      {
        inventory.push_back(obj);
      }
    }
  TMPInventory.clear();
}

void PlayerCharacter::ShowInventory()
{
  for (InventoryObject* obj : inventory)
      {
        std::cout << obj->Name << " " << obj->Quantity << std::endl;
      }
}

PlayerCharacter::PlayerCharacter()
{
  
}