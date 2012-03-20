/*
Copyright (C) 2009-2012 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, 51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA.
*/

#include "../headers.h"

#include "../audio/audio.h"
#include "../custom_actions.h"
#include "../collisions.h"
#include "../dialog.h"
#include "../enemy/rock.h"
#include "../enemy/thunder_cloud.h"
#include "../entity.h"
#include "../event/global_trigger.h"
#include "../event/trigger.h"
#include "../game.h"
#include "../geometry.h"
#include "../graphics/animation.h"
#include "../graphics/decoration.h"
#include "../graphics/gib.h"
#include "../hud.h"
#include "../inventory.h"
#include "../map.h"
#include "../player.h"
#include "../projectile.h"
#include "../system/error.h"
#include "../system/properties.h"
#include "../system/random.h"

extern Entity *self, player;

static void entityWait(void);
static void vineMoveDown(void);
static void vineMoveUp(void);
static void grabPlayer(void);
static void touch(Entity *);
static void grabPlayer(void);
static void raiseOffGround(void);
static void takeDamage(Entity *, int);

Entity *addChaosVine(int x, int y, char *name)
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		showErrorAndExit("No free slots to add a Chaos Vine");
	}

	loadProperties(name, e);

	e->x = x;
	e->y = y;

	e->action = &entityWait;

	e->draw = &drawLoopingAnimationToMap;
	e->takeDamage = &takeDamage;

	e->type = ENEMY;

	setEntityAnimation(e, "STAND");

	return e;
}

static void entityWait()
{
	if (self->active == TRUE)
	{
		if (self->y < self->endY)
		{
			self->health = self->maxHealth;

			self->action = &vineMoveDown;
		}

		if (player.health > 0 && collision(player.x, player.y, player.w, player.h, self->x, self->y, self->w, SCREEN_HEIGHT) == 1)
		{
			playSoundToMap("sound/boss/armour_boss/tongue_start.ogg", -1, self->x, self->y, 0);

			self->targetY = player.y + player.h - self->h;

			self->touch = &touch;

			self->action = &grabPlayer;
		}
	}

	checkToMap(self);
}

static void vineMoveDown()
{
	if (self->y >= self->endY)
	{
		self->y = self->endY;

		self->dirY = 0;

		self->action = &entityWait;
	}

	else
	{
		self->dirY = 4;
	}

	checkToMap(self);
}

static void vineMoveUp()
{
	if (self->y <= self->startY)
	{
		self->y = self->startY;

		self->dirY = 0;

		self->action = &entityWait;
	}

	else
	{
		self->dirY = 8;
	}

	checkToMap(self);
}

static void grabPlayer()
{
	if (self->y >= self->targetY)
	{
		self->y = self->targetY;

		self->dirY = 0;

		self->action = &entityWait;
	}

	else
	{
		self->dirY = 4;
	}

	checkToMap(self);
}

static void touch(Entity *other)
{
	int y;

	if (self->target == NULL && other->type == PLAYER && other->health > 0)
	{
		self->target = other;

		self->target->flags |= FLY;

		self->thinkTime = 180;

		self->action = &raiseOffGround;

		self->targetY = self->endY - self->target->h;

		y = other->y + other->h - self->h;

		if (y < self->endY)
		{
			self->y = y;
		}
	}

	else
	{
		entityTouch(other);
	}
}

static void raiseOffGround()
{
	if (self->y <= self->targetY)
	{
		self->dirY = 0;

		self->action = &entityWait;
	}

	else
	{
		self->dirY = -2;
	}

	checkToMap(self);
}

static void takeDamage(Entity *other, int damage)
{
	Entity *temp;

	if (self->flags & INVULNERABLE)
	{
		return;
	}

	if (damage != 0)
	{
		self->health -= damage;

		if (other->type == PROJECTILE)
		{
			temp = self;

			self = other;

			self->die();

			self = temp;
		}

		if (self->health > 0)
		{
			setCustomAction(self, &flashWhite, 6, 0, 0);

			/* Don't make an enemy invulnerable from a projectile hit, allows multiple hits */

			if (other->type != PROJECTILE)
			{
				setCustomAction(self, &invulnerableNoFlash, HIT_INVULNERABLE_TIME, 0, 0);
			}

			if (self->pain != NULL)
			{
				self->pain();
			}
		}

		else
		{
			self->touch = NULL;

			if (self->target != NULL)
			{
				self->target->flags &= ~FLY;
			}

			self->active = FALSE;

			self->target = NULL;

			self->action = &vineMoveUp;
		}
	}
}
