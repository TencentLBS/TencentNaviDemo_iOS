//
//  QHeatTileNodeProtocol.h
//  QMapKit
//
//  Created by tabsong on 15/8/19.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 *  @brief 协议类。用于提供生成热力图时需要的数据
 */
@protocol QHeatTileNodeProtocol <NSObject>

@required

/**
 *  @brief  坐标.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/**
 *  @brief  热力值.
 */
@property (nonatomic, readonly) CGFloat value;

@end
