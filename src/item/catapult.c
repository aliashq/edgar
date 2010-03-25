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
#include "../hud.h"
#include "../player.h"
#include "../custom_actions.h"
#include "item.h"
#include "../system/error.h"
#include "../event/script.h"

extern Entity *self, player;

static void touch(Entity *);
static void bucketTouch(Entity *);
static void bucketWait(void);
static void init(void);
static void activate(int);

Entity *addCatapult(int x, int y, char *name)
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		showErrorAndExit("No free slots to add a Catapult");
	}

	loadProperties(name, e);

	e->x = x;
	e->y = y;

	e->type = KEY_ITEM;

	e->face = RIGHT;

	e->action = &init;
	e->touch = &touch;
	e->fallout = &itemFallout;

	e->draw = &drawLoopingAnimationToMap;

	setEntityAnimation(e, STAND);

	return e;
}

static void touch(Entity *other)
{
	if (other->type != PLAYER)
	{
		self->flags |= OBSTACLE;
	}

	else
	{
		self->flags &= ~OBSTACLE;
	}

	pushEntity(other);

	self->flags &= ~OBSTACLE;
}

static void init()
{
	Entity *e = getFreeEntity();

	if (e == NULL)
	{
		showErrorAndExit("No free slots to add a Catapult Bucket");
	}

	loadProperties("item/catapult_bucket", e);

	e->type = KEY_ITEM;

	e->face = RIGHT;

	e->action = &bucketWait;
	e->touch = &bucketTouch;
	e->activate = &activate;

	e->draw = &drawLoopingAnimationToMap;
	
	e->head = self;

	setEntityAnimation(e, STAND);

	self->action = &doNothing;
}

static void bucketWait()
{
	self->x = self->head->x + self->offsetX;
	self->y = self->head->y + self->offsetY;
}

static void bucketTouch(Entity *other)
{
	if (other->type == PLAYER)
	{
		setInfoBoxMessage(0, _("Press Action to interact"));
	}
}

static void activate(int val)
{
	if (self->head->active == FALSE)
	{
		runScript("rusted");
	}
	
	else
	{
		setCustomAction(&player, &invulnerableNoFlash, 60, 0, 0);

		setPlayerStunned(60);

		player.dirX = 12;
		player.dirY = -22;
	}
}