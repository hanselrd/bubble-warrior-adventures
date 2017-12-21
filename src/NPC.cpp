#include "NPC.hpp"

NPC::NPC()
    : Entity() {
    _name = "castle_npc";
    _filePath = _name + ".png";
    _isAttacking = false;
    _entityType = EntityType::NPC;
}

NPC::NPC(sf::IntRect)
    :NPC() {


}
NPC::NPC(Map::Object mapObject)
    : Entity(mapObject) {
    _name = mapObject.getName();
    _filePath = _name + ".png";
    _isAttacking = false;
}


NPC::NPC(std::string filePath, std::string npcName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat) {
    _name = npcName;
    _filePath = filePath;
    _isAttacking = false;
    _entityType = EntityType::NPC;
}
void NPC::update(float delta) {



}