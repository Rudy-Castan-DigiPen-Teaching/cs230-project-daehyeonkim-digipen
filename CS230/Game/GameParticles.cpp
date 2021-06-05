/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/26/2021
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