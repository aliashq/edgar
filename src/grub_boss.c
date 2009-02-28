#include "headers.h"

#include "animation.h"
#include "properties.h"
#include "entity.h"
#include "collisions.h"
#include "game.h"
#include "audio.h"
#include "music.h"
#include "map.h"
#include "random.h"
#include "custom_actions.h"
#include "projectile.h"

extern Entity *self, player;

static void wait(void);
static void spitStart(void);
static void spit(void);
static void spitEnd(void);
static void initialise(void);
static void takeDamage(Entity *, int);
static void die(void);
static void attackFinished(void);
static void spinAttackStart(void);
static void spinAttack(void);
static void spinAttackEnd(void);
static void doIntro(void);
static void introPause(void);

Entity *addGrubBoss(int x, int y)
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		printf("No free slots to add the Grub Boss\n");

		exit(1);
	}

	loadProperties("boss/grub_boss", e);

	e->x = x;
	e->y = y;

	e->action = &initialise;

	e->draw = &drawLoopingAnimationToMap;
	e->takeDamage = &takeDamage;

	e->type = ENEMY;

	e->flags |= NO_DRAW|FLY;

	e->active = FALSE;

	setEntityAnimation(e, STAND);

	return e;
}

static void takeDamage(Entity *other, int damage)
{
	self->health -= damage;
	
	setCustomAction(self, &flashWhite, 6);

	if (self->health < 0)
	{
		self->action = &die;
	}
}

static void wait()
{
	self->dirX = 0;

	self->thinkTime--;

	if (self->thinkTime <= 0)
	{
		if (prand() % 2 == 0)
		{
			self->action = &spitStart;

			self->thinkTime = 1;
		}

		else
		{
			self->action = &spinAttackStart;

			self->thinkTime = 60;
		}
	}

	checkToMap(self);
}

static void spitStart()
{
	if (self->frameSpeed > 0)
	{
		if (self->thinkTime > 0)
		{
			setEntityAnimation(self, ATTACK_1);

			self->animationCallback = &spit;
		}

		else
		{
			attackFinished();
		}
	}

	else
	{
		self->animationCallback = &spitEnd;
	}

	checkToMap(self);
}

static void spitEnd()
{
	self->frameSpeed *= -1;
}

static void spit()
{
	int x = (self->face == RIGHT ? 40 : 17);
	int i = prand() % 3;
	
	addProjectile("boss/grub_boss_shot", self, self->x + x, self->y + 6, (self->face == RIGHT ? 7 : -7), -12);
	
	if (i == 1)
	{
		addProjectile("boss/grub_boss_shot", self, self->x + x, self->y + 6, (self->face == RIGHT ? 4 : -4), -12);
	}
	
	if (i > 0)
	{
		addProjectile("boss/grub_boss_shot", self, self->x + x, self->y + 6, (self->face == RIGHT ? 1 : -1), -12);
	}

	self->thinkTime--;

	self->frameSpeed *= -1;
}

static void initialise()
{
	int minX, minY;

	minX = getMapStartX();
	minY = getMapStartY();

	if (self->active == TRUE)
	{
		adjustMusicVolume(-1);
		
		centerMapOnEntity(NULL);
		
		if (minX < self->endX)
		{
			minX++;
		}
		
		else if (minX > self->endX)
		{
			minX--;
		}

		if (minY < self->endY)
		{
			minY++;
		}
		
		else if (minY > self->endY)
		{
			minY--;
		}
		
		setMapStartX(minX);
		setMapStartY(minY);

		if (minX == self->endX && minY == self->endY)
		{
			self->dirX = self->speed;

			setEntityAnimation(self, ATTACK_2);

			self->action = &doIntro;

			self->flags &= ~NO_DRAW;
			self->flags &= ~FLY;

			printf("Starting\n");
		}
	}
}

static void doIntro()
{
	if (self->dirX == 0)
	{
		shakeScreen(MEDIUM, 15);

		self->face = LEFT;

		self->dirX = -3;

		self->dirY = -8;

		self->thinkTime = 1;
	}

	else if ((self->flags & ON_GROUND) && self->thinkTime == 1)
	{
		setEntityAnimation(self, STAND);

		self->thinkTime = 60;

		self->dirX = 0;

		self->action = &introPause;
	}

	checkToMap(self);
}

static void introPause()
{
	self->thinkTime--;

	if (self->thinkTime <= 0)
	{
		self->touch = &entityTouch;

		attackFinished();
	}

	checkToMap(self);
}

static void spinAttackStart()
{
	setEntityAnimation(self, ATTACK_2);

	if (self->thinkTime > 0)
	{
		self->thinkTime--;

		if (self->thinkTime == 0)
		{
			self->face = (player.x > self->x ? RIGHT : LEFT);

			self->frameSpeed = 2;

			self->dirY = -8;
		}
	}

	else if (self->thinkTime == 0 && self->flags & ON_GROUND)
	{
		self->dirX = (self->face == RIGHT ? self->speed : -self->speed);

		self->action = &spinAttack;
	}

	checkToMap(self);
}

static void spinAttack()
{
	float speed = self->dirX;

	checkToMap(self);

	if (self->dirX == 0)
	{
		shakeScreen(MEDIUM, 15);

		self->face = (player.x > self->x ? RIGHT : LEFT);

		self->dirX = speed < 0 ? 3 : -3;

		self->dirY = -6;

		self->action = &spinAttackEnd;

		self->thinkTime = 0;
	}
}

static void spinAttackEnd()
{
	checkToMap(self);

	if (self->flags & ON_GROUND && self->thinkTime == 0)
	{
		self->dirX = 0;

		self->action = &attackFinished;
	}
}

static void attackFinished()
{
	setEntityAnimation(self, STAND);

	self->frameSpeed = 1;

	self->thinkTime = 90;

	self->action = &wait;
}

static void die()
{
	setMinMapX(0);
	setMinMapX(0);

	centerMapOnEntity(&player);

	entityDie();
}
