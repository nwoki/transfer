import QtQuick 2.4
import QtQuick.Controls 1.4

import "TransferList"
import "UserList"

TabView {
    id: tabRoot

    width: 300;
    height: 400;

    Tab {
        title: qsTr("Users");

        Item {
            id: userTab;

            ListView {
                id: userList;

                model: userListModel;

                anchors {
                    fill: parent;
                }

                height: parent.height;
                width: parent.width/2;


                delegate:
                    UserDelegate {
                        clientUuid: uuid;
                        clientUserName: userName;
                        clientOnlineStatus: online;

                        height: 30;
                        width: parent.width;
                    }
            }
        }
    }

    Tab {
        title: qsTr("Transfers");

        Item {
            id: transferTab;

            ListView {
                id: transferList;
                model: fileTransferListModel;

                anchors.fill: parent;

                delegate:
                    TransferDelegate {
                        transferFileName: fileName;
                        transferUserName: userName;
                        transferUserUuid: userUuid;

                        height: 30;
                        width: parent.width;
                    }

            }
        }
    }
}
