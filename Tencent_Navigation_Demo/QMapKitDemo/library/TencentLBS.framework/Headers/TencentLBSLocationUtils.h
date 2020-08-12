//
//  TencentLBSLocationUtils.h
//  TencentLBS
//
//  Created by mirantslu on 16/8/11.
//  Copyright © 2016年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class TencentLBSLocation;

NS_ASSUME_NONNULL_BEGIN

@interface TencentLBSLocationUtils : NSObject

+ (double)distanceBetweenTwoCoordinate2D:(const CLLocationCoordinate2D *)coordinate coordinateTwo:(const CLLocationCoordinate2D *)coordinate2;

+ (double)distanceBetweenTwoCLLocations:(const CLLocation *)location locationTwo:(const CLLocation *)location2;

+ (double)distanceBetweenTwoTencentLBSLocations:(const TencentLBSLocation *)location locationTwo:(const TencentLBSLocation *)location2;

// 参数add表示是否要包括台湾，YES为包括， NO不包括
+ (BOOL) isInRegionWithLatitude:(double)latitude longitude:(double)longitude addTaiwan:(BOOL)add;

+ (CLLocationCoordinate2D)WGS84TOGCJ02:(CLLocationCoordinate2D)coordinate;

@end

@interface TencentLBSServiceManager : NSObject

/**
 *  设置ID，如QQ号，微信号或是其他的登录账号，可用在发布前联调使用
 */
@property (atomic, copy) NSString *deviceID;

+ (instancetype)sharedInsance;

@end

NS_ASSUME_NONNULL_END
