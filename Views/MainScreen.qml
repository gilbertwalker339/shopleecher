import QtQuick 2.0
import QtQuick.Controls 2.5
import "./Components" as Components

Rectangle {
    id: background;
    color: "#2E412B"

    Text {
        id: title;
        anchors {
            top: parent.top;
            topMargin: 130;
            horizontalCenter: parent.horizontalCenter;
        }
        text: qsTr("ShopLeecher");
        font {
            bold: true;
            pixelSize: 64;
        }
        color: "white";
    }

    Components.EasyButton {
        id: btnLogin;
        anchors {
            top: title.bottom;
            topMargin: 100;
            horizontalCenter: parent.horizontalCenter;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Login";
        onClicked: {
            mainLoader.source = "Views/LoginScreen.qml";
        }
    }

    Components.EasyButton {
        id: btnSettings;
        anchors {
            top: btnLogin.bottom;
            topMargin: 35;
            horizontalCenter: parent.horizontalCenter;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Settings";
        onClicked: {
            mainLoader.source = "Views/SettingsScreen.qml";
        }
    }

    Components.EasyButton {
        id: btnQuit;
        anchors {
            top: btnSettings.bottom;
            topMargin: 35;
            horizontalCenter: parent.horizontalCenter;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Quit";
        onClicked: {
            Qt.quit();
        }
    }
}
