#include "game/player.h"
#include <iostream>

Player::Player()
{
    this->initVariables();
    this->initTextures();
    this->initSprite();
    this->initAnimations();
    this->initPhysics();
}

Player::~Player()
{
}

void Player::update()
{
    this->updateMovement();
    this->updateAnimations();
    this->updatePhysics();
}

void Player::render(sf::RenderTarget &target)
{
    sf::RectangleShape hitbox;
    hitbox.setPosition(this->sprite.getPosition());
    hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
    target.draw(hitbox);
    target.draw(this->sprite);
}
const sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Player::resetVelocityY()
{
    this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
    this->velocity.x = 0.f;
}

sf::Vector2f Player::getVelocity()
{
    return this->velocity;
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition()
{
    return this->sprite.getPosition();
}

MovementState Player::getMovementState()
{
    return this->animationState;
}

void Player::setMovementState(MovementState value)
{
    this->animationState = value;
}

void Player::initVariables()
{
}

void Player::initTextures()
{
    if (!this->idleSheet.loadFromFile("../assets/images/player/idleSheet.png"))
    {
        std::cerr << "Error while loading playerSheet.png" << std::endl;
    }
    if (!this->runSheet.loadFromFile("../assets/images/player/runSheet.png"))
    {
        std::cerr << "Error while loading runSheet.png" << std::endl;
    }
    if (!this->fallSheet.loadFromFile("../assets/images/player/fall.png"))
    {
        std::cerr << "Error while loading fall.png" << std::endl;
    }
}

void Player::initSprite()
{
    this->sprite.setTexture(this->idleSheet);
    this->currentFrame = sf::IntRect(0, 0, 32, 32);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.f, 2.f);
}

void Player::initAnimations()
{
    this->animationState = MovementState::Idle;
    this->animationTimer.restart();
}

void Player::initPhysics()
{
    this->minVelocity = 0.1f;
    this->maxVelocity = 20.f;
    this->accelerationRate = 2.f;
    this->decelerationRate = 0.5f;
    this->gravity = 1.f;
    this->maxFallSpeed = 5.f;
    this->canJump = true;
    this->jumpTimer.restart();
}

void Player::move(const float dir_x, const float dir_y)
{
    this->velocity.x += dir_x * this->accelerationRate;
    this->velocity.y += dir_y * this->accelerationRate;
    if (std::abs(this->velocity.x) > this->maxVelocity)
    {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f); // if moving left already cap at Max * -1, inverse otherwise
    }
}

void Player::jump()
{
    if (this->jumpTimer.getElapsedTime().asMilliseconds() >= 400)
    {
        this->velocity.y = -35.f;
        this->setCanJump(false);
        this->jumpTimer.restart();
    }
}

void Player::updateMovement()
{
    if (this->velocity.x > 0.f)
    {
        this->setMovementState(MovementState::RunRight);
    }
    else if (this->velocity.x < 0.f)
    {
        this->setMovementState(MovementState::RunLeft);
    }
    else if (this->velocity.y < 0.f)
    {
        this->setMovementState(MovementState::Jump);
    }
    else if (this->velocity.y > 0.f)
    {
        this->setMovementState(MovementState::Fall);
    }
    else
    {
        this->setMovementState(MovementState::Idle);
    }
}

void Player::updatePhysics()
{
    this->velocity.y += this->gravity;
    if (this->velocity.y > this->maxFallSpeed)
    {
        this->velocity.y = this->maxFallSpeed;
    }

    this->sprite.move(0.f, this->velocity.y);

    if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height >= 640)
    {
        this->velocity.y = 0.f;
        this->canJump = true;
        this->sprite.setPosition(this->sprite.getPosition().x, 640 - this->sprite.getGlobalBounds().height);
    }

    this->velocity *= this->decelerationRate;
    if (std::abs(this->velocity.x) < this->minVelocity)
    {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) < this->minVelocity)
    {
        this->velocity.y = 0.f;
    }

    this->sprite.move(this->velocity);
}

void Player::updateAnimations()
{
    const float MAX_LEFT_IDLE = 320.f;
    const float MAX_LEFT_RUN = 352.f;
    const float FRAME_WIDTH = 32.f;

    if (this->animationTimer.getElapsedTime().asMilliseconds() >= 50)
    {
        switch (this->animationState)
        {
        case MovementState::Idle:
            this->sprite.setTexture(this->idleSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_IDLE)
            {
                this->currentFrame.left = 0;
            }
            break;

        case MovementState::RunRight:
            this->sprite.setTexture(this->runSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_RUN)
            {
                this->currentFrame.left = 0;
            }
            this->sprite.setScale(2.f, 2.f);
            this->sprite.setOrigin(0.f, 0.f);

            break;

        case MovementState::RunLeft:
            this->sprite.setTexture(this->runSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_RUN)
            {
                this->currentFrame.left = 0;
            }
            this->sprite.setScale(-2.f, 2.f);
            this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, 0.f); // we change the reference point for the flip to fix teleports on turn
            break;

        case MovementState::Fall:
            this->sprite.setTexture(this->fallSheet);
            this->currentFrame.left = 0;
            break;

        default:
            break;
        }

        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}
