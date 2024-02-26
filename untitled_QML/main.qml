import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    //Item用于布局及组合其他元素,所有可视化元素的基础对象
    //Row以行的形式排列
    //Rectangle矩形框
    //Text文本
    //image图像
    //MouseArea//鼠标区域

    Item {
        id: name
        Row{             //Row以行的形式排列
            spacing: 10  //设置以下矩形框之间的间距
            Rectangle{   //Rectangle矩形框
                //z:1    //默认是0现在是1就出来了  z代表堆叠次序
                id:rect1
                width: 100
                height: 100
                color: "red"
            }//rect1 end
            //
            Rectangle{
                id:rect2
                width: 100
                height: 100
                color: "blue"
            }//redct2 end
            //
            Rectangle{
                id:rect3
                width: 100
                height: 100
                border.width: 5      //设置边界宽度
                border.color: "red"  //设置边界颜色
                color: "green"
                radius: 50           //设置圆角半径
            }//redct3 end
            //以下为画个圆
            Rectangle{
                id:rect4
                width: 100
                height: width
                radius: width/2    //设置圆角半径
                color: "yellow"
            }//rect4 end

        }//Row end

        //        Rectangle{
        //            z:1  //默认是0现在是1就出来了
        //            id:rect1
        //            width: 100
        //            height: 100
        //            color: "red"
        //        }//rect1
        //        //
        //        Rectangle{
        //            id:rect2
        //            width: 100
        //            height: 100
        //            color: "green"
        //        }//redct2
    }//Item end
/////////////////////////////////////////////////////////
    //text的使用方法
    Item {
        id: name1
        //anchors.centerIn: parent   //将子控件放在父控件中心
        x:0     //位置
        y:100   //位置
        Column  //盒子
        {
            Text {
                id: text1
                text: qsTr("你好哇,李银河")
                color: "#303030"
                font.family: "Ubuntu"
                font.pixelSize: 28
            }//text end
            Text {
                id: text2
                text: qsTr("HelloWorld")
                color: "#303030"
                font.family: "Ubuntu"
                font.pixelSize: 28
            }//text end
        }//Column end
    }//item  end
    ////////////////////////////////////////////////////////////////
    //image的使用方法
    Item {
        id: nam2
        x:0 ;y:180
        Row{  //Row横向排列
             spacing: 5  //设置间距
             Image {
                 id: imag1
                 width: 150
                 height: 250
                 source: "qrc:/image/111.jpg"
             } //image end
             Image {
                 id: imag2
                 width: 150
                 height: 250
                 source: "qrc:/image/222.jpg"
             } //image end
             Image {
                 id: imag3
                 width: 150
                 height: 250
                 source: "qrc:/image/333.jpg"
             } //image end
             Image {
                 id: imag4
                 width: 200
                 height: 250
                 source: "qrc:/image/444.jpg"
             } //image end

        }//Row end

    }//item end



}//window end
