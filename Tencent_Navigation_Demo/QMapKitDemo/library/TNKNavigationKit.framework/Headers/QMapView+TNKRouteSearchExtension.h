//
//  QMapView+TNKRouteSearchExtension.h
//  TNKNavigationKit
//
//  Created by mol on 2019/7/16.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <QMapKit/QMapKit.h>
#import "TNKCarRouteSearchTypes.h"

NS_ASSUME_NONNULL_BEGIN

@interface QMapView (TNKRouteSearchExtension)

/**
 根据路线调整地图的显示范围。使线路居中显示

 @param coordinates 路线点串数据
 @param edgeInsets 根据样式设置边缘
 @param animated 是否做过渡动画。
 */
- (void)fitsWithCoordinates:(NSArray<TNKCoordinatePoint *> *)coordinates edgeInsets:(UIEdgeInsets)edgeInsets animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
