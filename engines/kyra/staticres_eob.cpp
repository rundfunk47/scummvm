/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 */

#include "kyra/eob1.h"
#include "kyra/eob2.h"
#include "kyra/resource.h"


namespace Kyra {


#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
const uint16 *StaticResource::loadRawDataBe16(int id, int &entries) {
	return (const uint16 *)getData(id, kLolRawDataBe16, entries);
}

const uint32 *StaticResource::loadRawDataBe32(int id, int &entries) {
	return (const uint32 *)getData(id, kLolRawDataBe32, entries);
}
#endif // defined(ENABLE_EOB) || defined(ENABLE_LOL)

#ifdef ENABLE_EOB
const EobSequenceStep *StaticResource::loadEob2SeqData(int id, int &entries) {
	return (const EobSequenceStep *)getData(id, kEob2SequenceData, entries);
}

const EobShapeDef *StaticResource::loadEob2ShapeData(int id, int &entries) {
	return (const EobShapeDef *)getData(id, kEob2ShapeData, entries);
}

const EobCharacter *StaticResource::loadEobNpcData(int id, int &entries) {
	return (const EobCharacter *)getData(id, kEobNpcData, entries);
}
#endif // ENABLE_EOB

#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
bool StaticResource::loadRawDataBe16(Common::SeekableReadStream &stream, void *&ptr, int &size) {
	size = stream.size() >> 1;

	uint16 *r = new uint16[size];

	for (int i = 0; i < size; i++)
		r[i] = stream.readUint16BE();

	ptr = r;
	return true;
}

bool StaticResource::loadRawDataBe32(Common::SeekableReadStream &stream, void *&ptr, int &size) {
	size = stream.size() >> 2;

	uint32 *r = new uint32[size];

	for (int i = 0; i < size; i++)
		r[i] = stream.readUint32BE();

	ptr = r;
	return true;
}
#endif // defined(ENABLE_EOB) || defined(ENABLE_LOL)

#ifdef ENABLE_EOB
bool StaticResource::loadEob2SeqData(Common::SeekableReadStream &stream, void *&ptr, int &size) {
	size = stream.size() / 11;

	EobSequenceStep *s = new EobSequenceStep[size];

	for (int i = 0; i < size; i++) {
		s[i].command = stream.readByte();
		s[i].obj = stream.readByte();
		s[i].x1 = stream.readSint16BE();
		s[i].y1 = stream.readByte();
		s[i].delay = stream.readByte();
		s[i].pal = stream.readByte();
		s[i].x2 = stream.readByte();
		s[i].y2 = stream.readByte();
		s[i].w = stream.readByte();
		s[i].h = stream.readByte();
	}

	ptr = s;
	return true;
}

bool StaticResource::loadEob2ShapeData(Common::SeekableReadStream &stream, void *&ptr, int &size) {
	size = stream.size() / 6;

	EobShapeDef *s = new EobShapeDef[size];

	for (int i = 0; i < size; i++) {
		s[i].index = stream.readSint16BE();
		s[i].x = stream.readByte();
		s[i].y = stream.readByte();
		s[i].w = stream.readByte();
		s[i].h = stream.readByte();
	}

	ptr = s;
	return true;
}

bool StaticResource::loadEobNpcData(Common::SeekableReadStream &stream, void *&ptr, int &size) {
	size = stream.readUint16BE();

	EobCharacter *e = new EobCharacter[size];
	memset(e, 0, size * sizeof(EobCharacter));
	EobCharacter *s = e;

	for (int i = 0; i < size; i++, s++) {
		s->id = stream.readByte();
		s->flags = stream.readByte();
		stream.read(s->name, 11);
		s->strengthCur = stream.readSByte();
		s->strengthMax = stream.readSByte();
		s->strengthExtCur = stream.readSByte();
		s->strengthExtMax = stream.readSByte();
		s->intelligenceCur = stream.readSByte();
		s->intelligenceMax = stream.readSByte();
		s->wisdomCur = stream.readSByte();
		s->wisdomMax = stream.readSByte();
		s->dexterityCur = stream.readSByte();
		s->dexterityMax = stream.readSByte();
		s->constitutionCur = stream.readSByte();
		s->constitutionMax = stream.readSByte();
		s->charismaCur = stream.readSByte();
		s->charismaMax = stream.readSByte();
		s->hitPointsCur = stream.readSint16BE();
		s->hitPointsMax = stream.readSint16BE();
		s->armorClass = stream.readSByte();
		s->disabledSlots = stream.readByte();
		s->raceSex = stream.readByte();
		s->cClass = stream.readByte();
		s->alignment = stream.readByte();
		s->portrait = stream.readByte();
		s->food = stream.readByte();
		stream.read(s->level, 3);
		s->experience[0] = stream.readUint32BE();
		s->experience[1] = stream.readUint32BE();
		s->experience[2] = stream.readUint32BE();
		s->mageSpellsAvailabilityFlags = stream.readUint32BE();
		for (int ii = 0; ii < 27; ii++)
			s->inventory[i] = stream.readUint16BE();
	}

	ptr = e;
	return true;
}
#endif // ENABLE_EOB

#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
void StaticResource::freeRawDataBe16(void *&ptr, int &size) {
	uint16 *data = (uint16 *)ptr;
	delete[] data;
	ptr = 0;
	size = 0;
}

void StaticResource::freeRawDataBe32(void *&ptr, int &size) {
	uint32 *data = (uint32 *)ptr;
	delete[] data;
	ptr = 0;
	size = 0;
}
#endif // defined(ENABLE_EOB) || defined(ENABLE_LOL)

#ifdef ENABLE_EOB
void StaticResource::freeEob2SeqData(void *&ptr, int &size) {
	EobSequenceStep *d = (EobSequenceStep *)ptr;
	delete[] d;
	ptr = 0;
	size = 0;
}

void StaticResource::freeEob2ShapeData(void *&ptr, int &size) {
	EobShapeDef *d = (EobShapeDef *)ptr;
	delete[] d;
	ptr = 0;
	size = 0;
}

void StaticResource::freeEobNpcData(void *&ptr, int &size) {
	EobCharacter *d = (EobCharacter *)ptr;
	delete[] d;
	ptr = 0;
	size = 0;
}

const ScreenDim Screen_Eob::_screenDimTable[] = {
	{ 0x00, 0x00, 0x28, 0xC8, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x08, 0x48, 0x18, 0x38, 0x0E, 0x0C, 0x00, 0x00 },
	{ 0x13, 0x40, 0x14, 0x80, 0x06, 0x0C, 0x00, 0x00 },
	{ 0x1D, 0x78, 0x08, 0x40, 0x0F, 0x0D, 0x00, 0x00 },
	{ 0x02, 0x18, 0x14, 0x78, 0x0F, 0x02, 0x03, 0x00 },
	{ 0x00, 0x00, 0x16, 0x78, 0x0F, 0x0D, 0x00, 0x00 },
	{ 0x0A, 0x6C, 0x15, 0x28, 0x0F, 0x00, 0x00, 0x00 },
	{ 0x01, 0xB4, 0x22, 0x12, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x02, 0x18, 0x14, 0x00, 0x0F, 0x02, 0x03, 0x00 },
	{ 0x01, 0x7D, 0x26, 0x40, 0x0F, 0x00, 0x03, 0x00 },
	{ 0x00, 0x00, 0x16, 0x90, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x01, 0x14, 0x14, 0x38, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x01, 0x04, 0x14, 0x9C, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x01, 0x19, 0x26, 0x64, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x01, 0x14, 0x14, 0x58, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x02, 0x06, 0x23, 0x78, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x09, 0x14, 0x16, 0x38, 0x0F, 0x02, 0x00, 0x00 },
	{ 0x01, 0x96, 0x26, 0x31, 0x0F, 0x00, 0x00, 0x00 },
	{ 0x01, 0x08, 0x26, 0x80, 0x0C, 0x0F, 0x00, 0x00 },
	{ 0x01, 0x10, 0x26, 0x14, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x10, 0x10, 0x0C, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x10, 0x17, 0x00, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x10, 0x10, 0x00, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x10, 0x07, 0x04, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x00, 0x11, 0x05, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x00, 0x15, 0x05, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x00, 0x11, 0x08, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x00, 0x00, 0x15, 0x03, 0x00, 0x0F, 0x06, 0x00 },
	{ 0x0A, 0xA8, 0x15, 0x18, 0x0F, 0x0C, 0x00, 0x00 }
};

const int Screen_Eob::_screenDimTableCount = ARRAYSIZE(Screen_Eob::_screenDimTable);
#endif

#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
const uint8 LolEobBaseEngine::_dropItemDirIndex[] = { 0, 1, 2, 3, 1, 3, 0, 2, 3, 2, 1, 0, 2, 0, 3, 1 };

void LolEobBaseEngine::initStaticResource() {
	int temp;
	_dscShapeX = (const int16 *)_staticres->loadRawDataBe16(kLolEobCommonDscX, temp);
	_dscShapeIndex = (const int8 *)_staticres->loadRawData(kLolEobCommonDscShapeIndex, temp);
	_dscTileIndex = _staticres->loadRawData(kLolEobCommonDscTileIndex, temp);
	_dscDim1 = (const int8 *)_staticres->loadRawData(kLolEobCommonDscDimData1, temp);
	_dscDim2 = (const int8 *)_staticres->loadRawData(kLolEobCommonDscDimData2, temp);
	_dscUnk2 = _staticres->loadRawData(kLolEobCommonDscUnk2, temp);
	_dscBlockMap = _staticres->loadRawData(kLolEobCommonDscBlockMap, temp);
	_dscBlockIndex = (const int8 *)_staticres->loadRawData(kLolEobCommonDscBlockIndex, temp);
	_dscDimMap = _staticres->loadRawData(kLolEobCommonDscDimMap, temp);
	_dscDoorShpIndex = _staticres->loadRawData(kLolEobCommonDscDoorShapeIndex, temp);
	_dscDoorY2 = _staticres->loadRawData(kLolEobCommonDscDoorY2, temp);
	_moreStrings = _staticres->loadStrings(kLolEobCommonMoreStrings, temp);
}

#endif // (ENABLE_EOB || ENABLE_LOL)
#ifdef ENABLE_EOB

const uint8 EobCoreEngine::_hpIncrPerLevel[] = { 10, 4, 8, 6, 10, 10, 9, 10, 9, 10, 9, 9, 3, 1, 2, 2, 3, 3 };

const uint8 EobCoreEngine::_numLevelsPerClass[] = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 2, 3, 2, 2 };

