import QtQuick
import QtQuick.Controls
import QtQuick.Window
import com.shopleecher.settingsController 1.0

ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")

    SettingsController {
        id: settingsController;
    }

    Component.onCompleted: {
        settingsController.load();
    }

    Loader {
        id: mainLoader;
        anchors.fill: parent;
        source: "Views/MainScreen.qml";
    }
}
