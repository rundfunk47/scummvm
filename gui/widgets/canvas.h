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

#ifndef GUI_WIDGETS_CANVAS_H
#define GUI_WIDGETS_CANVAS_H

#include "gui/widget.h"
#include "common/str.h"
#include "common/array.h"
#include "gui/widgets/scrollbar.h"

namespace GUI {

/*
 * A scrollable canvas, which can have widgets inside of it
 */

class ScrollableCanvasWidget : public Widget {
public:
	typedef Common::String String;
protected:
protected:
	Widget	*_mouseWidget;
	Widget  *_focusedWidget;
	Widget  *_dragWidget;
	Widget 	*_tickleWidget;
	bool	_visible;
	GuiObject	*_boss;
	
	ThemeEngine::DialogBackground _backgroundType;

	int		_scrollPosx;
	int		_scrollPosy;
	
	int		_scrollBarWidth;

	ScrollBarWidget	*_scrollBar;
public:
	ScrollableCanvasWidget(GuiObject *boss, int x, int y, int w, int h);
	ScrollableCanvasWidget(GuiObject *boss, const String &name);
	
	bool	isVisible() const	{ return _visible; }

	void	releaseFocus();
	void	setFocusWidget(Widget *widget);
	Widget *getFocusWidget() { return _focusedWidget; }

	void init();
	void scrollBarRecalc();
	int calcMax();
	void drawWidget();
	void reflowLayout();
	
	Widget *findWidget(int x, int y);

	void handleMouseWheel(int x, int y, int direction);
	void handleFingerMoved(int x, int y, int deltax, int deltay, int button);
	
	void handleCommand(CommandSender *sender, uint32 cmd, uint32 data);
};

} // End of namespace GUI

#endif
