/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
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
 */
 
#ifndef PEGASUS_CONSTANTS_H
#define PEGASUS_CONSTANTS_H

#include "common/endian.h"

#include "pegasus/types.h"

namespace Pegasus {

const tGameID kGameIDNothing = -1;

const tActorID kNoActorID = kGameIDNothing;
const tActorID kPlayerID = 0;
const tItemID kNoItemID = kGameIDNothing;
const tRoomID kNoRoomID = kGameIDNothing;
const tExtraID kNoExtraID = 0xFFFFFFFF;
const tNeighborhoodID kNoNeighborhoodID = kGameIDNothing;
const tAlternateID kNoAlternateID = 0;
const tGameMenuCommand kMenuCmdNoCommand = 0;

const tHotSpotActivationID kActivateHotSpotAlways = 0;
const tHotSpotActivationID kActivateHotSpotNever = -1;

const tItemState kNoItemState = -1;

const tDirectionConstant kNoDirection = 0xFF;

const tTurnDirection kNoTurn = 0xFF;
const tTurnDirection kTurnLeft = 0;
const tTurnDirection kTurnRight = 1;
const tTurnDirection kTurnUp = 2;
const tTurnDirection kTurnDown = 3;
const tTurnDirection kMaxTurns = 4;

const tGameMode kNoMode = -1;
const tGameMode kModeNavigation = 0;
const tGameMode kLastGameShellMode = kModeNavigation;

const tCanMoveForwardReason kCanMoveForward = 0;
const tCanMoveForwardReason kCantMoveBlocked = kCanMoveForward + 1;
const tCanMoveForwardReason kCantMoveDoorClosed = kCantMoveBlocked + 1;
const tCanMoveForwardReason kCantMoveDoorLocked = kCantMoveDoorClosed + 1;
const tCanMoveForwardReason kCantMoveLastReason = kCantMoveDoorLocked;

const tCanTurnReason kCanTurn = 0;
const tCanTurnReason kCantTurnNoTurn = kCanTurn + 1;
const tCanTurnReason kCantTurnLastReason = kCantTurnNoTurn;

const tCanOpenDoorReason kCanOpenDoor = 0;
const tCanOpenDoorReason kCantOpenNoDoor = kCanOpenDoor + 1;
const tCanOpenDoorReason kCantOpenLocked = kCantOpenNoDoor + 1;
const tCanOpenDoorReason kCantOpenAlreadyOpen = kCantOpenLocked + 1;
const tCanOpenDoorReason kCantOpenLastReason = kCantOpenAlreadyOpen;

const tDisplayElementID kNoDisplayElement = -1;
const tDisplayElementID kHighestReservedElementID = -2;

const tDisplayElementID kCursorID = kHighestReservedElementID;
const tDisplayElementID kLoadScreenID = kCursorID - 1;

const tDisplayOrder kMinAvailableOrder = 0;
const tDisplayOrder kMaxAvailableOrder = 999998;
const tDisplayOrder kLoadScreenOrder = 900000;
const tDisplayOrder kCursorOrder = 1000000;

const tHotSpotID kNoHotSpotID = -1;
const tHotSpotFlags kNoHotSpotFlags = 0;
const tHotSpotFlags kAllHotSpotFlags = ~kNoHotSpotFlags;

const tNotificationFlags kNoNotificationFlags = 0;

const tDisplayElementID kCurrentDragSpriteID = 1000;

// TODO
//const Fixed kFixed1 = 1 << 16;
//const Fixed kFixedMinus1 = -1 << 16;

const TimeScale kDefaultTimeScale = 600;

// TODO
//const RGBColor kWhiteRGB = {0xFFFF, 0xFFFF, 0xFFFF};

//	Ticks per second.

const TimeScale kOneTickPerSecond = 1;
const TimeScale kTwoTicksPerSecond = 2;
const TimeScale kFifteenTicksPerSecond = 15;
const TimeScale kThirtyTicksPerSecond = 30;
const TimeScale kSixtyTicksPerSecond = 60;
const TimeScale kMovieTicksPerSecond = 600;

//	These times are in seconds.

const TimeValue kOneSecond = 1;
const TimeValue kTwoSeconds = 2;
const TimeValue kThreeSeconds = 3;
const TimeValue kFourSeconds = 4;
const TimeValue kFiveSeconds = 5;
const TimeValue kSixSeconds = 6;
const TimeValue kSevenSeconds = 7;
const TimeValue kEightSeconds = 8;
const TimeValue kNineSeconds = 9;
const TimeValue kTenSeconds = 10;
const TimeValue kElevenSeconds = 11;
const TimeValue kTwelveSeconds = 12;
const TimeValue kThirteenSeconds = 13;
const TimeValue kFourteenSeconds = 14;
const TimeValue kFifteenSeconds = 15;
const TimeValue kSixteenSeconds = 16;
const TimeValue kSeventeenSeconds = 17;
const TimeValue kEighteenSeconds = 18;
const TimeValue kNineteenSeconds = 19;
const TimeValue kTwentySeconds = 20;
const TimeValue kThirtySeconds = 30;
const TimeValue kFortySeconds = 40;
const TimeValue kFiftySeconds = 50;
const TimeValue kSixtySeconds = 60;
const TimeValue kOneMinute = 60;
const TimeValue kTwoMinutes = kOneMinute * 2;
const TimeValue kThreeMinutes = kOneMinute * 3;
const TimeValue kFourMinutes = kOneMinute * 4;
const TimeValue kFiveMinutes = kOneMinute * 5;
const TimeValue kSixMinutes = kOneMinute * 6;
const TimeValue kSevenMinutes = kOneMinute * 7;
const TimeValue kEightMinutes = kOneMinute * 8;
const TimeValue kNineMinutes = kOneMinute * 9;
const TimeValue kTenMinutes = kOneMinute * 10;
const TimeValue kElevenMinutes = kOneMinute * 11;
const TimeValue kTwelveMinutes = kOneMinute * 12;
const TimeValue kThirteenMinutes = kOneMinute * 13;
const TimeValue kFourteenMinutes = kOneMinute * 14;
const TimeValue kFifteenMinutes = kOneMinute * 15;
const TimeValue kSixteenMinutes = kOneMinute * 16;
const TimeValue kSeventeenMinutes = kOneMinute * 17;
const TimeValue kEighteenMinutes = kOneMinute * 18;
const TimeValue kNineteenMinutes = kOneMinute * 19;
const TimeValue kTwentyMinutes = kOneMinute * 20;
const TimeValue kThirtyMinutes = kOneMinute * 30;
const TimeValue kFortyMinutes = kOneMinute * 40;
const TimeValue kFiftyMinutes = kOneMinute * 50;
const TimeValue kOneHour = kOneMinute * 60;
const TimeValue kTwoHours = kOneHour * 2;

//	Common times.

const TimeValue kHalfSecondPerTwoTicks = kTwoTicksPerSecond / 2;
const TimeValue kHalfSecondPerThirtyTicks = kThirtyTicksPerSecond / 2;
const TimeValue kHalfSecondPerSixtyTicks = kSixtyTicksPerSecond / 2;

const TimeValue kOneSecondPerTwoTicks = kTwoTicksPerSecond;
const TimeValue kOneSecondPerThirtyTicks = kThirtyTicksPerSecond;
const TimeValue kOneSecondPerSixtyTicks = kSixtyTicksPerSecond;

const TimeValue kOneMinutePerFifteenTicks = kOneMinute * kFifteenTicksPerSecond;
const TimeValue kFiveMinutesPerFifteenTicks = kFiveMinutes * kFifteenTicksPerSecond;
const TimeValue kTenMinutesPerFifteenTicks = kTenMinutes * kFifteenTicksPerSecond;

const TimeValue kOneMinutePerThirtyTicks = kOneMinute * kThirtyTicksPerSecond;
const TimeValue kFiveMinutesPerThirtyTicks = kFiveMinutes * kThirtyTicksPerSecond;
const TimeValue kTenMinutesPerThirtyTicks = kTenMinutes * kThirtyTicksPerSecond;

const TimeValue kOneMinutePerSixtyTicks = kOneMinute * kSixtyTicksPerSecond;
const TimeValue kFiveMinutesPerSixtyTicks = kFiveMinutes * kSixtyTicksPerSecond;
const TimeValue kTenMinutesPerSixtyTicks = kTenMinutes * kSixtyTicksPerSecond;

//	Time in seconds you can hang around Caldoria without going to work...
const TimeValue kLateWarning2TimeLimit = kFiveMinutes;
const TimeValue kLateWarning3TimeLimit = kTenMinutes;

const TimeValue kSinclairShootsTimeLimit = kThreeMinutes;
const TimeValue kCardBombCountDownTime = kTwelveSeconds;

const TimeValue kOxyMaskFullTime = kThirtyMinutes;

const TimeValue kTSAUncreatedTimeLimit = kFiveMinutes;
const TimeValue kRipTimeLimit = kTenMinutesPerFifteenTicks;
const TimeScale kRipTimeScale = kFifteenTicksPerSecond;

const TimeValue kIntroTimeOut = kThirtySeconds;

const TimeValue kMarsRobotPatienceLimit = kFifteenSeconds;
const TimeValue kLockFreezeTimeLmit = kFifteenSeconds;
const TimeValue kSpaceChaseTimeLimit = kTenMinutes;
const TimeValue kVacuumSurvivalTimeLimit = kThirtySeconds;
const TimeValue kColorMatchingTimeLimit = kFourMinutes;
const TimeScale kJunkTimeScale = kFifteenTicksPerSecond;
const TimeValue kJunkDropBaseTime = kFiveSeconds;
const TimeValue kJunkDropSlopTime = kThreeSeconds;
const TimeValue kJunkTravelTime = kTenSeconds * kJunkTimeScale;
const TimeValue kCollisionReboundTime = kOneSecond * kJunkTimeScale;
const TimeValue kWeaponReboundTime = kTwoSeconds * kJunkTimeScale;

const TimeValue kGawkAtRobotTime = kTenSeconds;
const TimeValue kGawkAtRobotTime2 = kThirteenSeconds;
const TimeValue kPlasmaImpactTime = kTwoSeconds;

const TimeValue kNoradAirMaskTimeLimit = kOneMinute + kFifteenSeconds;

const tNotificationID kNeighborhoodNotificationID = 1;
const tNotificationID kLastNeighborhoodNotificationID = kNeighborhoodNotificationID;

const tNotificationFlags kNeighborhoodMovieCompletedFlag = 1;
const tNotificationFlags kMoveForwardCompletedFlag = kNeighborhoodMovieCompletedFlag << 1;
const tNotificationFlags kStrideCompletedFlag = kMoveForwardCompletedFlag << 1;
const tNotificationFlags kTurnCompletedFlag = kStrideCompletedFlag << 1;
const tNotificationFlags kSpotCompletedFlag = kTurnCompletedFlag << 1;
const tNotificationFlags kDoorOpenCompletedFlag = kSpotCompletedFlag << 1;
const tNotificationFlags kExtraCompletedFlag = kDoorOpenCompletedFlag << 1;
const tNotificationFlags kSpotSoundCompletedFlag = kExtraCompletedFlag << 1;
const tNotificationFlags kDelayCompletedFlag = kSpotSoundCompletedFlag << 1;
const tNotificationFlags kActionRequestCompletedFlag = kDelayCompletedFlag << 1;
const tNotificationFlags kDeathExtraCompletedFlag = kActionRequestCompletedFlag << 1;
const tNotificationFlags kLastNeighborhoodNotificationFlag = kDeathExtraCompletedFlag;

const tNotificationFlags kNeighborhoodFlags =	kNeighborhoodMovieCompletedFlag |
												kMoveForwardCompletedFlag |
												kStrideCompletedFlag |
												kTurnCompletedFlag |
												kSpotCompletedFlag |
												kDoorOpenCompletedFlag |
												kExtraCompletedFlag |
												kSpotSoundCompletedFlag |
												kDelayCompletedFlag |
												kActionRequestCompletedFlag |
												kDeathExtraCompletedFlag;

const uint32 kPegasusPrimeCreator = MKTAG('J', 'P', 'P', 'P');
const uint32 kPegasusPrimeContinueType = MKTAG('P', 'P', 'C', 'T');

const uint32 kPegasusPrimeDisk1GameType = MKTAG('P', 'P', 'G', '1');
const uint32 kPegasusPrimeDisk2GameType = MKTAG('P', 'P', 'G', '2');
const uint32 kPegasusPrimeDisk3GameType = MKTAG('P', 'P', 'G', '3');
const uint32 kPegasusPrimeDisk4GameType = MKTAG('P', 'P', 'G', '4');

// We only support one of the save versions; the rest are from betas
// and we are not supporting them.
const uint32 kPegasusPrimeVersion = 0x00009019;

const char kNormalSave = 0;
const char kContinueSave = 1;

} // End of namespace Pegasus

#endif
