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

#ifndef GUI_WIDGETS_GRID_H
#define GUI_WIDGETS_GRID_H

#include "gui/widgets/canvas.h"
#include "common/util.h"
#include "common/system.h"
#include "gui/object.h"

// Included for us to be able to re-use commands used for list-selection
#include "gui/widgets/list.h"

namespace GUI {
// Grid of picbuttons
class GridWidget : public ScrollableCanvasWidget, public CommandSender {
public:
	typedef Common::Array<Common::String> StringArray;
	typedef Common::List<CoverArtWidget> CoverList;
protected:
	uint32			_cmd;

	StringArray		_list;
	StringArray		_dataList;
	StringArray		_imageList;
	
	Common::Array<int>		_listIndex;
	
	int				_padding;
	int				_buttonWidth;
	int				_buttonHeight;

	CoverList		_buttons;
	
	String			_filter;

	int				_selectedItem;
public:
	GridWidget(GuiObject *boss, int x, int y, int w, int h, uint32 cmd = 0);
	GridWidget(GuiObject *boss, const String &name, uint32 cmd = 0);
	
	//void reflowLayout();
	void setGrid(const StringArray &list, const StringArray &listImages);
	void setSelected(int selection);
	void setFilter(const String &filter, bool redraw = true);

	int getSelected();
	
	const StringArray &getList()	const			{ return _dataList; }

	void handleCommand(CommandSender *sender, uint32 cmd, uint32 data);

protected:
	void init();

	void drawWidget();
	void reflowLayout();
};

} // End of namespace GUI

#endif
