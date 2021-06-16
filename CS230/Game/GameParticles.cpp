/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: CS230
Author: Kevin Wright
Modifier: Daehyeon Kim
Creation date: 2/26/2021
Modification Date : 06/09/2021
-----------------------------------------------------------------*/

#include "GameParticles.h"

SmokeEmitter::SmokeEmitter() : CS230::ParticleEmitter(1.0) {
	for (int i = 0; i < SmokeEmitter::NumParticles; i++) {
		AddParticle(new SmokeParticle("assets/Smoke.spt"));
	}
}

HitEmitter::HitEmitter() : CS230::ParticleEmitter(1.0) {
	for (int i = 0; i < HitEmitter::NumParticles; i++) {
		AddParticle(new HitParticle("assets/Hit.spt"));
	}
}

MeteorBitEmitter::MeteorBitEmitter() : CS230::ParticleEmitter(1.5) {
	for (int i = 0; i < MeteorBitEmitter::NumParticles; i++) {
		AddParticle(new MeteorBit("assets/MeteorBit.spt"));
	}
}

ShootCannonEmitter::ShootCannonEmitter() : CS230::ParticleEmitter(0.5)
{
	for (int i = 0; i < ShootCannonEmitter::NumParticles; i++) {
		AddParticle(new ShootCannon("assets/LEVEL3/Shoot.spt"));
	}
}

BombBoomEmitter::BombBoomEmitter() : CS230::ParticleEmitter(1.0)
{
	for (int i = 0; i < BombBoomEmitter::NumParticles; i++) {
		AddParticle(new BombBoom("assets/LEVEL3/Boom.spt"));
	}
}

UnitHurtEmitter::UnitHurtEmitter() : CS230::ParticleEmitter(3)
{
	for (int i = 0; i < UnitHurtEmitter::NumParticles; i++) {
		AddParticle(new UnitHurt("assets/LEVEL3/Blood.spt"));
	}
}