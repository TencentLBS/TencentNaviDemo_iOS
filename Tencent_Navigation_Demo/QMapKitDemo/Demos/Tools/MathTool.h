//
//  MathTool.h
//  TNKNavigationDebugging
//
//  Created by xue on 2018/6/19.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QMapKit/QGeometry.h>
#import <TNKNavigationKit/TNKNavigationKit.h>
#import "DeviceUtils.h"

#define KISIphoneX  [DeviceUtils isIPhoneXSeries]

#define kHomeIndicatorHeight (KISIphoneX? 34 : 0)

#define kStatusBarHeight (KISIphoneX? 44 : 20)

#define kNavigationBarHeight (KISIphoneX? 88 : 64)


@interface MathTool : NSObject

+ (QMapRect)mapRectFitsPoints:(NSArray<TNKCoordinatePoint *>*)points;

@end
