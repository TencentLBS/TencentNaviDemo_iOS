//
//  QPolygon.h
//  QMapKit
//
//  Created by fan on 2017/5/19.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QMultiPoint.h"

/**
 * @brief  面覆盖物
 */
@interface QPolygon : QMultiPoint

/**
 * @brief  区域外接矩形. 此类用于定义一个由多个点组成的闭合多边形, 点与点之间按顺序尾部相连, 第一个点与最后一个点相连
 */
@property(nonatomic, readonly) QMapRect boundingMapRect;

/**
 *  @brief  根据经纬度坐标数据生成闭合多边形
 *
 *  @param coords 经纬度坐标点数据, coords对应的内存会拷贝, 调用者负责该内存的释放
 *  @param count  经纬度坐标点数组个数
 *
 *  @return 新生成的多边形
 */
+ (QPolygon *)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

/**
 *  @brief  根据mapPoint数据生成多边形
 *
 *  @param points mapPoint数据,points对应的内存会拷贝,调用者负责该内存的释放
 *  @param count  点的个数
 *
 *  @return 新生成的多边形
 */
+ (QPolygon *)polygonWithPoints:(QMapPoint *)points count:(NSUInteger)count;

/**
 *  @brief  根据经纬度坐标数据生成闭合多边形
 *
 *  @param coords 经纬度坐标点数据, coords对应的内存会拷贝, 调用者负责该内存的释放
 *  @param count  经纬度坐标点数组个数
 *
 *  @return 新生成的多边形
 */
-(id)initWithWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

/**
 *  @brief  根据mapPoint数据生成多边形
 *
 *  @param points mapPoint数据,points对应的内存会拷贝,调用者负责该内存的释放
 *  @param count  点的个数
 *
 *  @return 新生成的多边形
 */
- (id)initWithPoints:(QMapPoint *)points count:(NSUInteger)count;

@end
