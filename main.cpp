#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "InventoryObject.h"
#include "AbyssalMirror.h"
#include "PlayerCharacter.h"
#include "KeyCard.h"
using namespace std;


/* class AbyssalMirror : public InventoryObject
{
  public:
  string Name = "AbyssalMirror";
  void Use()
  {
    cout << "You gaze into the strange mirror and feel your sanity slip ever so slightly";
    Quantity -= 1;
  }
}; */

class Room
{
private:
  string Description;
  string DescriptionOnEntry;
public:
  vector<InventoryObject*> RoomObjects;
  int Position[2] = {0, 0};
  bool Visited = false;
  void PrintDescription()
  {
    // Specification C4 – Abbreviated Room Description
    if(Visited == 0)
    {
      cout << DescriptionOnEntry << endl;
    }
    else
    {
      cout << Description << endl;
    }
    SetVisited(true);
  }

void SetVisited(bool VisitedRoom)
{
  Visited = VisitedRoom;
}
  void SetDescription(string DescOnEntry, string Desc)
  {
    Description = Desc;
    DescriptionOnEntry = DescOnEntry;
  }
  void SetCoords(int X, int Y)
  {
    Position[0] = X;
    Position[1] = Y;
  }

  void ConsolidateRoomObjects()
  {
    RoomObjects.clear();
  }
};

int rooms[3][7] = {{0, 0, 0, 1, 1, 1, }, {1, 1, 0, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 0}};

bool ObjectQuantityIsZero(InventoryObject obj)
{
  if (obj.Quantity == 0)
          {
            return true;
          }
  else 
  {
    return false;
  }
}

void MainGameLoop();
void AcceptCommands();

string ProcessedInput(string);

class Door
{
public:
  bool IsOpen = false;
  string KeyName;
  int Position[2] = {0, 0};
};

void ProgramGreeting()
{
  cout << "Welcome to The Violet Star\n";
  cout << "By David Ferrel\n";
  cout << "December 15th, 2022\n";
}

int AmountOfRooms()
  {
    int Count = 0;
    for(int YRoomCoord = 2; YRoomCoord >= 0; YRoomCoord--)
    {
      for(int XRoomCoord = 0; XRoomCoord <= 6; XRoomCoord++)
      {
        if (rooms[YRoomCoord][XRoomCoord] == 1)
        {
          Count += 1;
        }
      }
    }
    return Count;
  };

void DisplayMap(PlayerCharacter&);

