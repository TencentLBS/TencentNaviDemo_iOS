//
//  QBasicMapViewLayer.h
//  QMapKit
//
//  Created by tabsong on 17/5/16.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "QGeometry.h"

/**
 * 中心点动画对应的key.
 */
extern NSString *const kQBasicMapViewLayerCenterCoordinateKey;

/**
 * 缩放级别动画对应的key.
 */
extern NSString *const kQBasicMapViewLayerZoomLevelKey;

/**
 * 旋转动画对应的key.
 */
extern NSString *const kQBasicMapViewLayerRotationKey;

/**
 * Overlooking动画对应的key.
 */
extern NSString *const kQBasicMapViewLayerOverlookingKey;


/**
 *  @brief  执行地图动画对应的layer.
 */
@interface QBasicMapViewLayer : CALayer

/**
 *  @brief  中心点, Animatable
 * x 表示 latitude
 * y 表示 longitude
 */
@property (nonatomic, assign) CGPoint centerCoordinate;

/**
 *  @brief  缩放级别, Animatable
 */
@property (nonatomic, assign) CGFloat zoomLevel;

/**
 *  @brief  旋转角度, Animatable
 */
@property (nonatomic, assign) CGFloat rotation;

/**
 *  @brief  overlooking, Animatable
 */
@property (nonatomic, assign) CGFloat overlooking;

@end