const int8 EobCoreEngine::_classHpIncreaseType[] = {
	0, -1, -1, 5, -1, -1, 4, -1, -1, 1, -1, -1, 2, -1, -1, 3, -1, -1,  0,
	2, -1, 0, 3, -1, 0, 1, -1, 0, 1, 3, 3, 1, -1, 2, 3, -1, 0, 2,  1,  5,
	2, -1, 2, 1, -1
};

const int16 EobCoreEngine::_hpConstModifiers[] = { -1, -3, -2, -2, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 7 };

const uint8 EobCoreEngine::_charClassModUnk[] = {
	0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
	0x00, 0x00, 0x02
};

const uint8 EobCoreEngine::_teleporterShapeDefs[] = {
	0x0C, 0x58, 0x02, 0x0E,
	0x0C, 0x67, 0x01, 0x07,
	0x0C, 0x6F, 0x01, 0x07,
	0x0C, 0x77, 0x01, 0x05,
	0x0C, 0x7D, 0x01, 0x05,
	0x0C, 0x83, 0x01, 0x03
};

const uint8 EobCoreEngine::_wallOfForceShapeDefs[] = {
	0x00, 0x00, 0x04, 0x08,
	0x00, 0x08,	0x04, 0x08,
	0x04, 0x00, 0x04, 0x08,
	0x04, 0x08, 0x04, 0x08,
	0x08, 0x00, 0x05, 0x10,
	0x0C, 0x00,	0x05, 0x10
};

