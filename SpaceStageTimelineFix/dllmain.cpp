/****************************************************************************
* Copyright (C) 2020-2024 Zarklord
*
* This file is part of SpaceStageTimelineFix.
*
* SpaceStageTimelineFix is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with SpaceStageTimelineFix.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "pch.h"
#include <variant>

enum TimelineEventGameLevel : uint32_t
{
	TimelineEventGameLevelInvalid = 0,
	TimelineEventGameLevelCell = id("CellGame"),
	TimelineEventGameLevelCreature = id("CreatureGame"),
	TimelineEventGameLevelTribe = id("TribeGame"),
	TimelineEventGameLevelCiv = id("CivGame"),
	TimelineEventGameLevelSpace = id("SpaceGame"),
};

constexpr uint32_t TimelineEventGameLevelProperty = 0x091AD064;

member_detour(timelineEventGameLevel_detour, std::monostate, uint32_t*(uint32_t* param_1, uint32_t instanceID, uint32_t num_stacks, uint32_t param_4))
{
	uint32_t* detoured(uint32_t* param_1, uint32_t instanceID, uint32_t num_stacks, uint32_t param_4)
	{
		if (instanceID == id("_crg_befriendedsomething"))
			instanceID = id("crg_befriendedsomething");
		
		static TimelineEventGameLevel last_event_level = TimelineEventGameLevelInvalid;
		if (!Simulator::IsSpaceGame())
		{
			last_event_level = TimelineEventGameLevelInvalid;
			return original_function(this, param_1, instanceID, num_stacks, param_4);
		}

		PropertyListPtr prop_list;
		PropManager.GetPropertyList(instanceID, id("TimelineEvents"), prop_list);
		uint32_t timeline_event_game_level = TimelineEventGameLevelInvalid;
		App::Property::GetKeyInstanceID(prop_list.get(), TimelineEventGameLevelProperty, timeline_event_game_level);
		if (instanceID == id("crg_befriendedsomething"))
		{
			if (last_event_level == TimelineEventGameLevelInvalid || last_event_level == TimelineEventGameLevelCell || last_event_level == TimelineEventGameLevelSpace)
			{
				instanceID = id("spg_befriendedsomething");
				timeline_event_game_level = TimelineEventGameLevelSpace;
			}
		}
		last_event_level = static_cast<TimelineEventGameLevel>(timeline_event_game_level);

		return original_function(this, param_1, instanceID, num_stacks, param_4);
	}
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		PrepareDetours(hModule);
		timelineEventGameLevel_detour::attach(Address(ModAPI::ChooseAddress(0x0, 0xE48EB0)));
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

