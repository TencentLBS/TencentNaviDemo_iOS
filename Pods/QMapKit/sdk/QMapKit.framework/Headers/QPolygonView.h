//
//  QPolygonView.h
//  QMapKit
//
//  Created by fan on 2017/5/21.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QPolygon.h"
#import "QOverlayPathView.h"

/**
 *  @brief  此类是QPolygon的显示多边形View
 *
 * 可以通过QOverlayPathView修改其fill和stroke属性来配置样式
 */
@interface QPolygonView : QOverlayPathView

/**
 *  @brief  关联的QPolygon对象
 */
@property (nonatomic, readonly) QPolygon    *polygon;

/**
 *  @brief  根据指定的多边形生成一个多边形view
 *
 *  @param polygon 指定的多边形数据对象
 *
 *  @return 新生成的多边形view
 */
- (instancetype)initWithPolygon:(QPolygon *)polygon;

@end