const int16 EobCoreEngine::_buttonList1[] = {
	58, 0, 1, 2, 3, 90, 91, 4, 5, 6, 7, 8, 9, 10, 11, 12, 78, 79, 13, 14,  15,  16,
	80, 81, 17, 18, 19, 20, 82, 83, 49, 50, 51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList2[] = {
	58, 61, 62, 63,	64, 65, 93, 94, 66, 67, 68, 69, 70, 71, 76, 77, 88, 0, 1, 2, 3,
	90, 91,  4,  5,	6, 7, 8, 9, 10, 11, 12, 78, 79, 13, 14, 15, 16, 80, 81, 17, 18,
	19, 20, 82, 83,	49, 50, 51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList3[] = {
	58, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 84, 85, 46, 47, 48, 60,	59, 92, 4, 5, 6, 7, 8, 49,  50,
	51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList4[] = {
	58, 47, 48, 60, 59, 92, 4, 5, 6, 7, 8, 49, 50, 51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList5[] = {
	58, 61, 62, 63, 64, 65, 93, 66,	67, 68, 69, 70, 71, 88, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,	35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 84,
	85, 46, 47, 48, 60, 59, 92, 4, 5, 6, 7, 8, 49, 50, 51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList6[] = {
	58, 61, 62, 63, 64, 65, 93, 66, 67, 68, 69, 70, 71, 88, 46, 47, 48, 60, 59, 92,
	4, 5, 6, 7, 8, 49, 50, 51, 52, 53, 54, 56, 57, -1
};

const int16 EobCoreEngine::_buttonList7[] = {
	17, 18, 19, 20, 82, 83, 55, -1
};

const int16 EobCoreEngine::_buttonList8[] = {
	72, 73, 74, 75, 86, 87, 89, -1
};

const uint8 EobCoreEngine::_clock2Timers[] = {
	0x00, 0x01, 0x20, 0x21, 0x22, 0x22,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
	0x04, 0x05, 0x06, 0x07
};

const uint8 EobCoreEngine::_numClock2Timers = ARRAYSIZE(EobCoreEngine::_clock2Timers);

void EobCoreEngine::initStaticResource() {
	int temp;
	_chargenStatStrings = _staticres->loadStrings(kEobBaseChargenStatStrings, temp);
	_chargenRaceSexStrings = _staticres->loadStrings(kEobBaseChargenRaceSexStrings, temp);
	_chargenClassStrings = _staticres->loadStrings(kEobBaseChargenClassStrings, temp);
	_chargenAlignmentStrings = _staticres->loadStrings(kEobBaseChargenAlignmentStrings, temp);

	_pryDoorStrings = _staticres->loadStrings(kEobBasePryDoorStrings, temp);
	_warningStrings = _staticres->loadStrings(kEobBaseWarningStrings, temp);
	_itemSuffixStrings = _staticres->loadStrings(kEobBaseItemSuffixStrings, temp);
	_itemExtraStrings = _staticres->loadStrings(kEobBaseItemExtraStrings, temp);
	_takenStrings = _staticres->loadStrings(kEobBaseTakenStrings, temp);
	_potionEffectStrings = _staticres->loadStrings(kEobBasePotionEffectStrings, temp);

	_yesNoStrings = _staticres->loadStrings(kEobBaseYesNoStrings, temp);
	_npcMaxStrings = _staticres->loadStrings(kEobBaseNpcMaxStrings, temp);
	_okStrings = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseOkStrings : kLolEobCommonMoreStrings, temp);
	_npcJoinStrings = _staticres->loadStrings(kEobBaseNpcJoinStrings, temp);
	_cancelStrings = _staticres->loadStrings(kEobBaseCancelStrings, temp);
	_abortStrings = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseAbortStrings : kEobBaseCancelStrings, temp);

	_menuStringsMain = _staticres->loadStrings(kEobBaseMenuStringsMain, temp);
	_menuStringsSaveLoad = _staticres->loadStrings(kEobBaseMenuStringsSaveLoad, temp);
	_menuStringsOnOff = _staticres->loadStrings(kEobBaseMenuStringsOnOff, temp);
	_menuStringsSpells = _staticres->loadStrings(kEobBaseMenuStringsSpells, temp);
	_menuStringsRest = _staticres->loadStrings(kEobBaseMenuStringsRest, temp);
	_menuStringsDrop = _staticres->loadStrings(kEobBaseMenuStringsDrop, temp);
	_menuStringsExit = _staticres->loadStrings(kEobBaseMenuStringsExit, temp);
	_menuStringsStarve = _staticres->loadStrings(kEobBaseMenuStringsStarve, temp);
	_menuStringsScribe = _staticres->loadStrings(kEobBaseMenuStringsScribe, temp);
	_menuStringsDrop2 = _staticres->loadStrings(kEobBaseMenuStringsDrop2, temp);
	_menuStringsHead = _staticres->loadStrings(kEobBaseMenuStringsHead, temp);
	_menuStringsPoison = _staticres->loadStrings(kEobBaseMenuStringsPoison, temp);
	_menuStringsMgc = _staticres->loadStrings(kEobBaseMenuStringsMgc, temp);
	_menuStringsPrefs = _staticres->loadStrings(kEobBaseMenuStringsPrefs, temp);
	_menuStringsRest2 = _staticres->loadStrings(kEobBaseMenuStringsRest2, temp);
	_menuStringsDefeat = _staticres->loadStrings(kEobBaseMenuStringsDefeat, temp);
	_menuStringsTransfer = _staticres->loadStrings(kEobBaseMenuStringsTransfer, temp);
	_menuStringsSpec = _staticres->loadStrings(kEobBaseMenuStringsSpec, temp);
	_menuStringsSpellNo = _staticres->loadStrings(kEobBaseMenuStringsSpellNo, temp);

	_characterGuiStringsHp = _staticres->loadStrings(kEobBaseCharGuiStringsHp, temp);
	_characterGuiStringsWp = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseCharGuiStringsWp2 : kEobBaseCharGuiStringsWp1, temp);
	_characterGuiStringsWr = _staticres->loadStrings(kEobBaseCharGuiStringsWr, temp);
	_characterGuiStringsSt = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseCharGuiStringsSt2 : kEobBaseCharGuiStringsSt1, temp);
	_characterGuiStringsIn = _staticres->loadStrings(kEobBaseCharGuiStringsIn, temp);

	_characterStatusStrings7 = _staticres->loadStrings(kEobBaseCharStatusStrings7, temp);
	_characterStatusStrings8 = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseCharStatusStrings82 : kEobBaseCharStatusStrings81, temp);
	_characterStatusStrings9 = _staticres->loadStrings(kEobBaseCharStatusStrings9, temp);
	_characterStatusStrings12 = _staticres->loadStrings(kEobBaseCharStatusStrings12, temp);
	_characterStatusStrings13 = _staticres->loadStrings(_flags.gameID == GI_EOB2 ? kEobBaseCharStatusStrings132 : kEobBaseCharStatusStrings131, temp);

	_levelGainStrings = _staticres->loadStrings(kEobBaseLevelGainStrings, temp);
	_expRequirementTables[0] = _staticres->loadRawDataBe32(kEobBaseExperienceTable0, temp);
	_expRequirementTables[1] = _staticres->loadRawDataBe32(kEobBaseExperienceTable1, temp);
	_expRequirementTables[2] = _staticres->loadRawDataBe32(kEobBaseExperienceTable2, temp);
	_expRequirementTables[3] = _staticres->loadRawDataBe32(kEobBaseExperienceTable3, temp);
	_expRequirementTables[4] = _staticres->loadRawDataBe32(kEobBaseExperienceTable4, temp);
	_expRequirementTables[5] = _staticres->loadRawDataBe32(kEobBaseExperienceTable4, temp);

	_classModifierFlags = _staticres->loadRawData(kEobBaseClassModifierFlags, temp);

	_constModTables[0] = _constModTables[4] = _constModTables[5] = _staticres->loadRawData(kEobBaseConstModTable1, temp);
	_constModTables[1] = _staticres->loadRawData(kEobBaseConstModTable2, temp);
	_constModTables[2] = _staticres->loadRawData(kEobBaseConstModTable3, temp);
	_constModTables[3] = _staticres->loadRawData(kEobBaseConstModTable4, temp);
	_constModLevelIndex = _staticres->loadRawData(kEobBaseConstModLvlIndex, temp);
	_constModDiv = _staticres->loadRawData(kEobBaseConstModDiv, temp);
	_constModExt = _staticres->loadRawData(kEobBaseConstModExt, temp);

	_encodeMonsterShpTable = _staticres->loadRawDataBe16(kEobBaseEncodeMonsterDefs, temp);
	_npcPreset = _staticres->loadEobNpcData(kEobBaseNpcPresets, temp);

	_teleporterShapeCoords = _staticres->loadRawData(kEobBaseDscTelptrShpCoords, temp);

	_monsterStepTable0 = (int8*) _staticres->loadRawData(_flags.gameID == GI_EOB2 ? kEobBaseMonsterStepTable02 : kEobBaseMonsterStepTable01, temp);
	_monsterStepTable1 = (int8*)_staticres->loadRawData(kEobBaseMonsterStepTable1, temp);
	_monsterStepTable2 = (int8*)_staticres->loadRawData(kEobBaseMonsterStepTable2, temp);
	_monsterStepTable3 = (int8*)_staticres->loadRawData(kEobBaseMonsterStepTable3, temp);
	_monsterCloseAttPosTable1 = _staticres->loadRawData(kEobBaseMonsterCloseAttPosTable1, temp);
	_monsterCloseAttPosTable2 = _staticres->loadRawData(_flags.gameID == GI_EOB2 ? kEobBaseMonsterCloseAttPosTable22 : kEobBaseMonsterCloseAttPosTable21, temp);
	_monsterCloseAttUnkTable = (int8*)_staticres->loadRawData(kEobBaseMonsterCloseAttUnkTable, temp);
	_monsterCloseAttChkTable1 = _staticres->loadRawData(kEobBaseMonsterCloseAttChkTable1, temp);
	_monsterCloseAttChkTable2 = _staticres->loadRawData(kEobBaseMonsterCloseAttChkTable2, temp);
	_monsterCloseAttDstTable1 = _staticres->loadRawData(kEobBaseMonsterCloseAttDstTable1, temp);
	_monsterCloseAttDstTable2 = _staticres->loadRawData(kEobBaseMonsterCloseAttDstTable2, temp);

	_monsterProximityTable = _staticres->loadRawData(kEobBaseMonsterProximityTable, temp);
	_findBlockMonstersTable = _staticres->loadRawData(kEobBaseFindBlockMonstersTable, temp);
	_monsterDirChangeTable = (const int8*)_staticres->loadRawData(kEobBaseMonsterDirChangeTable, temp);
	_monsterSpecAttStrings = _staticres->loadStrings(kEobBaseMonsterDistAttStrings, temp);

	_monsterFrmOffsTable1 = (const int8*)_staticres->loadRawData(kEobBaseDscMonsterFrmOffsTbl1, temp);
	_monsterFrmOffsTable2 = (const int8*)_staticres->loadRawData(kEobBaseDscMonsterFrmOffsTbl2, temp);

	_inventorySlotsX = _staticres->loadRawDataBe16(kEobBaseInvSlotX, temp);
	_inventorySlotsY = _staticres->loadRawData(kEobBaseInvSlotY, temp);
	_slotValidationFlags = _staticres->loadRawDataBe16(kEobBaseSlotValidationFlags, temp);

	_drawObjPosIndex = _staticres->loadRawData(kEobBaseDrawObjPosIndex, temp);
	_flightObjFlipIndex = _staticres->loadRawData(kEobBaseFlightObjFlipIndex, temp);
	_flightObjShpMap = (const int8*)_staticres->loadRawData(kEobBaseFlightObjShpMap, temp);
	_flightObjSclIndex = (const int8*)_staticres->loadRawData(kEobBaseFlightObjSclIndex, temp);

	_wllFlagPreset = _staticres->loadRawData(kEobBaseWllFlagPreset, _wllFlagPresetSize);
	_dscShapeCoords = (const int16*)_staticres->loadRawDataBe16(kEobBaseDscShapeCoords, temp);

	_dscDoorScaleOffs = _staticres->loadRawData(kEobBaseDscDoorScaleOffs, temp);
	_dscDoorScaleMult1 = _staticres->loadRawData(kEobBaseDscDoorScaleMult1, temp);
	_dscDoorScaleMult2 = _staticres->loadRawData(kEobBaseDscDoorScaleMult2, temp);
	_dscDoorScaleMult3 = _staticres->loadRawData(kEobBaseDscDoorScaleMult3, temp);
	_dscDoorY1 = _staticres->loadRawData(kEobBaseDscDoorY1, temp);

	_dscItemPosIndex= _staticres->loadRawData(kEobBaseDscItemPosIndex, temp);
	_dscItemShpX = (const int16*)_staticres->loadRawDataBe16(kEobBaseDscItemShpX, temp);
	_dscItemScaleIndex = _staticres->loadRawData(kEobBaseDscItemScaleIndex, temp);
	_dscItemTileIndex = _staticres->loadRawData(kEobBaseDscItemTileIndex, temp);
	_dscItemShapeMap = _staticres->loadRawData(kEobBaseDscItemShapeMap, temp);

	_bookNumbers = _staticres->loadStrings(kEobBaseBookNumbers, temp);
	_mageSpellList = _staticres->loadStrings(kEobBaseMageSpellsList, _mageSpellListSize);
	_clericSpellList = _staticres->loadStrings(kEobBaseClericSpellsList, temp);
	_spellNames = _staticres->loadStrings(kEobBaseSpellNames, temp);

	_magicStrings1 = _staticres->loadStrings(kEobBaseMagicStrings1, temp);
	_magicStrings2 = _staticres->loadStrings(kEobBaseMagicStrings2, temp);
	_magicStrings3 = _staticres->loadStrings(kEobBaseMagicStrings3, temp);
	_magicStrings4 = _staticres->loadStrings(kEobBaseMagicStrings4, temp);
	_magicStrings6 = _staticres->loadStrings(kEobBaseMagicStrings6, temp);
	_magicStrings7 = _staticres->loadStrings(kEobBaseMagicStrings7, temp);
	_magicStrings8 = _staticres->loadStrings(kEobBaseMagicStrings8, temp);

	_expObjectTlMode = _staticres->loadRawData(kEobBaseExpObjectTlMode, temp);
	_expObjectTblIndex = _staticres->loadRawData(kEobBaseExpObjectTblIndex, temp);
	_expObjectShpStart = _staticres->loadRawData(kEobBaseExpObjectShpStart, temp);
	_expObjectAnimTbl1 = _staticres->loadRawData(kEobBaseExpObjectTbl1, _expObjectAnimTbl1Size);
	_expObjectAnimTbl2 = _staticres->loadRawData(kEobBaseExpObjectTbl2, _expObjectAnimTbl2Size);
	_expObjectAnimTbl3 = _staticres->loadRawData(kEobBaseExpObjectTbl3, _expObjectAnimTbl3Size);

	_sparkEffectDefSteps = _staticres->loadRawData(kEobBaseSparkDefSteps, temp);
	_sparkEffectDefSubSteps = _staticres->loadRawData(kEobBaseSparkDefSubSteps, temp);
	_sparkEffectDefShift = _staticres->loadRawData(kEobBaseSparkDefShift, temp);
	_sparkEffectDefAdd = _staticres->loadRawData(kEobBaseSparkDefAdd, temp);
	_sparkEffectDefX = _staticres->loadRawData(kEobBaseSparkDefX, temp);
	_sparkEffectDefY = _staticres->loadRawData(kEobBaseSparkDefY, temp);
	_sparkEffectOfFlags1 = _staticres->loadRawDataBe32(kEobBaseSparkOfFlags1, temp);
	_sparkEffectOfFlags2 = _staticres->loadRawDataBe32(kEobBaseSparkOfFlags2, temp);
	_sparkEffectOfShift = _staticres->loadRawData(kEobBaseSparkOfShift, temp);
	_sparkEffectOfX = _staticres->loadRawData(kEobBaseSparkOfX, temp);
	_sparkEffectOfY = _staticres->loadRawData(kEobBaseSparkOfY, temp);
	_magicFlightObjectProperties = _staticres->loadRawData(kEobBaseMagicFlightProps, temp);
}

