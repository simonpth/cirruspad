/*
    Copyright 2026, Simon Thal

    This file is part of CirrusPad.

    CirrusPad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CirrusPad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CirrusPad. If not, see <http://www.gnu.org/licenses/>.
*/
import QtQuick
import QtQuick.Controls
import cirruspad

SplitView {
    id: root
    anchors.fill: parent

    Sidebar {
        SplitView.preferredWidth: root.width * 0.2
        SplitView.minimumWidth: 150
        SplitView.maximumWidth: 400

        onFileSelected: function (index) {
            workspace.openFile(index);
        }
    }

    Workspace {
        id: workspace
        SplitView.fillWidth: true
    }
}
