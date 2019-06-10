//
//  QUserLocation.h
//  QMapKit
//
//  Created by tabsong on 17/5/23.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 *  @brief  定位信息类
 */
@interface QUserLocation : NSObject

/**
 *  @brief  位置信息.
 */
@property (readonly, nonatomic, strong) CLLocation *location;

/**
 *  @brief  heading信息.
 */
@property (readonly, nonatomic, strong) CLHeading *heading;

@end
