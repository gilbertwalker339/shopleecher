import QtQuick 2.0
import QtQuick.Controls 2.5
import com.shopleecher.userController 1.0
import "./Components" as Components

Rectangle {
    id: background;
    color: "#2E412B"

    function isValidInput() {
        return Boolean(txtUsername.text) && Boolean(txtPassword.text);
    }

    UserController {
        id: userController;
    }

    Text {
        id: title;
        anchors {
            top: parent.top;
            topMargin: 50;
            horizontalCenter: parent.horizontalCenter;
        }
        text: qsTr("ShopLeecher - Login");
        font {
            bold: true;
            pixelSize: 64;
        }
        color: "white";
    }

    Column {
        id: columnId
        anchors {
            top: title.bottom;
            topMargin: 60;
            horizontalCenter: parent.horizontalCenter;
        }
        spacing: 20;
        width: 600;
        height: 200;

        Label {
            font {
                bold: true;
                pixelSize: 36;
            }
            color: "white";
            text: "Username:"
        }

        Rectangle {
            width: 600;
            height: 45;
            color: "#C4C4C4";

            TextInput {
                id: txtUsername;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                verticalAlignment: Text.AlignVCenter;
                color: "black";
            }
        }

        Label {
            font {
                bold: true;
                pixelSize: 36;
            }
            color: "white";
            text: "Password:"
        }

        Rectangle {
            width: 600;
            height: 45;
            color: "#C4C4C4";

            TextInput {
                id: txtPassword;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                verticalAlignment: Text.AlignVCenter;
                color: "black";
                echoMode: TextInput.Password;
            }
        }
    }

    Components.EasyButton {
        id: btnLogin;
        anchors {
            top: columnId.bottom;
            topMargin: 100;
            horizontalCenter: parent.horizontalCenter;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Login";
        onClicked: {
            if(!isValidInput()) errorPopup.open();
            else {
                if(userController.login(txtUsername.text, txtPassword.text)) {
                    mainLoader.source = "Views/DetailsScreen.qml";
                }
                else {
                    errorPopup.open();
                }
            }
        }
    }

    Components.EasyButton {
        id: btnBack;
        anchors {
            top: btnLogin.bottom;
            topMargin: 40;
            horizontalCenter: parent.horizontalCenter;
        }
        buttonWidth: 280;
        buttonHeight: 70;
        buttonText: "Back";
        onClicked: {
            mainLoader.source = "Views/MainScreen.qml";
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
                id: titleErrorPopup;
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
                text: qsTr("Error your login input");
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
}
