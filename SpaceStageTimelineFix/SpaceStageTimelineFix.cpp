/****************************************************************************
* Copyright (C) 2020 Zarklord
*
* This file is part of CellStagePartsAPI.
*
* CellStagePartsAPI is free software: you can redistribute it and/or modify
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
* along with CellStagePartsAPI.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "stdafx.h"
#include "SpaceStageTimelineFix.h"

namespace SpaceStageTimelineFix {
	long AttachDetours() {
		long result = 0;
		result |= sub_E396C0__detour::attach(Address(ModAPI::ChooseAddress(0x0, 0xE396C0)));

		return result;
	}
};

using namespace SpaceStageTimelineFix;

uint32_t SpaceStageTimelineFix::sub_E396C0__detour::DETOUR(uint32_t instanceID, uint32_t* a2, uint32_t* a3, uint32_t* a4, uint32_t* a5) {
	if (instanceID == id("crg_befriendedsomething") && Simulator::IsSpaceGame()) {
		instanceID = id("spg_befriendedsomething");
	}
	return original_function(instanceID, a2, a3, a4, a5);
}