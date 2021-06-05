/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#include "Engine.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collision.h"
#include "ShowCollision.h"

CS230::GameObject::GameObject() : GameObject({ 0,0 }) {}

CS230::GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
							: velocity{ 0,0 }, position(position), updateMatrix(true), 
							scale(scale), rotation(rotation), currState(&state_nothing) {
}

CS230::GameObject::~GameObject() {
	ClearGOComponents();
}

void CS230::GameObject::Update(double dt) {
	currState->Update(this, dt);
	if (velocity.x != 0 || velocity.y != 0) {
		UpdatePosition(velocity * dt);
	}
	UpdateGOComponents(dt);
	currState->TestForExit(this);
}

void CS230::GameObject::ChangeState(State* newState) {
	currState = newState;
	currState->Enter(this);
}

void CS230::GameObject::Draw(math::TransformMatrix displayMatrix) {
	Sprite* spritePtr = GetGOComponent<Sprite>();
	if (spritePtr != nullptr) {
		spritePtr->Draw(displayMatrix * GetMatrix());
	}
	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true) {
		Collision* collisionPtr = GetGOComponent<Collision>();
		if (collisionPtr != nullptr) {
			collisionPtr->Draw(displayMatrix);
		}
	}
}

const math::vec2& CS230::GameObject::GetPosition() const { return position; }
const math::vec2& CS230::GameObject::GetVelocity() const { return velocity; }
const math::vec2& CS230::GameObject::GetScale() const { return scale; }
double CS230::GameObject::GetRotation() const { return rotation; }
const math::TransformMatrix& CS230::GameObject::GetMatrix() {
	if (updateMatrix == true) {
		objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
		updateMatrix = false;
	}
	return objectMatrix;
}

void CS230::GameObject::SetPosition(math::vec2 newPosition) {
	position = newPosition;
	updateMatrix = true;
}

void CS230::GameObject::SetVelocity(math::vec2 newVelocity) {
	velocity = newVelocity;
}

void CS230::GameObject::UpdateVelocity(math::vec2 newVelocity) {
	velocity += newVelocity;
}

void CS230::GameObject::UpdatePosition(math::vec2 addPosition) {
	position += addPosition;
	updateMatrix = true;
}

void CS230::GameObject::SetScale(math::vec2 newScale) {
	scale = newScale;
	updateMatrix = true;
}

void CS230::GameObject::SetRotation(double newRotationAmount) {
	rotation = newRotationAmount;
	updateMatrix = true;
}
void CS230::GameObject::UpdateRotation(double adjustRotation) {
	rotation += adjustRotation;
	updateMatrix = true;
}

bool CS230::GameObject::CanCollideWith(GameObjectType) {
	return false;
}

bool CS230::GameObject::DoesCollideWith(CS230::GameObject* objectB) {
	return GetGOComponent<Collision>() != nullptr && objectB->GetGOComponent<Collision>() != nullptr 
				&& GetGOComponent<Collision>()->DoesCollideWith(objectB);
}

bool CS230::GameObject::DoesCollideWith(math::vec2 point) {
	return GetGOComponent<Collision>() != nullptr && GetGOComponent<Collision>()->DoesCollideWith(point);
}

void CS230::GameObject::ResolveCollision(CS230::GameObject*) {
	Engine::GetLogger().LogError("Base class collision resolution should not be called");
}