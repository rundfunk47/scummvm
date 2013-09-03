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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "common/rect.h"
#include "common/system.h"
#include "common/timer.h"
#include "gui/widgets/scrollbar.h"
#include "gui/gui-manager.h"
#include "gui/ThemeEngine.h"

namespace GUI {

#define UP_DOWN_BOX_HEIGHT	 (_w+1)
#define LEFT_RIGHT_BOX_WIDTH (_h+1)

ScrollBarWidget::ScrollBarWidget(GuiObject *boss, int x, int y, int w, int h, bool horizontal)
	: Widget (boss, x, y, w, h), CommandSender(boss) {
	setFlags(WIDGET_ENABLED | WIDGET_TRACK_MOUSE | WIDGET_CLEARBG | WIDGET_WANT_TICKLE);
	_type = kScrollBarWidget;

	_part = kNoPart;
	_sliderLength = 0;
	_sliderPos = 0;

	_draggingPart = kNoPart;
	_sliderDeltaMouseDownPos = 0;

	_numEntries = 0;
	_entriesPerPage = 0;
	_currentPos = 0;
	_scrollOffset = 0;

	_repeatTimer = 0;

	_horizontal = horizontal;
}

void ScrollBarWidget::handleScroll(int pixels, int stepSize) {
	int old_pos = _currentPos;

	if (_numEntries < _entriesPerPage)
		return;

	int i = _scrollOffset + pixels;

	if (i > 0) {
		while (i >= stepSize) {
			i = i - stepSize;
			_currentPos--;	
		}
	} else {
		while (i <= stepSize*-1) {
			i = i + stepSize;
			_currentPos++;	
		}
	}

	_scrollOffset = i;
	checkBounds(old_pos);
	sendCommand(kSetScrollOffset, pixels);
}

void ScrollBarWidget::handleMouseDown(int x, int y, int button, int clickCount) {
	int old_pos = _currentPos;

	// Do nothing if there are less items than fit on one page
	if (_numEntries <= _entriesPerPage)
		return;

	if (_horizontal) {
		if (x <= LEFT_RIGHT_BOX_WIDTH) {
			// Left arrow
			_currentPos--;
			_repeatTimer = g_system->getMillis() + kRepeatInitialDelay;
			_draggingPart = kUpArrowPart;
		} else if (x >= _w - LEFT_RIGHT_BOX_WIDTH) {
			// Right arrow
			_currentPos++;
			_repeatTimer = g_system->getMillis() + kRepeatInitialDelay;
			_draggingPart = kDownArrowPart;
		} else if (x < _sliderPos) {
			_currentPos -= _entriesPerPage - 1;
		} else if (x >= _sliderPos + _sliderLength) {
			_currentPos += _entriesPerPage - 1;
		} else {
			_draggingPart = kSliderPart;
			_sliderDeltaMouseDownPos = x - _sliderPos;
		}
	} else {
		if (y <= UP_DOWN_BOX_HEIGHT) {
			// Up arrow
			_currentPos--;
			_repeatTimer = g_system->getMillis() + kRepeatInitialDelay;
			_draggingPart = kUpArrowPart;
		} else if (y >= _h - UP_DOWN_BOX_HEIGHT) {
			// Down arrow
			_currentPos++;
			_repeatTimer = g_system->getMillis() + kRepeatInitialDelay;
			_draggingPart = kDownArrowPart;
		} else if (y < _sliderPos) {
			_currentPos -= _entriesPerPage - 1;
		} else if (y >= _sliderPos + _sliderLength) {
			_currentPos += _entriesPerPage - 1;
		} else {
			_draggingPart = kSliderPart;
			_sliderDeltaMouseDownPos = y - _sliderPos;
		}
	}

	// Make sure that _currentPos is still inside the bounds
	checkBounds(old_pos);
}

void ScrollBarWidget::handleMouseUp(int x, int y, int button, int clickCount) {
	_draggingPart = kNoPart;
	_repeatTimer = 0;
}

void ScrollBarWidget::handleMouseMoved(int x, int y, int button) {
	// Do nothing if there are less items than fit on one page
	if (_numEntries <= _entriesPerPage)
		return;
	
	if (_horizontal) {
		if (_draggingPart == kSliderPart) {
			int old_pos = _currentPos;
			_sliderPos = x - _sliderDeltaMouseDownPos;

			if (_sliderPos < LEFT_RIGHT_BOX_WIDTH)
				_sliderPos = LEFT_RIGHT_BOX_WIDTH;

			if (_sliderPos > _w - LEFT_RIGHT_BOX_WIDTH - _sliderLength)
				_sliderPos = _w - LEFT_RIGHT_BOX_WIDTH - _sliderLength;

			_currentPos =
				(_sliderPos - LEFT_RIGHT_BOX_WIDTH) * (_numEntries - _entriesPerPage) / (_w - 2 * LEFT_RIGHT_BOX_WIDTH - _sliderLength);
			checkBounds(old_pos);
		} else {
			int old_part = _part;

			if (x <= LEFT_RIGHT_BOX_WIDTH)	// Left arrow
				_part = kUpArrowPart;
			else if (x >= _w - LEFT_RIGHT_BOX_WIDTH)	// Right arrow
				_part = kDownArrowPart;
			else if (x < _sliderPos)
				_part = kPageUpPart;
			else if (x >= _sliderPos + _sliderLength)
				_part = kPageDownPart;
			else
				_part = kSliderPart;

			if (old_part != _part)
				draw();
		}
	} else {
		if (_draggingPart == kSliderPart) {
			int old_pos = _currentPos;
			_sliderPos = y - _sliderDeltaMouseDownPos;

			if (_sliderPos < UP_DOWN_BOX_HEIGHT)
				_sliderPos = UP_DOWN_BOX_HEIGHT;

			if (_sliderPos > _h - UP_DOWN_BOX_HEIGHT - _sliderLength)
				_sliderPos = _h - UP_DOWN_BOX_HEIGHT - _sliderLength;

			_currentPos =
				(_sliderPos - UP_DOWN_BOX_HEIGHT) * (_numEntries - _entriesPerPage) / (_h - 2 * UP_DOWN_BOX_HEIGHT - _sliderLength);
			checkBounds(old_pos);
		} else {
			int old_part = _part;

			if (y <= UP_DOWN_BOX_HEIGHT)	// Up arrow
				_part = kUpArrowPart;
			else if (y >= _h - UP_DOWN_BOX_HEIGHT)	// Down arrow
				_part = kDownArrowPart;
			else if (y < _sliderPos)
				_part = kPageUpPart;
			else if (y >= _sliderPos + _sliderLength)
				_part = kPageDownPart;
			else
				_part = kSliderPart;

			if (old_part != _part)
				draw();
		}
	}
}

void ScrollBarWidget::handleTickle() {
	if (_repeatTimer) {
		const uint32 curTime = g_system->getMillis();
		if (curTime >= _repeatTimer) {
			const int old_pos = _currentPos;

			if (_part == kUpArrowPart)
				_currentPos -= 3;
			else if (_part == kDownArrowPart)
				_currentPos += 3;

			checkBounds(old_pos);

			_repeatTimer = curTime + kRepeatDelay;
		}
	}
}

void ScrollBarWidget::checkBounds(int old_pos) {
	if (_numEntries <= _entriesPerPage || _currentPos < 0)
		_currentPos = 0;
	else if (_currentPos > _numEntries - _entriesPerPage)
		_currentPos = _numEntries - _entriesPerPage;

	if (old_pos != _currentPos) {
		recalc();
		draw();
		sendCommand(kSetPositionCmd, _currentPos);
	}
}

void ScrollBarWidget::recalc() {
	if (_horizontal) {
		if (_numEntries > _entriesPerPage) {
			_sliderLength = (_w - 2 * LEFT_RIGHT_BOX_WIDTH) * _entriesPerPage / _numEntries;
			if (_sliderLength < LEFT_RIGHT_BOX_WIDTH)
				_sliderLength = LEFT_RIGHT_BOX_WIDTH;

			_sliderPos =
				LEFT_RIGHT_BOX_WIDTH + (_w - 2 * LEFT_RIGHT_BOX_WIDTH - _sliderLength) * _currentPos / (_numEntries - _entriesPerPage);
			if (_sliderPos < 0)
				_sliderPos = 0;
			setVisible(true);
		} else {
			_sliderLength = _w - 2 * LEFT_RIGHT_BOX_WIDTH;
			_sliderPos = LEFT_RIGHT_BOX_WIDTH;
			setVisible(false);
		}
	} else {
		if (_numEntries > _entriesPerPage) {
			_sliderLength = (_h - 2 * UP_DOWN_BOX_HEIGHT) * _entriesPerPage / _numEntries;
			if (_sliderLength < UP_DOWN_BOX_HEIGHT)
				_sliderLength = UP_DOWN_BOX_HEIGHT;

			_sliderPos =
				UP_DOWN_BOX_HEIGHT + (_h - 2 * UP_DOWN_BOX_HEIGHT - _sliderLength) * _currentPos / (_numEntries - _entriesPerPage);
			if (_sliderPos < 0)
				_sliderPos = 0;
			setVisible(true);
		} else {
			_sliderLength = _h - 2 * UP_DOWN_BOX_HEIGHT;
			_sliderPos = UP_DOWN_BOX_HEIGHT;
			setVisible(false);
		}
	}
}

void ScrollBarWidget::drawWidget() {
	if (_draggingPart != kNoPart)
		_part = _draggingPart;

	ThemeEngine::ScrollbarState state = ThemeEngine::kScrollbarStateNo;
	if (_numEntries <= _entriesPerPage) {
		state = ThemeEngine::kScrollbarStateSinglePage;
	} else if (_part == kUpArrowPart) {
		state = ThemeEngine::kScrollbarStateUp;
	} else if (_part == kDownArrowPart) {
		state = ThemeEngine::kScrollbarStateDown;
	} else if (_part == kSliderPart) {
		state = ThemeEngine::kScrollbarStateSlider;
	}

	g_gui.theme()->drawScrollbar(Common::Rect(_x, _y, _x+_w, _y+_h), _sliderPos, _sliderLength, state, _state, _horizontal);
}

} // End of namespace GUI
