//
//  QGeometry.h
//  QMapKit
//
//  Created by tabsong on 17/5/16.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     *  @brief 定义了以 CLLocationDegree 为单位的矩形
     *
     *  一单位纬度 (latitudeDelta) 大约为111公里; 单位经度和纬度相关, 一单位经度值 (latitudeDelta) 赤道时大约是111公里, 到极地为0
     */
    typedef struct
    {
        CLLocationDegrees latitudeDelta;
        CLLocationDegrees longitudeDelta;
    } QCoordinateSpan;
    
    /**
     *  @brief 定义了地图的某一部份的数据结构
     */
    typedef struct
    {
        CLLocationCoordinate2D center;
        QCoordinateSpan span;
    } QCoordinateRegion;
    
    /**
     *  @brief 构造 QCoordinateSpan 类型数据
     *
     *  @param latitudeDelta  纬度值
     *  @param longitudeDelta 经度值
     *
     *  @return 构造的 span 数据
     */
    static inline QCoordinateSpan QCoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
    {
        return (QCoordinateSpan){latitudeDelta, longitudeDelta};
    }
    
    /**
     *  @brief 构造 QCoordinateRegion 类型数据
     *
     *  @param centerCoordinate 中心点经纬度坐标
     *  @param span             span 大小
     *
     *  @return 构造的 region 数据
     */
    static inline QCoordinateRegion QCoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, QCoordinateSpan span)
    {
        return (QCoordinateRegion){centerCoordinate, span};
    }
    
    
    /**
     *  @brief 平面投影坐标结构定义
     */
    typedef struct
    {
        double x;
        double y;
    } QMapPoint;
    
    /**
     *  @brief 平面投影大小结构定义
     */
    typedef struct
    {
        double width;
        double height;
    } QMapSize;
    
    /**
     *  @brief 平面投影矩形结构定义
     */
    typedef struct
    {
        QMapPoint origin;
        QMapSize size;
    } QMapRect;
    
    /**
     *  @brief 为空的平面投影矩形
     */
    extern const QMapRect QMapRectNull;
    
    /**
     *  @brief 根据 x, y 坐标构建 QMapPoint
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
     *  @brief 根据长宽构建 QMapSize
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
     *  @brief 构建 QMapRect
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
     *  @brief 获取 QMapRect 左上点 x 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 顶点 x 值
     */
    static inline double QMapRectGetMinX(QMapRect rect)
    {
        return rect.origin.x;
    }
    
    /**
     *  @brief 获取 QMapRect 左上点 y 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 顶点 y 值
     */
    static inline double QMapRectGetMinY(QMapRect rect)
    {
        return rect.origin.y;
    }
    
    /**
     *  @brief 获取 QMapRect 中心点 x 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 中心点 x 值
     */
    static inline double QMapRectGetMidX(QMapRect rect)
    {
        return rect.origin.x + rect.size.width / 2.0;
    }
    
    /**
     *  @brief 获取 QMapRect 中心点 y 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 中心点 y 值
     */
    static inline double QMapRectGetMidY(QMapRect rect)
    {
        return rect.origin.y + rect.size.height / 2.0;
    }
    
    /**
     *  @brief 获取 QMapRect 右下角 x 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 右下角 x 值
     */
    static inline double QMapRectGetMaxX(QMapRect rect)
    {
        return rect.origin.x + rect.size.width;
    }
    
    /**
     *  @brief 获取 QMapRect 右下角 y 值
     *
     *  @param rect QMapRect 数据
     *
     *  @return 右下角 y 值
     */
    static inline double QMapRectGetMaxY(QMapRect rect)
    {
        return rect.origin.y + rect.size.height;
    }
    
    /**
     *  @brief 获取 QMapRect 宽度
     *
     *  @param rect QMapRect 数据
     *
     *  @return 宽度值
     */
    static inline double QMapRectGetWidth(QMapRect rect)
    {
        return rect.size.width;
    }
    
    /**
     *  @brief 获取 QMapRect 长度
     *
     *  @param rect QMapRect 数据
     *
     *  @return 长度值
     */
    static inline double QMapRectGetHeight(QMapRect rect)
    {
        return rect.size.height;
    }
    
    /**
     *  @brief 比较两个 QMapPoint x, y 值是否同时相等
     *
     *  @param point1 第一个点
     *  @param point2 第二个点
     *
     *  @return 是否相等
     */
    static inline BOOL QMapPointEqualToPoint(QMapPoint point1, QMapPoint point2)
    {
        return point1.x == point2.x && point1.y == point2.y;
    }
    
    /**
     *  @brief 判断两个 QMapSize 是否相等
     *
     *  @param size1 QMapSize1
     *  @param size2 QMapSize2
     *
     *  @return 是否相等
     */
    static inline BOOL QMapSizeEqualToSize(QMapSize size1, QMapSize size2)
    {
        return size1.width == size2.width && size1.height == size2.height;
    }
    
    /**
     *  @brief 判断两个 QMapRect 是否相等
     *
     *  @param rect1 QMapRect1
     *  @param rect2 QMapRect2
     *
     *  @return 是否相等
     */
    static inline BOOL QMapRectEqualToRect(QMapRect rect1, QMapRect rect2)
    {
        return
        QMapPointEqualToPoint(rect1.origin, rect2.origin) &&
        QMapSizeEqualToSize(rect1.size, rect2.size);
    }
    
    /**
     *  @brief 判断 QMapRect 是否为 NULL
     *
     *  @param rect QMapRect
     *
     *  @return 是否为 NULL
     */
    static inline BOOL QMapRectIsNull(QMapRect rect)
    {
        return QMapPointEqualToPoint(rect.origin, QMapRectNull.origin);
    }
    
    /**
     *  @brief 判断 QMapRect 是否为空
     *
     *  @param rect QMapRect
     *
     *  @return 是否为空
     */
    static inline BOOL QMapRectIsEmpty(QMapRect rect)
    {
        return QMapRectIsNull(rect) || (rect.size.width == 0.0 && rect.size.height == 0.0);
    }
    
    /**
     *  @brief 判断点是否在矩形内
     *
     *  @param rect  矩形
     *  @param point 点
     *
     *  @return 是否在内
     */
    extern BOOL QMapRectContainsPoint(QMapRect rect, QMapPoint point);
    
    /**
     * @brief 计算矩形和点的并集
     *
     *  @param rect  矩形
     *  @param point 点
     *
     *  @return 矩形
     */
    extern QMapRect QMapRectUnionPoint(QMapRect rect, QMapPoint point);
    
    /**
     *  @brief 返回两个矩形的并集
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 并集
     */
    extern QMapRect QMapRectUnion(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief 判断两个矩形是否相交
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 是否相交
     */
    extern BOOL QMapRectIntersectsRect(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief 判断 rect1 是否包含 rect2
     *
     *  @param rect1 矩形1
     *  @param rect2 矩形2
     *
     *  @return 是否包含
     */
    extern BOOL QMapRectContainsRect(QMapRect rect1, QMapRect rect2);
    
    /**
     *  @brief 格式化输出 QMapPoint 类型数据
     *
     *  @param point QMapPoint
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapPoint(QMapPoint point)
    {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", point.x, point.y];
    }
    
    /**
     *  @brief 格式化输出 QMapSize 类型数据
     *
     *  @param size QMapSize
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapSize(QMapSize size)
    {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", size.width, size.height];
    }
    
    /**
     *  @brief 格式化输出 QMapRect 类型数据
     *
     *  @param rect QMapRect
     *
     *  @return 格式化后的字符串
     */
    static inline NSString *QStringFromMapRect(QMapRect rect)
    {
        return [NSString stringWithFormat:@"{%@, %@}", QStringFromMapPoint(rect.origin), QStringFromMapSize(rect.size)];
    }
    
    
    /**
     *  @brief 经纬度坐标转平面投影坐标
     *
     *  @param coordinate 要转化的经纬度坐标
     *
     *  @return 平面投影坐标
     */
    extern QMapPoint QMapPointForCoordinate(CLLocationCoordinate2D coordinate);
    
    /**
     *  @brief 平面投影坐标转经纬度坐标
     *
     *  @param mapPoint 要转化的平面投影坐标
     *
     *  @return 经纬度坐标
     */
    extern CLLocationCoordinate2D QCoordinateForMapPoint(QMapPoint mapPoint);
    
    /**
     *  @brief 平面投影矩形转 region
     *
     *  @param rect 要转化的平面投影矩形
     *
     *  @return region
     */
    extern QCoordinateRegion QCoordinateRegionForMapRect(QMapRect rect);
    
    /**
     *  @brief region 转平面投影矩形
     *
     *  @param region 要转化的region
     *
     *  @return 平面投影矩形
     */
    extern QMapRect QMapRectForCoordinateRegion(QCoordinateRegion region);
    
    /**
     *  @brief 在特定纬度单位 mapPoint 代表的距离, 单位:米
     *
     *  @param latitude 纬度参数
     *
     *  @return 距离大小
     */
    extern CLLocationDistance QMetersPerMapPointAtLatitude(CLLocationDegrees latitude);
    
    /**
     *  @brief 在特定纬度每米代表的 mapPoint 值
     *
     *  @param latitude 纬度参数
     *
     *  @return mapPoint 个数
     */
    extern double QMapPointsPerMeterAtLatitude(CLLocationDegrees latitude);
    
    /**
     *  @brief  生成一个新的 QCoordinateRegion
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
     *  @brief 返回两个 QMapPoint 之间的距离, 单位:米
     *
     *  @param a 点 a
     *  @param b 点 b
     *
     *  @return 距离值
     */
    extern CLLocationDistance QMetersBetweenMapPoints(QMapPoint a, QMapPoint b);
    
    /**
     *  @brief 返回两个经纬度之间的距离, 单位:米
     *
     *  @param a 点 a
     *  @param b 点 b
     *
     *  @return 距离值
     */
    extern CLLocationDistance QMetersBetweenCoordinates(CLLocationCoordinate2D a, CLLocationCoordinate2D b);
    
    /**
     *  @brief 返回最小外接平面投影矩形.
     *
     *  @param points 点数组
     *  @param count  点个数
     *
     *  @return 最小外接平面投影矩形
     */
    extern QMapRect QBoundingMapRectWithPoints(QMapPoint *points, NSUInteger count);
    
    /**
     *  @brief 根据中心点构建最小外接平面投影矩形.
     *
     *  @param points      点数组
     *  @param count       点个数
     *  @param centerPoint 中心点
     *
     *  @return 最小外接平面投影矩形
     */
    extern QMapRect QBoundingMapRectWithPointsAndCenter(QMapPoint *points, NSUInteger count, QMapPoint centerPoint);
    
    /**
     *  @brief 返回最小外接 region.
     *
     *  @param coordinates 点数组
     *  @param count       点个数
     *
     *  @return 最小外接 region
     */
    extern QCoordinateRegion QBoundingCoordinateRegionWithCoordinates(CLLocationCoordinate2D *coordinates, NSUInteger count);
    
    /**
     *  @brief 根据中心点构建最小外接 region.
     *
     *  @param coordinates      点数组
     *  @param count            点个数
     *  @param centerCoordinate 中心点
     *
     *  @return 最小外接 region
     */
    extern QCoordinateRegion QBoundingCoordinateRegionWithCoordinatesAndCenter(CLLocationCoordinate2D *coordinates, NSUInteger count, CLLocationCoordinate2D centerCoordinate);
    
    /**
     *  @brief 返回全球范围外接平面投影矩形.
     *
     *  @return 全球范围外接平面投影矩形
     */
    extern QMapRect QWorldMapRect(void);
    
#ifdef __cplusplus
}
#endif
