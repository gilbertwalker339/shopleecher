import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: easyButton;

    signal clicked();

    property int buttonWidth: 280;
    property int buttonHeight: 70;
    property int buttonRadius: 5;
    property color backgroundColor: "#657559";
    property color textColor: "white";
    property string buttonText: "Default";
    property int textSize: 48;

    width: easyButton.buttonWidth;
    height: easyButton.buttonHeight;
    color: easyButton.backgroundColor;
    radius: easyButton.buttonRadius;

    Text {
        id: textButton;
        anchors.centerIn: parent;
        color: easyButton.textColor;
        font {
            bold: true;
            pixelSize: easyButton.textSize;
        }
        text: easyButton.buttonText;
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            easyButton.clicked();
        }
    }
}
