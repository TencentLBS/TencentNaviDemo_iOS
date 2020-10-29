//
//  SearchManager.h
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/4/27.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SearchManager : NSObject

// 缓存搜索的数组
+ (void)SearchText: (NSString *)seaTxt;
// 清楚缓存数组
+ (void)removeAllArray;

@end

NS_ASSUME_NONNULL_END