void EobCoreEngine::initButtonData() {
	#define EOB_CB(x)	BUTTON_FUNCTOR(EobCoreEngine, this, &EobCoreEngine::x)
	static const EobGuiButtonDef buttonDefs[] = {
		{ 112, 0, 0x1100, 184, 2, 63, 50, EOB_CB(clickedCharPortraitDefault), 0 },
		{ 113, 0, 0x1100, 256, 2, 63, 50, EOB_CB(clickedCharPortraitDefault), 1 },
		{ 114, 0, 0x1100, 184, 54, 63, 50, EOB_CB(clickedCharPortraitDefault), 2 },
		{ 115, 0, 0x1100, 256, 54, 63, 50, EOB_CB(clickedCharPortraitDefault), 3 },
		{ 48, 110, 0x1100, 289, 177, 31, 21, EOB_CB(clickedCamp), 0 },
		{ 0, 0, 0x1100, 0, 102, 88, 18, EOB_CB(clickedSceneDropPickupItem), 0 },
		{ 0, 0, 0x1100, 89, 102, 88, 18, EOB_CB(clickedSceneDropPickupItem), 1 },
		{ 0, 0, 0x1100, 0, 72, 88, 29, EOB_CB(clickedSceneDropPickupItem), 2 },
		{ 0, 0, 0x1100, 89, 72, 88, 29, EOB_CB(clickedSceneDropPickupItem), 3 },
		{ 24, 0, 0x1100, 184, 10, 33, 33, EOB_CB(clickedCharPortrait2), 0 },
		{ 0, 0, 0x1100, 256, 10, 33, 33, EOB_CB(clickedCharPortrait2), 1 },
		{ 0, 0, 0x1100, 184, 62, 33, 33, EOB_CB(clickedCharPortrait2), 2 },
		{ 0, 0, 0x1100, 256, 62, 33, 33, EOB_CB(clickedCharPortrait2), 3 },
		{ 0, 0, 0x1100, 216, 10, 31, 33, EOB_CB(clickedWeaponSlot), 0 },
		{ 0, 0, 0x1100, 288, 10, 31, 33, EOB_CB(clickedWeaponSlot), 1 },
		{ 0, 0, 0x1100, 216, 62, 31, 33, EOB_CB(clickedWeaponSlot), 2 },
		{ 0, 0, 0x1100, 288, 62, 31, 33, EOB_CB(clickedWeaponSlot), 3 },
		{ 368, 0, 0x1000, 184, 2, 63, 8, EOB_CB(clickedCharNameLabelRight), 0 },
		{ 369, 0, 0x1000, 256, 2, 63, 8, EOB_CB(clickedCharNameLabelRight), 1 },
		{ 370, 0, 0x1000, 184, 54, 63, 8, EOB_CB(clickedCharNameLabelRight), 2 },
		{ 371, 0, 0x1000, 256, 54, 63, 8, EOB_CB(clickedCharNameLabelRight), 3 },
		{ 0, 0, 0x1100, 230, 116, 16, 16, EOB_CB(clickedInventorySlot), 0 },
		{ 0, 0, 0x1100, 278, 116, 16, 16, EOB_CB(clickedInventorySlot), 1 },
		{ 0, 0, 0x1100, 181, 40, 16, 16, EOB_CB(clickedInventorySlot), 2 },
		{ 0, 0, 0x1100, 199, 40, 16, 16, EOB_CB(clickedInventorySlot), 3 },
		{ 0, 0, 0x1100, 181, 58, 16, 16, EOB_CB(clickedInventorySlot), 4 },
		{ 0, 0, 0x1100, 199, 58, 16, 16, EOB_CB(clickedInventorySlot), 5 },
		{ 0, 0, 0x1100, 181, 76, 16, 16, EOB_CB(clickedInventorySlot), 6 },
		{ 0, 0, 0x1100, 199, 76, 16, 16, EOB_CB(clickedInventorySlot), 7 },
		{ 0, 0, 0x1100, 181, 94, 16, 16, EOB_CB(clickedInventorySlot), 8 },
		{ 0, 0, 0x1100, 199, 94, 16, 16, EOB_CB(clickedInventorySlot), 9 },
		{ 0, 0, 0x1100, 181, 112, 16, 16, EOB_CB(clickedInventorySlot), 10 },
		{ 0, 0, 0x1100, 199, 112, 16, 16, EOB_CB(clickedInventorySlot), 11 },
		{ 0, 0, 0x1100, 181, 130, 16, 16, EOB_CB(clickedInventorySlot), 12 },
		{ 0, 0, 0x1100, 199, 130, 16, 16, EOB_CB(clickedInventorySlot), 13 },
		{ 0, 0, 0x1100, 181, 148, 16, 16, EOB_CB(clickedInventorySlot), 14 },
		{ 0, 0, 0x1100, 199, 148, 16, 16, EOB_CB(clickedInventorySlot), 15 },
		{ 0, 0, 0x1100, 225, 55, 16, 16, EOB_CB(clickedInventorySlot), 16 },
		{ 0, 0, 0x1100, 224, 76, 16, 16, EOB_CB(clickedInventorySlot), 17 },
		{ 0, 0, 0x1100, 225, 96, 16, 16, EOB_CB(clickedInventorySlot), 18 },
		{ 0, 0, 0x1100, 298, 55, 16, 16, EOB_CB(clickedInventorySlot), 19 },
		{ 0, 0, 0x1100, 287, 75, 16, 16, EOB_CB(clickedInventorySlot), 20 },
		{ 0, 0, 0x1100, 277, 137, 16, 16, EOB_CB(clickedInventorySlot), 21 },
		{ 0, 0, 0x1100, 300, 94, 16, 16, EOB_CB(clickedInventorySlot), 22 },
		{ 0, 0, 0x1100, 300, 112, 16, 16, EOB_CB(clickedInventorySlot), 23 },
		{ 0, 0, 0x1100, 300, 130, 16, 16, EOB_CB(clickedInventorySlot), 24 },
		{ 0, 0, 0x1100, 236, 37, 31, 16, EOB_CB(clickedEatItem), 25 },
		{ 26, 0, 0x1100, 291, 149, 25, 17, EOB_CB(clickedInventoryNextPage), 25 },
		{ 110, 24, 0x1100, 181, 3, 32, 32, EOB_CB(clickedPortraitRestore), 25 },
		{ 96, 352, 0x1100, 24, 128, 21, 16, EOB_CB(clickedUpArrow), 25 },
		{ 98, 97, 0x1100, 24, 144, 21, 16, EOB_CB(clickedDownArrow), 25 },
		{ 92, 348, 0x1100, 3, 144, 21, 16, EOB_CB(clickedLeftArrow), 25 },
		{ 102, 358, 0x1100, 45, 144, 21, 16, EOB_CB(clickedRightArrow), 25 },
		{ 91, 0, 0x1100, 3, 128, 21, 16, EOB_CB(clickedTurnLeftArrow), 25 },
		{ 101, 0, 0x1100, 45, 128, 21, 16, EOB_CB(clickedTurnRightArrow), 25 },
		{ 110, 0, 0x1100, 184, 0, 136, 120, EOB_CB(clickedAbortCharSwitch), 0 },
		{ 0, 0, 0x1100, 0, 8, 88, 48, EOB_CB(clickedSceneThrowItem), 0 },
		{ 0, 0, 0x1100, 88, 8, 88, 48, EOB_CB(clickedSceneThrowItem), 1 },
		{ 0, 0, 0x1100, 24, 8, 128, 96, EOB_CB(clickedSceneSpecial), 1 },
		{ 112, 113, 0x1100, 274, 35, 20, 15, EOB_CB(clickedInventoryPrevChar), 1 },
		{ 114, 115, 0x1100, 297, 35, 20, 15, EOB_CB(clickedInventoryNextChar), 1 },
		{ 2, 0, 0x1100, 68, 121, 18, 10, EOB_CB(clickedSpellbookTab), 0 },
		{ 3, 0, 0x1100, 86, 121, 18, 10, EOB_CB(clickedSpellbookTab), 1 },
		{ 4, 0, 0x1100, 104, 121, 15, 10, EOB_CB(clickedSpellbookTab), 2 },
		{ 5, 0, 0x1100, 122, 121, 15, 10, EOB_CB(clickedSpellbookTab), 3 },
		{ 6, 0, 0x1100, 140, 121, 15, 10, EOB_CB(clickedSpellbookTab), 4 },
		{ 0, 0, 0x1100, 75, 131, 97, 6, EOB_CB(clickedSpellbookList), 0 },
		{ 0, 0, 0x1100, 75, 137, 97, 6, EOB_CB(clickedSpellbookList), 1 },
		{ 0, 0, 0x1100, 75, 143, 97, 6, EOB_CB(clickedSpellbookList), 2 },
		{ 0, 0, 0x1100, 75, 149, 97, 6, EOB_CB(clickedSpellbookList), 3 },
		{ 0, 0, 0x1100, 75, 155, 97, 6, EOB_CB(clickedSpellbookList), 4 },
		{ 0, 0, 0x1100, 75, 161, 97, 6, EOB_CB(clickedSpellbookList), 5 },
		{ 112, 0, 0x1100, 184, 2, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 0 },
		{ 113, 0, 0x1100, 256, 2, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 1 },
		{ 114, 0, 0x1100, 184, 54, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 2 },
		{ 115, 0, 0x1100, 256, 54, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 3 },
		{ 53, 54, 0x1100, 320, 200, 0, 0, EOB_CB(clickedSpellbookList), 6 },
		{ 61, 0, 0x1100, 320, 200, 0, 0, EOB_CB(clickedSpellbookList), 7 },
		{ 0, 0, 0x1100, 184, 114, 33, 33, EOB_CB(clickedCharPortrait2), 4 },
		{ 0, 0, 0x1100, 256, 114, 33, 33, EOB_CB(clickedCharPortrait2), 5 },
		{ 0, 0, 0x1100, 216, 114, 31, 33, EOB_CB(clickedWeaponSlot), 4 },
		{ 0, 0, 0x1100, 288, 114, 31, 33, EOB_CB(clickedWeaponSlot), 5 },
		{ 372, 0, 0x1000, 184, 106, 63, 8, EOB_CB(clickedCharNameLabelRight), 4 },
		{ 373, 0, 0x1000, 256, 106, 63, 8, EOB_CB(clickedCharNameLabelRight), 5 },
		{ 0, 0, 0x1100, 227, 135, 10, 10, EOB_CB(clickedInventorySlot), 25 },
		{ 0, 0, 0x1100, 239, 135, 10, 10, EOB_CB(clickedInventorySlot), 26 },
		{ 116, 0, 0x1100, 184, 106, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 4 },
		{ 117, 0, 0x1100, 256, 106, 63, 50, EOB_CB(clickedCastSpellOnCharacter), 5 },
		{ 110, 0, 0x1100, 68, 168, 78, 10, EOB_CB(clickedSpellbookAbort), 0 },
		{ 110, 0, 0x1100, 68, 168, 78, 10, EOB_CB(clickedCastSpellOnCharacter), 65535 },
		{ 116, 0, 0x1100, 184, 106, 63, 50, EOB_CB(clickedCharPortraitDefault), 4 },
		{ 117, 0, 0x1100, 256, 106, 63, 50, EOB_CB(clickedCharPortraitDefault), 5 },
		{ 116, 117, 0x1100, 320, 200, 1, 1, EOB_CB(clickedInventoryNextChar), 2 },
		{ 7, 0, 0x1100, 158, 121, 15, 10, EOB_CB(clickedSpellbookTab), 5 },
		{ 0, 0, 0x1100, 146, 168, 32, 10, EOB_CB(clickedSpellbookScroll), 0 },

		// EOB1 spellbook modifications
		{ 2, 0, 0x1100, 71, 122, 20, 8, EOB_CB(clickedSpellbookTab), 0 },
		{ 3, 0, 0x1100, 92, 122, 20, 8, EOB_CB(clickedSpellbookTab), 1 },
		{ 4, 0, 0x1100, 113, 122, 20, 8, EOB_CB(clickedSpellbookTab), 2 },
		{ 5, 0, 0x1100, 134, 122, 20, 8, EOB_CB(clickedSpellbookTab), 3 },
		{ 6, 0, 0x1100, 155, 122, 20, 8, EOB_CB(clickedSpellbookTab), 4 },
		{ 110, 0, 0x1100, 75, 168, 97, 6, EOB_CB(clickedSpellbookAbort), 0 },
	};

	_buttonDefs = buttonDefs;
}