int main() {
  bool UselessBool = true;
  bool Gamefinished = false;
  // Specification A4 - Sanity Mechanic
  int SanityLastUpdate = 5;
  string PlayerName = "Whateley";
  string UselessString = "TextHere";
  string AmnaeoticWallText = "You stab the knife into the sinuey mass upon the wall and are immediately assaulted by the coppery scent of blood. You quickly find that the scent is strangely inauthentic, as though it is a near-perfect imitation rather than the genuine article. You brace yourself and move the blade down with some effort and the barrier gives way with a sound like the tearing of heavy cloth. Hot blood leaks from the incision through veins almost as thick as your finger. Several times you find that you need to retract the blade and begin cuttin from somewhere slightly adjacent to where you left off. By the time you have carved an incision large enough that you can fit through the wall is left a set of tattered, bleeding ribbons.";
  // Specification A5 - Environmental puzzles
  Door DefaultDoor;
  DefaultDoor.KeyName = "None";
  DefaultDoor.Position[0] = 0;
  DefaultDoor.Position[1] = 0;
  
  Door AmnaeoticWall;
  AmnaeoticWall.KeyName = "Knife";
  AmnaeoticWall.Position[0] = 6;
  AmnaeoticWall.Position[1] = 2;

  Door Acolyte;
  Acolyte.KeyName = "Knife";
  Acolyte.Position[0] = 5;
  Acolyte.Position[1] = 3;

  Door AirlockDoor;
  AirlockDoor.KeyName = "Keycard";
  AirlockDoor.Position[0] = 4;
  AirlockDoor.Position[1] = 3;
  
  Door* Doors[] = {&AmnaeoticWall, &Acolyte, &AirlockDoor};
  
  PlayerCharacter Player;

  // Specification C1 - Five Rooms
  Room* RoomArray[AmountOfRooms()];
  
  ProgramGreeting();
  
  // Specification C2 - Player Name
  cout << "What is your name?" << endl;
  cin >> PlayerName;
  
  Room Bridge;
  // Specification B3 - Trap Encounter
  Bridge.SetDescription("You step into the bridge. At The bow is a large, sealed glass array of windows, out of which you behold The Star. It appears to be a white dwarf, however it forgoes the traditional pale hue of a White Dwarf in favour of a colour which you would fancy to be the colour of lightning. As you gaze upon the star you are overcome with the sense that the star should not be stared at. 'It does not like to be challenged.' a voice in your mind states plainly and with unnerving clarity. You decide that it would be best to look away from the thing. Sitting in the captain's chair you behold a being draped with loose-fitting robes of a dark crimson. The being's face is concealed entirely in the inky shadows of his hood and you suddenly know that the being is an acolyte of The Star. You stare at the being hardly more than a millisecond before he begins to speak. \n'Do you wish to know its name, " + PlayerName + "?' \nBefore you have the chance to deny the acolyte's query it profanes your ears with an inhuman utterance which could only be the name of some extraterrestrial prescence woefully beyond human comprehension. The sound was entirely alien and only served to show the laughable inadequacy of the concept of language itself. Upon hearing such an utterance you are bombarded by extrasensory stimuli which combine to givee ou the feeling as though your very soul lies on a precipice so vast that to attempt to comprehend it would be like an inchworm attempting to measure the walls of a cathedral. 'Good Day!' You shout deleriously as you begin to make your exit, however the acolyte suddenly stands and shouts 'Wait!'. Upon this you are suddenly and overwhelmingly overcome with a feeling of groundedness and presence which is almost unbearable. You tureen to the being and he speaks once more. \n'I have only one request of you. I traded my humanity for the ability to speak to the star. I was made immortal. You would think that such a thing would lead one to their loftiest dreams.. but... insead I am forced to live out this miserable existence in perpetuity. I have seen things as beautiful and terrible as the blackness betwixt the stars... I... ' The being descends into mad ramblings and you are forced to bring him to his senses. \n'What do you want from me, then?' you ask, curtly.\n'Kill Me.' The being responds simply. 'End this miserable half-life which I was foolish enough to step into.'", "You walk into the bridge and observe the being as he sits in the captain's chair mumbling incoherently to himself. You dare not listen too intently to his words for fear of hearing something else which the human species is not meant to comprehend");
  Bridge.SetCoords(5, 3);

  Room Airlock;
  Airlock.SetDescription("You step into the airlock leading to the SSG Anesidora. Before you is a large, airtight bulkhead leading to the Anesidora's docking umbilical.", "You walk into the Commodore-side airlock");
  Airlock.SetCoords(4, 3);

  Room Umbilical;
  Umbilical.SetDescription("You step through the bulkhead and into the Ansidora's docking umbilical, a square tube with walls of a thick, grey rubber which is corregated in a way that reminds you of an accordion. This, you know, is so that the umbilical can be retracted into the exterior hull of the ship during standard spaceflight. You feel the gravity shift almost imperceptibly as you transition between the two ships' artificial gravity fields.", "You walk into the docking umbilical and feel it flex ever so slightly under your weight");
  Umbilical.SetCoords(3, 3);

  Room AneAirlock;
  AneAirlock.SetDescription("You step into the Aneasidora's airlock. Before you is a slighltiy different bulkhead to that on the Commodore which leads back out to the ship's docking umbilical.", "You step into the Anesidora's airlock");
  AneAirlock.SetCoords(2, 3);

  Room TelescopeRoom;
  // Specification A2 - Another monster (technically). It's Azathoth so you can't kill it.
  TelescopeRoom.SetDescription("You walk into the helm of the Anesidora. Amongst all of the crew stations and flight readouts containing information which you cannot begin to decypher, you spot the digital viewport for the large, boxy exterior telescope which you can see through the forward windows to be gazing directly at the violet abomination. You feel some primordial need to behold the star and you begin to move towards the viewport as if your limbs are not your own. You find youself gazing into the small monitor and are instantly snapped back into your own body as you behold the ungodly thing before you. You are immediately overcome with a vertigenious nausia which remind you of staring up into the starlit sky as a child and beginning to feel as though you may at any moment fall outward into the abyss. The sensation overwhelms your vestibular system and sends you toppling onto your knees with the image of the godforsaken thing left in your mind's eye like a burn to your retinae. You behold the fading after-image of a haphazard conglomeration eyes and limbs. Slick, black tendrils curling wickedly out into the vacuum of space, probing for something unseen. You seem to remember seeing, within the thing's churning mass, multitudinous, enormous eyes madly darting hither and thither. Moreover, from the thing you suddenly became aware of a hatred from the thing so deep and powerful that it radiated off of the thing like the hot, foul air off of a putrefying corpse. A hatred which mad the most powerful hatred you could ever feel appear to be so shallow and dull as to be utterly insignificant. Furthermore, that same hatred of yours is yet again outmatched in complexity, like attempting to compare the impulses of an amoeba to the thoughts of a god. The thing is obscene in it's every aspect, an insult to the very fabric of existence. No god could create such a heinous thing nor could he forgive it for its crime of mere existence. After a time, you stand feeling utterly drained and the realization occurs to you that the creature itself being jet black, only appears to be that strange violet from what must be an accretion disc. You avert your gaze from the monitor and from the star itself.", "You move into the helm and avert your gaze from the monitor displaying the wretched thing at the centre of the solar system which you now have the misfortune to occupy.");
  TelescopeRoom.SetCoords(1, 3);

  Room SpookyRoom;
  SpookyRoom.SetDescription("You step through the tattered hole you made and observe a room which is altogether wrong. At one angle, any given wall would appear just a fraction longer than one could possibly stand, and yet at another, it would appear just a hair short of the barest tolerable length. Gazing around the room you begin to notice more and more things which are somehow wrong on some fundamental level. You realize that, like the stench of blood from the wall that brought you here, this room is an imperfect recreation, a mockery, of the rest of the rooms in the ship.", "You walk into the illusory room and attempt to pay no mind to its fundamental wrongness.");
  SpookyRoom.SetCoords(7, 2);
  
  Room SpookyHallway;
  SpookyHallway.SetDescription("You step into the starboard-side hallway. It appears supperficially normal, however you get the bizarre feeling that reality is a bit thin along the exterior wall.", "You walk into starboard-side hallway and feel reality shift slightly.");
  SpookyHallway.SetCoords(6, 2);

  Room MessHall;
  MessHall.SetDescription("You step into the Common Room. An octagonal table stands in the centre of the room with half-eaten food and empty coffee cups scattered across its surface. The pantry sits in the corner with a dry cereal dispensor on top. Both, however, are empty. The room gives off an eerie feeling, seeming as though frozen in time. At one moment, it was bustling with life, then in what seemed to be an instant, it was empty.", "You step into the Common Room and feel a sense of ennui.");
  MessHall.SetCoords(5, 2);

  Room ConnectingHallway;
  ConnectingHallway.SetDescription("You step into the port-side hallway. Looking through the large, segmented window you see the exterior hull of the SSG Anesidora.", "You walk into the port-side hallway and see the Anesidora.");
  ConnectingHallway.SetCoords(4, 2);

  Room EscapePodRoom;
  EscapePodRoom.SetDescription("You step into the Escape Pod bay. You see three remaining escape pods, and with them, your freedom.", "You walk into the pod bay, itching for freedom.");
  EscapePodRoom.SetCoords(2, 2);

  Room AneCrewQuarters;
  AneCrewQuarters.SetDescription("You walk into the Anesidora's crew compartment. The room is divided into two sections. Towards the bow is a small dining area with a pantry and dry cereal dispensor similar to that of the Commodore. Towards the stern is a doorway into a compartment with bunk beds in small alcoves in the walls.", "You walk into the Anesidora's Crew Quarters");
  AneCrewQuarters.SetCoords(1, 2);

  Room CommEscapePods;
  CommEscapePods.SetDescription("You walk into the Escape Pod Bay hoping to find a way off the ship, however, to your dismay, you find that 5 of the 8 escape pods have already been jetissoned. Two of the remaining pods have had their displays smashed to the point of unusability, and have had the interior airlock viewports cracked so that they would no longer be capable of withstanding the depressurization of the airlock. The last pod, however, suffered te worst fate. Through unknown means, the pod was rotated approximately 10 degrees about the vertical axis, and thus when a jetisson was attempted the capsule smashed into the side of the airlock, rupturing the capsule and causing it to depressurize, as evidenced by the remains of the occupant, reduced to a crumpled mass of flesh and agony against the capsule's footwell.", "You walk into the pod bay and try to ignore the failed attempt at escape.");
  CommEscapePods.SetCoords(6, 1);

  Room CommCrewQuarters;
  CommCrewQuarters.SetDescription("You walk back into the Crew Quarters and read the names on the beds as you try to remember your crewmates; Kane, Lambert, Parker, Brett, Ash, and Dallas.", "You walk back into the Crew Quarters in which you gained consciousness.");
  CommCrewQuarters.SetCoords(5, 1);

  Room Kitchen;
  Kitchen.SetDescription("You move into the kitchen. It is outfitted with basic amenities for heating food such as a microwave and several electric stoves as well as a refrigerator and a freezer which you always questioned the need for, as perishable items are almost never packed due to the long duration of spaceflights.", "You walk into the kitchen.");
  Kitchen.SetCoords(4, 1);

  Room NavRoom;
  NavRoom.SetDescription("You move into the Navigation Centre. The room is densely packed with terminals containing flight readouts which you were not trained to read. You find one terminal interesing, however, as it is connected to the ship's Blackbox. Out of curiosity, you make your way over to the terminal and read it. Amongst the smattering of coordinates, quaternions, and other miscellanious data, you notice that the ship made emergency evasive maneuvers and deployed several of its escape pods, however no threat was detected, and the onboard systems attempted to counteract these maneuvers before being overridden.", "You walk into the ship's Navigation Centre.");
  NavRoom.SetCoords(6, 3);
  
  Player.position = {5, 1};
  KeyCard AirlockCard;
  AirlockCard.SetName("Keycard");
  KeyCard Knife;
  Knife.SetName("Knife");
  AbyssalMirror TestObject3;
  string command = "";
  string object = "";

  cout << "You regain consciousness in the Crew Quarters of the USCSS Commodore, a lightweight research vessel sent to investigate Luyten 726-8, a star which was otherwise unremarkable until 14 days before your mission began when over the course of 22 hours, the star went out briefly before seeming to reignite, though with a decreased luminosity. The most bizarre detail, and the one which prompted the urgent response, was the fact that the star now shone a bizarre violet. there were even rumours that looking at the star caused certain people to feel physically ill. The last notable event you remember was the captain announcing that the ship was approximately 8 AU from the star. After that, absolutely nothing. You sit up from your bed and survey the room around you. The Crew Quarters comprise 8 bunk beds, each set into the wall of a short walkway wide enough for about two people comfortably and three shoulder-to-shoulder. You begin to place your right hand down on the bed and you feel something cold, hard, and smooth. You look down at the object and find what appears to be an odd handheld mirror of sorts. The frame is a slightly rotated scalene triangle, with a ring centered around the middle of the triangle, intersecting with the frame twice along each face. The reflection in the mirror, however, is the most curious aspect. The mirror does not simply reflect what was before it, instead it seems to act more as a window. Through the glass can be seen a vast field of stars ranging from blue to a deep violet, with nebulae of similar colors and clusters of stars scattered about. The mirror would otherwise be wonderous, however gazing into it elicits a strange sensation as if the very fabric of reality is beginning to unwind. You decide to stow the mirror away on your person as you stand up to move about the ship." << endl;
  
  //Player.inventory.push_back(&AirlockCard);
  // Specification A1 - Treasure
  SpookyRoom.RoomObjects.push_back(&AirlockCard);
  Kitchen.RoomObjects.push_back(&Knife);
  Player.inventory.push_back(&TestObject3);
  
  RoomArray[0] = &Bridge;
  RoomArray[1] = &Airlock;
  RoomArray[2] = &Umbilical;
  RoomArray[3] = &AneAirlock;
  RoomArray[4] = &TelescopeRoom;
  RoomArray[5] = &SpookyRoom;
  RoomArray[6] = &SpookyHallway;
  RoomArray[7] = &MessHall;
  RoomArray[8] = &ConnectingHallway;
  RoomArray[9] = &EscapePodRoom;
  RoomArray[10] = &CommCrewQuarters;
  RoomArray[11] = &CommEscapePods;
  RoomArray[12] = &AneCrewQuarters;
  RoomArray[13] = &Kitchen;
  RoomArray[14] = &NavRoom;


  do {
  if(SanityLastUpdate < 1)
  {
    system("clear");
    cout << "You feel the fabric of reality unwind and at once the hands of chittering, cackling madness wrap around your throat as you lose your grip on reality and fall completely into madness." << endl;
    main();
  }
  cin >> command;
  command = ProcessedInput(command);
  bool SuccessfulMove = false;
  //cout << DefaultDoor.IsOpen << endl;
  //cout << Player.position[0] << " " << Player.position[1] << endl;
  if (command == "use") 
  {
    // Specification A3 - Dynamic item usage
    cin >> object;
    object = ProcessedInput(object);
    if (object == "knife")
    {
      Door *TargetDoor = &DefaultDoor;
      for (Door *CurrentDoor : Doors)
      {
        if(CurrentDoor->Position[0] == Player.position[0] && CurrentDoor->Position[1] == Player.position[1])
        {
          TargetDoor = CurrentDoor;
          break;
        }
      }
      for (InventoryObject* obj : Player.inventory)
          {
            if (ProcessedInput(obj->Name) == "knife")
            {
                if(TargetDoor == &Acolyte && !TargetDoor->IsOpen)
                {
                  // Specification B2 - Combat
                  cout << "You equip ypur knife and steel yourself for the attack. At once you make a stab into the inky blackness of the Acolyte's face. The knife enters the being with a sickening noise similar to that of stabbing a rotted pumpkin. As the long blade exits through the back of the being's skull it catches on his hood and draws it back and for an instand you behold the thing's distorted, inhuman face. You turn away as you pull back the knife and attempt to block the view of the things face with the blur of your arm and the knife as you stab again aiming at the thing's chelicerae. You look away as you stab again and again ath the being's face and neck, noticing you are coated more and more in spurts of the thing's blood, unnaturally cold and a colour that at first appears to be black, but you realize is an extremely dark purple. You relinquish your attack after stabbing at the thing countless times and look upon the thing laying in a heap upon the floor. The thing is, bizarrely, much more tolerable to look at in this state. This is probably due to most of the detail of the things face either being destroyed or obscured by a thick layer of inky blood." << endl;
                  Bridge.SetDescription("You step into the bridge. At The bow is a large, sealed glass array of windows, out of which you behold The Star. It appears to be a white dwarf, however it forgoes the traditional pale hue of a White Dwarf in favour of a colour which you would fancy to be the colour of lightning. As you gaze upon the star you are overcome with the sense that the star should not be stared at. 'It does not like to be challenged.' a voice in your mind states plainly and with unnerving clarity. You decide that it would be best to look away from the thing. Sitting in the captain's chair you behold a being draped with loose-fitting robes of a dark crimson. The being's face is concealed entirely in the inky shadows of his hood and you suddenly know that the being is an acolyte of The Star. You stare at the being hardly more than a millisecond before he begins to speak. \n'Do you wish to know its name?' \nBefore you have the chance to deny the acolyte's query it profanes your ears with an inhuman utterance which could only be the name of some extraterrestrial prescence woefully beyond human comprehension. The sound was entirely alien and only served to show the laughable inadequacy of the concept of language itself. Upon hearing such an utterance you are bombarded by extrasensory stimuli which combine to give ou the feeling as though your very soul lies on a precipice so vast that to attempt to comprehend it would be like an inchworm attempting to measure the walls of a cathedral. 'Good Day!' You shout deleriously as you begin to make your exit, however the acolyte suddenly stands and shouts 'Wait!'. Upon this you are suddenly and overwhelmingly overcome with a feeling of groundedness and presence which is almost unbearable. You tureen to the being and he speaks once more. \n'I have only one request of you. I traded my humanity for the ability to speak to the star. I was made immortal. You would think that such a thing would lead one to their loftiest dreams.. but... insead I am forced to live out this miserable existence in perpetuity. I have seen things as beautiful and terrible as the blackness betwixt the stars... I... ' The being descends into mad ramblings and you are forced to bring him to his senses. \n'What do you want from me, then?' you ask, curtly.\n'Kill Me.' The being responds simply. 'End this miserable half-life which I was foolish enough to step into.'", "You walk into the bridge and observe the being's mutilated corpse in a heap upon the ground, still oozing that vile fluid from his ruined face.");
                }
                else if (TargetDoor == &AmnaeoticWall && !TargetDoor->IsOpen)
                {
                  if (Player.Sanity <= 3)
                  {
                    obj->Use(Player.Sanity, TargetDoor->IsOpen, TargetDoor->KeyName);
                    if(TargetDoor->IsOpen)
                    {   
                      cout << AmnaeoticWallText << endl;
                      SpookyHallway.SetDescription("You step into the starboard-side hallway. It appears supperficially normal, however you get the bizarre feeling that reality is a bit thin along the exterior wall.", "You walk into starboard-side hallway and observe the tattered, bleeding remains of the mass upon the wall.");
                    }
                  }
                  else
                  {
                    obj->Use(Player.Sanity, TargetDoor->IsOpen, UselessString);
                  }
                }
              Player.ConsolidateInventory();
              break;
            }
          }
    }
    else if (object == "keycard")
    {
      Door *TargetDoor = &DefaultDoor;
      for (Door *CurrentDoor : Doors)
      {
        if(CurrentDoor->Position[0] == Player.position[0] && CurrentDoor->Position[1] == Player.position[1])
        {
          TargetDoor = CurrentDoor;
          break;
        }
      }
      for (InventoryObject* obj : Player.inventory)
          {
            if (ProcessedInput(obj->Name) == "keycard")
            {
              obj->Use(Player.Sanity, TargetDoor->IsOpen, TargetDoor->KeyName);
              Player.ConsolidateInventory();
              break;
            }
          }
    }
    else
    {
    for (InventoryObject* obj : Player.inventory)
      {
        if (ProcessedInput(obj->Name) == object)
        {
          obj->Use(Player.Sanity, UselessBool, "None");
          Player.ConsolidateInventory();
          break;
        }
      }
    }
  }
  else if (command == "move")
  {
    cin >> command;
    command = ProcessedInput(command);
    int XCoord = Player.position[0] - 1;
    int YCoord = Player.position[1] - 1;
    if (command == "bow")
    {
      if (rooms[YCoord + 1][XCoord] == 1 && (YCoord + 1 <= 2))
        {
          Player.position[1] += 1;
          SuccessfulMove = true;
        }
      else
        {
          cout << "There is nothing there." << endl;
        }
    }
    else if (command == "stern")
    {
      if (rooms[YCoord - 1][XCoord] == 1 && (YCoord - 1 >= 0))
        {
          Player.position[1] -= 1;
          SuccessfulMove = true;
        }
      else
        {
          cout << "There is nothing there." << endl;
        }
    }
    else if (command == "port")
    {
      if(Player.position[0] == 4 && Player.position[1] == 3)
      {
        if (AirlockDoor.IsOpen)
          {
            Player.position[0] -= 1;
            SuccessfulMove = true;
          }
        else
          {
            cout << "You cannot move in that direction." << endl;
          }
      }
      else if (rooms[YCoord][XCoord - 1] == 1 && (XCoord - 1 >= 0))
        {
          Player.position[0] -= 1;
          SuccessfulMove = true;
        }
      else
        {
          cout << "There is nothing there." << endl;
        }
    }
    else if (command == "starboard")
    {
      if(Player.position[0] == 6 && Player.position[1] == 2)
      {
        if (AmnaeoticWall.IsOpen)
          {
            Player.position[0] += 1;
            SuccessfulMove = true;
          }
        else
          {
            cout << "You cannot move in that direction." << endl;
          }
      }
      else if (rooms[YCoord][XCoord + 1] == 1 && (XCoord + 1 <= 6))
        {
          Player.position[0] += 1;
          SuccessfulMove = true;
        }
      else
        {
          cout << "There is nothing there." << endl;
        }
    }
    else
    {
      cout << "Unrecognized Direction. directions are Port, Starboard, Bow, and Stern" << endl;
    }
  }
  else if (command == "take")
    {
      for (Room* CurrentLoopRoom: RoomArray)
      {
        if(Player.position[0] == CurrentLoopRoom->Position[0] && Player.position[1] == CurrentLoopRoom->Position[1])
        {
          cin >> object;
          object = ProcessedInput(object);
          if (CurrentLoopRoom->RoomObjects.size() == 0)
          {
            cout << "You don't find anyting to take" << endl;
          }
          else
          {
            for (InventoryObject* obj : CurrentLoopRoom->RoomObjects)
            {
            if (ProcessedInput(obj->Name) == object)
              {
                CurrentLoopRoom->ConsolidateRoomObjects();
                Player.inventory.push_back(obj);
                Player.ConsolidateInventory();
                Player.ShowInventory();
                break;
              }
              else
              {
                cout << "You don't find a " << object << "." << endl;
              }
            }
          }
          break;
        }
      }
    }
else if (command == "show")
{
  cin >> command;
  command = ProcessedInput(command);
  if (command == "map")
  {
    DisplayMap(Player);
  }
  else if (command == "sanity")
  {
    cout << Player.Sanity << endl;
  }
  else if (command == "inventory")
  {
    Player.ShowInventory();
  }
  else
  {
    cout << "Unrecognized Command." << endl;
  }
}
else if (command == "search")
{
  // Specification C5 - Detailed Look
  for (Room* CurrentLoopRoom: RoomArray)
    {
       if(Player.position[0] == CurrentLoopRoom->Position[0] && Player.position[1] == CurrentLoopRoom->Position[1])
        { 
          if (CurrentLoopRoom->RoomObjects.size() == 0)
          {
            cout << "You don't find anyting useful" << endl;
          }
          else
          {
            for (InventoryObject* obj : CurrentLoopRoom->RoomObjects)
            {
            cout << "You find a " << obj->Name << "." << endl;
            }
          }
          break;
        }
    }
}
else if (command == "help")
{
  //Specification B1 - Additional Commands
  cout << "Commands:" << endl;
  cout << "Move [Direction]: Move in a direction (Bow, Stern, Port, Starboard)" << endl;
  cout << "Take [Object]: take an object from a room, if the object exists in that room" << endl;
  cout << "Search: Search the current room. Show what is found in the room" << endl;
  cout << "Use [Object]: Use an object in your inventory, if you have that object" << endl;
  cout << "Show [Stat]: Show a certain statistic or piece of data (Map, Sanity, Inventory)" << endl;
}
else
{
  cout << "Unrecognized Command. Enter 'help' for list of commands." << endl;
}

  if (Player.Sanity < SanityLastUpdate && SanityLastUpdate == 4)
  {
    if (Player.Sanity != SanityLastUpdate && Player.position[0] == 6 && Player.position[1] == 2)
      {
        cout << "You look up to see the room and recoil in horror as you observe the starboard-side wall. Growing on the wall is a mass of flesh. Muscle and skin pulsate occasionally with thick veins. With sudden, frightening clarity the idea comes to you that the mass is sunken into and through the wall, and that there is something on the other side." << endl;
      }
      SpookyHallway.SetDescription("You step into the starboard-side hallway. It appears supperficially normal until you observe the starboard-side wall. Growing on the wall is a mass of flesh. Muscle and skin pulsate occasionally with thick veins. With sudden, frightening clarity the idea comes to you that the mass is sunken into and through the wall, and that there is something on the other side.", "You walk into starboard-side and observe the grotesque mass upon the wall.");
  }
  else if(SuccessfulMove) 
    {
      for (Room* CurrentLoopRoom: RoomArray)
      {
        if(Player.position[0] == CurrentLoopRoom->Position[0] && Player.position[1] == CurrentLoopRoom->Position[1])
        {  
          CurrentLoopRoom->PrintDescription();
          if(Player.position[0] == 2 && Player.position[1] == 2)
            {  
              Gamefinished = true;
            }
          break;
        }
      }
    }
  
  SanityLastUpdate = Player.Sanity;
  } while (!Gamefinished);
    cout << "you tap the button on the display for pod 5 and climb into the escape pod. The lid closes and the pod slides back into its bay and you hear the door close behind you. A holographic display projected on the glass in front of your face displays a counter.\n10...\n9...\nYou begin to fasten a harness similar to a seatbelt to your chest and slide your right hand into the combination EEG/ECG monitor at your side while placing the pod's inbuilt oxygen mask over your mouth and nose.\n5...\n4...\nYou brace yourself for the sudden jolt.\n3...\n2...\n1...\nThe pod bay door on the exterior of the ship opens rapidly and there is a short, loud 'thump!' followed by absolute silence as the pod bay depressurizes. You do not hear the monopropellant thrusters, you feel them rumbling against the back of your skull. As you drift off into space, you hear a change in the flow of oxygen as anaesthetic gas is released into your oxygen supply and you fall unconscious for cryosleep. \nCONGRATULATIONS! You have finished The Violet Star. Thank you for playing!\nWhen you are ready, enter anything to exit." << endl;
    cin >> command;
}

// Specification C3 - Input Validation
string ProcessedInput(string Input)
{
  string ProcessedInput;
  for (int i = 0; i < Input.length(); i++)
    {
      ProcessedInput += tolower(Input[i]);
    }
  return ProcessedInput;
}

void DisplayMap(PlayerCharacter& Player)
  {
    //system("clear");
    for(int YRoomCoord = 2; YRoomCoord >= 0; YRoomCoord--)
    {
      for(int XRoomCoord = 0; XRoomCoord <= 6; XRoomCoord++)
      {
        if (XRoomCoord == Player.position[0] - 1 && YRoomCoord == Player.position[1] - 1)
        {
          cout << "█";
        }
        else
        {
          if (rooms[YRoomCoord][XRoomCoord] == 1)
          {
            cout << "░";
          }
          else
          {
            cout << " ";
          }
        }
      }
      cout << endl;
    }
  }
