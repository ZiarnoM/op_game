#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <player.h>

TEST_CASE("Player resetVelocityY")
{
    Player player;
    player.resetVelocityY();
    REQUIRE(player.getVelocity().y == 0.f);
}

TEST_CASE("Player resetVelocityX")
{
    Player player;
    player.resetVelocityX();
    REQUIRE(player.getVelocity().x == 0.f);
}

TEST_CASE("Player setPosition")
{
    Player player;
    player.setPosition(10.f, 20.f);
    REQUIRE(player.getPosition().x == 10.f);
    REQUIRE(player.getPosition().y == 20.f);
}

TEST_CASE("Player setMovementStateFall")
{
    Player player;
    player.setMovementState(MovementState::Fall);
    REQUIRE(player.getMovementState() == MovementState::Fall);
}

TEST_CASE("Player setMovementStateRunRight")
{
    Player player;
    player.setMovementState(MovementState::RunRight);
    REQUIRE(player.getMovementState() == MovementState::RunRight);
}