void EobCoreEngine::initSpells() {
#define mpn magicTimingParaAssign.push_back(0);
#define mp1n if (_flags.gameID == GI_EOB1) magicTimingParaAssign.push_back(0);
#define mp2n if (_flags.gameID == GI_EOB2) magicTimingParaAssign.push_back(0);
#define mp(x) magicTimingParaAssign.push_back(&magicTimingPara[x << 2]);
#define mp1(x) if (_flags.gameID == GI_EOB1) magicTimingParaAssign.push_back(&magicTimingPara[x << 2]);
#define mp2(x) if (_flags.gameID == GI_EOB2) magicTimingParaAssign.push_back(&magicTimingPara[x << 2]);

#define sc(x) startCallback.push_back(&EobCoreEngine::spellCallback_start_##x);
#define sc1(x) if (_flags.gameID == GI_EOB1) startCallback.push_back(&EobCoreEngine::spellCallback_start_##x);
#define sc2(x) if (_flags.gameID == GI_EOB2) startCallback.push_back(&EobCoreEngine::spellCallback_start_##x);
#define ec(x) endCallback.push_back(&EobCoreEngine::spellCallback_end_##x);
#define ec1(x) if (_flags.gameID == GI_EOB1) endCallback.push_back(&EobCoreEngine::spellCallback_end_##x);
#define ec2(x) if (_flags.gameID == GI_EOB2) endCallback.push_back(&EobCoreEngine::spellCallback_end_##x);

	static const uint16 magicTimingPara[] = {
		0, 546, 2, 1, // 0 detect magic
		0, 546, 5, 1, // 1 shield, detect invis, magical vestment
		0, 546, 1, 1, // 2 shocking grasp, vamp touch, true seeing, prayer
		3, 546, 1, 1, // 3 blur, haste
		5, 546, 1, 1, // 4 imp invisibility
		6, 546, 0, 1, // 5 bless
		0, 546, 3, 1, // 6 prot from evil
		1, 546, 1, 1, // 7 aid
		4, 546, 1, 1, // 8 flame blade
		0, 32760, 1, 1, // 9 slow poison
		1, 546, 0, 1, // 10 mystic defense
	};

	Common::Array<const uint16*> magicTimingParaAssign;
	mpn;
	mpn;
	mpn;
	mp(0);	// Detect Magic
	mpn;	// Magic Missile
	mp1n;						///
	mp(1);	// Shield
	mp(2);	// Shocking Grasp
	mp2(3);	// Blur				///
	mp2(1);	// Detect Invis		///
	mp2n;	// Imp Identify		///
	mpn;	// Invis
	mp1n;						///
	mpn;	// Melf
	mp1n;	// Stinking Cloud	///
	mpn;	// Dispel Magic
	mpn;	// Fireball
	mp1n;	// Flame Arrow		///
	mp(3);	// Haste
	mpn;	// Hold Person
	mpn;	// Invisibility
	mpn;	// Lightning Bolt
	mp(2);	// Vampiric Touch
	mpn;	// Fear
	mpn;	// Ice Storm
	mp1n;	// Stone Skin		/// --- para required?
	mp1n;	// Cloud Kill		///
	mp2(4);	// Improved Invisibility	///
	mp2n;	// remove Curse		///
	mpn;	// Cone of Cold
	mpn;	// Hold Monster
	mp2n;	// Wall of Force	///
	mp2n;	// Disintegrate		///
	mp2n;	// Flesh To Stone	///
	mp2n;	// Stone To Flesh	///
	mp2(2);	// True Seeing		///
	mp2n;	// Finger of Death	///
	mp2n;	// Power Word Stun	///
	mp2n;	// Bigby's Fist		///
	mp2n;	// empty			///
	mp(5);	// Bless
	mpn;						/// EOB1: cure, EOB2: cause
	mpn;						/// EOB1: cause, EOB2: cure
	mp(0);	// Detect Magic
	mp(6);	// Prot from Evil
	mp(7);	// Aid
	mp(8);	// Flame Blad
	mpn;	// Hold Person
	mp(9);	// Slow Poison
	mpn;	// Create Food
	mpn;	// Dispel Magic
	mp(1);	// Magical Vestment
	mp(2);	// Prayer
	mpn;	// Remove Paralysis
	mpn;						/// EOB1: cure, EOB2: cause
	mpn;						/// EOB1: cause, EOB2: cure
	mpn;	// Neutral Poison
	mp(6);	// Prot From Evil 10'
	mp1n;	// Prot From Lightning			/// --- para required?
	mpn;						/// EOB1: cure, EOB2: cause
	mpn;						/// EOB1: cause, EOB2: cure
	mpn;	// Flame Strike
	mpn;	// Raise Dead
	mp2n;	// Slay Living		///
	mp2(2);	// True Seeing		///
	mp2n;	// Harm				///
	mp2n;	// Heal				///
	mp2n;	// Resurrect		///
	mpn;	// Lay on Hands
	mp2n;	// Turn Undead		///
	mpn;	// UNK 1 passive
	mp2(10);// Mystic Defense	///
	mp2n;	// UNK 2 passive	///
	mpn;	// death spell passive
	mpn;	// disintegrate passive
	mp2n;	// cause critical passive
	mp2n;	// flesh to stone passive

	Common::Array<SpellStartCallback> startCallback;
	sc(empty);
	sc(armor);
	sc(burningHands);
	sc(detectMagic);
	sc(magicMissile);
	sc1(empty);
	sc(empty);
	sc(shockingGrasp);
	sc(empty);
	sc2(empty);
	sc2(improvedIdentify);
	sc(empty);
	sc(melfsAcidArrow);
	sc1(empty);		// Stinking Cloud
	sc(dispelMagic);
	sc(fireball);
	sc1(flameArrow);
	sc(empty);
	sc(holdPerson);
	sc(empty);
	sc(lightningBolt);
	sc(vampiricTouch);
	sc(fear);
	sc(iceStorm);
	sc(empty);	// EOB1: stone skin, EOB2: imp invisibility
	sc1(empty); // Cloudkill
	sc2(removeCurse);
	sc(coneOfCold);
	sc(holdMonster);
	sc2(wallOfForce);
	sc2(disintegrate);
	sc2(fleshToStone);
	sc2(stoneToFlesh);
	sc2(trueSeeing);
	sc2(slayLiving);
	sc2(powerWordStun);
	sc2(empty);
	sc2(empty);
	sc(empty);	// Bless
	sc2(causeLightWounds);
	sc(cureLightWounds);
	sc1(causeLightWounds);
	sc(detectMagic);
	sc(empty);
	sc(aid);
	sc(flameBlade);
	sc(holdPerson);
	sc(slowPoison);
	sc(createFood);
	sc(dispelMagic);
	sc(empty);
	sc(empty);
	sc(removeParalysis);
	sc2(causeSeriousWounds);
	sc(cureSeriousWounds);
	sc1(causeSeriousWounds);
	sc(neutralizePoison);
	sc(empty);
	sc1(empty);	// Prot from Lightning
	sc2(causeCriticalWounds);
	sc(cureCriticalWounds);
	sc1(causeCriticalWounds);
	sc(flameStrike);
	sc(raiseDead);
	sc2(slayLiving);
	sc2(trueSeeing);
	sc2(harm);
	sc2(heal);
	sc2(empty);
	sc(layOnHands);
	sc2(turnUndead);
	sc(empty);
	sc2(empty);
	sc2(empty);
	sc(empty);
	sc(empty);
	sc2(empty);
	sc2(empty);

	Common::Array<SpellEndCallback> endCallback;
	ec(empty);
	ec(empty);
	ec(empty);
	ec(detectMagic);
	ec(magicMissile);
	ec1(empty);
	ec(empty);
	ec(shockingGraspFlameBlade);
	ec(empty);
	ec(empty);
	ec2(empty);
	ec2(empty);
	ec(melfsAcidArrow);
	ec1(empty);		// Stinking Cloud
	ec(empty);
	ec(fireball);
	ec1(flameArrow);
	ec(empty);
	ec(holdPerson);
	ec(empty);
	ec(lightningBolt);
	ec(vampiricTouch);
	ec(empty);
	ec(iceStorm);
	ec(empty);		// EOB1: stone skin, EOB2: imp invisibility
	ec(empty);		// EOB1: cloud kill, EOB2: remove curse
	ec(empty);
	ec(holdMonster);
	ec2(empty);
	ec2(empty);
	ec2(empty);
	ec2(empty);
	ec2(trueSeeing);
	ec2(empty);
	ec2(empty);
	ec2(empty);
	ec2(empty);
	ec(empty);	// Bless
	ec(empty);
	ec(empty);
	ec(detectMagic);
	ec(empty);
	ec(aid);
	ec(shockingGraspFlameBlade);
	ec(holdPerson);
	ec(slowPoison);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec(empty);
	ec1(empty);	// Prot from Lightning
	ec(empty);
	ec(empty);
	ec(flameStrike);
	ec(empty);
	ec2(empty);
	ec2(trueSeeing);
	ec2(empty);
	ec2(empty);
	ec2(empty);
	ec(empty);
	ec2(empty);
	ec(unk1Passive);
	ec2(empty);
	ec2(unk2Passive);
	ec(deathSpellPassive);
	ec(disintegratePassive);
	ec2(causeCriticalWoundsPassive);
	ec2(fleshToStonePassive);

	_spells = new EobSpell[_numSpells];
	memset(_spells, 0, _numSpells * sizeof(EobSpell));

	for (int i = 0; i < _numSpells; i++) {
		EobSpell *s = &_spells[i];
		s->name = _flags.gameID == GI_EOB2 ? ((i == 0 || i == _mageSpellListSize) ? _mageSpellList[0] : ((i < (_mageSpellListSize + 1)) ? _spellNames[i - 1] : _spellNames[i - 2])) : _spellNames[i];
		s->startCallback = startCallback[i];
		s->timingPara = magicTimingParaAssign[i];
		s->endCallback = endCallback[i];
	}

	magicTimingParaAssign.clear();
	startCallback.clear();
	endCallback.clear();

	_clericSpellOffset = _mageSpellListSize;

#undef mpn
#undef mp1n
#undef mp2n
#undef mp
#undef mp1
#undef mp2
#undef sc
#undef sc1
#undef sc2
#undef ec
#undef ec1
#undef ec2
}

