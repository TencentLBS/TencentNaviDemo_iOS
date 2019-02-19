//
//  QOverlay.h
//  QMapKit
//
//  Created by fan on 2017/5/17.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QGeometry.h"

/**
 * @brief QOverlay:地图覆盖物的基类，所有地图的覆盖物需要继承自此类
 */
@protocol QOverlay <NSObject>

@optional

/**
 * @brief  区域外接矩形
 */
@property(nonatomic, readonly) QMapRect boundingMapRect;

@end
