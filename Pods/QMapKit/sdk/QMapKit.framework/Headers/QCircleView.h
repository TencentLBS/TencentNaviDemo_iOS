//
//  QCircleView.h
//  QMapKit
//
//  Created by fan on 2017/5/21.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QOverlayPathView.h"
#import "QCircle.h"

/**
 *  @brief  该类是QCircle用来显示圆的view
 *
 * 可以通过QOverlayPathView修改其fill和stroke相关属性来配置样式
 */
@interface QCircleView : QOverlayPathView

/**
 *  @brief  根据指定圆生成对应的view
 *
 *  @param circle 指定的QCircle对象
 *
 *  @return 生成的view
 */
- (id)initWithCircle:(QCircle *)circle;

/**
 *  @brief  关联的QCirlce对象
 */
@property (nonatomic, readonly) QCircle *circle;

@end