void EobEngine::initStaticResource() {
	int temp;
	_mainMenuStrings = _staticres->loadStrings(kEob1MainMenuStrings, temp);

	_doorShapeEncodeDefs = _staticres->loadRawData(kEob1DoorShapeDefs, temp);
	_doorSwitchShapeEncodeDefs = _staticres->loadRawData(kEob1DoorSwitchShapeDefs, temp);
	_doorSwitchCoords = _staticres->loadRawData(kEob1DoorSwitchCoords, temp);

	_dscDoorScaleMult4 = _staticres->loadRawData(kEobBaseDscDoorScaleMult4, temp);
	_dscDoorScaleMult5 = _staticres->loadRawData(kEobBaseDscDoorScaleMult5, temp);
	_dscDoorScaleMult6 = _staticres->loadRawData(kEobBaseDscDoorScaleMult6, temp);
	_dscDoorY3 = _staticres->loadRawData(kEobBaseDscDoorY3, temp);
	_dscDoorY4 = _staticres->loadRawData(kEobBaseDscDoorY4, temp);
	_dscDoorY5 = _staticres->loadRawData(kEobBaseDscDoorY5, temp);
	_dscDoorY6 = _staticres->loadRawData(kEobBaseDscDoorY6, temp);
	_dscDoorCoordsExt = (const int16*)_staticres->loadRawDataBe16(kEobBaseDscDoorCoordsExt, temp);

	_monsterDistAttType10 = _staticres->loadRawData(kEob1MonsterDistAttType10, temp);
	_monsterDistAttSfx10 = _staticres->loadRawData(kEob1MonsterDistAttSfx10, temp);
	_monsterDistAttType17 = _staticres->loadRawData(kEob1MonsterDistAttType17, temp);
	_monsterDistAttSfx17 = _staticres->loadRawData(kEob1MonsterDistAttSfx17, temp);

	const uint8 *ps = _staticres->loadRawData(kEob1MonsterProperties, temp);
	temp /= 27;
	_monsterProps = new EobMonsterProperty[temp];
	memset(_monsterProps, 0, temp * sizeof(EobMonsterProperty));
	// Try to convert EOB1 (hard coded) monster properties to EOB2 type monster properties.
	// This is still WIP, since most properties are unknown for now.
	for (int i = 0; i < temp; i++) {
		EobMonsterProperty *p = &_monsterProps[i];
		p->armorClass = (int8)*ps++;
		p->hitChance = (int8)*ps++;
		p->hpDcTimes = *ps++;
		p->attacksPerRound = *ps++;
		p->dmgDc[0].times = *ps++;
		p->dmgDc[0].pips = *ps++;
		p->dmgDc[0].base = (int8)*ps++;
		p->dmgDc[1].times = *ps++;
		p->dmgDc[1].pips = *ps++;
		p->dmgDc[1].base =(int8) *ps++;
		p->dmgDc[2].times = *ps++;
		p->dmgDc[2].pips = *ps++;
		p->dmgDc[2].base = (int8)*ps++;
		ps++;
		p->flags = *ps++;
		ps++;
		ps++;
		ps++;
		ps++;
		p->experience = READ_LE_UINT16(ps);
		ps += 2;
		p->u30 = *ps++;
		p->sound1 = *ps++;
		p->sound2 = *ps++;
		p->numRemoteAttacks = *ps++;
		ps++;
		p->dmgModifierEvade = *ps++;
	}
}

