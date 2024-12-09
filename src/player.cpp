#include <player.h>
#include <iostream>

// Public
// constructors and destructors
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

// general methods
void Player::update()
{
    this->updateMovement();
    this->updateAnimations();
    this->updatePhysics();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
const sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

// modifiers
void Player::resetVelocityY()
{
    this->velocity.y = 0.f;
}

// getters and setters
void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

bool Player::getMovementState()
{
    return this->animationState;
}

void Player::setMovementState(MovementState value)
{
    this->animationState = value;
}

// Private
// initialization
void Player::initVariables()
{
}

void Player::initTextures()
{
    if (!this->idleSheet.loadFromFile("../assets/images/player/idleSheet.png"))
    {
        std::cout << "Error while loading playerSheet.png" << std::endl;
    }
    if (!this->runSheet.loadFromFile("../assets/images/player/runSheet.png"))
    {
        std::cout << "Error while loading runSheet.png" << std::endl;
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
    this->maxVelocity = 4.f;
    this->accelerationRate = 2.f;
    this->decelerationRate = 0.5f;
    this->gravity = 5.f;
    this->maxFallSpeed = 10.f;
}

// Movement
void Player::move(const float dir_x, const float dir_y)
{
    this->velocity.x += dir_x * this->accelerationRate;
    this->velocity.y += dir_y * this->accelerationRate;
    if (std::abs(this->velocity.x) > this->maxVelocity)
    {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f); // if moving left already cap at Max * -1, inverse otherwise
    }
}

void Player::updateMovement()
{
    this->setMovementState(MovementState::Idle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->move(-1.f, 0.f);
        this->setMovementState(MovementState::RunLeft);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->move(1.f, 0.f);
        this->setMovementState(MovementState::RunRight);
    }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    // {
    //     this->sprite.move(0.f, -speed);
    //     this->setMovementState(MovementState::Run);
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    // {
    //     this->sprite.move(0.f, speed);
    //     this->setMovementState(MovementState::Run);
    // }
}

void Player::updatePhysics()
{
    // gravity handling and limiting
    this->velocity.y += this->gravity;
    if (this->velocity.y > this->maxFallSpeed)
    {
        this->velocity.y = this->maxFallSpeed;
    }

    // slowing down for smooth movement
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

// Animations
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

        default:
            break;
        }

        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}
