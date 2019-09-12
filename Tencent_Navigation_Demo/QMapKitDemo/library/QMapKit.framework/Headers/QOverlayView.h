//
//  QOverlayView.h
//  QMapKit
//
//  Created by fan on 2017/5/17.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QTypes.h"
#import "QOverlay.h"

/**
 *  @brief  该类是地图覆盖物View的基类, 提供了绘制overlay的接口, 但是没有实际实现。希望不要直接实例化
 */
@interface QOverlayView : NSObject

/**
 * @brief 本view对应的数据类
 */
@property (nonatomic, readonly) id <QOverlay> overlay;

/**
 * @brief 覆盖物的显示级别，决定了与POI等其它地理元素的压盖关系
 *
 * 默认在POI之上(QOverlayLevelAboveLabels). 在添加之前可修改
 */
@property (nonatomic, assign) QOverlayLevel displayLevel;

/**
 * @brief 覆盖物的显示顺序，决定了它与其它QOverlayView的压盖关系. 默认为0.
 *
 * 大值压盖小值. 只有同displayLevel的QOverlayView才会比较zIndex
 */
@property (nonatomic, assign) int zIndex;

@end
