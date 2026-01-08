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

Item {
    id: root
    property var modelIndex

    TextArea {
        id: textArea
        anchors.fill: parent
        anchors.margins: 10
        // We bind the text to the model's ContentRole
        // Since we can't easily two-way bind to a model function result without a proxy,
        // we'll fetch on change and save on change.

        text: root.modelIndex && root.modelIndex.valid ? MainController.fileSystemModel.data(root.modelIndex, FileSystemModel.ContentRole) : ""

        // Save changes back to model?
        // We need a setData implementation C++ side for ContentRole
        onEditingFinished: {
            MainController.fileSystemModel.setData(root.modelIndex, text, FileSystemModel.ContentRole);
        }
    }
}
