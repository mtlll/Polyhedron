#pragma once
 namespace entities { namespace classes { class CoreEntity; } }

extern int particlelayers;

enum { PL_ALL = 0, PL_UNDER, PL_OVER, PL_NOLAYER };

void initparticles();
void clearparticles();
void clearparticleemitters();
void seedparticles();
void updateparticles();
void debugparticles();
void renderparticles(int layer = PL_ALL);
bool printparticles(entities::classes::CoreEntity *e, char *buf, int len);
void cleanupparticles();