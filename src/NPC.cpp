#include "NPC.hpp"

NPC::NPC(std::string filePath, std::string npcName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat) {
    _name = npcName;
    _filePath = filePath;
    _isAttacking = false;
    _entityType = EntityType::NPC;
}

NPC::NPC(sf::IntRect)
    :NPC() {


}

NPC::NPC()
    : Entity() {

    _isAttacking = false;
    _entityType = EntityType::NPC;
}

void NPC::update(float delta) {



}