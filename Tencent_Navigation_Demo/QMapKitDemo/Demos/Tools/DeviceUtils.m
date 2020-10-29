//
//  DeviceUtils.m
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/10/29.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import "DeviceUtils.h"

@implementation DeviceUtils

/**
 *  @brief  是否是iPhoneX系列
 */
+ (BOOL)isIPhoneXSeries {
    
    return [DeviceUtils hasTopNotch];
}

// 是否有刘海儿
+ (BOOL)hasTopNotch {
    
    BOOL hasTopNotch = NO;
    
    if([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        switch ((int)[[UIScreen mainScreen] nativeBounds].size.height) {
            case 1136:
                //printf("iPhone 5 or 5S or 5C");
                
                break;
                
            case 1334:
                //printf("iPhone 6/6S/7/8");
                break;
                
            case 1920:
            case 2208:
                //printf("iPhone 6+/6S+/7+/8+");
                break;
                
            case 2436:
                //print("iPhone X/XS/11 Pro");
                hasTopNotch = YES;
                break;
                
            case 2688:
                //print("iPhone XS Max/11 Pro Max");
                hasTopNotch = YES;
                break;
                
            case 1792:
                //print("iPhone XR/ 11 ");
                hasTopNotch = YES;
                break;
            
            case 2340:
                //print("iPhone 12 mini")
                hasTopNotch = YES;
                break;
            
            case 2532:
                //print("iPhone 12 / 12 Pro")
                hasTopNotch = YES;
                break;
                
            case 2778:
                //print("iPhone 12 Pro Max")
                hasTopNotch = YES;
                break;
                
            default:
                //printf("Unknown");
                hasTopNotch = NO;
                break;
        }
    }
    
    return hasTopNotch;
}


@end
