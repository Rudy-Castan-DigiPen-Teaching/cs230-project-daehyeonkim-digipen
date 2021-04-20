/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 4/19/2021
-----------------------------------------------------------------*/
#include "GameObject.h"

CS230::GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true),
    scale(scale), rotation(rotation), currState(&state_nothing) {
}

void CS230::GameObject::Update(double dt) {
    currState->Update(this, dt);
    sprite.Update(dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    currState->TestForExit(this);
}

void CS230::GameObject::ChangeState(State* newState) {
    currState = newState;
    currState->Enter(this);
}

void CS230::GameObject::Draw(math::TransformMatrix cameraMatrix) {
    sprite.Draw(cameraMatrix * GetMatrix());
}

const math::TransformMatrix& CS230::GameObject::GetMatrix() {
    if (updateMatrix == true) {
        objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
        updateMatrix = false;
    }
    return objectMatrix;
}

const math::vec2& CS230::GameObject::GetPosition() const
{
    return position;
}

void CS230::GameObject::SetPosition(math::vec2 newPosition) {
    position = newPosition;
    updateMatrix = true;
}

void CS230::GameObject::UpdatePosition(math::vec2 adjustPosition)
{
    position += adjustPosition;
    updateMatrix = true;
}

const math::vec2& CS230::GameObject::GetVelocity() const
{
    return velocity;
}

const math::vec2& CS230::GameObject::GetScale() const
{
    return scale;
}

double CS230::GameObject::GetRotation() const
{
    return rotation;
}

void CS230::GameObject::SetVelocity(math::vec2 newVelocity)
{
    velocity = newVelocity;
    updateMatrix = true;
}

void CS230::GameObject::UpdateVelocity(math::vec2 adjustVelocity)
{
    velocity += adjustVelocity;
    updateMatrix = true;
}

void CS230::GameObject::SetScale(math::vec2 newScale)
{
    scale = newScale;
    updateMatrix = true;
}

void CS230::GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
    updateMatrix = true;
}

void CS230::GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

