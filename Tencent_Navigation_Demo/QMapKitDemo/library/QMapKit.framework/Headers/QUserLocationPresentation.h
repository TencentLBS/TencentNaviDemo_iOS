//
//  QUserLocationPresentation.h
//  QMapKit
//
//  Created by tabsong on 2017/6/26.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * @brief 用户定位图标自定义样式类
 */
@interface QUserLocationPresentation : NSObject

/**
 * @brief 定位图标.
 */
@property (nonatomic, strong) UIImage *icon;

/**
 * @brief 定位圈的填充色.
 */
@property (nonatomic, strong) UIColor *circleFillColor;

@end
