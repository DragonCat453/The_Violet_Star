#include "InventoryObject.h"

class KeyCard : public InventoryObject
{
  public:
    void Use(int&, bool&, std::string);
    void SetName(std::string);
};