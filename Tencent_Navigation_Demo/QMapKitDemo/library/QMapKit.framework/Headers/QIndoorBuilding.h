//
//  QIndoorBuilding.h
//  QMapKit
//
//  Created by tabsong on 2017/11/16.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QIndoorLevel.h"
#import "QGeometry.h"

/**
 * @brief  表示室内图的建筑物
 */
@interface QIndoorBuilding : NSObject

/**
 * @brief 唯一标识.
 */
@property (nonatomic, copy, readonly) NSString *guid;

/**
 * @brief  默认加载的楼层索引
 */
@property(nonatomic, assign, readonly) NSUInteger defaultLevelIndex;

/**
 * @brief  楼层数据
 */
@property(nonatomic, strong, readonly) NSArray<QIndoorLevel *> *levels;

/**
 * @brief  坐标. 目前无效，保留字段.
 */
@property (nonatomic, assign, readonly) QMapPoint centerPoint;

/**
 * @brief  楼的名称.
 */
@property (nonatomic, copy, readonly) NSString *name;

/**
 * @brief  楼的外接矩形.
 */
@property (nonatomic, assign, readonly) QMapRect boundingMapRect;

@end
