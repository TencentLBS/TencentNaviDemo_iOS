//
//  TNKRouteTrafficData.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/5/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 交通状态

 - TNKRouteTrafficDataStatusPassed: 已走过的路
 - TNKRouteTrafficDataStatusSmooth: 通畅
 - TNKRouteTrafficDataStatusSlow: 缓行
 - TNKRouteTrafficDataStatusVerySlow: 堵塞
 - TNKRouteTrafficDataStatusUnkown: 未知路况
 - TNKRouteTrafficDataStatusJam: 严重堵塞
 */
typedef NS_ENUM(NSInteger, TNKRouteTrafficDataStatus)
{
    TNKRouteTrafficDataStatusPassed = -1,
    TNKRouteTrafficDataStatusSmooth = 0,
    TNKRouteTrafficDataStatusSlow = 1,
    TNKRouteTrafficDataStatusVerySlow = 2,
    TNKRouteTrafficDataStatusUnkown = 3,
    TNKRouteTrafficDataStatusJam = 4,
};

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief 路线路况数据.
 */
@interface TNKRouteTrafficData : NSObject

/**
 * @brief 该段路线距离
 */
@property (nonatomic, assign) NSInteger distance;

/**
 * @brief 该段路线起点在路线点串中的索引. 索引值从0开始, 若该段为偏航前行驶部分, 则索引值为-1. 绘制导航路况线时请将第一段剔除.
 */
@property (nonatomic, assign) NSInteger from;

/**
 * @brief 该段路线终点在路线点串中的索引. 若该段为偏航前行驶部分, 则索引值为0.
 */
@property (nonatomic, assign) NSInteger to;

/**
* @brief 该段路况状态 0:通畅 1:缓行 2:堵塞 3:未知路况 4:严重堵塞.
*/
@property (nonatomic, assign) TNKRouteTrafficDataStatus color;

@property (nonatomic) NSInteger speed;

// 获取导航SDK默认路况颜色
UIColor *TNKRouteTrafficStatusColor(TNKRouteTrafficDataStatus trafficDataStatus);

// 获取导航SDK伴随路线默认路况颜色
UIColor *TNKAccompanyRouteTrafficStatusColor(TNKRouteTrafficDataStatus trafficDataStatus);

@end

NS_ASSUME_NONNULL_END
