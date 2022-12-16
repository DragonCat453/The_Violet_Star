#include "InventoryObject.h"

class AbyssalMirror : public InventoryObject
{
  public:
    void Use(int&, bool&, std::string);
    AbyssalMirror();
};