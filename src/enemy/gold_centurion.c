/*
Copyright (C) 2009-2010 Parallel Realities

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "../headers.h"

#include "../graphics/animation.h"
#include "../system/properties.h"
#include "../entity.h"
#include "../system/random.h"
#include "../audio/audio.h"
#include "../collisions.h"
#include "../custom_actions.h"
#include "../game.h"
#include "../player.h"
#include "../item/item.h"
#include "../event/trigger.h"
#include "../event/global_trigger.h"
#include "../system/error.h"

extern Entity *self;

static void walk(void);
static void die(void);
static void fallout(void);

Entity *addGoldCenturion(int x, int y, char *name)
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		showErrorAndExit("No free slots to add a Gold Centurion");
	}

	loadProperties(name, e);

	e->x = x;
	e->y = y;

	e->action = &walk;
	e->die = &die;
	e->draw = &drawLoopingAnimationToMap;
	e->touch = &entityTouch;
	e->fallout = &fallout;

	e->type = ENEMY;

	setEntityAnimation(e, STAND);

	return e;
}

static void walk()
{
	if (self->active == FALSE)
	{
		self->flags &= ~ATTACKING;
		
		self->damage = 0;
		
		setEntityAnimation(self, STAND);
		
		checkToMap(self);
	}
	
	else
	{
		self->damage = 1;
		
		self->flags |= ATTACKING;
		
		setEntityAnimation(self, WALK);
		
		if (self->currentFrame == 2 || self->currentFrame == 5)
		{
			if (self->maxThinkTime == 0)
			{
				playSoundToMap("sound/enemy/centurion/walk.ogg", -1, self->x, self->y, 0);

				self->maxThinkTime = 1;
			}

			self->dirX = 0;
		}

		else
		{
			self->maxThinkTime = 0;
		}
		
		checkToMap(self);

		if (self->currentFrame == 2 || self->currentFrame == 5)
		{
			self->dirX = (self->face == RIGHT ? self->speed : -self->speed);
		}
	}
}

static void fallout()
{
	self->dirX = 0;

	self->dirY = 0;

	self->frameSpeed = 0;

	self->flags |= DO_NOT_PERSIST;

	self->action = &die;
}

static void die()
{
	self->dirX = 0;
	
	self->dirY = 0.5;

	checkToMap(self);

	if (self->flags & ON_GROUND)
	{
		entityDieNoDrop();
	}
}