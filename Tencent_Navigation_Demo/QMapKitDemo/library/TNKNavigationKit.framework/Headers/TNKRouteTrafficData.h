//
//  TNKRouteTrafficData.h
//  TNKNavigation
//
//  Created by 薛程 on 2018/5/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief 路线路况数据
 */
@interface TNKRouteTrafficData : NSObject

/**
* @brief 线路路况状态 0: 通畅 1:缓行 2:堵塞 3:未知路况 4:严重堵塞
*/
@property (nonatomic, assign) NSInteger color;

/**
 * @brief 线路距离
 */
@property (nonatomic, assign) NSInteger distance;

@end
