import QtQuick 2.4

Item {
    id: root;

    property string clientUuid: "";
    property string clientUserName: "";

    OnlineStatusAvatar {
        id: avatar;

        width: 24;
        height: 24;

        anchors {
            left: parent.left;
            leftMargin: 10;
            verticalCenter: parent.verticalCenter;
        }
    }

    Text {
        id: userNameText;
        text: root.clientUserName;
        color: "black";
        smooth: true;

        anchors {
            left: avatar.right;
            leftMargin: 20;
            verticalCenter: parent.verticalCenter;
        }

        font {
            bold: true;
            pixelSize: 16;
        }
    }

    // Check this out. It was causing the listview to show doubles
//     SelectionStatus {
//         id: selectionStatus;
//
// //        selected: root.clientSelected;
//         selected: false;
//
//         width: 25;
//         height: 25;
//
//         anchors {
//             verticalCenter: parent.verticalCenter;
//             right: parent.right;
//             rightMargin: 20;
//         }
//     }

    Rectangle {
        id: seperator;
        height: 1;
        width: (parent.width/3)*2;
        color: "black";

        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter;
        }
    }

    MouseArea {
        id: clickArea;
        anchors.fill: parent;

        // TODO use for selection
//         onClicked: {
//             avatar.online = true;
//         }
    }
}
