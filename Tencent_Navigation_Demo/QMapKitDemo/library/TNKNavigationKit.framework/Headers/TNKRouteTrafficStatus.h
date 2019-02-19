//
//  TNKRouteTrafficStatus.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/5/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TNKRouteTrafficData.h"

/**
 * @brief 路线路况状态类
 */
@interface TNKRouteTrafficStatus : NSObject

/**
 * @brief 剩余距离
 */
@property (nonatomic, assign) NSUInteger remainingDistance;

/**
 * @brief 总距离
 */
@property (nonatomic, assign) NSUInteger totalDistance;

/**
 * @brief 路况状态数组
 */
@property (nonatomic, strong) NSArray <TNKRouteTrafficData *> *trafficDataArray;

@end
