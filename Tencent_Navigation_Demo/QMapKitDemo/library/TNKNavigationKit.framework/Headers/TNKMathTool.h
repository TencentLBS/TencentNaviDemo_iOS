//
//  TNKMathTool.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/5/3.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface TNKMathTool : NSObject

// 计算两点直接的距离
+ (double)distanceBetweenCoordinate:(CLLocationCoordinate2D)coordinate1
                         coordinate:(CLLocationCoordinate2D)coordinate2;


@end
