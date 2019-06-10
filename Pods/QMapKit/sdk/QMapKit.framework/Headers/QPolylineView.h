//
//  QPolylineView.h
//  QMapKit
//
//  Created by fan on 2017/5/17.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "QOverlayPathView.h"
#import "QPolyline.h"

#pragma mark - QPolylineView

/**
 *  @brief 此类是QPolyline用于显示多段线的view
 */
@interface QPolylineView : QOverlayPathView

/**
 *  @brief  关联的QPolyline对象
 */
@property (nonatomic, readonly) QPolyline   *polyline;

/**
 *  @brief  根据指定的QPolyline生成一个多段线view
 *
 *  @param polyline 指定的QPolyline
 *
 *  @return 新生成的折线段view
 */
- (instancetype)initWithPolyline:(QPolyline *)polyline;

/**
 * @brief 描边的宽度。 单位：Point. 宽度为0时无描边(描边宽度请小于lineWidth的一半)
 */
@property(nonatomic, assign) CGFloat     borderWidth;

/**
 * @brief 描边的颜色。 宽度为0时无描边
 */
@property(nonatomic, strong) UIColor     *borderColor;

/**
 * @brief 实线和虚线的线长序列(元素个数必须是偶数)。默认为nil为实线
 */
@property (nonatomic, copy) NSArray<NSNumber *> *lineDashPattern;

@end
