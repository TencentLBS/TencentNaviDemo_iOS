//
//  QPolylineView.h
//  QMapKit
//
//  Created by fan on 2017/5/17.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "QOverlayPathView.h"
#import "QPolyline.h"

/**
 * @brief 线覆盖物的显示级别，决定了与POI的压盖关系
 */
typedef NS_ENUM(NSInteger, QOverlayLevel) {
    QOverlayLevelAboveRoads = 0,    // 在道路之下POI之下
    QOverlayLevelAboveLabels        // 显示在所有POI之上
};

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
 * @brief 线覆盖物的显示级别，决定了与POI的压盖关系
 *
 * 默认在POI之上. 在添加之前可修改
 */
@property (nonatomic, assign) QOverlayLevel displayLevel;

/**
 * @brief 描边的宽度。 宽度为0时无描边(描边宽度请小于lineWidth的一半)
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
