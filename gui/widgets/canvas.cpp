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

#include "common/system.h"
#include "common/rect.h"
#include "gui/dialog.h"

#include "gui/widgets/canvas.h"
#include "gui/widgets/scrollbar.h"
#include "gui/gui-manager.h"

#include "engines/dialogs.h"

#include "gui/saveload.h"

#include "gui/ThemeEval.h"	
#include "gui/widget.h"


namespace GUI {

//
// ScrollableCanvasWidget
//

ScrollableCanvasWidget::ScrollableCanvasWidget(GuiObject *boss, const Common::String &name)
	: Widget(boss, name) {
	setFlags(WIDGET_ENABLED | WIDGET_DRAGABLE_CONTAINER);
	init();
}

ScrollableCanvasWidget::ScrollableCanvasWidget(GuiObject *boss, int x, int y, int w, int h)
	: Widget(boss, x, y, w, h) {
	setFlags(WIDGET_ENABLED | WIDGET_DRAGABLE_CONTAINER);
	init();
}

void ScrollableCanvasWidget::init() {
	Widget *w = _firstWidget;
	while (w) {
		w->setDrawableArea(_drawableArea);
		w = w->next();
	}

	// We don't want a drawableArea on scrollbar
	_scrollPosx = 0;
	_scrollPosy = 0;
	_drawableArea = Common::Rect(_x, _y, _x+_w, _y+_h);

	_scrollBarWidth = g_gui.xmlEval()->getVar("Globals.Scrollbar.Width", 0);

	_scrollBar = new ScrollBarWidget(this, 0, _h - _scrollBarWidth + 1, _w, _scrollBarWidth, true);
	_scrollBar->setTarget(this);

	scrollBarRecalc();
}

int ScrollableCanvasWidget::calcMax() {
	int xmax = 0;
	
	Widget *w = _firstWidget;
	while (w) {
		int x = w->getAbsX() + w->getWidth() - _x + 16; // FIXME: Fix padding to something..
		if (x > xmax)
			xmax = x;
		w = w->next();
	}

	return xmax;
}

void ScrollableCanvasWidget::scrollBarRecalc() {
	_scrollBar->_numEntries = calcMax();
	_scrollBar->_entriesPerPage = (this->getWidth());
	_scrollBar->_currentPos = 0;
	_scrollBar->recalc();
}


void ScrollableCanvasWidget::drawWidget() {
	g_gui.theme()->drawWidgetBackground(Common::Rect(_x, _y, _x+_w, _y+_h), 0, ThemeEngine::kWidgetBackgroundBorder);

	Widget *w = _firstWidget;
	while (w) {
		w->draw();
		w = w->next();
	}
}

void ScrollableCanvasWidget::setFocusWidget(Widget *widget) {
	// The focus will change. Tell the old focused widget (if any)
	// that it lost the focus.
	releaseFocus();

	// Tell the new focused widget (if any) that it just gained the focus.
	if (widget)
		widget->receivedFocus();

	_focusedWidget = widget;
}


void ScrollableCanvasWidget::reflowLayout() {
	Widget::reflowLayout();

	_drawableArea = Common::Rect(_x, _y, _x+_w, _y+_h);
	
	Widget *w = _firstWidget;
	while (w) {
		w->setDrawableArea(_drawableArea);
		w = w->next();
	}

	if (_scrollBar) {
		_scrollBar->setDrawableArea(Common::Rect(0, 0, 0, 0));
		_scrollBar->resize(0, _h - _scrollBarWidth + 1, _w, _scrollBarWidth);
		scrollBarRecalc();
	}
}

void ScrollableCanvasWidget::handleMouseWheel(int x, int y, int direction) {
	_scrollBar->handleScroll(direction, 1);
}

void ScrollableCanvasWidget::handleFingerMoved(int x, int y, int deltax, int deltay, int button) {
	_scrollBar->handleScroll(deltax, 1);
}

void ScrollableCanvasWidget::handleCommand(CommandSender *sender, uint32 cmd, uint32 data) {
	switch (cmd) {
	case kSetScrollOffset:
		if ((int)data > 0 && _scrollPosx >= 0)
			data = 0;
		if ((int)data < 0 && -1*_scrollPosx + this->getWidth() >= _scrollBar->_numEntries)
			data = 0;

		Widget *w = _firstWidget;
		while (w) {
			// Only apply scrolling to items with drawableArea, ignoring scrollbar, bg...
			if (w->hasDrawableArea()) {
				w->setPos((w->getAbsX() - _x) + data, (w->getAbsY() - _y));
			}
			w = w->next();
		}	

		_scrollPosx = _scrollPosx + data;
		drawWidget();
	}
}

void ScrollableCanvasWidget::releaseFocus() {
	if (_focusedWidget) {
		_focusedWidget->lostFocus();
		_focusedWidget = 0;
	}
}

Widget *ScrollableCanvasWidget::findWidget(int x, int y) {
	Widget *w;
	w = findWidgetInChain(_firstWidget, x, y);

	if (w)
		return w;
	else
		return this;
}

} // End of namespace GUI
