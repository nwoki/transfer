import QtQuick 2.4


Item {
    id: root;

    property string transferFileName;
    property string transferUserName;
    property string transferUserUuid;

    Text {
        text: "<b>" + root.transferFileName + "</b> from <b>" + root.transferUserName + "</b>";
        color: "black";
        smooth: true;
        verticalAlignment: Text.AlignVCenter

        anchors {
            left: parent.left;
            leftMargin: 10;
            verticalCenter: parent.verticalCenter;
        }
    }

    // TODO accept decline buttons (USE ICONS! NOT TEXT)
}
