import QtQuick 1.1
import com.nokia.meego 1.0
import QtQuick 1.0
import QtMobility.contacts 1.1

Page {
    tools: commonTools
    ListView {
        id: contactList
        anchors.fill: parent
        delegate: Item {
            x: 5
            height: 80
            width: parent.width
            Row {

                id: row1
                spacing: 10
                width: parent.width

                Rectangle {
                    width: 80
                    height: 80
                    Image {
                        anchors.fill: parent
                        source: model.contact.avatar.imageUrl
                    }
                }

                Text {
                    text: model.contact.name.firstName + " " + model.contact.name.lastName
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    font.pixelSize: 25
                }

                Button {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    text: {if (sm.checkIfExists(model.contact.contactId)) return 'delete'; else return 'add'}
                    width: 100
                    onClicked: {
                        var res = sm.toggleShortcut(model.contact.contactId, model.contact.name.firstName + " " + model.contact.name.lastName, model.contact.avatar.imageUrl);
                        if ( res == 1) text = "delete"; else if ( res == 2 ) text = "add"; else text="failed";
                    }
                }

            }
        }
        model: ContactModel {
            sortOrders: [
                SortOrder {
                    detail:ContactDetail.Name
                    field: Name.FirstName
                    direction: Qt.AscendingOrder;
                    blankPolicy: Qt.BlanksLast;
                }
            ]
        }
    }
}
