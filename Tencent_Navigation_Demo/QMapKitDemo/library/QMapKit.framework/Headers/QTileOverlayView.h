//
//  QTileOverlayRender.h
//  QMapKit
//
//  Created by tabsong on 2017/6/27.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QTileOverlay.h"
#import "QOverlayView.h"

/**
 * @brief QTileOverlayView默认的zIndex值
 */
extern const int QTileOverlayDefaultZIndex;

/**
 * @brief 用于自定义瓦片视图的类
 */
@interface QTileOverlayView : QOverlayView

/**
 * @brief QTileOverlayView的构造函数
 */
- (instancetype)initWithTileOverlay:(QTileOverlay *)tileOverlay;

/**
 * @brief 本View对应的数据类
 */
@property (nonatomic, strong, readonly) QTileOverlay *tileOverlay;

/**
 * @brief 覆盖物的显示顺序，决定了它与其它QTileOverlayView的压盖关系. 默认为QTileOverlayDefaultZIndex.
 *
 * 大值压盖小值. 允许范围>=0. QTileOverlayView只会比较zIndex并忽略displayLevel.
 */
@property (nonatomic, assign) int zIndex;

/**
 * @brief 刷新渲染缓存（当改变配置项时需要调用本接口来刷新生效）
 */
- (void)reloadData;

@end
