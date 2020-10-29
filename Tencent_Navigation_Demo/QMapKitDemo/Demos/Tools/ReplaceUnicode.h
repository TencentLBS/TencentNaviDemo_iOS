//
//  ReplaceUnicode.h
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/4/27.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ReplaceUnicode : NSObject

// 改变unicode到中文
+ (NSString *)replaceUnicode:(NSString *)unicodeStr;

@end

NS_ASSUME_NONNULL_END
