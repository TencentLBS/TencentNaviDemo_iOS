//
//  QIndoorLevel.h
//  QMapKit
//
//  Created by tabsong on 2017/11/16.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief  表示室内图的楼层
 */
@interface QIndoorLevel : NSObject

/**
 * @brief  名称.
 */
@property(nonatomic, copy, readonly) NSString *name;

/**
 * @brief  名称简写. 目前无效，保留字段.
 */
@property(nonatomic, copy, readonly) NSString *shortName;

@end
