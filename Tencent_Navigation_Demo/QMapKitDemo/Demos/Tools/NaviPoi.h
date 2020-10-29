//
//  NaviPoi.h
//  TNKNavigationDebugging
//
//  Created by xue on 2018/7/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface NaviPoi : NSObject

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@property (nonatomic, strong) NSString *uid;

@end
