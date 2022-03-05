import QtQuick
import QtQuick.Controls 2.2
import Qt.labs.qmlmodels 1.0

TableView {
    property int selectedRow: 1

     id: tableView
     anchors.fill: parent
     clip: true

     model: TableModel {
         TableModelColumn { display: "name" }
         rows: [ { "name": "Harry" }, { "name": "Hedwig" } ]
     }

     delegate: ItemDelegate {
         implicitWidth: 100
         implicitHeight: 30
         onClicked: selectedRow = row;
         text: display
         highlighted: row == selectedRow;
     }
 }
