/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particle.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/26/2021
-----------------------------------------------------------------*/

#include "Engine.h"
#include "GameObjectManager.h"
#include "ParticleEmitter.h"
#include "Sprite.h"

CS230::ParticleEmitter::ParticleEmitter(double lifetime) : particleIndexToUse(0), lifetime(lifetime) {}

CS230::ParticleEmitter::~ParticleEmitter() { particleMemoryPool.clear(); }


void CS230::ParticleEmitter::AddParticle(ParticleEmitter::Particle* particleData) {
    particleMemoryPool.push_back(particleData);
    Engine::GetGSComponent<GameObjectManager>()->Add(particleData);
}

void CS230::ParticleEmitter::Emit(int toEmit, math::vec2 emitterPosition, math::vec2 emitterVelocity, math::vec2 emitVector, double spread, math::vec2 scale, double rotate) {
    for (int i = 0; i < toEmit; i++) {
        if (particleMemoryPool[particleIndexToUse]->IsAlive() == true) {
            Engine::GetLogger().LogError("Particle is being overwritten");
        }

        double angleVariation = spread != 0 ? ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2 : 0;
        math::vec2 particleVelocity = math::RotateMatrix(angleVariation) * emitVector * (((rand() % 1024) / 2048.0f) + 0.5f) + emitterVelocity;
        particleMemoryPool[particleIndexToUse++]->Revive(emitterPosition, particleVelocity, lifetime, scale,rotate);
        if (particleIndexToUse >= particleMemoryPool.size()) {
            particleIndexToUse = 0;
        }
    }
}

CS230::ParticleEmitter::Particle::Particle(std::string spriteFile) : GameObject({ 0,0 }), life(0) {
    AddGOComponent(new Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 newPosition, math::vec2 newVelocity, double newLife, math::vec2 newScale, double newAngle) {
    life = newLife;
    SetPosition(newPosition);
    SetScale(newScale);
    SetVelocity(newVelocity);
    SetRotation(newAngle);
    GetGOComponent<Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt) {
    if (IsAlive() == true) {
        life -= dt;
        GameObject::Update(dt);
    }
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix) {
    if (IsAlive() == true) {
        GameObject::Draw(matrix);
    }
}