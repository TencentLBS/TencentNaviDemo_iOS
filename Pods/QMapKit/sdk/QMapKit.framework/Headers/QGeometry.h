//
//  QGeometry.h
//  QMapKit
//
//  Created by tabsong on 17/5/16.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     *  @brief  定义了以CLLocationDegree为单位的矩形
     *
     *  一单位纬度(latitudeDelta)大约为111公里; 单位经度和纬度相关,一单位经度值(latitudeDelta)赤道时大约是111公里, 到极地为0
     */
    typedef struct {
        CLLocationDegrees latitudeDelta;
        CLLocationDegrees longitudeDelta;
    } QCoordinateSpan;
    
    /**
     *  @brief 定义了地图的某一部份的数据结构
     */
    typedef struct {
        CLLocationCoordinate2D center;
        QCoordinateSpan span;
    } QCoordinateRegion;
    
    /**
     *  @brief  构造QCoordinateSpan类型数据
     *
     *  @param latitudeDelta  纬度值
     *  @param longitudeDelta 经度值
     *
     *  @return 构造的span数据
     */
    static inline QCoordinateSpan QCoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
    {
        return (QCoordinateSpan){latitudeDelta, longitudeDelta};
    }
    
    /**
     *  @brief  构造QCoordinateRegion类型数据
     *
     *  @param centerCoordinate 中心点经纬度坐标
     *  @param span             span大小
     *
     *  @return 构造的region数据
     */
    static inline QCoordinateRegion QCoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, QCoordinateSpan span)
    {
        return (QCoordinateRegion){centerCoordinate, span};
    }
    
    
    /**
     *  @brief  平面投影坐标结构定义
     */
    typedef struct {
        double x;
        double y;
    } QMapPoint;
    
    /**
     *  @brief  平面投影大小结构定义
     */
    typedef struct {
        double width;
        double height;
    } QMapSize;
    
    /**
     *  @brief  平面投影矩形结构定义
     */
    typedef struct {
        QMapPoint origin;
        QMapSize size;
    } QMapRect;
    
    /**
     *  @brief  根据x,y坐标构建QMapPoint
     *
     *  @param x 横轴坐标
     *  @param y 纵轴坐标
     *
     *  @return mapPoint
     */
    static inline QMapPoint QMapPointMake(double x, double y)
    {
        return (QMapPoint){x, y};
    }
    
    /**
     *  @brief  根据长宽构建QMapSize
     *
     *  @param width  宽
     *  @param height 长
     *
     *  @return mapSize
     */
    static inline QMapSize QMapSizeMake(double width, double height)
    {
        return (QMapSize){width, height};
    }
    
    /**
     *  @brief  构建QMapRect
     *
     *  @param x      横轴顶点坐标
     *  @param y      纵轴顶点坐标
     *  @param width  宽
     *  @param height 长
     *
     *  @return mapRect
     */
    static inline QMapRect QMapRectMake(double x, double y, double width, double height)
    {
        return (QMapRect){QMapPointMake(x, y), QMapSizeMake(width, height)};
    }
    
    /**
     *  @brief  获取QMapRect左上点x值
     *
     *  @param rect QMapRect数据
     *
     *  @return 顶点x值
     */
    static inline double QMapRectGetMinX(QMapRect rect)
    {
        return rect.origin.x;
    }
    
    /**
     *  @brief  获取QMapRect左上点y值
     *
     *  @param rect QMapRect数据
     *
     *  @return 顶点y值
     */
    static inline double QMapRectGetMinY(QMapRect rect)
    {
        return rect.origin.y;
    }
    
    /**
     *  @brief  获取QMapRect中心点x值
     *
     *  @param rect QMapRect数据
     *
     *  @return 中心点x值
     */
    static inline double QMapRectGetMidX(QMapRect rect)
    {
        return rect.origin.x + rect.size.width / 2.0;
    }
    
    /**
     *  @brief  获取QMapRect中心点y值
     *
     *  @param rect QMapRect数据
     *
     *  @return 中心点y值
     */
    static inline double QMapRectGetMidY(QMapRect rect)
    {
        return rect.origin.y + rect.size.height / 2.0;
    }
    
    /**
     *  @brief  获取QMapRect右下角x值
     *
     *  @param rect QMapRect数据
     *
     *  @return 右下角x值
     */
    static inline double QMapRectGetMaxX(QMapRect rect)
    {
        return rect.origin.x + rect.size.width;
    }
    
    /**
     *  @brief  获取QMapRect右下角y值
     *
     *  @param rect QMapRect数据
     *
     *  @return 右下角y值
     */
    static inline double QMapRectGetMaxY(QMapRect rect)
    {
        return rect.origin.y + rect.size.height;
    }
    
    /**
     *  @brief  获取QMapRect宽度
     *
     *  @param rect QMapRect数据
     *
     *  @return 宽度值
     */
    static inline double QMapRectGetWidth(QMapRect rect)
    {
        return rect.size.width;
    }
    
    /**
     *  @brief  获取QMapRect长度度
     *
     *  @param rect QMapRect数据
     *
     *  @return 长度值
     */
    static inline double QMapRectGetHeight(QMapRect rect)
    {
        return rect.size.height;
    }
    
    /**
     *  @brief  比较两个QMapPoint x, y值是否同时相等
     *
     *  @param point1 第一个点
     *  @param point2 第二个点
     *
     *  @return 是否相等
     */
    static inline BOOL QMapPointEqualToPoint(QMapPoint point1, QMapPoint point2) {
        return point1.x == point2.x && point1.y == point2.y;
    }
    
    /**
     *  @brief  判断两个QMapSize是否相等
     *
     *  @param size1 QMapSize1
     *  @param size2 QMapSize2
     *
     *  @return 是否相等
     */
    static inline BOOL QMapSizeEqualToSize(QMapSize size1, QMapSize size2) {
        return size1.width == size2.width && size1.height == size2.height;
    }
    
    /**
     *  @brief  判断两个QMapRect是否相等
     *
     *  @param rect1 QMapRect1
     *  @param rect2 QMapRect2
     *
     *  @return 是否相等
     */
    static inline BOOL QMapRectEqualToRect(QMapRect rect1, QMapRect rect2) {
        return
        QMapPointEqualToPoint(rect1.origin, rect2.origin) &&
        QMapSizeEqualToSize(rect1.size, rect2.size);
    }
    
    /**
     *  @brief  判断QMapRect是否为NULL, x或y为无穷小是返回YES
     *
     *  @param rect QMapRect
     *
     *  @return 是否为NULL
     */
    static inline BOOL QMapRectIsNull(QMapRect rect) {
        return isinf(rect.origin.x) || isinf(rect.origin.y);
    }
    
    /**
     *  @brief  判断QMapRect是否为空
     *
     *  @param rect QMapRect
     *
     *  @return 是否为空
     */
    static inline BOOL QMapRectIsEmpty(QMapRect rect) {
        return QMapRectIsNull(rect) || (rect.size.width == 0.0 && rect.size.height == 0.0);
    }
    
    /**
     *  @brief  判断点是否在矩形内
     *
     *  @param rect  矩形
     *  @param point 点
     *
     *  @return 是否在内
     */
    extern BOOL QMapRectContainsPoint(QMapRect rect, QMapPoint point);
    
    /**
     * @brief   计算矩形和点的并集
     *
     *  @param rect1 矩形
     *  @param point 点
     *
     *  @return 矩形
     */
    QMapRect QMapRectUnionPoint(QMapRect rect1, QMapPoint point);
    
    /**
     *  @brief  返回两个矩形的并集
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 并集
     */
    extern QMapRect QMapRectUnion(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief  判断两个矩形是否相交
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 是否相交
     */
    extern BOOL QMapRectIntersectsRect(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief  判断rect1是否包含rect2
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 是否包含
     */
    extern BOOL QMapRectContainsRect(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief  格式化输出QMapPoint类型数据
     *
     *  @param point QMapPoint
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapPoint(QMapPoint point) {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", point.x, point.y];
    }
    
    /**
     *  @brief  格式化输出QMapSize类型数据
     *
     *  @param size QMapSize
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapSize(QMapSize size) {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", size.width, size.height];
    }
    
    /**
     *  @brief  格式化输出QMapRect类型数据
     *
     *  @param rect QMapRect
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapRect(QMapRect rect) {
        return [NSString stringWithFormat:@"{%@, %@}", QStringFromMapPoint(rect.origin), QStringFromMapSize(rect.size)];
    }
    
    
    /**
     *  @brief  经纬度坐标转平面投影坐标
     *
     *  @param coordinate 要转化的经纬度坐标
     *
     *  @return 平面投影坐标
     */
    extern QMapPoint QMapPointForCoordinate(CLLocationCoordinate2D coordinate);
    
    /**
     *  @brief  平面投影坐标转经纬度坐标
     *
     *  @param mapPoint 要转化的平面投影矩形
     *
     *  @return 经纬度坐标
     */
    extern CLLocationCoordinate2D QCoordinateForMapPoint(QMapPoint mapPoint);
    
    /**
     *  @brief  平面投影矩形转region
     *
     *  @param rect 要转化的平面投影矩形
     *
     *  @return region
     */
    extern QCoordinateRegion QCoordinateRegionForMapRect(QMapRect rect);
    
    /**
     *  @brief  region转平面投影矩形
     *
     *  @param region 要转化的region
     *
     *  @return 平面投影矩形
     */
    extern QMapRect QMapRectForCoordinateRegion(QCoordinateRegion region);
    
    /**
     *  @brief  在特定纬度单位mapPoint代表的距离, 单位:米
     *
     *  @param latitude 纬度参数
     *
     *  @return 距离大小
     */
    extern CLLocationDistance QMetersPerMapPointAtLatitude(CLLocationDegrees latitude);
    
    /**
     *  @brief  在特定纬度每米代表的mapPoint值
     *
     *  @param latitude 纬度参数
     *
     *  @return mapPoint个数
     */
    extern double QMapPointsPerMeterAtLatitude(CLLocationDegrees latitude);
    
    /**
     *  @brief  生成一个新的QCoordinateRegion
     *
     *  @param centerCoordinate   中心点坐标
     *  @param latitudinalMeters  垂直跨度(单位 米)
     *  @param longitudinalMeters 水平跨度(单位 米)
     *
     *  @return QCoordinateRegion
     */
    static inline QCoordinateRegion QCoordinateRegionMakeWithDistance(CLLocationCoordinate2D centerCoordinate, CLLocationDistance latitudinalMeters, CLLocationDistance longitudinalMeters)
    {
        QMapSize spanSize = QMapSizeMake(QMapPointsPerMeterAtLatitude(centerCoordinate.latitude) * latitudinalMeters, QMapPointsPerMeterAtLatitude(centerCoordinate.latitude) * longitudinalMeters);
        
        QMapPoint center       = QMapPointForCoordinate(centerCoordinate);
        QMapPoint leftTop      = QMapPointMake(center.x - spanSize.width / 2.0, center.y - spanSize.height / 2.0);
        QMapPoint rightBottom  = QMapPointMake(center.x + spanSize.width / 2.0, center.y + spanSize.height / 2.0);
        
        CLLocationCoordinate2D leftTopCoordinate     = QCoordinateForMapPoint(leftTop);
        CLLocationCoordinate2D rightBottomCoordinate = QCoordinateForMapPoint(rightBottom);
        
        return QCoordinateRegionMake(centerCoordinate,
                                     QCoordinateSpanMake(fabs(leftTopCoordinate.latitude - rightBottomCoordinate.latitude),
                                                         fabs(leftTopCoordinate.longitude - rightBottomCoordinate.longitude)));
    }
    
    /**
     *  @brief 判断点是否在多边形内部
     *
     *  @param point   点
     *  @param polygon 多边形端点
     *  @param count   多边形端点个数
     *
     *  @return 是否在内
     */
    extern BOOL QPolygonContainsPoint(QMapPoint point, QMapPoint *polygon, NSUInteger count);
    
    /**
     *  @brief 判断点是否在多边形内
     *  @param coordinate 经纬度点
     *  @param polygon    多边形端点
     *  @param count      多边形端点个数
     *  @return 是否在内
     */
    extern BOOL QPolygonContainsCoordinate(CLLocationCoordinate2D coordinate, CLLocationCoordinate2D *polygon, NSUInteger count);
    
    /**
     *  @brief  返回两个QapPoint之间的距离 单位:米
     *
     *  @param a 点a
     *  @param b 点b
     *
     *  @return 距离值
     */
    extern CLLocationDistance QMetersBetweenMapPoints(QMapPoint a, QMapPoint b);
    
    /**
     *  @brief  返回两个经纬度之间的距离 单位:米
     *
     *  @param a 点a
     *  @param b 点b
     *
     *  @return 距离值
     */
    extern CLLocationDistance QMetersBetweenCoordinates(CLLocationCoordinate2D a, CLLocationCoordinate2D b);
    
    /**
     *  @brief  返回最小外接矩形.
     *
     *  @param points 点数组
     *  @param count  点个数
     *
     *  @return 最小外接矩形
     */
    extern QMapRect QBoundingMapRectWithPoints(QMapPoint *points, NSUInteger count);
    
    /**
     *  @brief  根据中心点构建最小外接矩形.
     *
     *  @param points      点数组
     *  @param count       点个数
     *  @param centerPoint 中心点
     *
     *  @return 最小外接矩形
     */
    extern QMapRect QBoundingMapRectWithPointsAndCenter(QMapPoint *points, NSUInteger count, QMapPoint centerPoint);
    
    
#ifdef __cplusplus
}
#endif

