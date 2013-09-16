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

#include "gui/widget.h"
#include "gui/widgets/grid.h"
#include "gui/widgets/canvas.h"
#include "common/str-array.h"

#include "common/tokenizer.h"
#include "gui/gui-manager.h"

namespace GUI {

enum {
	kSelectCover = 'SELC'
};

GridWidget::GridWidget(GuiObject *boss, const Common::String &name, uint32 cmd)
	: ScrollableCanvasWidget(boss, name), CommandSender(boss), _cmd(cmd) {

	init();
}

GridWidget::GridWidget(GuiObject *boss, int x, int y, int w, int h, uint32 cmd)
	: ScrollableCanvasWidget(boss, x, y, w, h), CommandSender(boss), _cmd(cmd) {

	init();
}

void GridWidget::init() {
	_padding = 16;
	_buttonWidth = 96;
	_buttonHeight = 128;
		
	char * imageName = "nocover_2x.bmp";
	g_gui.theme()->addBitmap(imageName);
}

void GridWidget::setGrid(const StringArray &list, const StringArray &listImages) {
	assert(list.size() == listImages.size());

	_dataList = list;
	_list = list;
	_imageList = listImages;

	// Set drawableArea
	ScrollableCanvasWidget::init();
}

void GridWidget::setSelected(int selection) {
	for (CoverList::iterator button = _buttons.begin(); button != _buttons.end(); ++button) {
		if (selection == button->number()) {
			button->setSelected(true);
			button->setFlags(WIDGET_BORDER);
		} else {
			button->setSelected(false);
			button->clearFlags(WIDGET_BORDER);
		}
	}

	_selectedItem = selection;
	sendCommand(kListSelectionChangedCmd, _selectedItem);
	
	this->draw();
}

void GridWidget::setFilter(const String &filter, bool redraw) {
	String filt = filter;
	filt.toLowercase();
	
	_filter = filt;

	if (_filter.empty()) {
		// No filter -> display everything
		_list = _dataList;
		_listIndex.clear();
	} else {
		// Restrict the list to everything which contains all words in _filter
		// as substrings, ignoring case.

		Common::StringTokenizer tok(_filter);
		String tmp;
		int n = 0;

		_list.clear();
		_listIndex.clear();

		for (StringArray::iterator i = _dataList.begin(); i != _dataList.end(); ++i, ++n) {
			tmp = *i;
			tmp.toLowercase();
			bool matches = true;
			tok.reset();
			while (!tok.empty()) {
				if (!tmp.contains(tok.nextToken())) {
					matches = false;
					break;
				}
			}

			if (matches) {
				_list.push_back(*i);
				_listIndex.push_back(n);
			}
		}
	}

	_scrollPosx = 0;
	_scrollPosy = 0;
	_selectedItem = -1;
	setSelected(_selectedItem);

	// Destroy previous buttons, and redraw
	Widget *w = _firstWidget;
	while (w) {
		Widget *del_next = w->next();
		// Only delete objects that are supposed to be moved (i.e. buttons)
		if (w->hasDrawableArea()) {
			w->setNext(NULL);
			removeWidget(w);
		}
		w = del_next;
	}

	for (uint i = 0; i < _list.size(); i++) {
		const char *tooltip = _list[i].c_str();
		CoverArtWidget *button = new CoverArtWidget(this, (_padding * (i + 1)) + (_buttonWidth * i), _padding, _buttonWidth, _buttonHeight, tooltip, i, kSelectCover); 

		char * imageName = "nocover_2x.bmp";
		button->setGfx(g_gui.theme()->getImageSurface(imageName));
		button->setDrawableArea(_drawableArea);
		_buttons.push_back(*button);
	}
	
	scrollBarRecalc();
	this->drawWidget();
}

int GridWidget::getSelected() {
	for (CoverList::iterator button = _buttons.begin(); button != _buttons.end(); ++button) {
		if (button->selected()) {
			return button->number();
		}
	}

	return -1;
}

void GridWidget::drawWidget() {
	ScrollableCanvasWidget::drawWidget();
}

void GridWidget::reflowLayout() {
	ScrollableCanvasWidget::reflowLayout();
}

void GridWidget::handleCommand(CommandSender *sender, uint32 cmd, uint32 data) {
	switch (cmd) {
	case kSelectCover:
		setSelected(data);
		break;
	// From canvas
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

} // End of namespace GUI
