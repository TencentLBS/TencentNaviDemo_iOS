//
//  TNKNaviTrafficBarWidget.h
//  TNKNavigationKit
//
//  Created by mol on 2019/6/22.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TNKCarNaviManager.h"

NS_ASSUME_NONNULL_BEGIN


/**
 路况光柱图展示方向

 - TNKNaviTrafficBarWidgetOrientationVertical: 垂直展示，由下至上展示路况信息
 - TNKNaviTrafficBarWidgetOrientationHorizontal: 水平展示，由左至右展示路况信息
 */
typedef NS_ENUM(NSUInteger, TNKNaviTrafficBarWidgetOrientation)
{
    TNKNaviTrafficBarWidgetOrientationVertical = 0,
    TNKNaviTrafficBarWidgetOrientationHorizontal = 1,
};

/**
 *  @brief 路况光柱图
 */
@interface TNKNaviTrafficBarWidget : UIView<TNKCarNaviUIDelegate>

/// 视图展示方向，默认为TNKNaviTrafficBarWidgetOrientationVertical
@property(nonatomic, assign) TNKNaviTrafficBarWidgetOrientation orientation;

/// 边框颜色
@property (nonatomic, strong) UIColor *borderColor;
/// 边框宽度
@property (nonatomic, assign) CGFloat borderWidth;
/// 圆角半径
@property (nonatomic, assign) CGFloat cornerRadius;

/**
 * @breif 交通状态的颜色
 *  例如，@{@(TNKRouteTrafficDataStatusSmooth): [UIColor greenColor], @(TNKRouteTrafficDataStatusSlow) : [UIColor yellowColor]}
 */
@property (nonatomic, copy) NSDictionary<NSNumber *, UIColor *> *colorConfig;

/**
 * @breif 在导航开始之前可设置小车的图标以及大小
 *
 * @param icon 小车图标
 * @param size 小车的大小
 */
- (void)setCarIcon:(UIImage *)icon size:(CGSize)size;

@end

NS_ASSUME_NONNULL_END