void EobEngine::initSpells() {
	EobCoreEngine::initSpells();

	struct FlagTableEntry {
		uint16 typeFlag;
		uint32 effectFlag;
		uint8 damageFlag;
	};

	static const FlagTableEntry flagTable[] = {
		{ 0x0000, 0x000000, 0x00 },	// dummy
		{ 0x0033, 0x000001, 0x00 },	// armor
		{ 0x0100, 0x000000, 0x21 },	// burning hands
		{ 0x004c, 0x000002, 0x00 },	// detect magic
		{ 0x0100, 0x000000, 0x01 },	// magic missile
		{ 0x0000, 0x000000, 0x00 },	// dummy
		{ 0x008b, 0x000008, 0x00 },	// shield
		{ 0x0488, 0x000000, 0x03 },	// shocking grasp
		{ 0x0021, 0x000040, 0x00 },	// invisibility
		{ 0x0000, 0x000000, 0x00 },	// dummy
		{ 0x0100, 0x000000, 0x11 },	// melf's acid arrow
		{ 0x0000, 0x000000, 0x00 },	// STINKING CLOUD
		{ 0x1000, 0x000000, 0x00 },	// dispel magic
		{ 0x0100, 0x000000, 0x21 },	// fireball
		{ 0x0100, 0x000000, 0x11 },	// FLAME ARROW
		{ 0x0248, 0x010000, 0x00 },	// haste
		{ 0x0100, 0x000000, 0x00 },	// hold person
		{ 0x0240, 0x000040, 0x00 },	// inv 10'
		{ 0x0100, 0x000000, 0x03 },	// lightning bolt
		{ 0x0488, 0x000000, 0x01 },	// vampiric touch
		{ 0x0100, 0x000000, 0x00 },	// fear
		{ 0x0100, 0x000000, 0x41 },	// ice storm
		{ 0x0000, 0x000000, 0x00 },	// STONE SKIN
		{ 0x0000, 0x000000, 0x00 },	// CLOUD KILL
		{ 0x0100, 0x000000, 0x41 },	// cone of cold
		{ 0x0100, 0x000000, 0x00 },	// hold monster
		{ 0x005c, 0x000400, 0x00 },	// bless
		{ 0x0020, 0x000000, 0x00 },	// cure light wounds
		{ 0x0100, 0x000000, 0x01 },	// cause light wounds
		{ 0x004c, 0x000002, 0x00 },	// detect magic
		{ 0x0029, 0x000800, 0x00 },	// prot from evil
		{ 0x0039, 0x000000, 0x00 },	// aid
		{ 0x2408, 0x000000, 0x21 },	// flame blade
		{ 0x0100, 0x000000, 0x00 },	// hold person
		{ 0x0028, 0x002000, 0x00 },	// slow poison
		{ 0x0040, 0x000000, 0x00 },	// create food
		{ 0x1000, 0x000000, 0x00 },	// dispel magic
		{ 0x0099, 0x004000, 0x00 },	// magical vestment
		{ 0x004c, 0x008000, 0x00 },	// prayer
		{ 0x0040, 0x000000, 0x00 },	// remove paralysis
		{ 0x0020, 0x000000, 0x00 },	// cure serious
		{ 0x0100, 0x000000, 0x01 },	// cause serious
		{ 0x0020, 0x000000, 0x00 },	// neutralize poison
		{ 0x0248, 0x000800, 0x00 },	// prot from evil 10'
		{ 0x0000, 0x000000, 0x00 },	// PROT FROM LIGHTNING
		{ 0x0020, 0x000000, 0x00 },	// cure critical
		{ 0x0100, 0x000000, 0x01 },	// cause critical
		{ 0x0100, 0x000000, 0x21 },	// flame strike
		{ 0x0020, 0x000000, 0x00 },	// raise dead
		{ 0x0020, 0x000000, 0x00 },	// lay on hands
		{ 0x0000, 0x000000, 0x00 },	// obj hit passive
		{ 0x0000, 0x000000, 0x00 },	// disintegrate passive
		{ 0x0000, 0x000000, 0x00 }	// death spell passive
	};

	int temp;
	const uint8 *src = _staticres->loadRawData(kEobBaseSpellProperties, temp);
	_clericSpellOffset -= 3;

	for (int i = 0; i < _numSpells; i++) {
		EobSpell *s = &_spells[i];
		src += 4;
		s->flags = flagTable[i].typeFlag;/*convertSpellFlagToEob2Format(src[0], src[14]);*/
		s->damageFlags = flagTable[i].damageFlag;
		s->effectFlags = flagTable[i].effectFlag;
		s->sound = src[13];
		src += 15;
	}
}

