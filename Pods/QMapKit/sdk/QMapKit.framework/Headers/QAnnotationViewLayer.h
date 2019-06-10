//
//  QAnnotationViewLayer.h
//  QMapKit
//
//  Created by tabsong on 17/5/21.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

/**
 * @brief QAnnotationView的layer. 基于CALayer扩展了自定义能力
 */
@interface QAnnotationViewLayer : CALayer

/**
 *  @brief  坐标平移动画的keyPath, animatable
 *   x 表示 latitude
 *   y 表示 longitude
 */
@property (nonatomic, assign) CGPoint coordinate;

@end
