//
//  QMapView+Accessibility.h
//  QMapKit
//
//  Created by tabsong on 2018/9/5.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import <QMapKit/QMapKit.h>

/**
 *  @brief  MapView的无障碍功能
 */
@interface QMapView (Accessibility)

/**
 *  @brief  定位图标对应的无障碍label.
 */
@property (nonatomic, copy) NSString *userLocationAccessibilityLabel;

/**
 *  @brief  标注view的accessibilityFrame是否会包含其子view. 默认为YES
 */
@property (nonatomic, assign) BOOL annotationAccessibilityFrameClipToBounds;

@end
