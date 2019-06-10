//
//  BaseNaviViewController.h
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/6.
//  Copyright © 2018年 tencent. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLHeading.h>
#import <TNKNavigationKit/TNKNavigationKit.h>
#import <TNKNavigationKit/TNKLocationEntryProtocol.h>
#import <QMapKit/QMapKit.h>

@interface BaseNaviViewController : UIViewController <TNKCarNaviDelegate, TNKCarNaviViewDelegate, TNKLocationEntryDelegate, QMapViewDelegate>

@property (nonatomic, strong, readonly) TNKCarNaviView *naviView;
@property (nonatomic, strong, readonly) TNKCarNaviManager *carManager;

-(void)setupSDK;

@end
