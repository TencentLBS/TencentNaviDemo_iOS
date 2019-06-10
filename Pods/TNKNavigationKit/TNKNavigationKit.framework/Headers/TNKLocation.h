//
//  TNKLocation.h
//  TNKNavigationKit
//
//  Created by 薛程 on 2018/11/22.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 * @brief  导航的定位信息.
 */
@interface TNKLocation : NSObject

/**
 * @brief  导航的原始定位信息.
 */
@property (nonatomic, strong, nonnull) CLLocation *location;

/**
 * @brief  吸附到导航路线上的经纬度信息. 若未成功吸附到路线上会返回kCLLocationCoordinate2DInvalid.
 */
@property (nonatomic, assign) CLLocationCoordinate2D matchedCoordinate;

/**
 * @brief  吸附到导航路线上的角度信息. 若未成功吸附到路线上会返回-1.
 */
@property (nonatomic, assign) CLLocationDirection matchedCourse;

/**
 * @brief  吸附到导航路线上的位置索引. 若未成功吸附到路线上会返回-1.
 */
@property (nonatomic, assign) NSInteger matchedIndex;

@end
