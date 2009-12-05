/*
Copyright (C) 2009 Parallel Realities

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

#include "../system/error.h"
#include "../custom_actions.h"
#include "../inventory.h"
#include "../entity.h"
#include "item.h"
#include "key_items.h"
#include "../collisions.h"

#include "chicken_feed.h"
#include "chicken_trap.h"
#include "coal_pile.h"
#include "rock_pile.h"
#include "heart_container.h"
#include "shrub.h"
#include "stalactite.h"
#include "bomb.h"
#include "bomb_pile.h"
#include "potions.h"
#include "power_generator.h"
#include "grabber.h"
#include "../world/arrow_target.h"
#include "symbol_block.h"
#include "force_field.h"
#include "gazer_eye_slot.h"
#include "spring.h"
#include "number_block.h"
#include "bubble_machine.h"
#include "bubble.h"
#include "potion_dispenser.h"
#include "tesla_charger.h"
#include "tesla_pack.h"
#include "high_striker.h"
#include "containment_unit.h"
#include "containment_unit_controls.h"
#include "ice_spray.h"
#include "blending_machine.h"
#include "spike_ball.h"
#include "code_door.h"
#include "code_display.h"
#include "skull.h"
#include "glass_wall.h"
#include "robot.h"
#include "tuning_fork.h"
#include "pedestal.h"
#include "cauldron.h"
#include "soul_bottle.h"
#include "instruction_machine.h"
#include "movable_lift.h"

extern Entity *self, player;

static Constructor items[] = {
{"item/chicken_feed_bag", &addChickenFeedBag},
{"item/chicken_trap", &addChickenTrap},
{"item/coal_pile", &addCoalPile},
{"item/rock_pile", &addRockPile},
{"misc/small_tree", &addShrub},
{"item/heart_container", &addHeartContainer},
{"item/stalactite", &addStalactite},
{"item/bomb", &addBomb},
{"item/bomb_pile", &addBombPile},
{"item/health_potion", &addHealthPotion},
{"item/slime_potion", &addSlimePotion},
{"item/invisibility_potion", &addInvisibilityPotion},
{"item/arrow_target", &addArrowTarget},
{"item/power_generator", &addPowerGenerator},
{"item/grabber", &addGrabber},
{"item/symbol_block", &addSymbolBlock},
{"item/force_field", &addForceField},
{"item/gazer_eye_slot", &addGazerEyeSlot},
{"item/spring", &addSpring},
{"item/number_block", &addNumberBlock},
{"item/bubble_machine", &addBubbleMachine},
{"item/bubble", &addBubble},
{"item/high_striker", &addHighStriker},
{"item/potion_dispenser", &addPotionDispenser},
{"item/tesla_charger", &addTeslaCharger},
{"item/tesla_pack_empty", &addTeslaPack},
{"item/tesla_pack_full", &addTeslaPack},
{"item/containment_unit", &addContainmentUnit},
{"item/containment_unit_controls", &addContainmentUnitControls},
{"item/ice_spray", &addIceSpray},
{"item/blender", &addBlendingMachine},
{"item/spike_ball", &addSpikeBall},
{"item/code_door", &addCodeDoor},
{"item/code_display", &addCodeDisplay},
{"item/skull", &addSkull},
{"item/glass_wall", &addGlassWall},
{"item/robot", &addRobot},
{"item/tuning_fork", &addTuningFork},
{"item/pedestal", &addPedestal},
{"item/cauldron", &addCauldron},
{"item/soul_bottle", &addSoulBottle},
{"item/instruction_machine", &addInstructionMachine},
{"item/moveable_lift", &addMovableLift}
};

static int length = sizeof(items) / sizeof(Constructor);

Entity *addKeyItem(char *name, int x, int y)
{
	int i;
	Entity *e;

	for (i=0;i<length;i++)
	{
		if (strcmpignorecase(items[i].name, name) == 0)
		{
			e = items[i].construct(x, y, name);

			if (e->fallout == NULL)
			{
				e->fallout = &itemFallout;
			}

			return e;
		}
	}

	showErrorAndExit("Could not find key item %s", name);

	return NULL;
}

void keyItemTouch(Entity *other)
{
	if (!(self->flags & INVULNERABLE) && other->type == PLAYER)
	{
		addToInventory(self);
	}
}

void keyItemFallout()
{
	self->dirX = 0;

	self->thinkTime = 300;

	self->action = &keyItemRespawn;
}

void keyItemRespawn()
{
	self->thinkTime--;

	checkToMap(self);

	if (self->thinkTime <= 0)
	{
		self->x = player.x + (player.w - self->w) / 2;
		self->y = player.y + player.h - self->h;

		self->dirY = ITEM_JUMP_HEIGHT;

		setCustomAction(self, &invulnerable, 180, 0);

		self->action = &doNothing;
	}
}
