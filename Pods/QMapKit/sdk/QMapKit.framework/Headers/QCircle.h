//
//  QCircle.h
//  QMapKit
//
//  Created by fan on 2017/5/19.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QShape.h"
#import "QOverlay.h"

/**
 * @brief  该类用于定义一个圆, 通常QCircle是QCircleView中持有的对象
 */
@interface QCircle : QShape <QOverlay>

/**
 * @brief 根据中心点和半径生成圆
 * @param coord 中心点的经纬度坐标
 * @param radius 半径，单位：米
 * @return 新生成的圆
 */
+ (QCircle *)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                 radius:(double)radius;

/**
 * @brief 根据指定的直角坐标矩形生成圆，半径由较长的那条边决定，radius = MAX(width, height)/2
 * @param mapRect 指定的直角坐标矩形
 * @return 新生成的圆
 */
+ (QCircle *)circleWithMapRect:(QMapRect)mapRect;

/**
 * @brief 根据中心点和半径生成圆
 * @param coord 中心点的经纬度坐标
 * @param radius 半径，单位：米
 * @return 新生成的圆
 */
-(id)initWithWithCenterCoordinate:(CLLocationCoordinate2D)coord radius:(double)radius;

/**
 * @brief  中心坐标
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/**
 * @brief  半径，单位：米
 */
@property (nonatomic, assign) double radius;

/**
 * @brief  该圆的外接矩形
 */
@property (nonatomic, readonly) QMapRect boundingMapRect;

@end
