/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/24/2021
-----------------------------------------------------------------*/
#include "ParticleEmitter.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) : life(0)
{
	AddGOComponent(new Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 _position, math::vec2 _velocity, double _life)
{
	SetPosition(_position);
	SetVelocity(_velocity);
	life = _life;
	GetGOComponent<Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if(life > 0)
	{
		life -= dt;
		GameObject::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (life > 0)
	{
		GameObject::Draw(matrix);
	}
}

CS230::ParticleEmitter::ParticleEmitter(double lifetime) : lifetime(lifetime), particleIndexToUse(0){}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<GameObjectManager>()->Add(particleData);
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity,math::vec2 emitVector,
	double spread)
{
	for(int i = 0; i < number; i++)
	{
		if(particleMemoryPool[particleIndexToUse]->IsAlive() == true)
		{
			Engine::GetLogger().LogError("Currently alive particle is overwrote");
		}
		const double velocityScale = ((rand() % 1024) / 2048.0) + 0.5;
		particleMemoryPool[particleIndexToUse]->Revive(position, math::RotateMatrix(((rand() % static_cast<int>(1024) / 1024.0) - 0.5) * spread) * math::ScaleMatrix({ velocityScale, velocityScale }) * emitVector + emitterVelocity, lifetime);
		particleIndexToUse++;
		if (particleIndexToUse >= particleMemoryPool.size())
		{
			particleIndexToUse = 0;
		}
	}
}
