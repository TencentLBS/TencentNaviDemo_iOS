//
//  TNKCoordinatePoint.h
//  TNKNavigation
//
//  Created by fan on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

/**
 *  @brief 位置坐标
 */
@interface TNKCoordinatePoint : NSObject

/**
 * @brief 经纬度坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
