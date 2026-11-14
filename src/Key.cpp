#include "../headers/Key.hpp"

Key::Key(const Point2D& positionCenter, float radius, float objectHeight, sf::Color color, ObjectType objectType)
: Circle(positionCenter, radius, objectHeight, color, objectType){

}

Key::~Key(){
    
}

void Key::drawOnMinimap(sf::Color color, sf::RenderWindow& window) const{
    sf::CircleShape circle;
    
    float visualRadius = radius * MINIMAP_CHARACTER_SIZE_MULTIPLIER;
    circle.setRadius(visualRadius);

    float drawX = positionCenter.getX() - visualRadius;
    float drawY = positionCenter.getY() - visualRadius;
    circle.setPosition(sf::Vector2f(drawX, drawY));

    circle.setFillColor(color);

    window.draw(circle);
}

void Key::updateObject(const vector<Object2D*>& arrayObjects, float){
    Player* player = nullptr;
    Enemy* enemy = nullptr;

    for(int i = 0; i < (int)arrayObjects.size();i++){
        if(arrayObjects[i]->getObjectType() == ObjectType::Player)
            player = static_cast<Player*>(arrayObjects[i]);
        else if(arrayObjects[i]->getObjectType() == ObjectType::Enemy)
            enemy = static_cast<Enemy*>(arrayObjects[i]);

    }


    Point2D positionPlayer = player->getPositionCenter();
    Point2D vectorKeyToPlayer = Point2D(positionCenter.getX() - positionPlayer.getX(), positionCenter.getY() - positionPlayer.getY());
    float distanceToPlayer = vectorKeyToPlayer.getLenghtVector();

    if(distanceToPlayer <= KEY_PICK_UP_RADIUS){
        player->setCountCollectedKey(player->getCountCollectedKey() + 1);
        if(enemy != nullptr) enemy->foundCarefullyModeTarget(positionCenter);
        markedForDeletion = true;
    }
}
