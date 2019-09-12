//
//  QHeatTileOverlayView.h
//  QMapKit
//
//  Created by fan on 2019/6/6.
//  Copyright © 2019 tencent. All rights reserved.
//

#import "QTileOverlayView.h"
#import "QHeatTileOverlay.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief 用于热力图瓦片视图的类
 */
@interface QHeatTileOverlayView : QTileOverlayView

/**
 * @brief QHeatTileOverlayView的构造函数
 */
- (instancetype)initWithTileOverlay:(QHeatTileOverlay *)tileOverlay;

/**
 * @brief 本View对应的数据类
 */
@property (nonatomic, strong, readonly) QHeatTileOverlay *tileOverlay;

@end

NS_ASSUME_NONNULL_END
