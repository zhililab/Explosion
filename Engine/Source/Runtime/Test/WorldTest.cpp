//
// Created by johnk on 2022/8/15.
//

#include <gtest/gtest.h>

#include <Runtime/World.h>

struct Position : public Runtime::Component {
    Position(Runtime::World* inWorld, Runtime::Entity inEntity, float inX, float inY) : Runtime::Component(inWorld, inEntity), x(inX), y(inY) {}

    float x;
    float y;
};

struct Velocity : public Runtime::Component {
    Velocity(Runtime::World* inWorld, Runtime::Entity inEntity, float inX, float inY) : Runtime::Component(inWorld, inEntity), x(inX), y(inY) {}

    float x;
    float y;
};

class VelocitySystem : public Runtime::System {
public:
    VelocitySystem() = default;
    ~VelocitySystem() override = default;

    void Setup() {}

    void Tick(const Runtime::Query<Position, Velocity>& query) // NOLINT
    {
        query.ForEach([](Position& position, Velocity& velocity) -> void {
            position.x += velocity.x;
            position.y += velocity.y;
        });
    }
};

class PositionSetupSystem : public Runtime::System {
public:
    PositionSetupSystem(float inX, float inY) : x(inX), y(inY) {}
    ~PositionSetupSystem() override = default;

    void Setup(const Runtime::Query<Position>& query)
    {
        query.ForEach([this](Position& position) -> void {
            position.x = x;
            position.y = y;
        });
    }

    void Tick() {}

private:
    float x;
    float y;
};

TEST(WorldTest, ComponentBasicTest)
{
    Runtime::World world("TestWorld");

    auto entity = world.CreateEntity();
    world.AddComponent<Position>(entity, 1.0f, 2.0f);

    auto* position = world.GetComponent<Position>(entity);
    ASSERT_NE(position, nullptr);
    ASSERT_EQ(position->x, 1.0f);
    ASSERT_EQ(position->y, 2.0f);

    world.RemoveComponent<Position>(entity);
    position = world.GetComponent<Position>(entity);
    ASSERT_EQ(position, nullptr);
}

TEST(WorldTest, SystemBasicTest)
{
    Runtime::World world("SystemBasicTestWorld");

    auto entity0 = world.CreateEntity();
    world.AddComponent<Position>(entity0, 1.0f, 2.0f);
    world.AddComponent<Velocity>(entity0, 0.0f, 0.0f);

    auto entity1 = world.CreateEntity();
    world.AddComponent<Position>(entity1, 5.0f, 6.0f);
    world.AddComponent<Velocity>(entity1, 1.0f, 2.0f);

    auto* system = new VelocitySystem;
    system->Wait(world.EngineSystems());
    world.AddSystem(system);

    world.Setup();
    world.Tick();

    auto* position0 = world.GetComponent<Position>(entity0);
    ASSERT_EQ(position0->x, 1.0f);
    ASSERT_EQ(position0->y, 2.0f);

    auto* position1 = world.GetComponent<Position>(entity1);
    ASSERT_EQ(position1->x, 6.0f);
    ASSERT_EQ(position1->y, 8.0f);

    world.Tick();

    ASSERT_EQ(position0->x, 1.0f);
    ASSERT_EQ(position0->y, 2.0f);

    ASSERT_EQ(position1->x, 7.0f);
    ASSERT_EQ(position1->y, 10.0f);
}

TEST(WorldTest, SystemSetupTest)
{
    // TODO
}
