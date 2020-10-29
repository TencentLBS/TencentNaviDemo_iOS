//
//  SearchManager.m
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/4/27.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import "SearchManager.h"

@implementation SearchManager

// 缓存搜索数组
+ (void)SearchText: (NSString *)seaTxt
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSArray *myArray = [userDefaults arrayForKey:@"myArray"];
    if (myArray.count > 0) {
        
    }
    else
    {
        myArray = [NSArray array];
    }
    // nsarray --> nsmutablearray
    NSMutableArray *searTXT = [myArray mutableCopy];
    [searTXT addObject:seaTxt];
    if (searTXT.count > 20) {
        [searTXT removeObjectAtIndex:0];
    }
    
    // 将上述数据全部存储到nsuserdefaults
    [userDefaults setObject:searTXT forKey:@"myArray"];
    [userDefaults synchronize];
    
    
}

//删除缓存数组
+ (void)removeAllArray
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults removeObjectForKey:@"myArray"];
    [userDefaults synchronize];
}


@end