void DarkMoonEngine::initStaticResource() {
	int temp;
	_mainMenuStrings = _staticres->loadStrings(kEob2MainMenuStrings, temp);
	_introStrings = _staticres->loadStrings(kEob2IntroStrings, temp);
	_cpsFilesIntro = _staticres->loadStrings(kEob2IntroCPSFiles, temp);

	_seqIntro = new const EobSequenceStep*[44];
	for (int i = 0; i < 44; i++)
		_seqIntro[i] = _staticres->loadEob2SeqData(kEob2IntroSeqData00 + i, temp);

	_shapesIntro = new const EobShapeDef*[13];
	memset(_shapesIntro, 0, sizeof(EobShapeDef*) * 13);
 	_shapesIntro[0] = _staticres->loadEob2ShapeData(kEob2IntroShapes00, temp);
 	_shapesIntro[1] = _staticres->loadEob2ShapeData(kEob2IntroShapes01, temp);
 	_shapesIntro[4] = _staticres->loadEob2ShapeData(kEob2IntroShapes04, temp);
 	_shapesIntro[7] = _staticres->loadEob2ShapeData(kEob2IntroShapes07, temp);

	_finaleStrings = _staticres->loadStrings(kEob2FinaleStrings, temp);
	_creditsData = _staticres->loadRawData(kEob2CreditsData, temp);
	_cpsFilesFinale = _staticres->loadStrings(kEob2FinaleCPSFiles, temp);

	_seqFinale = new const EobSequenceStep*[21];
	for (int i = 0; i < 21; i++)
		_seqFinale[i] = _staticres->loadEob2SeqData(kEob2FinaleSeqData00 + i, temp);

	_shapesFinale = new const EobShapeDef*[13];
	memset(_shapesFinale, 0, sizeof(EobShapeDef*) * 13);
	_shapesFinale[0] = _staticres->loadEob2ShapeData(kEob2FinaleShapes00, temp);
 	_shapesFinale[3] = _staticres->loadEob2ShapeData(kEob2FinaleShapes03, temp);
 	_shapesFinale[7] = _staticres->loadEob2ShapeData(kEob2FinaleShapes07, temp);
 	_shapesFinale[9] = _staticres->loadEob2ShapeData(kEob2FinaleShapes09, temp);
 	_shapesFinale[10] = _staticres->loadEob2ShapeData(kEob2FinaleShapes10, temp);

	_dscDoorType5Offs = _staticres->loadRawData(kEobBaseDscDoorType5Offs, temp);

	_npcShpData = _staticres->loadRawData(kEob2NpcShapeData, temp);
	_npc1Strings = _staticres->loadStrings(kEob2Npc1Strings, temp);
	_npc2Strings = _staticres->loadStrings(kEob2Npc2Strings, temp);
	_monsterDustStrings = _staticres->loadStrings(kEob2MonsterDustStrings, temp);
}

void DarkMoonEngine::initSpells() {
	EobCoreEngine::initSpells();

	int temp;
	const uint8 *src = _staticres->loadRawData(kEobBaseSpellProperties, temp);

	for (int i = 0; i < _numSpells; i++) {
		EobSpell *s = &_spells[i];
		src += 8;
		s->flags = READ_LE_UINT16(src);
		src += 10;
		s->sound = *src++;
		s->effectFlags = READ_LE_UINT32(src);
		src += 4;
		s->damageFlags = READ_LE_UINT16(src);
		src += 2;
	}
}

const char *DarkMoonEngine::_palFilesIntro[] = {
	"PALETTE1.PAL", // EGA: palette0.pal
	"PALETTE3.PAL",
	"PALETTE2.PAL",
	"PALETTE4.PAL",
	0
};

const char *DarkMoonEngine::_palFilesFinale[] = {
	"FINALE_0.PAL",
	"FINALE_0.PAL",
	"FINALE_1.PAL",
	"FINALE_2.PAL",
	"FINALE_3.PAL",
	"FINALE_4.PAL",
	"FINALE_5.PAL",
	"FINALE_6.PAL",
	"FINALE_7.PAL",
	0
};

#endif // ENABLE_EOB

} // End of namespace Kyra
