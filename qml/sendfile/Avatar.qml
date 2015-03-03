import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id: root;

    property string avatarSrc: "";

    Image {
        id: avatar;
        source: root.avatarSrc;
        sourceSize: Qt.size(root.width, root.height);
        smooth: true;

        anchors.centerIn: parent;

        visible: false;
    }

    // Top rounded mask to make the avatar image a circle
    Image {
        id: mask;
        sourceSize: Qt.size(avatar.width, avatar.height);
        source: "qrc:/images/avatar_mask.png";
        visible: false;
        anchors.fill: root;
    }

    OpacityMask {
        id: opMask

        anchors.fill: root;
        source: avatar;
        maskSource: mask;
    }
}
