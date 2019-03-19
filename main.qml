import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: anchoredRectangle
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter // or, for example: anchors.right: parent.right


        width: parent.width * 0.8
        height: parent.height * 0.8

        border.color: "black"
        border.width: 2
        radius: 5

        Grid {
            id: mainTableGrid
            rows: 6
            columns: 7
            spacing: 5

            anchors.fill: parent

            //anchors.margins: (width - (spacing * (columns - 1)) - (elemWidth * columns)) / 4
            anchors.margins: 5

            property int elemWidth: (width - (spacing * (columns - 1))) / columns
            property int elemHeight: (height - (spacing * (rows - 1))) / rows


            Repeater {
                model: parent.rows * parent.columns
                Rectangle
                {
                    width: mainTableGrid.elemWidth    //parent.width/7
                    height: mainTableGrid.elemHeight  //parent.height/6

                    color: "lightgreen"

                    Text {
                        text: index
                        font.pointSize: 30
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("index ", index)
                        }
                    }
                }
            }
        }
    }
}
