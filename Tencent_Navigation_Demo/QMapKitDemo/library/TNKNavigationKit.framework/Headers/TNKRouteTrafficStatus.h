//
//  TNKRouteTrafficStatus.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/5/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TNKRouteTrafficData.h"

NS_ASSUME_NONNULL_BEGIN

@class TNKCoordinatePoint;
/**
 * @brief 路线路况状态类
 */
@interface TNKRouteTrafficStatus : NSObject

/**
 * @brief 当前路线ID
 */
@property (nonatomic, copy) NSString *routeID;

/**
 * @brief 剩余距离，单位：米
 */
@property (nonatomic, assign) NSUInteger remainingDistance;

/**
 * @brief 总距离，单位：米
 */
@property (nonatomic, assign) NSUInteger totalDistance;

/**
 * @brief 路况状态数组. 路况元素按起点到终点顺序排列. 路况数组始终存储由起点到终点的路况信息, 若导航过程中发生过偏航, 则路况状态数组第一个元素由偏航前行驶的部分构成.
 */
@property (nonatomic, strong) NSArray <TNKRouteTrafficData *> *trafficDataArray;

/**
 * @brief 道路信息的坐标点串
 */
@property (nonatomic, strong) NSArray<TNKCoordinatePoint *> *coordinatePoints;

@end

NS_ASSUME_NONNULL_END
