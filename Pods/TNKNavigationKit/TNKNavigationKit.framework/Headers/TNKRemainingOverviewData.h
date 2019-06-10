//
//  TNKRemainingOverviewData.h
//  TNKNavigationKit
//
//  Created by 薛程 on 2018/9/3.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/**
 *  @brief 剩余全览模式所需数据
 */
@protocol TNKRemainingOverviewData <NSObject>

@required

/**
 *  @brief  经纬度位置坐标
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

@end
