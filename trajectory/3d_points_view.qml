/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtDataVisualization 1.0
//! [0]

//! [1]
Rectangle {
    id: mainView
    //! [1]
//    width: 500
//    height: 500

    //! [4]
    Item {
        id: seriesData
        //! [1]
        property alias model: dataModel
        //! [1]

        //! [0]
        ListModel {
            id: dataModel
            objectName: "dataModel"

            function addPoint(x, y, z) {
                dataModel.append({"xPos": x, "yPos": y, "zPos": z});
            }

            function popHead() {
                dataModel.remove(0);
            }

            function reset(){
                dataModel.clear();
            }
        }
    }
    //! [4]
    Item {
        id: seriesData2
        property alias model: envData
        ListModel {
                id: envData
                objectName: "envData"

                function addEnvPoint(x, y, z) {
                    envData.append({"xPos": x, "yPos": y, "zPos": z});
                }

                function popHead() {
                    envData.remove(0);
                }

                function reset(){
                    envData.clear();
                }
        }
    }
    //! [13]
    Theme3D {
        id: themeIsabelle
        type: Theme3D.ThemeIsabelle
        font.family: "Lucida Handwriting"
        font.pointSize: 40
    }

    //! [8]
    //! [9]
    Item {
        id: dataView
        anchors.bottom: parent.bottom
        //! [9]
        width: parent.width
        height: parent.height
        //! [8]

        //! [2]
        Scatter3D {
            id: scatterGraph
            objectName: "scatterGraph"
            width: dataView.width
            height: dataView.height
            //! [2]
            //! [3]
            theme: themeIsabelle
            shadowQuality: AbstractGraph3D.ShadowQualitySoftLow
            //! [3]
            //! [6]
            axisX.segmentCount: 3
            axisX.subSegmentCount: 2
            axisX.labelFormat: "%.2f"
            axisZ.segmentCount: 2
            axisZ.subSegmentCount: 2
            axisZ.labelFormat: "%.2f"
            axisY.segmentCount: 2
            axisY.subSegmentCount: 2
            axisY.labelFormat: "%.2f"
            //! [6]
            //! [5]
            Scatter3DSeries {
                id: scatterSeries
                //! [5]
                //! [10]
                itemLabelFormat: "Series 1: X:@xLabel Y:@yLabel Z:@zLabel"
                //! [10]
                mesh: Abstract3DSeries.MeshPoint
                //! [11]
                ItemModelScatterDataProxy {
                    itemModel: seriesData.model
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }

            Scatter3DSeries{
                id: background
                itemLabelFormat: "Series 2: X:@xLabel Y:@yLabel Z:@zLabel"
                mesh: Abstract3DSeries.MeshPoint

                ItemModelScatterDataProxy{
                    itemModel: seriesData2.model
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
                //! [11]
        }
    }
}
