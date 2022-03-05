import QtQuick 2.0
import QtQuick.Controls 2.5
import com.shopleecher.settingsController 1.0
import "./Components" as Components

Rectangle {
    id: background;
    color: "#2E412B"

    function isValidInput() {
        return Boolean(txtDatabaseHostname.text) &&
                Boolean(txtDatabaseName.text) &&
                Boolean(txtDatabasePort) &&
                Boolean(txtDatabaseUsername);
    }

    Component.onCompleted: {
        settingsController.load();
    }

    SettingsController {
        id: settingsController;
    }

    Text {
        id: title;
        anchors { top: parent.top; topMargin: 50; horizontalCenter: parent.horizontalCenter; }
        text: qsTr("ShopLeecher - Settings");
        font { bold: true; pixelSize: 64; }
        color: "white";
    }

    Grid {
        id: grid;
        anchors {
            top: title.bottom;
            topMargin: 50;
            horizontalCenter: parent.horizontalCenter;
        }
        width: 800;
        height: 400;
        columnSpacing: 60;
        rowSpacing: 30;
        columns: 2;
        rows: 7;

        Label {
            id: lbServerFetchXMinutes;
            text: "Server fetch(minutes):";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        SpinBox {
            id: sbServerFetchXMinutes;
            font {
                bold: true;
                pixelSize: 24;
            }
            width: 320;
            height: 30;
            from: 60;
            to: 120;
            value: settingsController.serverFetchXMinutes >= 60 ? settingsController.serverFetchXMinutes : 60;
            editable: true;
        }

        Label {
            id: lbDatabaseRemoveXMinutes;
            text: "Database remove(minutes):";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        SpinBox {
            id: sbDatabaseRemoveXMinutes;
            font {
                bold: true;
                pixelSize: 24;
            }
            width: 320;
            height: 30;
            from: 60;
            to: 120;
            value: settingsController.databaseRemoveRecordXMinutes >= 60 ? settingsController.databaseRemoveRecordXMinutes : 60;
            editable: true;
        }

        Label {
            id: lbDatabaseHostname;
            text: "Database Hostname:";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        Rectangle {
            width: 320;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtDatabaseHostname;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                text: settingsController.databaseHostname;
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
            }
        }

        Label {
            id: lbDatabaseName;
            text: "Database name:";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        Rectangle {
            width: 320;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtDatabaseName;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                text: settingsController.databaseName;
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
            }
        }

        Label {
            id: lbDatabasePort;
            text: "Database port:";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        Rectangle {
            width: 320;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtDatabasePort;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                text: settingsController.databaseHostPort > 0 ? settingsController.databaseHostPort : 3360;
                inputMask: "9999";
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
            }
        }

        Label {
            id: lbDatabaseUsername;
            text: "Database username:";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        Rectangle {
            width: 320;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtDatabaseUsername;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                text: settingsController.databaseUsername;
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
            }
        }

        Label {
            id: lbDatabasePassword;
            text: "Database password:";
            font {
                bold: true;
                pixelSize: 24;
            }
            color: "white";
        }

        Rectangle {
            width: 320;
            height: 30;
            color: "#C4C4C4";
            clip: true;

            TextInput {
                id: txtDatabasePassword;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                text: settingsController.databasePassword;
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
            }
        }
    }

    Popup {
        id: savePopup;
        anchors.centerIn: parent;
        width: 800;
        height: 600;
        modal: true;
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside;

        Rectangle {
            anchors.fill: parent;
            color: "#2E412B";

            Text {
                id: titlePopup;
                anchors {
                    top: parent.top;
                    topMargin: 50;
                    horizontalCenter: parent.horizontalCenter;
                }
                font {
                    bold: true;
                    pixelSize: 48;
                }
                color: "white";
                text: "Settings";
            }

            Grid {
                anchors {
                    top: titlePopup.bottom;
                    topMargin: 30;
                    horizontalCenter: parent.horizontalCenter;
                }
                width: 400;
                height: 500;
                rowSpacing: 20;
                columnSpacing: 20;
                rows: 7;
                columns: 2;

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Server fetch(minutes):"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: sbServerFetchXMinutes.value;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database Remove(minutes):"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: sbDatabaseRemoveXMinutes.value;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database Hostname:"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: txtDatabaseHostname.text;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database name:"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: txtDatabaseName.text;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database port:"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: txtDatabasePort.text;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database Username:"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: txtDatabaseUsername.text;
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: "Database Password:"
                }

                Label {
                    font {
                        bold: true;
                        pixelSize: 18;
                    }
                    color: "white";
                    text: txtDatabasePassword.text;
                }
            }

            Components.EasyButton {
                id: btnSavePopup;
                anchors {
                    bottom: parent.bottom;
                    bottomMargin: 30;
                    right: parent.right;
                    rightMargin: 30;
                }
                buttonWidth: 100;
                buttonHeight: 30;
                textSize: 18;
                buttonText: "Save";
                onClicked: {
                    settingsController.serverFetchXMinutes = sbServerFetchXMinutes.value;
                    settingsController.databaseRemoveRecordXMinutes = sbDatabaseRemoveXMinutes.value;
                    settingsController.databaseHostname = txtDatabaseHostname.text;
                    settingsController.databaseHostPort = txtDatabasePort.text;
                    settingsController.databaseName = txtDatabaseName.text;
                    settingsController.databaseUsername = txtDatabaseUsername.text;
                    settingsController.databasePassword = txtDatabasePassword.text;
                    if(settingsController.save()) {
                        mainLoader.source = "Views/MainScreen.qml";
                    }
                    else {
                        savePopup.close();
                        errorPopup.open();
                    }

                }
            }

            Components.EasyButton {
                anchors {
                    bottom: parent.bottom;
                    bottomMargin: 30;
                    right: btnSavePopup.left;
                    rightMargin: 30;
                }
                buttonWidth: 100;
                buttonHeight: 30;
                textSize: 18;
                buttonText: "Cancel";
                onClicked: {
                    savePopup.close();
                }
            }
        }
    }

    Popup {
        id: errorPopup;
        anchors.centerIn: parent;
        width: 400;
        height: 250;
        modal: true;
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside;

        Rectangle {
            anchors.fill: parent;
            color: "#2E412B";

            Text {
                id: txtTitlePopup;
                anchors {
                    top: parent.top;
                    topMargin: 50;
                    horizontalCenter: parent.horizontalCenter;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "white";
                text: qsTr("Error your settings");
            }

            Text {
                anchors.centerIn: parent;
                font {
                    bold: true;
                    pixelSize: 18;
                }
                color: "white";
                text: "Please check your input!";
            }

            Components.EasyButton {
                anchors {
                    bottom: parent.bottom;
                    bottomMargin: 30;
                    horizontalCenter: parent.horizontalCenter;
                }
                buttonWidth: 100;
                buttonHeight: 30;
                textSize: 18;
                buttonText: "OK";
                onClicked: {
                    errorPopup.close();
                }
            }
        }
    }

    Components.EasyButton {
        id: btnBack;
        anchors {
            bottom: parent.bottom;
            bottomMargin: 30;
            left: parent.left;
            leftMargin: 30;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Back";
        onClicked: {
            mainLoader.source = "Views/MainScreen.qml";
        }
    }

    Components.EasyButton {
        id: btnSave;
        anchors {
            bottom: parent.bottom;
            bottomMargin: 30;
            right: parent.right;
            rightMargin: 30;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Save";
        onClicked: {
            if(isValidInput()) savePopup.open();
            else errorPopup.open();
        }
    }
}
