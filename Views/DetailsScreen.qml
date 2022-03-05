import QtQuick
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels 1.0
import com.shopleecher.detailsController 1.0
import "./Components" as Components

Rectangle {
    id: background;
    color: "#2E412B"

    Component.onCompleted: {
        detailsController.fetchServerData(cbxShop.currentValue, cbxCategories.currentValue);
    }

    Connections {
        target: detailsController;
        function onFinished(jsonArrayData) {
            detailsModel.rows = jsonArrayData;
        }
    }

    DetailsController {
        id: detailsController;
    }

    Text {
        id: title;
        anchors {
            top: parent.top;
            topMargin: 25;
            horizontalCenter: parent.horizontalCenter;
        }
        text: qsTr("ShopLeecher - Details");
        font {
            bold: true;
            pixelSize: 64;
        }
        color: "white";
    }

    Row {
        id: rowId;
        anchors {
            top: title.bottom;
            topMargin: 35;
            horizontalCenter: parent.horizontalCenter;
        }

        spacing: 30;

        Label {
            id: lbShop;
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
            text: "Shop name"
        }

        ComboBox {
            id: cbxShop;
            width: 200;
            height: 40;
            model: ListModel {
                ListElement { name: "TheGioiDiDong" }
                ListElement { name: "FPT" }
            }
            textRole: "name";
        }

        Label {
            id: lbCategories;
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
            text: "Categories"
        }

        ComboBox {
            id: cbxCategories;
            width: 200;
            height: 40;
            model: detailsController.categories();
        }

        Components.EasyButton {
            id: btnFetchDatabase;
            buttonWidth: 150;
            buttonHeight: 35;
            buttonText: "Fetch Database";
            textSize: 18;
            onClicked: {
                detailsController.fetchDatabaseData(cbxShop.currentValue, cbxCategories.currentValue);
                detailsTable.selectedRow = -1;
                txtName.text = "";
                txtPrice.text = "";
                txtScreen.text = "";
                txtCPU.text = "";
                txtRAM.text = "";
                txtCamera.text = "";
                txtPIN.text = "";
            }
        }

        Components.EasyButton {
            id: btnFetchOnline;
            buttonWidth: 150;
            buttonHeight: 35;
            buttonText: "Fetch Online";
            textSize: 18;
            onClicked: {
                detailsController.fetchServerData(cbxShop.currentValue, cbxCategories.currentValue);
                detailsTable.selectedRow = -1;
                txtName.text = "";
                txtPrice.text = "";
                txtScreen.text = "";
                txtCPU.text = "";
                txtRAM.text = "";
                txtCamera.text = "";
                txtPIN.text = "";
            }
        }
    }

    TableView {
        property int selectedRow: -1;

        id: detailsTable;
        width: 800;
        height: 480;
        anchors {
            top: rowId.bottom;
            topMargin: 30;
            left: parent.left;
            leftMargin: 30;
        }
        clip: true;
        boundsBehavior: Flickable.StopAtBounds;
        model: TableModel {
            id: detailsModel;
            TableModelColumn { display: "id" }
            TableModelColumn { display: "name" }
            TableModelColumn { display: "price" }
            TableModelColumn { display: "screen" }
            TableModelColumn { display: "cpu" }
            TableModelColumn { display: "ram" }
            TableModelColumn { display: "camera" }
            TableModelColumn { display: "pin" }

            rows: [
//                { id: 1000, name: "iPhone 6", price: 1000000, screen: "6 inches", cpu: "A5", ram: "5GB", camera: "1px * 2px", pin: "1000mhA" },
            ]
        }
        delegate: ItemDelegate {
            text: model.display;
            font.pixelSize: 13;
            padding: 20;
            onClicked: {
                detailsTable.selectedRow = row;
                txtName.text = detailsModel.getRow(row).name;
                txtPrice.text = detailsModel.getRow(row).price;
                txtScreen.text = detailsModel.getRow(row).screen;
                txtCPU.text = detailsModel.getRow(row).cpu;
                txtRAM.text = detailsModel.getRow(row).ram;
                txtCamera.text = detailsModel.getRow(row).camera;
                txtPIN.text = detailsModel.getRow(row).pin;
            }
            highlighted: detailsTable.selectedRow === row;
            background: Rectangle {
                anchors.fill: parent;
                color: highlighted ? "lightblue" : "#657559";
                border.width: 1;
            }
        }
    }

    Grid {
        id: gridId;
        anchors {
            top: detailsTable.top;
            right: parent.right;
            rightMargin: 25;
        }
        width: 400;
        height: 350;
        columns: 2;
        rows: 7;
        columnSpacing: 15;
        rowSpacing: 20;

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "Name";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtName;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "Price";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtPrice;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "Screen";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtScreen;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "CPU";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtCPU;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "RAM";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtRAM;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "Camera";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtCamera;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 24;
            }
            text: "PIN";
            color: "white";
        }

        Rectangle {
            width: 300;
            height: 30;
            color: "#C4C4C4";

            TextInput {
                id: txtPIN;
                anchors {
                    fill: parent;
                    leftMargin: 15;
                    rightMargin: 15;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: enabled ? "black" : "gray";
                enabled: false;
            }
        }
    }

    Components.EasyButton {
        id: btnEdit;
        anchors {
            top: gridId.bottom;
            topMargin: 15;
            left: gridId.left;
        }
        buttonWidth: gridId.width / 2 - 5;
        buttonHeight: 40;
        buttonText: "Edit";
        textSize: 24;
        onClicked: {
            txtName.enabled = true;
            txtPrice.enabled = true;
            txtScreen.enabled = true;
            txtCPU.enabled = true;
            txtRAM.enabled = true;
            txtCamera.enabled = true;
            txtPIN.enabled = true;
        }
    }

    Components.EasyButton {
        id: btnSave;
        anchors {
            top: gridId.bottom;
            topMargin: 15;
            right: gridId.right;
        }
        buttonWidth: gridId.width / 2 -5;
        buttonHeight: 40;
        buttonText: "Save";
        textSize: 24;
        onClicked: {
            var data = [detailsModel.getRow(detailsTable.selectedRow).id, txtName.text, txtPrice.text, txtScreen.text, txtCPU.text, txtRAM.text, txtCamera.text, txtPIN.text];
            detailsController.saveEditedShopRecord(cbxShop.currentValue, cbxCategories.currentValue, data);
            detailsController.fetchDatabaseData(cbxShop.currentValue, cbxCategories.currentValue);
            //detailsTable.selectedRow = -1;

            txtName.enabled = false;
            txtPrice.enabled = false;
            txtScreen.enabled = false;
            txtCPU.enabled = false;
            txtRAM.enabled = false;
            txtCamera.enabled = false;
            txtPIN.enabled = false;
        }
    }

    Components.EasyButton {
        id: btnDelete;
        anchors {
            top: btnSave.bottom;
            topMargin: 15;
            right: gridId.right;
        }
        buttonWidth: gridId.width;
        buttonHeight: 40;
        buttonText: "Delete this product";
        textSize: 24;
        onClicked: {
            detailsController.removeShopRecord(cbxShop.currentValue, cbxCategories.currentValue, detailsModel.getRow(detailsTable.selectedRow).id);
            detailsController.fetchDatabaseData(cbxShop.currentValue, cbxCategories.currentValue);
            detailsTable.selectedRow = -1;

            txtName.enabled = false;
            txtPrice.enabled = false;
            txtScreen.enabled = false;
            txtCPU.enabled = false;
            txtRAM.enabled = false;
            txtCamera.enabled = false;
            txtPIN.enabled = false;

            txtName.text = "";
            txtPrice.text = "";
            txtScreen.text = "";
            txtCPU.text = "";
            txtRAM.text = "";
            txtCamera.text = "";
            txtPIN.text = "";
        }
    }

//    Components.EasyButton {
//        id: btnBack;
//        anchors {
//            top: btnLogin.bottom;
//            topMargin: 40;
//            horizontalCenter: parent.horizontalCenter;
//        }
//        buttonWidth: 280;
//        buttonHeight: 70;
//        buttonText: "Back";
//        onClicked: {
//            mainLoader.source = "Views/MainScreen.qml";
//        }
//    }

}
